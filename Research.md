# Research on the useage of USEPLATFORMTICK

## 1. Initial Discovery and String Analysis

Only usage of USEPLATFORMTICK in all of the system, done by dumping all strings of system32 use [strings2.exe](https://github.com/glmcdona/strings2) and finding USEPLATFORMTICK, no other code uses `USEPLATFORMTICK` besides ntoskrnl.exe, and ntkrla57.exe

```c
      if ( strstr(v3, "USEPLATFORMTICK") )          // if bcdedit /set USEPLATFORMTICK yes
        HalpTimerPlatformClockSourceForced = 1;     // then we set HalpTimerPlatformClockSourceForced = 1, now we can look for references for HalpTimerPlatformClockSourceForced
```

## 2. Cross-Reference Analysis

The only xreferences to `HalpTimerPlatformClockSourceForced` is the function called `HalpTimerFindIdealClockSource`.

Now we can use the IDA plugins to look at references to `HalpTimerFindIdealClockSource`.

```py
Python>import export_clean_xrefs
Python>import export_each_func
Python>export_clean_xrefs.export_xrefs_pseudocode('HalpTimerFindIdealClockSource', max_depth=10)
Python>export_each_func.export_xrefs_pseudocode('HalpTimerFindIdealClockSource', max_depth=10)
```

## 3. Control Flow Analysis

In `HalpTimerFindIdealClockSource`(link the file here) we can now look at the control flow and see that.

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

Now we look at `HalpClockTimer` through windbg:
```
lkd> dq HalpClockTimer l1
fffff803`eadc2550  fffff7e0`80016000
```

After having looked around at the local types in IDA, i found thought it had the structure of `_HAL_CLOCK_TIMER_CONFIGURATION`:

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

By chaging the timer resolution of the system we can see that MaxIncrement changes, by going from 1ms to 0.5ms:
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

Now we get the memory address of `Timer + 0xE0` and dump it, so that we can see what the value of `v4` is:
```
lkd> dd fffff7e0`80016000+0xE0 L1
fffff7e0`800160e0  00210131
```

### 5.2 Decoding the Capability Check Logic

Now we return to the previous code:
```c
v4 = *(_DWORD *)(Timer + 0xE0);  // v4 = 0x00210131
if ( (v4 & 0x50) != 0 )
    return Timer & -(__int64)((v4 & 0x20) != 0);
```

We now run a command to evaluate the expression:
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
if bit 0x20 was clear, it would have become:
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

But how do we know what timer type/ID we are currently using?
We can look at
```c
&& (!a1 || a1 == *((_DWORD *)v11 + 57))
```
`v11` is the timer pointer and `*((_DWORD *)v11 + 57)`  means DWORD at offset `57*4`= `0xE4` bytes, which gives us the offset for timers we can look at, to see what type they have.

## 7. System Timer Enumeration

### 7.1 Registered Timer Overview


Here we get some more information on the timers for our system:
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
We can see that the first timer has type `5`, the second timer has type `12` and the third timer has type `15`, and the one we are using is `12`.

By the looks of it, timer type 5 appears to be TSC, as it seems to be the one that is used everywhere for tsc.

But lets take a look at this from `HalpTimerSaveProcessorFrequency`

```c
  result = HalpFindTimer(7, 0, 0, 0, 1);
  if ( result )
  {
    result = (ULONG_PTR *)(10000 * (unsigned int)((result[24] + 5000) / 0x2710));
    Pcr->HalReserved[3] = (unsigned int)result;
  }
  return result;
```

From the `HalpFindTimer` code, `result[24]` refers to offset `+0xC0 (24 * 8 = 192 decimal = 0xC0 hex)`

lets test this in windbg:
```
lkd> ? poi (fffff7e0`80001000+0xC0)
Evaluate expression: 3187201731 = 00000000`bdf8d6c3
lkd> ? poi (fffff7e0`80016000+0xC0)
Evaluate expression: 10000000 = 00000000`00989680
lkd> ? poi (fffff7e0`80013be0+0xC0)
Evaluate expression: 38400006 = 00000000`0249f006
```
So the first timer we see with type 5 looks to be the TSC timer, as it has a value of `3187201731` which is the TSC frequency in Hz, just for quick demonstration we can see it has 3187 MHz, which is essentially the same, or else you can refer to [my other repo](https://github.com/eskezje/time):
```
lkd> !cpuinfo
CP  F/M/S Manufacturer  MHz PRCB Signature    MSR 8B Signature Features ArchitectureClass
 0  6,183,1 GenuineIntel 3187 0000012f00000000 >0000012f00000000<351b3fff 0
```
So now we know that timer type 5 is TSC. What about timer type 12 and 15?

If we look at the specs of HPET, we can see that it has a frequency of 10 MHz, which is the same as the one we see in `HalpClockTimer`
And as for timer type 15, it is the LAPIC timer, we can find the frequency of that by using:
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


## 8. Investigating frequency of HPET

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






















later for vppt
```
lkd> dq HalpVpptPhysicalTimer l1
fffff803`eadc0760  fffff7e0`80013460
lkd> dt _HAL_CLOCK_TIMER_CONFIGURATION fffff7e0`80013460
nt!_HAL_CLOCK_TIMER_CONFIGURATION
   +0x000 Flags            : 0x48 'H'
   +0x000 AlwaysOnTimer    : 0y0
   +0x000 HighLatency      : 0y0
   +0x000 PerCpuTimer      : 0y0
   +0x000 DynamicTickSupported : 0y1
   +0x004 KnownType        : 0xfffff7e0
   +0x008 Capabilities     : 0x80013250
   +0x010 MaxIncrement     : 0x4a84
   +0x018 MinIncrement     : 0
lkd> dd fffff7e0`80013460+0xE4 l1
fffff7e0`80013544  00000003
lkd> ? poi (fffff7e0`80013460+0xC0)
Evaluate expression: 19200000 = 00000000`0124f800
```