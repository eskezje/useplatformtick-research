/* Call path: HalpHpetSetMatchValue <- HalpHpetAcknowledgeInterrupt <- HalpHpetDiscover <- HalpTimerRegisterBuiltinPluginsCommon <- HalpInitializeTimers <- HalpTimerInitSystem */

/* ===== Function: HalpHpetSetMatchValue @ 0x14046fdac ===== */
__int64 __fastcall HalpHpetSetMatchValue(int *a1, int a2, char a3)
{
  unsigned int v3; // edi
  __int64 v4; // r13
  char v5; // r10
  __int64 v6; // r15
  unsigned int v7; // r8d
  unsigned int v9; // ebp
  unsigned int *v10; // r14
  int *v11; // rdx
  unsigned int v13; // ebx
  int v14; // r12d
  __int64 result; // rax
  unsigned int v16; // ebx
  unsigned int v17; // ebx
  signed __int32 v18[22]; // [rsp+0h] [rbp-58h] BYREF
  unsigned int v19; // [rsp+60h] [rbp+8h]
  int *v21; // [rsp+78h] [rbp+20h]

  v3 = 0;
  v4 = HalpHpetBaseAddress;
  v5 = a3;
  v6 = 32LL * *a1;
  v7 = a1[4];
  v19 = v7;
  v9 = 10;
  v10 = (unsigned int *)(HalpHpetBaseAddress + 0x20 * (*a1 + 8LL));
  v11 = a1 + 2;
  v13 = 0;
  do
  {
    v21 = v11;
    v14 = v7 + a2;
    if ( !v5 )
    {
      v11 = a1 + 2;
      v21 = a1 + 2;
      v16 = *v10 & 0xFFFFFEB1 | 0x14C;
      if ( a1[2] != 2 )
        v16 = *v10 & 0xFFFFFEB1 | 0x104;
      v17 = ((a1[1] & 0x1F) << 9) | v16 & 0xFFFF81FF;
      *v10 = v17;
      _InterlockedOr(v18, 0);
      v13 = v17 & 0xFFFFFFBF;
    }
    *(_DWORD *)(v6 + v4 + 264) = v14;
    _InterlockedOr(v18, 0);
    if ( v5 )
    {
      v11 = a1 + 2;
    }
    else
    {
      if ( *v11 == 2 )
      {
        if ( !*((_BYTE *)a1 + 12) )
        {
          HalSetTimerProblem((__int64)a1, 2, 0);
          v11 = v21;
          v7 = v19;
          v5 = a3;
        }
        v13 |= 8u;
        *v10 = v13;
        _InterlockedOr(v18, 0);
        *(_DWORD *)(v6 + v4 + 264) = a1[4];
        _InterlockedOr(v18, 0);
        *v10 = v13;
        _InterlockedOr(v18, 0);
        *(_DWORD *)(v6 + v4 + 264) = a1[4];
        _InterlockedOr(v18, 0);
        *(_DWORD *)(v6 + v4 + 264) = a1[4];
      }
      else
      {
        *v10 = v13;
      }
      _InterlockedOr(v18, 0);
      a1[8] = v13;
    }
    a2 = *(_DWORD *)(HalpHpetBaseAddress + 0xF0);
    if ( v14 - a2 <= v7
      && v14 - a2 >= (unsigned int)HalpHpetComparatorLatchDelay
      && *(_DWORD *)(v6 + v4 + 264) != 2 * v14 )
    {
      break;
    }
    v7 = 1 << v9++;
    v19 = v7;
  }
  while ( v9 < 31 );
  if ( v9 != 10 )
  {
    if ( v9 == 31 )
    {
      HalSetTimerProblem((__int64)a1, 6, 0);
      v3 = 0xC0000001;
    }
    ++HalpHpetDebugTimerArm[v9 - 10];
  }
  result = v3;
  a1[5] = v14;
  return result;
}

/* ===== Function: HalpHpetAcknowledgeInterrupt @ 0x140475290 ===== */
void __fastcall HalpHpetAcknowledgeInterrupt(__int64 a1)
{
  if ( *(_DWORD *)(a1 + 8) == 1 )
  {
    HalpHpetSetMatchValue((int *)a1, *(_DWORD *)(a1 + 20), 1);
  }
  else if ( *(_DWORD *)(a1 + 8) == 2 && !*(_BYTE *)(a1 + 12) )
  {
    HalSetTimerProblem(a1, 2, 0);
  }
}

/* ===== Function: HalpHpetDiscover @ 0x14051a358 ===== */
__int64 HalpHpetDiscover()
{
  __int64 AcpiTable; // rax
  __int64 v1; // rdx
  __int64 v2; // r14
  unsigned int *v3; // r15
  unsigned int v4; // esi
  unsigned int v5; // ebx
  unsigned __int64 v6; // rax
  int v7; // r12d
  int v8; // esi
  bool v9; // zf
  unsigned int v10; // esi
  unsigned int v11; // r13d
  __int64 v12; // rbx
  unsigned int *v13; // r15
  __int64 v14; // r8
  int v15; // eax
  unsigned int v16; // ebx
  int v17; // edi
  unsigned __int8 v18; // dl
  int v19; // eax
  char v20; // cl
  int v21; // r9d
  __int64 v22; // r8
  signed __int32 v24[8]; // [rsp+8h] [rbp-100h] BYREF
  int v25; // [rsp+28h] [rbp-E0h] BYREF
  unsigned int v26; // [rsp+30h] [rbp-D8h]
  __int64 v27; // [rsp+38h] [rbp-D0h] BYREF
  __int64 (__fastcall *v28)(); // [rsp+40h] [rbp-C8h]
  __int64 (__fastcall *v29)(); // [rsp+48h] [rbp-C0h]
  __int64 (__fastcall *v30)(); // [rsp+50h] [rbp-B8h]
  __int64 (__fastcall *v31)(); // [rsp+58h] [rbp-B0h]
  __int64 (__fastcall *v32)(); // [rsp+60h] [rbp-A8h]
  _OWORD *v33; // [rsp+90h] [rbp-78h]
  int v34; // [rsp+98h] [rbp-70h]
  int v35; // [rsp+9Ch] [rbp-6Ch]
  __int64 v36; // [rsp+A0h] [rbp-68h]
  int v37; // [rsp+A8h] [rbp-60h]
  int v38; // [rsp+ACh] [rbp-5Ch]
  int v39; // [rsp+B0h] [rbp-58h]
  int v40; // [rsp+B4h] [rbp-54h]
  int v41; // [rsp+B8h] [rbp-50h]
  int v42; // [rsp+BCh] [rbp-4Ch]
  int v43; // [rsp+C0h] [rbp-48h]
  int v44; // [rsp+C4h] [rbp-44h]
  __int64 v45; // [rsp+C8h] [rbp-40h]
  unsigned int *v46; // [rsp+D0h] [rbp-38h]
  unsigned __int64 v47; // [rsp+D8h] [rbp-30h]
  _OWORD v48[2]; // [rsp+E0h] [rbp-28h] BYREF
  __int64 v49; // [rsp+100h] [rbp-8h]

  LOWORD(v25) = 0;
  memset(v48, 0, sizeof(v48));
  v49 = 0LL;
  AcpiTable = HalSocGetAcpiTable(1413828680LL);
  v2 = AcpiTable;
  if ( AcpiTable )
  {
    if ( !*(_BYTE *)(AcpiTable + 40) && (int)HalSocRequestConfigurationData(1LL, v1, (char *)&v25 + 1) >= 0 )
    {
      HalpHpetPhysicalAddress = *(LARGE_INTEGER *)(v2 + 44);
      if ( !HalpHpetPhysicalAddress.HighPart || BYTE1(v25) )
      {
        v46 = (unsigned int *)HalMapIoSpace(HalpHpetPhysicalAddress, 0x400uLL, MmNonCached);
        v3 = v46;
        if ( v46 )
        {
          if ( HalRegisterPermanentAddressUsage(HalpHpetPhysicalAddress, 0x400u) >= 0 )
          {
            v4 = *v3;
            v5 = HIWORD(*v3);
            if ( v5 )
            {
              if ( v5 != 0xFFFF )
              {
                HalpHpetComparatorLatchDelay = 2;
                if ( RtlCompareMemory((const void *)(v2 + 10), "VMWARE", 6uLL) == 6 )
                  HalpHpetComparatorLatchDelay = 1;
                if ( (v4 & 0x8000) != 0 )
                  HalpHpetLegacyInterrupts = 1;
                v6 = (((unsigned __int64)v3[1] >> 1) + 1000000000000000LL) / v3[1];
                v47 = v6;
                if ( v5 == 0x10DE )
                {
                  HalpHpetLegacyInterrupts = 0;
                  goto LABEL_43;
                }
                v7 = 1;
                v8 = (v4 >> 8) & 0x1F;
                v9 = v8 == -1;
                v10 = v8 + 1;
                v11 = 0;
                if ( !v9 )
                {
                  v12 = (unsigned int)v6;
                  v13 = v3 + 64;
                  v45 = (unsigned int)v6;
                  while ( 1 )
                  {
                    memset_0(&v27, 0, 0x90uLL);
                    v33 = v48;
                    v49 = 0LL;
                    v28 = (__int64 (__fastcall *)())HalpHpetInitialize;
                    v36 = v12;
                    v30 = HalpHpetAcknowledgeInterrupt;
                    memset((char *)v48 + 4, 0, 20);
                    v27 = 0x9000000001LL;
                    v31 = HalpHpetArmTimer;
                    v32 = HalpHpetStop;
                    v15 = (v11 + 1) | (*(unsigned __int8 *)(v2 + 52) << 16);
                    LODWORD(v48[0]) = v11;
                    v44 = v15;
                    *((LARGE_INTEGER *)&v48[1] + 1) = HalpHpetPhysicalAddress;
                    v16 = *v13 & 0xFFFFBFFB;
                    v35 = 31;
                    v34 = 40;
                    v42 = 1;
                    v41 = 1;
                    v43 = 3;
                    v37 = 1;
                    v38 = 48;
                    *v13 = v16;
                    v26 = v11 + 1;
                    _InterlockedOr(v24, 0);
                    if ( (v16 & 0x10) != 0 )
                    {
                      v17 = 112;
                      BYTE12(v48[0]) = 1;
                      v38 = 112;
                    }
                    else
                    {
                      v17 = v38;
                    }
                    if ( (v16 & 0x20) != 0 )
                    {
                      *v13 = v16 | 0x100;
                      _InterlockedOr(v24, 0);
                      v16 = *v13;
                      if ( (*v13 & 0x100) == 0 )
                        goto LABEL_41;
                      v17 = v38;
                    }
                    v18 = 0;
                    LODWORD(v49) = v16;
                    if ( HalpHpetLegacyInterrupts )
                    {
                      v19 = HalSocRequestConfigurationData(2LL, 0LL, &v25);
                      v20 = v25;
                      if ( v19 < 0 )
                        v20 = 0;
                      LOBYTE(v25) = v20;
                      if ( !v11 )
                      {
                        v17 |= 0x100u;
                        v38 = v17;
                        v39 = v20 == 0 ? 2 : 0;
                        v7 |= 4u;
                        goto LABEL_39;
                      }
                      if ( v11 == 1 )
                      {
                        v39 = 8;
                        v17 |= 0x100u;
                        v38 = v17;
                        v7 |= 0x100u;
LABEL_39:
                        if ( (v17 & 0xF00) != 0 )
                          HalpTimerRegister((__int64)&v27, 0LL, v14);
                        goto LABEL_41;
                      }
                      if ( (v16 & 0x8000) != 0 )
                        goto LABEL_39;
                    }
                    else
                    {
                      v21 = ~v7 & v13[1];
                      if ( v21 )
                      {
                        while ( v18 < 0x20u )
                        {
                          v14 = (unsigned int)(1 << v18);
                          if ( ((unsigned int)v14 & v21) != 0 )
                          {
                            LOWORD(v17) = v38 | 0x200;
                            v38 |= 0x200u;
                            v40 = v18 + (unsigned __int16)HalpHpetGsiOffset;
                            v7 |= v14;
                            BYTE4(v48[0]) = v18;
                            goto LABEL_39;
                          }
                          ++v18;
                        }
                        LOWORD(v17) = v38;
                        goto LABEL_39;
                      }
                    }
LABEL_41:
                    v11 = v26;
                    v13 += 8;
                    v12 = v45;
                    if ( v26 >= v10 )
                    {
                      v3 = v46;
                      break;
                    }
                  }
                }
LABEL_43:
                memset_0(&v27, 0, 0x90uLL);
                v27 = 0x9000000001LL;
                v49 = 0LL;
                v36 = (unsigned int)v47;
                memset(v48, 0, sizeof(v48));
                LODWORD(v48[0]) = -1;
                v33 = v48;
                v28 = (__int64 (__fastcall *)())HalpHpetInitialize;
                v29 = HalpHpetQueryCounter;
                v30 = HalpHpetAcknowledgeInterrupt;
                v31 = HalpHpetArmTimer;
                v44 = *(unsigned __int8 *)(v2 + 52) << 16;
                v35 = 32;
                v34 = 40;
                v43 = 3;
                v37 = 1;
                v38 = 2;
                HalpTimerRegister((__int64)&v27, 0LL, v22);
              }
            }
          }
          HalpUnmapVirtualAddress(v3, 1LL, 0LL);
        }
      }
    }
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

