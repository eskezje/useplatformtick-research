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