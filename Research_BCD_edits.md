# Taking a look at `tscsyncpolicy`

Important: This is on windows 24H2 windows 11 (OS Build 26100.3775)

We can start with the same approach as with `useplatformtick`, by starting to look through all the strings in system32. Utilizing the command

[Strings2](https://github.com/glmcdona/strings2)
```bash
strings2 -r -f C:\Windows\System32\ > strings.txt
```

By using the all mighty control+f in notepad++, we can search for `tscsyncpolicy` in the strings.txt file
```
Line   578415: bcdedit.exe,tscsyncpolicy
Line   583863: bcdsrv.dll,BcdOSLoaderInteger_TscSyncPolicy
Line 16806244: fveapi.dll,tscsyncpolicy
Line 32542722: Microsoft.Windows.Bcd.Utils.dll,tscsyncpolicy
```
These hold no functionality, feel free to check them out yourself.

I do know that this existed in windows 10, but was removed in windows 11 (Might add a section about this later.)

# 1. Taking a look at `useplatformclock`

With all of the strings already dumped, we can search for `useplatformclock` in the strings.txt file. We can see that we already have a lot more results than with `tscsyncpolicy`:
```
Line   578413: bcdedit.exe,useplatformclock
Line   582276:     USEPLATFORMCLOCK (bool) Forces the use of a platform clock source for the
Line   583859: bcdsrv.dll,BcdOSLoaderBoolean_UsePlatformClockW
Line   668241: winload.efi,/USEPLATFORMCLOCK
Line   675921: winload.exe,/USEPLATFORMCLOCK
Line 15678875:     USEPLATFORMCLOCK (bool) Forces the use of a platform clock source for the
Line 16806242: fveapi.dll,useplatformclock
Line 23507977: ntkrla57.exe,USEPLATFORMCLOCK
Line 24156018: ntkrla57.exe.i64,HalpSzUsePlatformClock
Line 24651614: ntoskrnl.exe,USEPLATFORMCLOCK
Line 24774284: ntoskrnl.exe.i64,HalpSzUsePlatformClock
Line 25996023: ntoskrnl.exe.id0,HalpSzUsePlatformClock
Line 29233285: tcblaunch.exe,/USEPLATFORMCLOCK
Line 32542720: Microsoft.Windows.Bcd.Utils.dll,useplatformclock
Line 33189562: winload.efi,/USEPLATFORMCLOCK
Line 33197242: winload.exe,/USEPLATFORMCLOCK
```

Lets dive into `ntoskrnl.exe` again.

# 2. Cross-referencing `USEPLATFORMCLOCK`
By looking at the strings in `ntoskrnl.exe`, we see the following:
```
.rdata:000000014001DBF0 ; const char HalpSzUsePlatformClock[]
.rdata:000000014001DBF0 HalpSzUsePlatformClock db 'USEPLATFORMCLOCK',0
.rdata:000000014001DBF0                                         ; DATA XREF: HalpMiscGetParameters:loc_140BD5916↓o
.rdata:000000014001DC01                 align 8
```
We then look at the reference of HalpTimerPlatformSourceForced, it is found the function [HalpMiscGetParameters](HalpMiscGetParameters.c#L128):
```c
      if ( strstr(v3, "USEPLATFORMCLOCK") )         // if bcdedit /set USEPLATFORMCLOCK yes
        HalpTimerPlatformSourceForced = 1;          // then we set HalpTimerPlatformSourceForced = 1, now we can look for references for HalpTimerPlatformSourceForced
      if ( strstr(v3, "USEPLATFORMTICK") ) 
        HalpTimerPlatformClockSourceForced = 1;
```
If you followed along from the previous section of `useplatformtick`, you would notice that `HalpTimerPlatformSourceForced` might look familiar.
It has 3 references excluding `HalpMiscGetParameters`: [HalpTimerFindIdealPerformanceCounterSource](HalpFindTimer_xrefs/01_HalpTimerFindIdealPerformanceCounterSource_1404f3ff0.c) as we previously saw, [HalSocRequestConfigurationData](HalpTimerRegisterBuiltinPluginsCommon/HalSocRequestConfigurationData.c) and then a function we havent seen before [HalpNumaInitializeStaticConfiguration](HalpNumaInitializeStaticConfiguration.c).

# 2.1 Looking into `HalpTimerFindIdealPerformanceCounterSource`

Lets start by taking a look at `HalpTimerFindIdealPerformanceCounterSource`, It has a very familiar structure as to `HalpTimerFindIdealClockSource` from the previous section of useplatformtick:
```c
if ( HalpTimerPlatformSourceForced )        // if bcdedit /set USEPLATFORMCLOCK yes
  goto SelectPlatform;                      // then we go to SelectPlatform
...
SelectPlatform:
          result = HalpFindTimer(11, 2, 0x6000, 0, 0);
          if ( !result )
          {
            result = HalpFindTimer(3, 2, 0x6000, 0, 0);
            if ( !result )
            {
              result = HalpFindTimer(1, 2, 0x6000, 0, 0);
              if ( !result )
              {
                if ( HalpIsHvPresent() )
                  return 0LL;
                result = HalpFindTimer(0, 2, 0x6000, 0, 0);
                if ( !result )
                  return 0LL;
```

It is still unclear what timer type 11 is, but `HalpTimerFindIdealPerformanceCounterSource` is also used the function `HalpTimerSelectRoles` as we are pretty familiar with:
We come from finding our `HalpClockTimer` with `HalpTimerFindIdealClockSource()`
```c
     *(_DWORD *)(v6 + 184) |= 4u;
      HalpClockTimer = v6;
      goto LABEL_11;
    }
  }
  do
  {
LABEL_11:
    // After HalpClockTimer is established
    if ( HalpPerformanceCounter
      && (*(_DWORD *)(HalpPerformanceCounter + 0xB8) & 4) != 0  // Already initialized
      && HalpPerformanceCounter != HalpClockTimer )             // Different from clock timer
    {
      goto LABEL_17;    // Use existing performance counter
    }
    IdealPerformanceCounterSource = (__int64)HalpTimerFindIdealPerformanceCounterSource();
    v8 = IdealPerformanceCounterSource;
    if ( !IdealPerformanceCounterSource )
    {
      HalpTimerLastProblem = 21;
      return 0xC0000001;
    }
  }
  while ( (int)HalpTimerInitialize(IdealPerformanceCounterSource) < 0 );
  HalpPerformanceCounter = v8;
```

# 2.2 Timer Type and Speed

So we try to find the "ideal performance counter source" and set it to `HalpPerformanceCounter`, which is then used in the function `HalpTimerInitialize`
We can first start off by looking at what my current `HalpPerformanceCounter` is set to (we already checked it in the previous section):
```
lkd> db HalpTimerPlatformSourceForced l1
fffff802`edfc24b0  00                                               .
lkd> dq HalpPerformanceCounter l1
fffff802`edfc2430  fffff796`00001000
```
We know that we can find the timer type by looking at the offset `0xE4` for any timer, as well as the speed in `0xC0`
```
lkd> dd fffff796`00001000+0xE4 l1
fffff796`000010e4  00000005
lkd> dd fffff796`00001000+0xC0 l1
fffff796`000010c0  bdf8cb9a
lkd> ? bdf8cb9a
Evaluate expression: 3187198874 = 00000000`bdf8cb9a
```
We can see that is as expected, the timer type is `5` (TSC) and a speed of 3187198874 (3.187 GHz), which means that we already find it early on:
```c
ULONG_PTR *HalpTimerFindIdealPerformanceCounterSource()
{
  int v0; // ebx
  ULONG_PTR *result; // rax

  if ( HalpTimerPlatformSourceForced )
    goto SelectPlatform;
  if ( HalpIsHvPresent() )
    goto LABEL_19;
  v0 = 0x2000;
  if ( (unsigned __int8)HalpTimerDeepestIdleState > 1u )
    v0 = 0x6000;
  result = HalpFindTimer(5, 3, v0, 0, 0); // Find timer type 5 (TSC) with flags 3 and v0
  if ( !result )
  {
    result = HalpFindTimer(10, 3, v0, 0, 0);
    if ( !result )
    {
```

# 2.3 Practical Effects on QueryPerformanceCounter

This timer is used as the performance counter on the system, whenever you are using `QueryPerformanceCounter` or `QueryPerformanceFrequency`, it will use this timer. Even though it is 3.187 GHz, QueryPerformanceCounter will still only be running with 10 MHz.

If you want to learn more about how it gets converted to 10 MHz, then i recommend lookinag at Casey Muratori breakdown of the [QueryPerformanceCounter video](https://www.youtube.com/watch?v=pZ0MF1q_LUE), [article format](https://www.computerenhance.com/p/how-does-queryperformancecounter).

If you wish you can take a look yourself at the function [KeQueryPerformanceCounter](KeQueryPerformanceCounter.c)

If you then turn on `HalpTimerPlatformSourceForced` you will get to this section:
Lets start by taking a look at `HalpTimerFindIdealPerformanceCounterSource`, It has a very familiar structure as to `HalpTimerFindIdealClockSource` from the previous section of useplatformtick:
```c
if ( HalpTimerPlatformSourceForced )        // if bcdedit /set USEPLATFORMCLOCK yes
  goto SelectPlatform;                      // then we go to SelectPlatform
...
SelectPlatform:
          result = HalpFindTimer(11, 2, 0x6000, 0, 0);
          if ( !result )
          {
            result = HalpFindTimer(3, 2, 0x6000, 0, 0);
            if ( !result )
            {
              result = HalpFindTimer(1, 2, 0x6000, 0, 0);
              if ( !result )
              {
                if ( HalpIsHvPresent() )
                  return 0LL;
                result = HalpFindTimer(0, 2, 0x6000, 0, 0);
                if ( !result )
                  return 0LL;
```

From previous research, we know that we wont find timer type 11, so we will try to find timer type 3 (HPET), and if that doesnt work, then we try to find timer type 1, i believe that this is ACPI PM Timer.
I previously tested with `QueryPerformanceFrequency` and `QueryPerformanceCounter` and saw that whenever I had `USEPLATFORMCLOCK yes` i would still be getting 10MHz, but tracing through it live debugging and using TTD (time travel debugging) we could see that we didnt get it from rdtscp, but some other location. Whenever i then disabled `USEPLATFORMCLOCK` i would get the speed of `3579545` which is the ACPI PM Timer, which is 3.579545 MHz. [OSDEV ACPI Timer](https://wiki.osdev.org/ACPI_Timer). If you dont trust my words, then you can check it yourself with the knowledge you have gained from reading hopefully both sections.

I have later found out that [djdallmann](https://github.com/djdallmann/GamingPCSetup/blob/5aecc5e85d919a3b119af81fa20f45d252a61a33/CONTENT/RESEARCH/WINKERNEL/README.md#hardware-abstraction-layer-hal) already had done some of the research, and you see that it matches with the research we have done here.