/* Call path: HalpFindTimer <- HalpTimerInitializeHypervisorTimer <- HalpTimerInitSystem */

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

/* ===== Function: HalpTimerInitializeHypervisorTimer @ 0x1405039c4 ===== */
__int64 HalpTimerInitializeHypervisorTimer()
{
  __int64 result; // rax
  __int64 v5; // rbx
  int v6; // esi
  unsigned int *v7; // r12
  int v8; // r14d
  _DWORD *v9; // rdx
  unsigned int v10; // ecx
  int v11; // eax
  unsigned int v12; // eax
  __int64 v13; // rdx
  __int64 v14; // r9
  unsigned int v15; // eax
  __int64 v16; // rax
  int v17; // r8d
  _BYTE v18[4]; // [rsp+38h] [rbp-39h] BYREF
  int v19; // [rsp+3Ch] [rbp-35h] BYREF
  __int64 v20; // [rsp+40h] [rbp-31h] BYREF
  int v21; // [rsp+48h] [rbp-29h] BYREF
  unsigned __int64 v22; // [rsp+50h] [rbp-21h] BYREF
  _DWORD v23[6]; // [rsp+58h] [rbp-19h] BYREF
  __int64 v24; // [rsp+70h] [rbp-1h]
  __int64 v25; // [rsp+78h] [rbp+7h]
  __int64 v26; // [rsp+80h] [rbp+Fh]
  __int64 v27; // [rsp+88h] [rbp+17h]
  __int128 v28; // [rsp+90h] [rbp+1Fh]

  v22 = 0LL;
  v28 = 0LL;
  v20 = 0LL;
  v18[0] = 0;
  result = HalpIsPartitionCpuManager();
  if ( (_BYTE)result )
  {
    if ( qword_140FC0400 )
    {
      _RAX = 1073741830LL;
      __asm { cpuid }
      if ( (result & 0x100) != 0 )
      {
        result = (__int64)HalpFindTimer(3, 32, 24576, 3840, 0);
        v5 = result;
        if ( result )
        {
          result = HalpTimerInitialize(result);
          if ( (int)result >= 0 )
          {
            *(_DWORD *)(v5 + 184) |= 4u;
            HalpHypervisorHpet = v5;
            result = HalpTimerTestHypervisorTimer(v5, v18);
            HalpHypervisorHpet = 0LL;
            if ( (int)result >= 0 )
            {
              v6 = 1;
              v7 = *(unsigned int **)(v5 + 72);
              v8 = 0;
              if ( v18[0] )
              {
                v9 = *(_DWORD **)(v5 + 288);
                v10 = v9[1];
                HIWORD(v19) = *v9 >> 8;
                BYTE1(v19) = *(_BYTE *)v9;
                LOBYTE(v19) = (8 * *((_BYTE *)v9 + 4)) | (v10 >> 5) & 7;
                HalpHvBuildDeviceId(&v19, v9 + 2, 0LL, &v22);
              }
              else
              {
                v11 = *(_DWORD *)(v5 + 224);
                if ( (v11 & 0x200) != 0 )
                {
                  result = HalpInterruptGsiToLine(*(unsigned int *)(v5 + 88), &v20);
                  if ( (int)result < 0 )
                    return result;
                }
                else if ( (v11 & 0x100) != 0 )
                {
                  v12 = *(_DWORD *)(v5 + 84);
                  if ( v12 >= 8 )
                  {
                    LODWORD(v20) = 45057;
                    v12 -= 8;
                  }
                  else
                  {
                    LODWORD(v20) = 45056;
                  }
                  HIDWORD(v20) = v12;
                }
                v19 = *(_DWORD *)(v5 + 96);
                v21 = *(_DWORD *)(v5 + 92);
                HalpInterruptApplyOverrides(&v20, &v21, &v19);
                v6 = v19;
                v8 = v21;
                v22 = 0x8000000000000000uLL;
                LOBYTE(v22) = v20;
              }
              result = guard_dispatch_icall_no_overrides(*v7);
              if ( (int)result >= 0 )
              {
                if ( v18[0] )
                {
                  *(_DWORD *)(v5 + 236) = 0;
                  *(_DWORD *)(v5 + 232) = DWORD2(v28);
                  *(_QWORD *)(v5 + 240) = HIDWORD(v28);
                  v15 = *(_DWORD *)(v5 + 184) | 0x10;
LABEL_25:
                  HalpHypervisorHpet = v5;
                  *(_DWORD *)(v5 + 184) = v15 | 0x40;
                  return HalpTimerEnableHypervisorTimer();
                }
                v23[4] = -1;
                v25 = *((_QWORD *)&v28 + 1);
                v23[1] = 0;
                v24 = 8LL;
                v26 = 0LL;
                v27 = 212LL;
                v23[0] = v8;
                v23[2] = v6;
                v23[3] = 0;
                v23[5] = 1;
                v16 = HalpInterruptLookupController((unsigned int)v20, v13, 1LL, v14);
                if ( !v16 )
                  return HalpInterruptSetProblemEx(
                           0,
                           17,
                           v17,
                           (unsigned int)"minkernel\\hals\\lib\\interrupts\\common\\connect.c",
                           3268);
                result = HalpInterruptSetRemappedLineStateInternal(v16, &v20, v23);
                if ( (int)result >= 0 )
                {
                  v15 = *(_DWORD *)(v5 + 184) & 0xFFFFFFEF;
                  goto LABEL_25;
                }
              }
            }
          }
        }
      }
    }
  }
  return result;
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

