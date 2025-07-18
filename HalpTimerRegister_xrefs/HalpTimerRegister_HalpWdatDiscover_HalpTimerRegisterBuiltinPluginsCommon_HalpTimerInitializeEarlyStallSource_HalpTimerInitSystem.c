/* Call path: HalpTimerRegister <- HalpWdatDiscover <- HalpTimerRegisterBuiltinPluginsCommon <- HalpTimerInitializeEarlyStallSource <- HalpTimerInitSystem */

/* ===== Function: HalpTimerRegister @ 0x140519b7c ===== */
__int64 __fastcall HalpTimerRegister(__int64 a1, UNICODE_STRING *p_DestinationString, __int64 a3)
{
  unsigned int v3; // ebx
  int v6; // ecx
  __int64 v7; // rdx
  __int64 v8; // rcx
  unsigned int MaximumProcessorCount; // r12d
  unsigned int v10; // ebp
  unsigned int v11; // r14d
  void *MemoryInternal; // rax
  __int64 v13; // rsi
  unsigned __int64 v14; // r14
  unsigned __int64 v15; // rcx
  __int128 v16; // xmm0
  unsigned int i; // ebp
  __int64 v18; // rcx
  __int64 *v19; // rax
  UNICODE_STRING DestinationString; // [rsp+20h] [rbp-F8h] BYREF
  WCHAR SourceString[80]; // [rsp+30h] [rbp-E8h] BYREF

  v3 = 0;
  DestinationString = 0LL;
  if ( !HalpTimerRegistrationAllowed )
    return 0xC0000189;
  if ( *(_DWORD *)a1 != 1 )
    return 0xC000000D;
  if ( *(_DWORD *)(a1 + 4) != 144 )
    return 0xC000000D;
  v6 = *(_DWORD *)(a1 + 116);
  if ( (v6 & 0xFE000000) != 0
    || (v6 & 0x400000) != 0
    || !*(_DWORD *)(a1 + 136)
    || (v6 & 0x400) != 0 && !*(_QWORD *)(a1 + 56) )
  {
    return 0xC000000D;
  }
  if ( (v6 & 0x1000) != 0 || (v6 & 0x80u) != 0 )
    return 0xC00000BB;
  v7 = 2048LL;
  if ( (v6 & 0x800) != 0 && !*(_QWORD *)(a1 + 72) )
    return 0xC000000D;
  if ( (v6 & 0x801) == 0x800 )
    return 0xC00000BB;
  if ( (v6 & 0xF00) != 0 && !*(_QWORD *)(a1 + 40) )
    return 0xC000000D;
  if ( (v6 & 2) != 0 && !*(_QWORD *)(a1 + 16) )
    return 0xC000000D;
  v8 = v6 & 0x10001;
  if ( (_DWORD)v8 == 0x10000 )
    return 0xC000000D;
  if ( !p_DestinationString )
  {
    HalpTimerBuildKnownResourceIdString(a1, 75, SourceString);
    p_DestinationString = &DestinationString;
    RtlInitUnicodeString(&DestinationString, SourceString);
  }
  if ( (*(_DWORD *)(a1 + 116) & 0x10000) != 0 )
  {
    MaximumProcessorCount = ((__int64 (__fastcall *)(__int64, __int64))HalQueryMaximumProcessorCount)(v8, v7);
    v10 = (*(_DWORD *)(a1 + 0x60) + 7) & 0xFFFFFFF8;
  }
  else
  {
    v10 = *(_DWORD *)(a1 + 0x60);
    MaximumProcessorCount = 1;
  }
  v11 = (((MaximumProcessorCount * v10 + 351) & 0xFFFFFFF8) + 9 + p_DestinationString->Length) & 0xFFFFFFF8;
  MemoryInternal = (void *)((__int64 (__fastcall *)(_QWORD, __int64, __int64))HalpMmAllocateMemoryInternal)(
                             v11,
                             1LL,
                             a3);
  v13 = (__int64)MemoryInternal;
  if ( MemoryInternal )
  {
    memset_0(MemoryInternal, 0, v11);
    v14 = (v13 + 0x12F) & 0xFFFFFFFFFFFFFFF8uLL;
    *(_QWORD *)(v13 + 288) = v14;
    v15 = (v14 + 0x37) & 0xFFFFFFFFFFFFFFF8uLL;
    *(_QWORD *)(v13 + 0x48) = v15;
    *(_QWORD *)(v14 + 0x20) = (MaximumProcessorCount * v10 + v15 + 7) & 0xFFFFFFFFFFFFFFF8uLL;
    *(_QWORD *)(v13 + 0xC0) = *(_QWORD *)(a1 + 0x68);
    *(_OWORD *)(v13 + 0x68) = *(_OWORD *)(a1 + 8);
    *(_OWORD *)(v13 + 0x78) = *(_OWORD *)(a1 + 0x18);
    *(_OWORD *)(v13 + 0x88) = *(_OWORD *)(a1 + 0x28);
    *(_OWORD *)(v13 + 0x98) = *(_OWORD *)(a1 + 0x38);
    v16 = *(_OWORD *)(a1 + 0x48);
    *(_DWORD *)(v13 + 0x50) = v10;
    *(_OWORD *)(v13 + 0xA8) = v16;
    *(_DWORD *)(v13 + 0xDC) = *(_DWORD *)(a1 + 0x64);
    *(_DWORD *)(v13 + 0xE0) = *(_DWORD *)(a1 + 0x74);
    *(_DWORD *)(v13 + 0x54) = *(_DWORD *)(a1 + 0x78);
    *(_DWORD *)(v13 + 0x58) = *(_DWORD *)(a1 + 0x7C);
    *(_DWORD *)(v13 + 0x60) = *(_DWORD *)(a1 + 0x84);
    *(_DWORD *)(v13 + 0x5C) = *(_DWORD *)(a1 + 0x80);
    *(_DWORD *)(v13 + 0xE4) = *(_DWORD *)(a1 + 0x88);
    *(_DWORD *)(v13 + 0xD8) = *(_DWORD *)(a1 + 0x70);
    if ( *(_DWORD *)(a1 + 0x60) )
    {
      if ( *(_QWORD *)(a1 + 88) )
      {
        for ( i = 0; i < MaximumProcessorCount; ++i )
          memmove(
            (void *)(*(_QWORD *)(v13 + 72) + *(_DWORD *)(v13 + 80) * i),
            *(const void **)(a1 + 0x58),
            *(unsigned int *)(a1 + 0x60));
      }
    }
    *(_DWORD *)(v13 + 0x11C) = *(_DWORD *)(a1 + 140);
    *(_WORD *)(v14 + 0x18) = 0;
    *(_WORD *)(v14 + 26) = p_DestinationString->Length + 2;
    RtlCopyUnicodeString((PUNICODE_STRING)(v14 + 0x18), p_DestinationString);
    if ( (*(_DWORD *)(a1 + 116) & 0x400) != 0 )
    {
      *(_QWORD *)(v14 + 12) = 0LL;
      *(_DWORD *)(v14 + 8) = 0;
      *(_DWORD *)v14 = 0;
      *(_DWORD *)(v14 + 4) = 0;
      if ( *(_DWORD *)(a1 + 0x88) == 3 )
      {
        LOBYTE(v18) = *(_BYTE *)(a1 + 142);
        ((void (__fastcall *)(__int64, unsigned __int64, unsigned __int64))HalpPciGetHpetInterruptSource)(
          v18,
          v14 + 8,
          (v13 + 0x12F) & 0xFFFFFFFFFFFFFFF8uLL);
      }
    }
    v19 = (__int64 *)qword_140FC2588;
    if ( *(ULONG_PTR **)qword_140FC2588 != &HalpRegisteredTimers )
      __fastfail(3u);
    LODWORD(HalpRegisteredTimerCount) = HalpRegisteredTimerCount + 1;
    *(_QWORD *)v13 = &HalpRegisteredTimers;
    *(_QWORD *)(v13 + 8) = v19;
    *v19 = v13;
    qword_140FC2588 = v13;
    if ( (*(_DWORD *)(v13 + 0xE0) & 0x100000) != 0 )
      HalpTimerAuxiliaryClockEnabled = 1;
  }
  else
  {
    return 0xC000009A;
  }
  return v3;
}

/* ===== Function: HalpWdatDiscover @ 0x140518e18 ===== */
__int64 HalpWdatDiscover()
{
  __int64 AcpiTable; // rbx
  __int64 v1; // rcx
  __int64 v2; // rax
  int v3; // ecx
  __int64 v4; // rdi
  char v5; // si
  unsigned int v6; // r15d
  unsigned int v7; // r8d
  unsigned int v8; // r12d
  int v9; // r14d
  unsigned __int64 i; // rdx
  int v11; // eax
  int v12; // edx
  int v13; // ecx
  __int64 v14; // r8
  unsigned __int64 v15; // rcx
  int v17; // [rsp+38h] [rbp-D0h] BYREF
  int v18; // [rsp+3Ch] [rbp-CCh] BYREF
  int v19; // [rsp+40h] [rbp-C8h] BYREF
  __int64 v20; // [rsp+48h] [rbp-C0h] BYREF
  _QWORD v21[11]; // [rsp+50h] [rbp-B8h] BYREF
  int v22; // [rsp+A8h] [rbp-60h]
  int v23; // [rsp+ACh] [rbp-5Ch]
  __int64 v24; // [rsp+B0h] [rbp-58h]
  int v25; // [rsp+BCh] [rbp-4Ch]
  int v26; // [rsp+D0h] [rbp-38h]
  int v27; // [rsp+D4h] [rbp-34h]
  _BYTE v28[8]; // [rsp+D8h] [rbp-30h] BYREF
  __int64 v29; // [rsp+E0h] [rbp-28h]
  unsigned int v30; // [rsp+E8h] [rbp-20h]
  unsigned int v31; // [rsp+ECh] [rbp-1Ch]
  unsigned int v32; // [rsp+F0h] [rbp-18h]
  __int128 v33; // [rsp+148h] [rbp+40h] BYREF

  v19 = 0;
  v18 = 0;
  memset_0(v21, 0, 0x88uLL);
  memset_0(v28, 0, 0x70uLL);
  v20 = 0x9000000001LL;
  v33 = 0LL;
  AcpiTable = 0LL;
  LOBYTE(v17) = 0;
  if ( !(unsigned __int8)HalpIsMicrosoftCompatibleHvLoaded(v1)
    || !HalpHvCpuManager
    || (HviGetHardwareFeatures(&v33), (v33 & 0x2000000) == 0) )
  {
    AcpiTable = HalSocGetAcpiTable(1413563479LL);
  }
  v2 = HalSocGetAcpiTable(1414677591LL);
  v4 = v2;
  if ( AcpiTable )
  {
    if ( (*(_BYTE *)(AcpiTable + 60) & 1) != 0 )
    {
      v5 = 1;
      v6 = *(_DWORD *)(AcpiTable + 52);
      v7 = *(_DWORD *)(AcpiTable + 56);
      v8 = *(_DWORD *)(AcpiTable + 48);
      v9 = (*(_DWORD *)(AcpiTable + 64) << 6) + 112;
      for ( i = 0LL; (unsigned int)i < *(_DWORD *)(AcpiTable + 64); i = (unsigned int)(i + 1) )
      {
        v3 = 3 * i;
        if ( *(_BYTE *)(AcpiTable + 24 * i + 68) == 6 )
          goto LABEL_15;
      }
      goto LABEL_28;
    }
    return 0LL;
  }
  if ( !v2 )
    return 0LL;
  v29 = v2;
  v11 = HalpWdatProcessWdrtInternalData(v2, v28, &v18, &v17);
  v5 = v17;
  if ( v11 >= 0 )
  {
    if ( !(_BYTE)v17 )
      return 0LL;
    v8 = v32;
    v7 = v31;
    v6 = v30;
    v9 = v18;
LABEL_15:
    if ( v8 && v6 >= v7 )
    {
      v25 = 163872;
      LOBYTE(v3) = 32;
      if ( (int)HalpWdatExecuteActionBeforeInitialize(v3, i, (unsigned int)&v19, AcpiTable, v4) >= 0 && v19 == 1 )
      {
        v25 = 426016;
        LOBYTE(v13) = 33;
        HalpWdatExecuteActionBeforeInitialize(v13, v12, 0, AcpiTable, v4);
      }
      v15 = v8 * (unsigned __int64)v6 / 0x3E8;
      if ( v15 > 0x12C436C73CE5LL )
      {
        v23 = 64;
LABEL_26:
        v21[2] = 0LL;
        v21[10] = 0LL;
        v27 = 0;
        v21[0] = HalpWdatInitialize;
        v21[3] = HalpWdatArmTimer;
        v21[4] = HalpWdatStop;
        v24 = 894000LL;
        v22 = v9;
        v26 = 13;
        HalpTimerRegister((__int64)&v20, 0LL, v14);
        goto LABEL_27;
      }
      i = 894000 * v15;
      v3 = 63;
      v23 = 63;
      do
      {
        if ( (1LL << v3) - 1 < i )
          break;
        --v3;
      }
      while ( v3 );
      v23 = v3;
      if ( v3 )
        goto LABEL_26;
    }
  }
LABEL_27:
  if ( v5 )
  {
LABEL_28:
    LOBYTE(v3) = 11;
    HalpWdatExecuteActionBeforeInitialize(v3, i, 0, AcpiTable, v4);
  }
  return 0LL;
}

/* ===== Function: HalpTimerRegisterBuiltinPluginsCommon @ 0x140501f84 ===== */
__int64 __fastcall HalpTimerRegisterBuiltinPluginsCommon(int a1)
{
  __int64 result; // rax
  int v2; // ecx

  if ( !a1 )
    return HalpTscDiscover();
  if ( a1 != 1 )
    return 0LL;
  result = HalpPmTimerDiscover();
  if ( (int)result >= 0 )
  {
    result = HalpHpetDiscover();
    if ( (int)result >= 0 )
    {
      result = HalpApicTimerDiscover();
      if ( (int)result >= 0 )
      {
        result = HalpArtDiscover();
        if ( (int)result >= 0 )
        {
          result = HalpHvWatchdogDiscover();
          if ( (int)result >= 0 )
          {
            result = HalpHvDiscover(v2);
            if ( (int)result >= 0 )
              return HalpWdatDiscover();
          }
        }
      }
    }
  }
  return result;
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

