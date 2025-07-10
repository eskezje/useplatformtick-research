/* Function: HalpInitializeTimers @ 0x1404f3950 (call depth 1) */

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
