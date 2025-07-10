/* Call path: HalpFindTimer <- HalpTimerInitializeEarlyStallSource <- HalpTimerInitSystem */

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

/* ===== Function: HalpTimerInitializeEarlyStallSource @ 0x1404f474c ===== */
__int64 __fastcall HalpTimerInitializeEarlyStallSource(__int64 a1)
{
  int v2; // r10d
  ULONG_PTR *Timer; // rax
  ULONG_PTR *v4; // rbx
  unsigned int v5; // eax
  bool v6; // zf
  unsigned __int64 v7; // rcx

  LODWORD(HalpRegisteredTimerCount) = 0;
  HalpTimerLoaderBlock = a1;
  qword_140FC2588 = (__int64)&HalpRegisteredTimers;
  HalpRegisteredTimers = (ULONG_PTR)&HalpRegisteredTimers;
  v2 = HalpTimerRegisterBuiltinPluginsCommon(0);
  if ( v2 >= 0 )
  {
    if ( (_DWORD)HalpRegisteredTimerCount && (Timer = HalpFindTimer(0, 2, 0, 0, 1), (v4 = Timer) != 0LL) )
    {
      HalpPerformanceCounter = (ULONG_PTR)Timer;
      HalpStallCounter = (__int64)Timer;
      v2 = HalpTimerInitialize((__int64)Timer);
      if ( v2 >= 0 )
      {
        v5 = v4[23] & 0xFFFFFFFB;
        v6 = v4[24] == 0;
        *((_DWORD *)v4 + 46) = v5;
        if ( v6 )
        {
          *((_DWORD *)v4 + 46) = v5 | 8;
          v7 = *(_QWORD *)(*(_QWORD *)(a1 + 240) + 2496LL);
          v4[24] = v7;
          if ( v7 < 0x3E8 )
          {
            v4[24] = 15625000LL;
            HalpTimerSetProblemEx(
              (_DWORD)v4,
              40,
              0,
              (unsigned int)"minkernel\\hals\\lib\\timers\\common\\timer.c",
              1193);
          }
        }
        else
        {
          HalpTimerProcessorFrequencyKnown = 1;
        }
      }
    }
    else
    {
      v2 = -1073741823;
      HalpTimerLastProblem = 21;
    }
  }
  else
  {
    HalpTimerLastProblem = 14;
  }
  return (unsigned int)v2;
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

