/* Call path: HalpFindTimer <- HalpTimerSelectRoles <- HalpInitializeTimers <- HalpTimerInitSystem */

/* ===== Function: HalpFindTimer @ 0x1405008d0 ===== */
ULONG_PTR *__fastcall HalpFindTimer(int a1, int a2, int a3, int a4, char a5)
{
  ULONG_PTR *v9; // r8
  ULONG_PTR *v10; // rdx
  ULONG_PTR *v11; // rsi
  ULONG_PTR *v12; // rbp
  ULONG_PTR *v13; // r10
  ULONG_PTR *v14; // r14
  int v15; // ecx
  int v16; // r11d
  ULONG_PTR v17; // rax
  ULONG_PTR v18; // rcx

  if ( !(_DWORD)HalpRegisteredTimerCount )
    return 0LL;
  v9 = (ULONG_PTR *)HalpRegisteredTimers;
  v10 = 0LL;
  while ( v9 != &HalpRegisteredTimers )
  {
    v11 = v9;
    v12 = v9;
    v13 = v9;
    v14 = v10;
    v9 = (ULONG_PTR *)*v9;
    v15 = *((_DWORD *)v11 + 46);
    if ( ((v15 & 0x100) == 0 || (a5 & 4) == 0)
      && (v15 & 1) == 0
      && ((v15 & 4) == 0 || (a5 & 1) != 0)
      && (!a1 || a1 == *((_DWORD *)v11 + 57)) )
    {
      v16 = *((_DWORD *)v13 + 56);
      if ( (a2 & v16) == a2 && (v16 & a3) == 0 && (!a4 || (v16 & a4) != 0) )
      {
        if ( v10 )
        {
          v17 = v11[24];
          v18 = v10[24];
          if ( (a5 & 2) != 0 )
          {
            v10 = v12;
            if ( v17 >= v18 )
              v10 = v14;
          }
          else if ( v17 > v18 )
          {
            v10 = v13;
          }
        }
        else
        {
          v10 = v13;
        }
      }
    }
  }
  if ( (a5 & 4) != 0 )
  {
    if ( v10 )
      *((_DWORD *)v10 + 46) |= 0x100u;
  }
  return v10;
}

/* ===== Function: HalpTimerSelectRoles @ 0x1404f4b88 ===== */
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

/* ===== Function: HalpInitializeTimers @ 0x1404f3950 ===== */
__int64 __fastcall HalpInitializeTimers(__int64 a1)
{
  int v2; // ebx
  __int64 InternalData; // rax
  __int64 v4; // rdx
  __int64 v5; // r8
  int v6; // eax
  __int64 v7; // rdx
  __int64 v8; // r8
  ULONG_PTR *Timer; // rax
  __int64 v10; // rdx
  __int64 v11; // rcx
  ULONG_PTR v12; // r8
  int v13; // ecx
  int v14; // eax
  unsigned int v15; // edx
  __int64 v16; // r8
  int v17; // eax
  __int64 v18; // rdx
  __int64 v19; // rcx
  __int64 v20; // rbx
  void *MemoryInternal; // rax
  _QWORD *v22; // rdi
  unsigned int v23; // r9d
  _BYTE v25[136]; // [rsp+30h] [rbp-98h] BYREF
  int v26; // [rsp+B8h] [rbp-10h]
  int v27; // [rsp+BCh] [rbp-Ch]

  memset_0(v25, 0, sizeof(v25));
  HalpTimerLoaderBlock = a1;
  v2 = HalpStallCounter;
  HalpOriginalStallTimer = HalpStallCounter;
  InternalData = HalpTimerGetInternalData(HalpStallCounter);
  v6 = guard_dispatch_icall_no_overrides(InternalData, v4, v5);
  if ( v6 < 0 )
  {
    HalpTimerSetProblemEx(v2, 15, v6, (unsigned int)"minkernel\\hals\\lib\\timers\\common\\timer.c", 1566);
    goto LABEL_3;
  }
  LODWORD(v8) = HalpTimerRegisterBuiltinPluginsCommon(1LL, v7, (unsigned int)v6);
  if ( (int)v8 < 0 )
  {
    HalpTimerLastProblem = 14;
    goto LABEL_3;
  }
  Timer = HalpFindTimer(5, 0, 0, 0, 1);
  if ( Timer )
  {
    v12 = Timer[36];
    v13 = *((_DWORD *)Timer + 57);
    v14 = *((_DWORD *)Timer + 71);
    v26 = v13;
    v15 = *(unsigned __int16 *)(v12 + 24);
    v16 = *(_QWORD *)(v12 + 32);
    v27 = v14;
    HalpTimerBuildKnownResourceIdString(v25, v15 >> 1, v16);
  }
  v17 = HalpTimerSelectRoles(v11, v10);
  v8 = (unsigned int)v17;
  if ( v17 < 0 )
LABEL_3:
    KeBugCheckEx(0x5Cu, 0x110uLL, 86312497uLL, HalpTimerLastProblem, (int)v8);
  v20 = HalpPerformanceCounter;
  if ( *(_DWORD *)(HalpPerformanceCounter + 228) == 5 )
  {
    MemoryInternal = (void *)HalpMmAllocateMemoryInternal(4096LL, 1LL, (unsigned int)v17);
    HalpTimerReferencePage = MemoryInternal;
    v22 = MemoryInternal;
    if ( !MemoryInternal )
    {
      LODWORD(v8) = 0xC000009A;
      goto LABEL_3;
    }
    memset_0(MemoryInternal, 0, 0x1000uLL);
    v20 = HalpPerformanceCounter;
    *(_DWORD *)v22 = 0x546C6148;
    v22[1] = RtlUdiv128(10000000LL, 0LL, *(_QWORD *)(v20 + 192), 0LL);
  }
  qword_140FC24F8 = (__int64)HalpTimerDpcRoutine;
  v23 = 0;
  HalpTimerPeriodicTimer = 8LL;
  qword_140FC2450 = (__int64)&qword_140FC2448;
  qword_140FC2448 = (__int64)&qword_140FC2448;
  off_140E00818[0] = HalpTimerReportIdleStateUsage;
  off_140E00810[0] = HalpTimerQueryWakeTime;
  HalpOriginalPerformanceCounter = v20;
  HalpTimerDpc = 275;
  qword_140FC2500 = 0LL;
  qword_140FC2518 = 0LL;
  qword_140FC24F0 = 0LL;
  qword_140FC2458 = 0LL;
  dword_140FC247C = 0;
  word_140FC2478 = 0;
  if ( HalpAlwaysOnCounter )
    HalpTimerMaximumAllowableDrift = HalpTimerCalculateMaximumAllowableDrift(v19, v18, v8, 0LL);
  return v23;
}

/* ===== Function: HalpTimerInitSystem @ 0x1404f42e0 ===== */
__int64 __fastcall HalpTimerInitSystem(int a1, __int64 a2, __int64 a3)
{
  unsigned int inited; // ebx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  __int64 v7; // rcx
  __int64 v8; // rcx
  __int64 v9; // rcx
  __int64 v10; // rcx
  __int64 v11; // rcx
  const EVENT_DESCRIPTOR *v12; // rcx
  __int64 v13; // rcx
  __int64 v14; // rdx
  __int64 v15; // rcx
  __int64 v16; // r8
  int v17; // r9d
  unsigned int MaximumProcessorCount; // eax
  __int64 v19; // rcx
  __int64 v21; // r8
  __int64 v22; // rcx
  int v23; // eax
  __int64 v24; // rdx
  __int64 v25; // r8
  unsigned __int8 v26; // cl
  LARGE_INTEGER PerformanceFrequency; // [rsp+30h] [rbp-38h] BYREF
  ULONG_PTR Context[2]; // [rsp+38h] [rbp-30h] BYREF
  int v29; // [rsp+48h] [rbp-20h]

  inited = 0;
  v4 = a1 - 1;
  if ( v4 )
  {
    v5 = v4 - 7;
    if ( !v5 )
    {
      v26 = byte_140FBFFAC;
      if ( !byte_140FBFFAC )
        v26 = 50;
      HalpCmosCenturyOffset = v26;
      xHalTimerQueryRtcErrors_1 = HalpTimerQueryRtcErrors;
      return inited;
    }
    v6 = v5 - 6;
    if ( !v6 )
    {
      if ( (unsigned int)HalpInterruptModel() == 1 )
        xHalTscSynchronization_0[0] = (__int64 (__fastcall *)())HalpTscSynchronization;
      xHalTimerWatchdogStop_0[0] = (__int64 (__fastcall *)())HalpTimerClockActivate;
      xHalTimerWatchdogStop_1[0] = HalpTimerClockInitialize;
      xHalTimerWatchdogStop_2[0] = HalpTimerClockStop;
      xHalUnmaskInterrupt_0[0] = (__int64 (__fastcall *)())HalpTimerClockArm;
      xHalTimerWatchdogStop_3[0] = (__int64 (__fastcall *)())HalpTimerGetClockConfiguration;
      ext_ms_win_ntos_tm_l1_1_0_TmIsKTMCommitCoordinator_0[0] = HalpTimerOnlyClockInterruptPending;
      off_140E00960 = HalpTimerQueryCycleCounter;
      PdcCreateWatchdogAroundClientCall_0 = HalpTimerGetReferencePage;
      xKdEnumerateDebuggingDevices_2[0] = HalpTimerConvertAuxiliaryCounterToPerformanceCounter;
      xKdEnumerateDebuggingDevices_1[0] = HalpTimerConvertPerformanceCounterToAuxiliaryCounter;
      xKdEnumerateDebuggingDevices_3[0] = HalpTimerQueryAuxiliaryCounterFrequency;
      HalpInitializeTimers(v21);
      HalpTimerSaveProcessorFrequency(v22);
      HalpTimerInitializeClock();
      KiProfileIrql = 15;
      v23 = HalpTimerInitializeProfiling();
      inited = v23;
      if ( v23 < 0 )
        KeBugCheckEx(0x5Cu, 0x110uLL, v23, 0LL, 0LL);
      HalpTimerPropagateQpcBiasUpdate(HalpPerformanceCounter, v24, v25);
      return inited;
    }
    v7 = (unsigned int)(v6 - 3);
    if ( (_DWORD)v7 )
    {
      v8 = (unsigned int)(v7 - 2);
      if ( !(_DWORD)v8 )
      {
        if ( !qword_140FC03C8 )
        {
          v8 = 16LL;
          __writemsr(0x10u, 0LL);
        }
        HalpTimerSaveProcessorFrequency(v8);
        HalpInitializePnTimers();
        HalpTimerInitializeClockPn(v15, v14, v16, v17);
        return (unsigned int)HalpTimerInitializeProfiling();
      }
      v9 = (unsigned int)(v8 - 2);
      if ( (_DWORD)v9 )
      {
        v10 = (unsigned int)(v9 - 4);
        if ( (_DWORD)v10 )
        {
          v11 = (unsigned int)(v10 - 4);
          if ( (_DWORD)v11 )
          {
            if ( (_DWORD)v11 == 3 )
            {
              LOBYTE(a2) = 1;
              xHalTimerQueryRtcErrors_0[0] = (__int64 (__fastcall *)())HalpTimerQueryAndResetRtcErrors;
              HalpTimerQueryAndResetRtcErrors(0LL, a2);
              HalpTimerTraceTimingHardware();
              HalpTscReportSyncStatus();
            }
          }
          else
          {
            inited = HalpTimerInitPowerManagement(v11, a2, a3);
            HalpTimerWatchdogLogReset();
          }
        }
        else if ( HalpWatchdogTimer )
        {
          HalpTimerInitializeSystemWatchdog(v10, a2, a3);
        }
        return inited;
      }
      HalpTimerSchedulePeriodicQueries(v9, a2, a3);
      HalpTimerConfigureQpcBypass();
      xHalUnmaskInterrupt_10[0] = HalpTimerQueryHostPerformanceCounter;
      if ( (unsigned int)HalpInterruptModel() == 1 )
      {
        if ( !HalpTimerProcessorFrequencyKnown && *(_DWORD *)(HalpPerformanceCounter + 228) != 5 )
        {
          Context[0] = KeQueryActiveProcessorCountEx(0xFFFFu);
          Context[1] = 0LL;
          v29 = 5;
          KeIpiGenericCall(HalpTimerMeasureProcessorsWorker, (ULONG_PTR)Context);
        }
        if ( *(_DWORD *)(HalpPerformanceCounter + 228) == 5 )
        {
          if ( HalpTscSynchronizationFailureFallback )
          {
            v12 = (const EVENT_DESCRIPTOR *)HAL_ETW_EVENT_UNEXPECTED_FALLBACK;
          }
          else
          {
            if ( !HalpTscProcessorFeatureFallback )
              goto LABEL_24;
            v12 = &HAL_ETW_EVENT_EXPECTED_FALLBACK;
          }
          HalpTscFallbackToPlatformSource(v12);
        }
      }
LABEL_24:
      v13 = HalpAuxiliaryCounter;
      PerformanceFrequency.QuadPart = 0LL;
      if ( HalpAuxiliaryCounter )
      {
        if ( HalpTimerAuxiliaryClockEnabled )
        {
          if ( (*(_DWORD *)(HalpAuxiliaryCounter + 224) & 0x6000) != 0 )
          {
            v13 = 0LL;
            HalpAuxiliaryCounter = 0LL;
          }
          if ( v13 )
          {
            if ( !HalpTimerQpcFreqForAuxQpcConversion )
            {
              KeQueryPerformanceCounter(&PerformanceFrequency);
              HalpTimerQpcFreqForAuxQpcConversion = PerformanceFrequency.QuadPart;
            }
            HalpTimerEarliestQpcAllowedToConvert = KeQueryPerformanceCounter(0LL).QuadPart;
            HalpTimerCaptureCloestAuxiliaryQpcPair();
          }
        }
        else
        {
          HalpAuxiliaryCounter = 0LL;
        }
      }
      return inited;
    }
    HalpTscReserveResources(v7, a2, a3);
    MaximumProcessorCount = HalQueryMaximumProcessorCount();
    HalpTimerSavedProcessorCounter = HalpMmAllocCtxAlloc(v19, 8LL * MaximumProcessorCount);
    if ( !HalpTimerSavedProcessorCounter )
      return 0xC000009ALL;
    if ( (unsigned int)HalpInterruptModel() == 1 )
      HalpTimerInitializeHypervisorTimer();
  }
  else
  {
    inited = HalpTimerInitializeEarlyStallSource(a3);
    xHalTimerWatchdogStop_8[0] = HalpTimerNotifyProcessorFreeze;
  }
  return inited;
}

