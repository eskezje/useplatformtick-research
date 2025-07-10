/* Function: HalpTimerSelectRoles @ 0x1404f4b88 (call depth 2) */

__int64 __fastcall HalpTimerSelectRoles(__int64 a1, __int64 a2)
{
  unsigned int v2; // ebx
  __int64 IdealScalingSource; // rax
  __int64 v4; // rdi
  __int64 IdealClockSource; // rax
  ULONG_PTR v6; // rdi
  __int64 IdealPerformanceCounterSource; // rax
  ULONG_PTR v8; // rdi
  __int64 v9; // rcx
  ULONG_PTR *Timer; // rax
  __int64 v11; // rdi
  __int64 BestAlwaysOnTimer; // rax
  ULONG_PTR v13; // rdi
  ULONG_PTR v14; // rcx
  ULONG_PTR *v15; // rax
  int v16; // eax
  ULONG_PTR *v17; // rax
  __int64 v18; // rax
  ULONG_PTR v19; // rdi
  ULONG_PTR *v20; // rdi
  __int64 v21; // rax
  __int64 v22; // rdi
  __int64 IdealWatchdog; // rax
  __int64 v24; // rdi

  v2 = 0;
  while ( !HalpTimerFrequenciesMeasured )
  {
    IdealScalingSource = HalpTimerFindIdealScalingSource();
    v4 = IdealScalingSource;
    if ( !IdealScalingSource )
    {
      HalpTimerLastProblem = 19;
      return 0xC0000001;
    }
    if ( (int)HalpTimerInitialize(IdealScalingSource) >= 0 )
    {
      HalpTimerMeasureFrequencies(v4);
      HalpTimerFrequenciesMeasured = 1;
    }
  }
  while ( !HalpClockTimer )
  {
    IdealClockSource = HalpTimerFindIdealClockSource();
    v6 = IdealClockSource;
    if ( !IdealClockSource )
    {
      HalpTimerLastProblem = 20;
      return 0xC0000001;
    }
    if ( (int)HalpTimerInitialize(IdealClockSource) >= 0 )
    {
      *(_DWORD *)(v6 + 184) |= 4u;
      HalpClockTimer = v6;
      goto LABEL_11;
    }
  }
  do
  {
LABEL_11:
    if ( HalpPerformanceCounter
      && (*(_DWORD *)(HalpPerformanceCounter + 184) & 4) != 0
      && HalpPerformanceCounter != HalpClockTimer )
    {
      goto LABEL_17;
    }
    IdealPerformanceCounterSource = HalpTimerFindIdealPerformanceCounterSource();
    v8 = IdealPerformanceCounterSource;
    if ( !IdealPerformanceCounterSource )
    {
      HalpTimerLastProblem = 21;
      return 0xC0000001;
    }
  }
  while ( (int)HalpTimerInitialize(IdealPerformanceCounterSource) < 0 );
  HalpPerformanceCounter = v8;
  HalpTimerPropagateQpcBiasUpdate(v8);
  *(_DWORD *)(v8 + 184) |= 4u;
LABEL_17:
  v9 = HalpStallCounter;
  if ( (*(_DWORD *)(HalpStallCounter + 224) & 0x2000) != 0 || HalpStallCounter == HalpClockTimer )
  {
    v9 = HalpPerformanceCounter;
    HalpStallCounter = HalpPerformanceCounter;
  }
  else
  {
    *(_DWORD *)(HalpStallCounter + 184) |= 4u;
  }
  if ( v9 != HalpOriginalStallTimer )
    *(_DWORD *)(HalpOriginalStallTimer + 184) |= 4u;
  if ( !HalpAuxiliaryCounter )
  {
    Timer = HalpFindTimer(15, 0x100002, 0x6000, 0, 0);
    v11 = (__int64)Timer;
    if ( Timer )
    {
      if ( Timer[24] <= 1000000000 && (int)HalpTimerInitialize(Timer) >= 0 )
      {
        *(_DWORD *)(v11 + 184) |= 4u;
        HalpAuxiliaryCounter = v11;
      }
    }
  }
  while ( !HalpAlwaysOnTimer )
  {
    if ( (*(_DWORD *)(HalpClockTimer + 224) & 0x8000) != 0 )
      break;
    BestAlwaysOnTimer = HalpTimerFindBestAlwaysOnTimer(0LL);
    v13 = BestAlwaysOnTimer;
    if ( !BestAlwaysOnTimer )
      break;
    if ( (int)HalpTimerInitialize(BestAlwaysOnTimer) >= 0 )
    {
      *(_DWORD *)(v13 + 184) |= 4u;
      HalpAlwaysOnTimer = v13;
      break;
    }
  }
  v14 = HalpClockTimer;
  if ( (*(_DWORD *)(HalpClockTimer + 224) & 1) == 0 )
  {
    if ( (int)HalpVpptTimerRegister(HalpClockTimer, 0LL) < 0 )
    {
      LODWORD(v15) = 0;
      HalpClockTimer = 0LL;
    }
    else
    {
      v15 = HalpFindTimer(12, 32, 0, 3840, 0);
      HalpClockTimer = (ULONG_PTR)v15;
      if ( v15 )
      {
        v16 = HalpTimerInitialize(v15);
        v14 = HalpClockTimer;
        if ( v16 < 0 )
        {
          HalpTimerSetProblemEx(
            HalpClockTimer,
            20,
            2,
            (unsigned int)"minkernel\\hals\\lib\\timers\\common\\timer.c",
            3378);
          return 0xC0000001;
        }
        *(_DWORD *)(HalpClockTimer + 184) |= 4u;
        goto LABEL_39;
      }
    }
    HalpTimerSetProblemEx((_DWORD)v15, 20, 1, (unsigned int)"minkernel\\hals\\lib\\timers\\common\\timer.c", 3366);
    return 0xC0000001;
  }
LABEL_39:
  if ( HalpAlwaysOnTimer && (*(_DWORD *)(HalpAlwaysOnTimer + 224) & 1) == 0 && (*(_DWORD *)(v14 + 224) & 1) != 0 )
  {
    LOBYTE(a2) = 1;
    if ( (int)HalpVpptTimerRegister(HalpAlwaysOnTimer, a2) < 0 )
    {
      HalpAlwaysOnTimer = 0LL;
    }
    else
    {
      v17 = HalpFindTimer(12, 32, 0, 3840, 0);
      HalpAlwaysOnTimer = (ULONG_PTR)v17;
      if ( v17 )
      {
        *((_DWORD *)v17 + 46) |= 4u;
        goto LABEL_45;
      }
    }
    HalpTimerLastProblem = 33;
    return 0xC0000001;
  }
LABEL_45:
  while ( !HalpAlwaysOnCounter
       && ((*(_DWORD *)(HalpPerformanceCounter + 224) & 0x8000) == 0
        || (*(_DWORD *)(HalpStallCounter + 224) & 0x8000) == 0) )
  {
    LOBYTE(v14) = 1;
    v18 = HalpTimerFindBestAlwaysOnTimer(v14);
    v19 = v18;
    if ( !v18 )
      break;
    if ( (int)HalpTimerInitialize(v18) >= 0 )
    {
      *(_DWORD *)(v19 + 184) |= 4u;
      HalpAlwaysOnCounter = v19;
      break;
    }
  }
  while ( !HalpProfileTimer && HalpProfileInterface == &DefaultProfileInterface )
  {
    v20 = HalpFindTimer(0, 0x41, 0, 0xF00, 0);
    if ( !v20
      && ((unsigned int)HalpQueryMaximumRegisteredProcessorCount() != 1
       || (v20 = HalpFindTimer(0, 0x40, 0, 0xF00, 0)) == 0LL) )
    {
      HalpTimerLastProblem = 23;
      break;
    }
    if ( (int)HalpTimerInitialize(v20) >= 0 )
    {
      *((_DWORD *)v20 + 46) |= 4u;
      HalpProfileTimer = (__int64)v20;
      HalpTimerStopProfileInterrupt();
      break;
    }
  }
  if ( (*(_DWORD *)(HalpPerformanceCounter + 224) & 1) != 0 )
  {
    while ( !HalpFallbackPerformanceCounter )
    {
      v21 = HalpTimerFindIdealPerformanceCounterSource();
      v22 = v21;
      if ( !v21 )
      {
        HalpTimerLastProblem = 22;
        break;
      }
      if ( (int)HalpTimerInitialize(v21) >= 0 )
      {
        *(_DWORD *)(v22 + 184) |= 4u;
        HalpFallbackPerformanceCounter = v22;
        break;
      }
    }
  }
  if ( !HalpTimerWatchdogDisable )
  {
    IdealWatchdog = HalpTimerFindIdealWatchdog();
    v24 = IdealWatchdog;
    if ( IdealWatchdog )
    {
      if ( (int)HalpTimerInitialize(IdealWatchdog) >= 0 )
      {
        *(_DWORD *)(v24 + 184) |= 4u;
        HalpWatchdogTimer = v24;
      }
    }
  }
  return v2;
}
