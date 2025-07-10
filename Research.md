# Research on the useage of USEPLATFORMTICK

Only useage of USEPLATFORMTICK in all of the system, done by dumping all strings of system32 use [strings2.exe](https://github.com/glmcdona/strings2) and finding USEPLATFORMTICK, no other code uses `USEPLATFORMTICK` besides ntoskrnl.exe, and ntkrla57.exe

```c
      if ( strstr(v3, "USEPLATFORMTICK") )          // if bcdedit /set USEPLATFORMTICK yes
        HalpTimerPlatformClockSourceForced = 1;     // then we set HalpTimerPlatformClockSourceForced = 1, now we can look for references for HalpTimerPlatformClockSourceForced
```

The only xreferences to `HalpTimerPlatformClockSourceForced` is the function called `HalpTimerFindIdealClockSource`.

Now we can use the IDA plugins to look at references to `HalpTimerFindIdealClockSource`.

```py
Python>import export_clean_xrefs
Python>import export_each_func
Python>export_clean_xrefs.export_xrefs_pseudocode('HalpTimerFindIdealClockSource', max_depth=10)
Python>export_each_func.export_xrefs_pseudocode('HalpTimerFindIdealClockSource', max_depth=10)
```

In `HalpTimerFindIdealClockSource`(link the file here) we can now look at the control flow and see that.

If either `HalpHvCpuManager` or `HalpHvPresent` are both false, then we jump to LABEL_7, where we then try to find this timer `Timer = (__int64)HalpFindTimer(11, 0x220, 0, 0x50, 0);`, whatever it might be. Then as it finds a suitable timer, it then jumps to LABEL_26, assigns `v4 = *(_DWORD *)(Timer + 0xE0);` if then `(v4 & 0x50) != 0` then we `return Timer & -(__int64)((v4 & 0x20) != 0);`, I do not know what the second part is yet (`-(__int64)((v4 & 0x20) != 0)`).

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

Now we get the memory address of `Timer + 0xE0` and dump it, so that we can see what the value of `v4` is:
```
lkd> dd fffff7e0`80016000+0xE0 L1
fffff7e0`800160e0  00210131
```

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

Can we maybe dig deeper into what HalpFindTimer does?
I will make some assumptions as to what each argument in `HalpFindTimer` does:
```c
ULONG_PTR *__fastcall HalpFindTimer(int a1, int a2, int a3, int a4, char a5)
a1 = Timer type/ID
```

But how do we know what timer type/ID we are currently using?
We can look at
```c
&& (!a1 || a1 == *((_DWORD *)v11 + 57))
```
`v11` is the timer pointer and `*((_DWORD *)v11 + 57)`  means DWORD at offset `57*4`= `0xE4` bytes, which gives us the offset for timers we can look at, to see what type they have.

Here we get some more information on the timers for our system:
```
lkd> dd HalpRegisteredTimerCount l1
fffff803`eadc259c  00000008
lkd> dq HalpRegisteredTimers l4
fffff803`eadc2580  fffff7e0`80001000 fffff7e0`80016000
fffff803`eadc2590  fffff7e0`80013be0 00000008`00000001
```
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

