# Research on the usage of USEPLATFORMTICK

[Discord server where I do research](https://discord.gg/YdYVSBbZWY)

## 1. Initial Discovery and String Analysis

The only usage of USEPLATFORMTICK in the entire system was found by dumping all strings of system32 using [strings2.exe](https://github.com/glmcdona/strings2) and searching for USEPLATFORMTICK. No other code uses `USEPLATFORMTICK` besides ntoskrnl.exe and ntkrla57.exe.

```c
if ( strstr(v3, "USEPLATFORMTICK") )          // if bcdedit /set USEPLATFORMTICK yes
  HalpTimerPlatformClockSourceForced = 1;     // then we set HalpTimerPlatformClockSourceForced = 1, now we can look for references for HalpTimerPlatformClockSourceForced
```

## 2. Cross-Reference Analysis

The only cross-references to `HalpTimerPlatformClockSourceForced` are found in the function `HalpTimerFindIdealClockSource`.

We can use IDA plugins to analyze references to `HalpTimerFindIdealClockSource`:

```py
Python>import export_clean_xrefs
Python>import export_each_func
Python>export_clean_xrefs.export_xrefs_pseudocode('HalpTimerFindIdealClockSource', max_depth=10)
Python>export_each_func.export_xrefs_pseudocode('HalpTimerFindIdealClockSource', max_depth=10)
```

## 3. Control Flow Analysis

In `HalpTimerFindIdealClockSource` (link the file here), we can analyze the control flow:

If either `HalpHvCpuManager` or `HalpHvPresent` are both false, then we jump to LABEL_7, where we then try to find this timer `Timer = (__int64)HalpFindTimer(11, 0x220, 0, 0x50, 0);`, whatever it might be. Then as it finds a suitable timer, it then jumps to LABEL_26, assigns `v4 = *(_DWORD *)(Timer + 0xE0);` if then `(v4 & 0x50) != 0` then we `return Timer & -(__int64)((v4 & 0x20) != 0);`, I do not know what the second part is yet (`-(__int64)((v4 & 0x20) != 0)`).

### 3.1 Timer Assignment Flow

Now we can connect to our local kernel debugger and take a look at `HalpClockTimer` as that is essentially the same as the Timer we find in `HalpTimerFindIdealClockSource`.

```c
IdealClockSource = HalpTimerFindIdealClockSource();     // The Timer we get from HalpTimerFindIdealClockSource()
v6 = IdealClockSource;                                  // the timer we found gets assigned to v6
if ( !IdealClockSource )
{
  HalpTimerLastProblem = 20;
  return 0xC0000001;
}
if ( (int)HalpTimerInitialize(IdealClockSource) >= 0 )
{
  *(_DWORD *)(v6 + 184) |= 4u;
  HalpClockTimer = v6;                                  // HalpClockTimer is now set to the timer we found
  goto LABEL_11;
}
```

## 4. Runtime Investigation with WinDbg

### 4.1 Verifying USEPLATFORMTICK Status

I currently have useplatformtick set to yes, as we can inspect through windbg.

It can be seen with in windbg
```
lkd> db HalpTimerPlatformClockSourceForced l1
fffff803`eadc2558  01    
```
or it can be seen through the terminal with `bcdedit /enum {current}`
```
C:\Windows\System32>bcdedit /enum {current}

Windows Boot Loader
-------------------
...
debug                   Yes
useplatformtick         Yes
...
```

### 4.2 Clock Timer Structure Analysis

Now let's examine `HalpClockTimer` through WinDbg:
```
lkd> dq HalpClockTimer l1
fffff803`eadc2550  fffff7e0`80016000
```

After examining the local types in IDA, I found it has the structure of `_HAL_CLOCK_TIMER_CONFIGURATION`:

```
lkd> dt _HAL_CLOCK_TIMER_CONFIGURATION fffff7e0`80016000
nt!_HAL_CLOCK_TIMER_CONFIGURATION
   +0x000 Flags            : 0x80 ''
   +0x000 AlwaysOnTimer    : 0y0
   +0x000 HighLatency      : 0y0
   +0x000 PerCpuTimer      : 0y0
   +0x000 DynamicTickSupported : 0y0
   +0x004 KnownType        : 0xfffff803
   +0x008 Capabilities     : 0x80013be0
   +0x010 MaxIncrement     : 0x2710
   +0x018 MinIncrement     : 0
```

### 4.3 Timer Resolution Impact

By changing the system's timer resolution we can see that `MaxIncrement` changes from `0x2710` to `0x1388`. These values are stored in 100‑ns units, so `0x2710` equals **1 ms** and `0x1388` equals **0.5 ms**:
```
lkd> dt _HAL_CLOCK_TIMER_CONFIGURATION fffff7e0`80016000
nt!_HAL_CLOCK_TIMER_CONFIGURATION
   +0x000 Flags            : 0x80 ''
   +0x000 AlwaysOnTimer    : 0y0
   +0x000 HighLatency      : 0y0
   +0x000 PerCpuTimer      : 0y0
   +0x000 DynamicTickSupported : 0y0
   +0x004 KnownType        : 0xfffff803
   +0x008 Capabilities     : 0x80013be0
   +0x010 MaxIncrement     : 0x1388
   +0x018 MinIncrement     : 0
```

## 5. Capability Flag Analysis

### 5.1 Extracting Timer Capability Data

Now let's get the memory address of `Timer + 0xE0` and dump it to see the value of `v4`:
```
lkd> dd fffff7e0`80016000+0xE0 L1
fffff7e0`800160e0  00210131
```

### 5.2 Decoding the Capability Check Logic

Now let's return to the previous code:
```c
v4 = *(_DWORD *)(Timer + 0xE0);  // v4 = 0x00210131
if ( (v4 & 0x50) != 0 )
    return Timer & -(__int64)((v4 & 0x20) != 0);
```

We evaluate the expression using WinDbg:
```
lkd> ? poi(fffff7e0`80016000+0xE0) & 0x50
Evaluate expression: 16 = 00000000`00000010
```

### 5.3 Understanding the Masking Operation

The value evaluates to non-zero, so we continue to the next part:
```c
return Timer & -(__int64)((v4 & 0x20) != 0);
```

We evaluate the expression:
```
lkd> ? poi(fffff7e0`80016000+0xE0) & 0x20
Evaluate expression: 32 = 00000000`00000020
lkd> ? (poi(fffff7e0`80016000+0xE0) & 0x20) != 0
Evaluate expression: 1 = 00000000`00000001
lkd> ? -((poi(fffff7e0`80016000+0xE0) & 0x20) != 0)
Evaluate expression: -1 = ffffffff`ffffffff
```

So it ends up becoming:
```c
return Timer & -(__int64)((v4 & 0x20) != 0);
// Becomes:
return Timer & 0xFFFFFFFFFFFFFFFF;
// Which is just:
return Timer;  // The original timer pointer unchanged
```
If bit 0x20 was clear, it would become:
```c
return Timer & 0x0000000000000000;
// Which is:
return 0;  // NULL pointer
```
## 6. HalpFindTimer Function Analysis

### 6.1 Function Parameter Investigation

Maybe we can dig deeper into what HalpFindTimer does?
I will make some assumptions as to what each argument in `HalpFindTimer` does:
```c
ULONG_PTR *__fastcall HalpFindTimer(int a1, int a2, int a3, int a4, char a5)
a1 = Timer type/ID
```

### 6.2 Timer Type Identification Method

How do we determine what timer type/ID we are currently using?
We can examine this code:
```c
&& (!a1 || a1 == *((_DWORD *)v11 + 57))
```
`v11` is the timer pointer and `*((_DWORD *)v11 + 57)` means DWORD at offset `57*4 = 0xE4` bytes, which gives us the offset for timers we can examine to see their type.

## 7. System Timer Enumeration

### 7.1 Registered Timer Overview


Here we get more information about the timers for our system:
```
lkd> dd HalpRegisteredTimerCount l1
fffff803`eadc259c  00000008
lkd> dq HalpRegisteredTimers l4
fffff803`eadc2580  fffff7e0`80001000 fffff7e0`80016000
fffff803`eadc2590  fffff7e0`80013be0 00000008`00000001
```

### 7.2 Timer Type Identification


We can see that the the 2nd entry mathes our `HalpClockTimer` (`fffff7e080016000`), lets now take a look at these 3 different timers:
```
lkd> dd fffff7e0`80001000+0xE4 l1
fffff7e0`800010e4  00000005
lkd> dd fffff7e0`80016000+0xE4 l1
fffff7e0`800160e4  0000000c
lkd> dd fffff7e0`80013be0+0xE4 l1
fffff7e0`80013cc4  0000000f
```
We can see that the first timer has type `5`, the second timer has type `12`, and the third timer has type `15`. The one we are using is type `12`.

Timer type 5 appears to be TSC, as it seems to be used everywhere for TSC functionality.

Let's examine this from `HalpTimerSaveProcessorFrequency`:

```c
result = HalpFindTimer(7, 0, 0, 0, 1);
if ( result )
{
  result = (ULONG_PTR *)(10000 * (unsigned int)((result[24] + 5000) / 0x2710));
  Pcr->HalReserved[3] = (unsigned int)result;
}
return result;
```

From the `HalpFindTimer` code, `result[24]` refers to offset `+0xC0` (24 * 8 = 192 decimal = 0xC0 hex).

Let's test this in WinDbg:
```
lkd> ? poi (fffff7e0`80001000+0xC0)
Evaluate expression: 3187201731 = 00000000`bdf8d6c3
lkd> ? poi (fffff7e0`80016000+0xC0)
Evaluate expression: 10000000 = 00000000`00989680
lkd> ? poi (fffff7e0`80013be0+0xC0)
Evaluate expression: 38400006 = 00000000`0249f006
```
The first timer with type 5 appears to be the TSC timer, as it has a value of `3187201731`, which is the TSC frequency in Hz. For quick demonstration, we can see it has 3187 MHz, which is essentially the same frequency. You can also refer to [my other repo](https://github.com/eskezje/time) for more details:
```
lkd> !cpuinfo
CP  F/M/S Manufacturer  MHz PRCB Signature    MSR 8B Signature Features ArchitectureClass
 0  6,183,1 GenuineIntel 3187 0000012f00000000 >0000012f00000000<351b3fff 0
```
So now we know that timer type 5 is TSC. What about timer types 12 and 15?

If we look at the HPET specifications, we can see that it has a frequency of 10 MHz, which matches what we see in `HalpClockTimer`.

If we examine the HPET registers, the main counter period is roughly `52 ns`, which corresponds to about `19.2 MHz`.  The `10 MHz` value reported in `HalpClockTimer` comes from VPPT's fixed virtual interface, not the physical HPET clock.

And as for timer type 15, it is the ART timer, we can find the frequency of that by using:
Refer to this for [CPUID](https://www.felixcloutier.com/x86/cpuid)
```c
#include <intrin.h>
#include <stdio.h>

int main() {
    int info[4];
    __cpuid(info, 0x15);
    printf("Core crystal freq from CPUID.15: %llu Hz\n", (unsigned long long)info[2]);
    return 0;
}
```
And here we can see me running it:
```
C:\Users\eske\Desktop\apic>cpuID.exe
Core crystal freq from CPUID.15: 38400000 Hz
```
Which is essentially the same as what we saw for:
```
lkd> ? poi (fffff7e0`80013be0+0xC0)
Evaluate expression: 38400006 = 00000000`0249f006
```

A quick short breakdown of what the `38400000` means, it is the processor’s nominal core‐crystal clock frequency in hertz:
That means that TSC is driven off this crystal, and multiplied by a small integer ratio (EBX/EAX) that  the CPU advertises in the same CPUID leaf. (see the file in the repo)
```bat
C:\Users\eske\Desktop\apic>cpuID.exe
EAX (denominator)       : 2
EBX (numerator)         : 166
ECX (core crystal clock): 38400000 Hz
=> Computed TSC freq    : 3187200000 Hz
```
tsc freq = `(core crystal clock * EBX) / EAX`


## 7.3 Being smarter by looking at HalpTimerTraceTimingHardware
We could also look at the HalpTimerTraceTimingHardware function to see all the different timers/counters there are, and look at their adresses.
```
HalpClockTimer
HalpPerformanceCounter
HalpAlwaysOnTimer
HalpVpptPhysicalTimer
HalpAlwaysOnCounter
HalpWatchdogTimer
HalpAuxiliaryCounter
HalpStallCounter
```
Now lets look at them in windbg:
```
lkd> dq HalpClockTimer l1; dd poi(HalpClockTimer)+0xE4 l1
fffff803`eadc2550  fffff7e0`80016000
fffff7e0`800160e4  0000000c      // Timer type 12 VPPT

lkd> dq HalpPerformanceCounter l1; dd poi(HalpPerformanceCounter)+0xE4 l1
fffff803`eadc2430  fffff7e0`80001000
fffff7e0`800010e4  00000005      // Timer type 5 TSC 

lkd> dq HalpAlwaysOnTimer l1; dd poi(HalpAlwaysOnTimer)+0xE4 l1
fffff803`eadc2568  00000000`00000000
00000000`000000e4  ????????

lkd> dq HalpVpptPhysicalTimer l1; dd poi(HalpVpptPhysicalTimer)+0xE4 l1
fffff803`eadc0760  fffff7e0`80013460
fffff7e0`80013544  00000003     // Timer type 3 HPET

lkd> dq HalpAlwaysOnCounter l1; dd poi(HalpAlwaysOnCounter)+0xE4 l1
fffff803`eadc25a0  fffff7e0`80013be0
fffff7e0`80013cc4  0000000f     // Timer type 15 ART

lkd> dq HalpWatchdogTimer l1; dd poi(HalpWatchdogTimer)+0xE4 l1
fffff803`eadc2488  00000000`00000000
00000000`000000e4  ????????

lkd> dq HalpAuxiliaryCounter l1; dd poi(HalpAuxiliaryCounter)+0xE4 l1
fffff803`eadc2590  fffff7e0`80013be0
fffff7e0`80013cc4  0000000f    // Timer type 15 ART

lkd> dq HalpStallCounter l1; dd poi(HalpStallCounter)+0xE4 l1
fffff803`eadc2560  fffff7e0`80001000
fffff7e0`800010e4  00000005   // Timer type 5 TSC
```
So it turns out that what i had previosuly thought was LAPIC, was actually intel ART instead, which refers to [\[v7,6/8\] x86: tsc: Always Running Timer (ART) correlated clocksource](https://patchwork.ozlabs.org/project/intel-wired-lan/patch/1455308729-6280-7-git-send-email-christopher.s.hall@intel.com/)

I noticed this by looking at this
```c
      v13 = HalpAuxiliaryCounter;
      PerformanceFrequency.QuadPart = 0LL;
      if ( HalpAuxiliaryCounter )
      {
        if ( HalpTimerAuxiliaryClockEnabled )
        {
          if ( (*(_DWORD *)(HalpAuxiliaryCounter + 0xE0) & 0x6000) != 0 )
          {
            v13 = 0LL;
            HalpAuxiliaryCounter = 0LL;
```

and looking at this `HalpArtDiscover()`, as we can see that sets the `HalpTimerAuxiliaryClockEnabled = 1`, which makde me believe that the intel ART was responsible for that timer:
```c
RtlInitUnicodeString(
  &DestinationString,
  L"VEN_vvvv&DEV_dddd&SUBVEN_ssss&SUBDEV_yyyy&REV_rrrr&INST_iiii&UID_uuuuuuuu");
HalpTimerRegister((__int64)v3, &DestinationString, v0);
HalpTimerAuxiliaryClockEnabled = 1;
```
In the end it ended up responding to the same thing as I showed in the beginning, which is the CPUID.15, which is the ART timer, as the ART post says: "On systems that support ART a new CPUID leaf (0x15) returns parameters
“m” and “n” such that: TSC_value = (ART_value * m) / n + k [n >= 2]"

which kind of exactly was the same as as we already explored with this
```bat
C:\Users\eske\Desktop\apic>cpuID.exe
EAX (denominator)       : 2
EBX (numerator)         : 166
ECX (core crystal clock): 38400000 Hz
=> Computed TSC freq    : 3187200000 Hz
```
tsc freq = `(core crystal clock * EBX) / EAX`

## 8. Investigating frequency of HPET (will be useful later)

```
[63 … 32] = Main Counter Period, in femtoseconds
[31 …  0] = Capability bits (vendor ID, # timers, 64-bit support, etc.)
```
We can get our HPET physical address by using the symbol `HalpHpetPhysicalAddress`, but thats not the one we want, we want the HPET base address(virual address), which is `HalpHpetBaseAddress`.
```
lkd> dq HalpHpetBaseAddress l1
fffff803`ead8e000  fffff7e0`80014000
```

Now we can dum the memory at that adress:
```
lkd> dq fffff7e0`80014000 l1
fffff7e0`80014000  031aba85`8086a701
```
So the upper 32 bits are `0x031aba85` and the lower 32 bits are `0x8086a701`, which is the vendor ID, which is Intel, and the lower 32 bits are the capability bits.

`0x031aba85` in decimal is `52083333` in femtoseconds, In seconds that would be equivilent to `52083333*1e-15s = 52.083333ns`

We can now get the frequency of my HPET:
`Frequency(Hz)=1000000000000000/52083333=19200000.1229`



## 9. VPPT (Virtual Processor Performance Timer) Discovery

### 9.1 investigating HalpTimerRegister

If we take a look at `HalpTimerRegister`, we can see multiple things getting saved in the pointers:

```c
*(_QWORD *)(v13 + 0xC0) = *(_QWORD *)(a1 + 0x68);    // Copy frequency from offset 0x68
*(_OWORD *)(v13 + 0x68) = *(_OWORD *)(a1 + 8);       // Copy function pointers from offset 8-24
*(_OWORD *)(v13 + 0x78) = *(_OWORD *)(a1 + 0x18);    // Copy more function pointers
*(_OWORD *)(v13 + 0x88) = *(_OWORD *)(a1 + 0x28);    // Copy more function pointers  
*(_OWORD *)(v13 + 0x98) = *(_OWORD *)(a1 + 0x38);    // Copy more function pointers
```

### 9.2 Timer Type 12 Analysis

From our analysis, we discovered that timer type 12 is a VPPT:

```
lkd> dq fffff7e0`80016000+0x68 l4
fffff7e0`80016068  fffff803`ea302380 00000000`00000000
fffff7e0`80016078  fffff803`ea132e50 fffff803`ea302240

lkd> u fffff803`ea302380 l1
nt!HalpVpptInitialize:
fffff803`ea302380 837910ff        cmp     dword ptr [rcx+10h],0FFFFFFFFh
lkd> u fffff803`ea132e50 l1
nt!HalpVpptAcknowledgeInterrupt:
fffff803`ea132e50 48895c2410      mov     qword ptr [rsp+10h],rbx
lkd> u fffff803`ea302240 l1
nt!HalpVpptArmTimer:
fffff803`ea302240 48895c2410      mov     qword ptr [rsp+10h],rbx
```

We can also see it in this function `HalpTimerInitializeVpptClockTimer`, if timertype is 12, then we initialize `HalpVpptInitializePhysicalTimer()` which shows that it is a Vppt Timer.
```c
__int64 HalpTimerInitializeVpptClockTimer()
{
  __int64 result; // rax

  result = HalpClockTimer;
  if ( *(_DWORD *)(HalpClockTimer + 0xE4) == 12 )
    return HalpVpptInitializePhysicalTimer();
  return result;
}
```

### 9.3 VPPT Registration Process

The VPPT timer registration occurs in `HalpTimerSelectRoles` when certain conditions are met:

```c
v14 = HalpClockTimer;  // Original timer from HalpTimerFindIdealClockSource
if ( (*(_DWORD *)(HalpClockTimer + 0xE0) & 1) == 0 )  // Timer lacks VPPT support
{
    if ( (int)HalpVpptTimerRegister(HalpClockTimer, 0LL) < 0 )
    {
        HalpClockTimer = 0LL;  // Registration failed
    }
    else
    {
        v15 = HalpFindTimer(12, 32, 0, 3840, 0);  // Create VPPT wrapper (type 12)
        HalpClockTimer = (ULONG_PTR)v15;          // Replace original with VPPT
    }
}
```

### 9.4 Looking closer at HalpVpptTimerRegister

```c
__int64 __fastcall HalpVpptTimerRegister(_DWORD *a1, char a2)
{    
    // Store reference to the physical timer being virtualized
    HalpVpptPhysicalTimerTarget = -1;
    *(_QWORD *)&HalpVpptPhysicalTimer = a1;  // Store original HPET timer
    
    // Initialize VPPT infrastructure
    ExtEnvInitializeSpinLock(&HalpVpptLock);
    qword_140FC0718 = (__int64)&HalpVpptQueue;
    *(_QWORD *)&HalpVpptQueue = &HalpVpptQueue;
    
    // Create new timer registration structure for VPPT
    memset_0(v7, 0, 0x90uLL);
    v8 = HalpVpptInitialize;           // VPPT initialization function
    v9 = HalpVpptAcknowledgeInterrupt; // VPPT interrupt handler
    v10 = HalpVpptArmTimer;            // VPPT timer arming function
    v11 = HalpVpptStop;                // VPPT stop function
    
    v21 = 12;                          // Timer type 12 (VPPT)
    v15 = 10000000LL;                  // Fixed 10 MHz frequency
    v16 = v4 | v5 | 0x210031;          // VPPT capability flags
    
    // Register the new VPPT timer
    return HalpTimerRegister((__int64)v7, 0LL, v6);
}
```


### 9.5 VPPT Physical Timer Relationship

VPPT virtualizes an underlying platform timer:

```
lkd> dd HalpVpptRegistered l1
fffff803`eadc0720  00000001                    // VPPT is active

lkd> dq HalpVpptPhysicalTimer l1
fffff803`eadc0760  fffff7e0`80013460           // Points to original HPET timer

lkd> dd fffff7e0`80013460+0xE4 l1
fffff7e0`80013544  00000003                    // Timer type 3 = HPET

lkd> ? poi (fffff7e0`80013460+0xC0)
Evaluate expression: 19200000 = 00000000`0124f800   // 19.2 MHz (actual HPET frequency)
```

## 10. The Complete USEPLATFORMTICK + VPPT Architecture

Based on our definitive reverse engineering findings, here's exactly how USEPLATFORMTICK works:

### 10.1 The Timer Selection and VPPT Registration Flow

**Step 1: Initial Platform Timer Discovery**
```c
// In HalpTimerFindIdealClockSource
if ( HalpTimerPlatformClockSourceForced )  // Set by USEPLATFORMTICK=yes
    goto LABEL_7;
```
- USEPLATFORMTICK forces selection of platform hardware timers (HPET, PM Timer, APIC)
- Skips synthetic/hypervisor timer sources

**Step 2: VPPT Eligibility Check**
```c
// In HalpTimerSelectRoles
v14 = HalpClockTimer;  // Original HPET timer (type 3, 19.2 MHz)
if ( (*(_DWORD *)(HalpClockTimer + 224) & 1) == 0 )  // Timer lacks VPPT support bit
```
- Checks if the selected platform timer can be virtualized by VPPT
- Bit 0x1 at offset +0xE0 indicates existing VPPT support

**Step 3: VPPT Registration and Timer Replacement**
```c
if ( (int)HalpVpptTimerRegister(HalpClockTimer, 0LL) < 0 )
{
    HalpClockTimer = 0LL;  // Registration failed
}
else
{
    v15 = HalpFindTimer(12, 32, 0, 3840, 0);  // Create VPPT wrapper
    HalpClockTimer = (ULONG_PTR)v15;          // REPLACE with type 12 VPPT
}
```

### 10.2 VPPT Internal Architecture

**Physical Timer Storage**
```c
// In HalpVpptTimerRegister
*(_QWORD *)&HalpVpptPhysicalTimer = a1;  // Store original HPET timer
```

**VPPT Timer Creation**
```c
v21 = 12;                          // Timer type 12 (VPPT)
v15 = 10000000LL;                  // Fixed 10 MHz frequency
v8 = HalpVpptInitialize;           // VPPT function pointers
v9 = HalpVpptAcknowledgeInterrupt;
v10 = HalpVpptArmTimer;
v11 = HalpVpptStop;
```

### 10.3 Verified Memory Layout

**From WinDbg Analysis:**
```
HalpClockTimer        -> fffff7e0`80016000  // VPPT interface (type 12, 10 MHz)
HalpVpptPhysicalTimer -> fffff7e0`80013460  // Original HPET (type 3, 19.2 MHz)

lkd> dd fffff7e0`80016000+0xE4 l1
fffff7e0`800160e4  0000000c              // Timer type 12 (VPPT)

lkd> dd fffff7e0`80013460+0xE4 l1
fffff7e0`80013544  00000003              // Timer type 3 (HPET)

lkd> ? poi (fffff7e0`80016000+0xC0)
Evaluate expression: 10000000 = 00000000`00989680   // 10 MHz VPPT interface

lkd> ? poi (fffff7e0`80013460+0xC0)
Evaluate expression: 19200000 = 00000000`0124f800   // 19.2 MHz HPET hardware
```

### 10.4 VPPT Operation Model

**Timer Queue Management**
```c
// From HalpVpptArmTimer
InterruptTimePrecise = RtlGetInterruptTimePrecise(&v16);
a1[4] = InterruptTimePrecise + a3;  // Store absolute deadline

// Insert into priority queue sorted by deadline
for ( i = *(int **)&HalpVpptQueue; i != &HalpVpptQueue; i = *(int **)i )
{
  if ( (unsigned __int64)(InterruptTimePrecise + a3) < *((_QWORD *)i + 4) )
    break;  // Found insertion point
}
```

**Physical Timer Programming**
```c
// From HalpVpptUpdatePhysicalTimer
v1 = *(_DWORD *)(*(_QWORD *)&HalpVpptQueue + 0x10LL);  // Target processor
v2 = *(_QWORD *)(*(_QWORD *)&HalpVpptQueue + 0x20LL);  // Earliest deadline

// Program physical HPET for earliest deadline
result = HalpSetTimerAnyMode(*(_QWORD *)&HalpVpptPhysicalTimer, v5, v4, &v12);
```

**Interrupt Processing**
```c
// From HalpVpptAcknowledgeInterrupt
InternalData = HalpTimerGetInternalData(*(__int64 *)&HalpVpptPhysicalTimer);
guard_dispatch_icall_no_overrides(InternalData);  // Acknowledge HPET interrupt

// Process expired timers and reschedule
HalpVpptUpdatePhysicalTimer();
```

### 10.5 Frequency Translation Layer

**VPPT provides frequency standardization:**
- **Application Interface**: 10 MHz (standardized virtual frequency)
- **Hardware Reality**: 19.2 MHz (actual HPET frequency from period calculation)
- **Conversion**: VPPT handles all frequency translations internally

### 10.6 The Complete Answer

**USEPLATFORMTICK + VPPT achieves:**

1. **Platform Timer Compliance**: Uses actual hardware timers (HPET) as required
2. **Virtualization Benefits**: VPPT provides timer multiplexing and standardized interface
3. **Frequency Standardization**: 10 MHz virtual interface regardless of hardware frequency
4. **Performance Optimization**: Single physical timer serves multiple virtual timers
5. **Hypervisor Compatibility**: VPPT is designed to work with virtualized environments

**Final Architecture:**
```
Windows Kernel
    ↓ (10 MHz interface)
Timer Type 12 (VPPT)
    ↓ (queue management, frequency conversion)
Timer Type 3 (HPET Hardware - 19.2 MHz)
    ↓
Physical HPET Chip
```