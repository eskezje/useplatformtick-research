/* Function: HaliAcpiSleep @ 0x140523370 (call depth 4) */

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
