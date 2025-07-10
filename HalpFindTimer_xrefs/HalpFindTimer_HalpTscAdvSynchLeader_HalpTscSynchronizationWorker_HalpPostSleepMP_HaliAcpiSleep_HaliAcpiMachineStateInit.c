/* Call path: HalpFindTimer <- HalpTscAdvSynchLeader <- HalpTscSynchronizationWorker <- HalpPostSleepMP <- HaliAcpiSleep <- HaliAcpiMachineStateInit */

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

/* ===== Function: HalpTscAdvSynchLeader @ 0x140502740 ===== */
__int64 __fastcall HalpTscAdvSynchLeader(__int64 a1)
{
  __int64 Number; // r15
  unsigned int v3; // ebx
  int v4; // r9d
  __int64 TimeStamp; // r14
  unsigned int v6; // r10d
  __int64 v7; // rax
  unsigned int v8; // r10d
  __int64 v9; // r9
  unsigned int i; // esi
  unsigned __int64 v11; // r14
  __int64 Timer; // rax
  __int64 v13; // rsi
  __int64 result; // rax
  unsigned __int64 v15; // rdx
  unsigned int v16; // [rsp+60h] [rbp+30h] BYREF
  __int64 v17; // [rsp+68h] [rbp+38h] BYREF
  __int64 v18; // [rsp+70h] [rbp+40h] BYREF

  Number = KeGetCurrentPrcb()->Number;
  v3 = 0;
  TimeStamp = HalpTscAdvSynchReadTimeStamp(Number);
  if ( HalpTscRequestedSynchronization )
  {
    if ( !HalpTscRequestedIterations )
      HalpTscRequestedIterations = 500;
    if ( *(_BYTE *)(a1 + 34) )
    {
      HalpTscAdvSynchToLeader(*(unsigned int *)(a1 + 36));
    }
    else
    {
      v17 = 0LL;
      v18 = 0LL;
      v16 = KeGetCurrentPrcb()->Number;
      HalpTscAdvSynchCalculateRemoteDeltas((unsigned int)&v17, (unsigned int)&v18, (unsigned int)&v16, v4);
      if ( v16 != KeGetCurrentPrcb()->Number )
      {
        HalpTscAdvSynchReadTimeStamp((unsigned int)Number);
        LODWORD(Number) = v6;
        v7 = HalpTscAdvSynchReadTimeStamp(v6);
        TimeStamp = v7 - v9;
        HalpTscAdvSynchToTarget(v8);
      }
      for ( i = 0; i < *(_DWORD *)(a1 + 40); ++i )
      {
        if ( i != KeGetCurrentPrcb()->Number && i != v16 )
          HalpTscAdvSynchToLeader(i);
      }
    }
  }
  v17 = 0LL;
  v18 = 0LL;
  v16 = KeGetCurrentPrcb()->Number;
  HalpTscAdvSynchCalculateRemoteDeltas((unsigned int)&v17, (unsigned int)&v18, (unsigned int)&v16, v4);
  v11 = (unsigned __int64)(1000000 * (HalpTscAdvSynchReadTimeStamp((unsigned int)Number) - TimeStamp))
      / *(_QWORD *)KeGetPcr()->HalReserved;
  Timer = HalpFindTimer(5, 0, 0, 0, 1);
  v13 = Timer;
  HalpTscMaximumComputedSpread = v18 - v17;
  if ( v18 - v17 <= (unsigned __int64)(unsigned int)HalpTscMaximumCounterSyncSpread )
  {
    result = HalpTscTraceSynchronizationSummary(KeGetCurrentPrcb()->Number, v16, v18, v17, v11);
    *(_DWORD *)(v13 + 184) |= 0x20u;
  }
  else
  {
    *(_DWORD *)(Timer + 184) &= ~0x20u;
    HalpTscSynchronizationFailureFallback = 1;
    result = HalpTscTraceStatus(&HAL_ETW_EVENT_TIMER_SYNCH_FAILED);
  }
  if ( *(_DWORD *)(a1 + 40) )
  {
    do
    {
      result = (__int64)KeGetCurrentPrcb();
      if ( v3 != *(_DWORD *)(result + 36) )
      {
        v15 = (unsigned __int64)v3 << 7;
        _InterlockedExchange((volatile __int32 *)(v15 + TscRequest), 7);
        result = *(unsigned int *)(v15 + TscRequest);
        if ( (_DWORD)result == 7 )
        {
          do
          {
            _mm_pause();
            result = TscRequest;
          }
          while ( *(_DWORD *)(v15 + TscRequest) == 7 );
        }
      }
      ++v3;
    }
    while ( v3 < *(_DWORD *)(a1 + 40) );
  }
  return result;
}

/* ===== Function: HalpTscSynchronizationWorker @ 0x140503150 ===== */
__int64 __fastcall HalpTscSynchronizationWorker(ULONG_PTR Argument)
{
  _QWORD *v1; // rbp
  __int64 result; // rax
  __int64 v3; // rdx
  __int16 v4; // bx
  int v5; // ebx
  _WORD v6[148]; // [rsp+60h] [rbp-8h] BYREF

  v1 = (_QWORD *)((unsigned __int64)v6 & 0xFFFFFFFFFFFFFFC0uLL);
  *(_QWORD *)((unsigned __int64)v6 & 0xFFFFFFFFFFFFFFC0uLL) = Argument;
  result = (__int64)memset_0((void *)(((unsigned __int64)v6 & 0xFFFFFFFFFFFFFFC0uLL) + 64), 0, 0xC0uLL);
  v3 = *(_QWORD *)((unsigned __int64)v6 & 0xFFFFFFFFFFFFFFC0uLL);
  if ( *(_DWORD *)(v3 + 40) >= 2u )
  {
    if ( *(_DWORD *)(HalpPerformanceCounter + 228) == 5 )
    {
      v4 = v6[144];
      *(_QWORD *)(((unsigned __int64)KeGetCurrentPrcb()->Number << 7) + TscRequest + 16) = v1 + 16;
      _disable();
      v5 = v4 & 0x200;
      if ( _InterlockedExchangeAdd((volatile signed __int32 *)v3, 0xFFFFFFFF) != 1 )
      {
        do
          _mm_pause();
        while ( *(_DWORD *)v3 );
      }
      if ( KeGetCurrentPrcb()->Number == HalpTscRequestedLeadProcessor )
        result = HalpTscAdvSynchLeader(v3);
      else
        result = HalpTscAdvSynchTarget();
      if ( v5 )
        _enable();
    }
    else
    {
      return HalpTscCompatibilitySynchronization(*v1);
    }
  }
  return result;
}

/* ===== Function: HalpPostSleepMP @ 0x140b2f36c ===== */
__int64 __fastcall HalpPostSleepMP(int a1)
{
  char IsReferenceTscConfigured; // al
  char v2; // bl
  __int64 result; // rax
  __int64 i; // rdi
  __int64 v5; // rbx
  signed int Number; // [rsp+20h] [rbp-3F8h]
  int v7; // [rsp+28h] [rbp-3F0h] BYREF
  _BYTE v8[976]; // [rsp+30h] [rbp-3E8h] BYREF

  v7 = a1;
  Number = KeGetCurrentPrcb()->Number;
  if ( Number )
  {
    HalpInterruptReinitializeThisProcessor();
    while ( Number != HalpBarrier )
      _mm_pause();
    __writecr8(0xFuLL);
  }
  if ( (HalpFeatureBits & 0xC) != 0 )
    HalpMcaResumeProcessorConfig(0LL);
  if ( (HalpFeatureBits & 1) != 0 )
    HalpInterruptEnablePerformanceEvents(0LL);
  IsReferenceTscConfigured = HalpHvIsReferenceTscConfigured();
  v2 = IsReferenceTscConfigured;
  if ( !Number )
  {
    dword_140E3E7DC = 0;
    dword_140E3E788 = 0;
    dword_140E3E7C4 = v7 - 1;
    qword_140E3E7D0 = (__int64)&dword_140E3E788;
    if ( !IsReferenceTscConfigured )
      HalpTscInitializeSynchronizationContext(&Argument, 0LL, 0LL, &v7);
  }
  _InterlockedAdd(&HalpBarrier, 1u);
  while ( HalpBarrier != v7 )
    ;
  if ( !Number && HalpHvWheaEnlightenedCpuManager && HalpMceEnabled )
    HalpHvSetMachineCheckHandlerState();
  if ( !Number )
    HalpSetResumeTime(0LL, 1LL);
  HalpTimerMarkWake();
  HalpTimerRestoreProcessorCounter();
  if ( !Number )
  {
    SystemPowerPhase = 1;
    HalpSetResumeTime(0LL, 2LL);
    HalpInterruptRestoreClock();
    HalpHiberInProgress = 0;
    dword_140E3E7D8 = 0;
  }
  _InterlockedAdd(&dword_140E3E7DC, 1u);
  while ( dword_140E3E7DC != v7 )
    ;
  while ( dword_140E3E7D8 < Number )
    ;
  HalpMcUpdateMicrocode();
  HalpErrataApplyPerProcessor();
  _InterlockedAdd(&dword_140E3E7D8, 1u);
  while ( dword_140E3E7D8 != v7 )
    ;
  HalpRestartProfiling();
  HalpInterruptEnableNmi();
  KeLoadMTRR(&unk_140E3E7C0);
  if ( !v2 )
    HalpTscSynchronizationWorker((ULONG_PTR)&Argument);
  memset_0(v8, 0, 0x3CCuLL);
  result = (unsigned int)HalpFeatureBits;
  if ( (HalpFeatureBits & 0xC) != 0 )
  {
    result = (__int64)KeGetPcr();
    for ( i = *(_QWORD *)(result + 216); i; i = *(_QWORD *)(i + 184) )
    {
      v5 = *(_QWORD *)(i + 172);
      HalpMcaSetProcessorConfig(HalpMceErrorSource, v5);
      result = HalpIsCmciImplemented();
      if ( (_BYTE)result )
        result = HalpCmciInitProcessor(HalpCmcErrorSource, v5);
    }
  }
  return result;
}

/* ===== Function: HaliAcpiSleep @ 0x140523370 ===== */
__int64 __fastcall HaliAcpiSleep(unsigned int a1, __int64 a2, __int64 a3, int a4, volatile signed __int32 *a5)
{
  int v6; // r14d
  unsigned int v9; // r12d
  char v10; // r13
  volatile signed __int32 *v11; // rdi
  unsigned int v12; // ebx
  struct _KPRCB *v13; // rbx
  unsigned int Number; // eax
  unsigned int v15; // r14d
  unsigned int v16; // ebx
  int v17; // edi
  unsigned int v18; // eax
  unsigned int v19; // ebx
  __int64 v20; // rcx
  int v21; // ecx
  unsigned int v22; // ebx
  int v23; // esi
  __int64 v24; // rdx
  unsigned __int8 v25; // bl
  int v27; // ecx
  __int64 v28; // rcx
  unsigned int v29; // ebx
  unsigned int v30; // ebx
  char v31[4]; // [rsp+30h] [rbp-68h] BYREF
  _WORD v32[2]; // [rsp+34h] [rbp-64h] BYREF
  _WORD v33[2]; // [rsp+38h] [rbp-60h] BYREF
  _WORD v34[2]; // [rsp+3Ch] [rbp-5Ch] BYREF
  __int16 v35; // [rsp+40h] [rbp-58h] BYREF
  struct _KPRCB *CurrentPrcb; // [rsp+48h] [rbp-50h]
  __int64 CurrentIrql; // [rsp+50h] [rbp-48h]
  int v38; // [rsp+90h] [rbp-8h]
  char v39; // [rsp+A0h] [rbp+8h] BYREF
  int v40; // [rsp+B8h] [rbp+20h]

  v40 = a4;
  v6 = a4;
  v39 = 0;
  v33[0] = 0;
  v34[0] = 0;
  v32[0] = 0;
  v31[0] = 0;
  v35 = 0;
  CurrentIrql = KeGetCurrentIrql();
  v9 = 0;
  _disable();
  v10 = 0;
  v11 = a5;
  v12 = 0;
  v38 &= 0x200u;
  CurrentPrcb = KeGetCurrentPrcb();
  _InterlockedDecrement(a5);
  while ( *v11 )
  {
    if ( (++v12 & dword_140FC03BC) != 0 || !qword_140FC03C0 )
      _mm_pause();
    else
      guard_dispatch_icall_no_overrides(v12);
  }
  if ( HalpProfileInterface[6] )
    guard_dispatch_icall_no_overrides(0LL);
  HalpTimerSaveProcessorCounter();
  HalpTscOnWake = 0LL;
  if ( !KeGetPcr()->Prcb.Number )
    HalpTscRestoreValue = *(_QWORD *)HalpTimerSavedProcessorCounter;
  v13 = CurrentPrcb;
  Number = CurrentPrcb->Number;
  if ( !Number )
  {
    HalpResumeFromHibernate = 0;
    HalpBarrier = 0;
    HalpAcpiPreSleep(a1);
    if ( byte_140F8E2F0 )
      HalpAcpiPmRegisterRead(1, 0, (unsigned int)v34, 2, 0LL);
    if ( byte_140F8E380 )
      HalpAcpiPmRegisterRead(4, 0, (unsigned int)&v35, 2, 0LL);
    v15 = a1 >> 12;
    if ( ((a1 >> 12) & 2) != 0
      && (unsigned __int8)HalpSetupRealModeResume(HalpLowStub, (unsigned int)HalpLowStubPhysicalAddress) )
    {
      goto LABEL_69;
    }
    HalpInterruptProcessorRestarting = 1;
    _InterlockedIncrement(&HalpSaveStateSync);
    v16 = 0;
    v17 = v40;
    while ( HalpSaveStateSync != v17 )
    {
      if ( (++v16 & dword_140FC03BC) != 0 || !qword_140FC03C0 )
        _mm_pause();
      else
        guard_dispatch_icall_no_overrides(v16);
    }
    if ( a2 )
    {
      v18 = guard_dispatch_icall_no_overrides(a3);
      v9 = v18;
      if ( (HalpPlatformFlags & 1) != 0 || v18 != -1073741632 )
      {
        if ( v18 )
        {
          if ( v18 == 1073742484 )
            HalpResumeFromHibernate = 1;
          else
            HalpReenableAcpi();
          goto LABEL_69;
        }
      }
      else
      {
        v10 = 1;
      }
    }
    _InterlockedAdd(&HalpFlushBarrier, 1u);
    v19 = 0;
    while ( HalpFlushBarrier != v17 )
    {
      if ( (++v19 & dword_140FC03BC) != 0 || !qword_140FC03C0 )
        _mm_pause();
      else
        guard_dispatch_icall_no_overrides(v19);
    }
    _InterlockedOr(&HalpFlushBarrier, 0);
    HalpCheckWakeupTimeAndAdjust();
    HalpCheckLowMemoryPreSleep(a1);
    v32[0] = 0x8000;
    if ( PmRegisters )
      HalpAcpiPmRegisterWrite(0, 0, (unsigned int)v32, 2, 0LL);
    if ( byte_140F8E350 )
      HalpAcpiPmRegisterWrite(3, 0, (unsigned int)v32, 2, 0LL);
    v39 = -112;
    if ( (v15 & 0x40) != 0 )
      HalSetEnvironmentVariableEx(
        (unsigned int)L"SystemSleepCheckpoint",
        (unsigned int)SYSTEM_SLEEP_ETW_CHECKPOINT_GUID,
        (unsigned int)&v39,
        1,
        1);
    if ( (a1 & 0x1000) != 0 )
    {
      if ( CurrentPrcb->CpuVendor == 1 )
      {
        LOBYTE(v20) = 1;
        KeWriteProtectPAT(v20);
      }
      __wbinvd();
    }
    if ( HalpHvSleepEnlightenedCpuManager )
    {
      v21 = (a1 >> 8) & 0xF;
      if ( v21 == 1 || ((v21 - 2) & 0xFFFFFFFC) == 0 && v21 != 4 )
      {
        v9 = HalpHvEnterSleepState();
LABEL_73:
        v39 = -97;
        if ( (v15 & 0x40) != 0 )
          HalSetEnvironmentVariableEx(
            (unsigned int)L"SystemSleepCheckpoint",
            (unsigned int)SYSTEM_SLEEP_ETW_CHECKPOINT_GUID,
            (unsigned int)&v39,
            1,
            1);
        HalpSaveStateSync = 0;
        HalpFlushBarrier = 0;
        HalpAcpiPostSleep(a1);
        v6 = v40;
        goto LABEL_76;
      }
    }
    if ( (HalpPlatformFlags & 1) == 0 )
    {
      if ( v10 )
        HalReturnToFirmware(2LL);
      HalReturnToFirmware(1LL);
    }
    if ( byte_140F8E2F0 )
    {
      HalpAcpiPmRegisterRead(1, 0, (unsigned int)v33, 2, 0LL);
      v33[0] = v33[0] & 0x203 | ((a1 & 7 | 8) << 10);
      HalpAcpiPmRegisterWrite(1, 0, (unsigned int)v33, 2, 0LL);
    }
    if ( byte_140F8E380 )
    {
      HalpAcpiPmRegisterRead(4, 0, (unsigned int)v33, 2, 0LL);
      v33[0] = v33[0] & 0x203 | (((a1 >> 4) & 7 | 8) << 10);
      HalpAcpiPmRegisterWrite(4, 0, (unsigned int)v33, 2, 0LL);
    }
    v22 = 0;
    if ( PmRegisters )
    {
      v23 = byte_140F8E350 != 0 ? 3 : 0;
      while ( 1 )
      {
        HalpAcpiPmRegisterRead(0, 0, (unsigned int)v32, 2, 0LL);
        if ( (v32[0] & 0x8000) != 0 )
          break;
        HalpAcpiPmRegisterRead(v23, 0, (unsigned int)v32, 2, 0LL);
        if ( (v32[0] & 0x8000) != 0 )
          break;
        if ( (++v22 & dword_140FC03BC) != 0 || !qword_140FC03C0 )
          _mm_pause();
        else
          guard_dispatch_icall_no_overrides(v22);
      }
    }
LABEL_69:
    if ( byte_140F8E2F0 )
      HalpAcpiPmRegisterWrite(1, 0, (unsigned int)v34, 2, 0LL);
    if ( byte_140F8E380 )
      HalpAcpiPmRegisterWrite(4, 0, (unsigned int)&v35, 2, 0LL);
    goto LABEL_73;
  }
  if ( (a1 & 0x8000) != 0 )
    v27 = 0;
  else
    v27 = HalpHiberProcState + 1472 * Number;
  v9 = HaliSaveProcessorContextAndSleep(v27, a2, a3, v6, (__int64)v31);
  if ( v31[0] )
  {
    v29 = 0;
    while ( HalpFlushBarrier )
    {
      if ( (++v29 & dword_140FC03BC) != 0 || !qword_140FC03C0 )
        _mm_pause();
      else
        guard_dispatch_icall_no_overrides(v29);
    }
  }
  else
  {
    if ( v13->CpuVendor == 1 )
    {
      LOBYTE(v28) = 1;
      KeWriteProtectPAT(v28);
    }
    if ( !(unsigned __int8)HalpIsMicrosoftCompatibleHvLoaded() )
    {
      HalpFlushAndWait(&HalpFlushBarrier);
      goto LABEL_77;
    }
    v30 = 0;
    if ( _InterlockedIncrement(&HalpFlushBarrier) )
    {
      do
      {
        if ( (++v30 & dword_140FC03BC) != 0 || !qword_140FC03C0 )
          _mm_pause();
        else
          guard_dispatch_icall_no_overrides(v30);
      }
      while ( HalpFlushBarrier );
    }
  }
LABEL_76:
  v13 = CurrentPrcb;
LABEL_77:
  if ( ((a1 >> 12) & 0x10) == 0 && (a1 & 0x1000) != 0 && v13->CpuVendor == 1 )
  {
    KeWriteProtectPAT(0LL);
    __wbinvd();
  }
  HalpPostSleepMP(v6);
  v25 = CurrentIrql;
  if ( KiIrqlFlags )
  {
    LOBYTE(v24) = CurrentIrql;
    KiLowerIrqlProcessIrqlFlags(KeGetCurrentIrql(), v24);
  }
  __writecr8(v25);
  if ( v38 )
    _enable();
  return v9;
}

/* ===== Function: HaliAcpiMachineStateInit @ 0x1406d6ce0 ===== */
int __fastcall HaliAcpiMachineStateInit(_BYTE *a1)
{
  bool v2; // di
  int v3; // eax
  _DWORD *v4; // rdx
  __int64 (__fastcall *v5)(unsigned int, __int64, __int64, int, volatile signed __int32 *); // rax
  __int64 v6; // rcx
  __int64 v7; // rax
  __int64 v8; // rdx
  __int64 v9; // r8
  char v10; // cl
  int v11; // eax
  unsigned int v12; // eax
  __int64 v13; // rdx
  __int64 v14; // r8
  char v15; // cl
  int v16; // eax
  unsigned int v17; // eax
  __int64 v18; // rdx
  __int64 v19; // r8
  __int64 v20; // rcx
  unsigned __int64 v21; // rcx
  int v22; // ecx
  int v23; // eax
  unsigned int v24; // eax
  int v25; // ecx
  int v26; // eax
  unsigned int v27; // eax
  __int64 v28; // rdx
  __int64 v29; // r8
  __int128 InputBuffer; // [rsp+30h] [rbp-20h] BYREF
  __int64 v32; // [rsp+40h] [rbp-10h]

  v32 = 0LL;
  v2 = 0;
  InputBuffer = 0LL;
  HalpWakeupState = 1;
  v3 = HalpInterruptModel();
  *v4 = v3;
  if ( a1[9] && !HalpDisableHibernate )
    v2 = (unsigned __int8)HalpIsXboxNanovisorPresent() == 0;
  v5 = HaliAcpiSleep;
  if ( *a1 )
  {
    v6 = a1[2] & 0xF;
    *((_QWORD *)&InputBuffer + 1) = HaliAcpiSleep;
    v7 = a1[1] & 0xF;
    BYTE4(InputBuffer) = 1;
    v32 = v7 | (16 * (v6 | 0x510));
    ZwPowerInformation(SystemPowerStateHandler, &InputBuffer, 0x18u, 0LL, 0);
    if ( HalpHvSleepEnlightenedCpuManager )
    {
      LOBYTE(v9) = a1[2];
      LOBYTE(v8) = a1[1];
      HalpHvSetSleepStateProperty(1LL, v8, v9);
    }
    v5 = HaliAcpiSleep;
  }
  if ( !HalpWakeVector )
    goto LABEL_22;
  if ( a1[3] )
  {
    v10 = a1[4];
    *((_QWORD *)&InputBuffer + 1) = HaliAcpiSleep;
    v11 = a1[5] & 0xF;
    LODWORD(InputBuffer) = 1;
    BYTE4(InputBuffer) = 1;
    v12 = v10 & 0xF | (16 * (v11 | 0x520));
    if ( !HalpHvSleepEnlightenedCpuManager )
      v12 |= 0x12000u;
    v32 = v12;
    LODWORD(v5) = ZwPowerInformation(SystemPowerStateHandler, &InputBuffer, 0x18u, 0LL, 0);
    if ( HalpHvSleepEnlightenedCpuManager )
    {
      LOBYTE(v14) = a1[5];
      LOBYTE(v13) = a1[4];
      LODWORD(v5) = HalpHvSetSleepStateProperty(2LL, v13, v14);
    }
  }
  if ( !a1[6] )
    goto LABEL_22;
  v15 = a1[7];
  *((_QWORD *)&InputBuffer + 1) = HaliAcpiSleep;
  v16 = a1[8] & 0xF;
  LODWORD(InputBuffer) = 2;
  BYTE4(InputBuffer) = 1;
  v17 = v15 & 0xF | (16 * (v16 | 0x530));
  if ( !HalpHvSleepEnlightenedCpuManager )
    v17 |= 0x32000u;
  v32 = v17;
  LODWORD(v5) = ZwPowerInformation(SystemPowerStateHandler, &InputBuffer, 0x18u, 0LL, 0);
  if ( HalpHvSleepEnlightenedCpuManager )
  {
    LOBYTE(v19) = a1[8];
    LOBYTE(v18) = a1[7];
    LODWORD(v5) = HalpHvSetSleepStateProperty(3LL, v18, v19);
  }
  if ( a1[6] )
  {
    if ( !v2 )
      goto LABEL_26;
    v20 = a1[8] & 0xF | 0x3740LL;
    BYTE4(InputBuffer) = (unsigned __int8)dword_140FBFFB0 >> 7;
    v21 = a1[7] & 0xF | (unsigned __int64)(16 * v20);
    LODWORD(InputBuffer) = 6;
    v32 = v21;
    *((_QWORD *)&InputBuffer + 1) = HaliAcpiSleep;
    ZwPowerInformation(SystemPowerStateHandler, &InputBuffer, 0x18u, 0LL, 0);
  }
  else
  {
LABEL_22:
    if ( !v2 )
      goto LABEL_26;
  }
  v22 = a1[10] & 0xF;
  BYTE4(InputBuffer) = (unsigned __int8)dword_140FBFFB0 >> 7;
  v23 = a1[11] & 0xF;
  LODWORD(InputBuffer) = 3;
  *((_QWORD *)&InputBuffer + 1) = HaliAcpiSleep;
  v24 = v22 | (16 * (v23 | 0x540));
  if ( !HalpHvSecureCpuResume )
    v24 |= 0x10000u;
  v32 = v24;
  LODWORD(v5) = ZwPowerInformation(SystemPowerStateHandler, &InputBuffer, 0x18u, 0LL, 0);
LABEL_26:
  if ( !a1[12] )
  {
    if ( !HalFirmwareTypeEfi )
      goto LABEL_32;
    goto LABEL_31;
  }
  if ( (HalpPlatformFlags & 1) == 0 )
  {
LABEL_31:
    HalpShutdownContext = 0;
    v32 = 0LL;
    *(_QWORD *)&InputBuffer = 4LL;
    *((_QWORD *)&InputBuffer + 1) = HalpLegacyShutdown;
    LODWORD(v5) = ZwPowerInformation(SystemPowerStateHandler, &InputBuffer, 0x18u, 0LL, 0);
    goto LABEL_32;
  }
  v25 = a1[13] & 0xF;
  v26 = a1[14] & 0xF;
  LODWORD(InputBuffer) = 4;
  BYTE4(InputBuffer) = 0;
  v27 = v25 | (16 * (v26 | 0x850));
  *((_QWORD *)&InputBuffer + 1) = HaliAcpiSleep;
  v32 = v27;
  HalpShutdownContext = v27;
  LODWORD(v5) = ZwPowerInformation(SystemPowerStateHandler, &InputBuffer, 0x18u, 0LL, 0);
  if ( !HalpHvSleepEnlightenedCpuManager )
    return (int)v5;
  LOBYTE(v29) = a1[14];
  LOBYTE(v28) = a1[13];
  LODWORD(v5) = HalpHvSetSleepStateProperty(5LL, v28, v29);
LABEL_32:
  if ( HalpHvSleepEnlightenedCpuManager )
    LODWORD(v5) = HalpHvSetSleepStateProperty(6LL, 0LL, 0LL);
  return (int)v5;
}

