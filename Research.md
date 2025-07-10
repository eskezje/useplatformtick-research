# Research on the useage of USEPLATFORMTICK

Only useage of USEPLATFORMTICK in all of the system, done by dumping all strings of system32 use [strings2.exe](https://github.com/glmcdona/strings2) and finding USEPLATFORMTICK, no other code uses `USEPLATFORMTICK` besides ntoskrnl.exe, and ntkrla57.exe

```c
      if ( strstr(v3, "USEPLATFORMTICK") )          // if bcdedit /set USEPLATFORMTICK yes
        HalpTimerPlatformClockSourceForced = 1;     // then we set HalpTimerPlatformClockSourceForced = 1, now we can look for references for HalpTimerPlatformClockSourceForced
```