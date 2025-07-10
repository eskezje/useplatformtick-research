/* Function: HalpTimerMeasureProcessorsWorker @ 0x140505a50 (call depth 1) */

ULONG_PTR __fastcall HalpTimerMeasureProcessorsWorker(ULONG_PTR Argument)
{
  int v2; // ebx
  __int16 v3; // bp
  int v4; // ebp
  ULONG ActiveProcessorCount; // eax
  KPCR *Pcr; // r14
  ULONG v7; // esi
  ULONG_PTR *Timer; // rbx
  unsigned __int64 v9; // rcx
  int Latency; // esi
  unsigned __int64 v11; // rax
  __int64 v12; // r11
  unsigned __int64 v13; // r8
  unsigned __int64 v14; // rcx
  LARGE_INTEGER PerformanceFrequency; // [rsp+30h] [rbp-48h] BYREF
  int v17; // [rsp+70h] [rbp-8h]
  __int64 v18; // [rsp+80h] [rbp+8h] BYREF
  __int64 v19; // [rsp+88h] [rbp+10h] BYREF
  __int64 v20; // [rsp+90h] [rbp+18h] BYREF
  __int64 v21; // [rsp+98h] [rbp+20h] BYREF

  v18 = 0LL;
  v20 = 0LL;
  PerformanceFrequency.QuadPart = 0LL;
  v19 = 0LL;
  v21 = 0LL;
  v2 = *(_DWORD *)(Argument + 16);
  v3 = v17;
  _disable();
  v4 = v3 & 0x200;
  ActiveProcessorCount = KeQueryActiveProcessorCountEx(0xFFFFu);
  Pcr = KeGetPcr();
  v7 = ActiveProcessorCount;
  Timer = HalpFindTimer(v2, 0, 0, 0, 1);
  v9 = __readcr2();
  __writecr2(v9);
  if ( _InterlockedExchangeAdd((volatile signed __int32 *)Argument, 0xFFFFFFFF) != 1 )
  {
    do
      _mm_pause();
    while ( *(_DWORD *)Argument );
  }
  if ( KeGetCurrentPrcb()->Number )
  {
    while ( *(_DWORD *)(Argument + 4) != KeGetCurrentPrcb()->Number )
      _mm_pause();
    KeQueryPerformanceCounter(&PerformanceFrequency);
    Latency = HalpTimerDetermineValidTimerPairReadLatency(Timer, HalpPerformanceCounter);
    HalpTimerReadTimerPairWithLatencyLimit(
      Latency,
      (_DWORD)Timer,
      HalpPerformanceCounter,
      (unsigned int)&v19,
      (__int64)&v21);
    _InterlockedIncrement((volatile signed __int32 *)(Argument + 4));
    while ( *(_DWORD *)(Argument + 8) != KeGetCurrentPrcb()->Number )
      _mm_pause();
    HalpTimerReadTimerPairWithLatencyLimit(
      Latency,
      (_DWORD)Timer,
      HalpPerformanceCounter,
      (unsigned int)&v18,
      (__int64)&v20);
    _InterlockedIncrement((volatile signed __int32 *)(Argument + 8));
    do
      _mm_pause();
    while ( !*(_DWORD *)(Argument + 12) );
    v11 = HalpTimerScaleCounter(v20 - v21, PerformanceFrequency.QuadPart, 1000000LL);
    v13 = 1000000 * v12 / v11;
    *(_QWORD *)Pcr->HalReserved = 10000 * ((v13 + 5000) / 0x2710);
    v14 = 1000000 * ((v13 + 500000) / 0xF4240);
    Pcr->StallScaleFactor = v14 / 0xF4240;
    KeGetCurrentPrcb()->MHz = v14 / 0xF4240;
  }
  else
  {
    _InterlockedIncrement((volatile signed __int32 *)(Argument + 4));
    do
      _mm_pause();
    while ( *(_DWORD *)(Argument + 4) != v7 );
    KeStallExecutionProcessor(0x1E848u);
    _InterlockedIncrement((volatile signed __int32 *)(Argument + 8));
    do
      _mm_pause();
    while ( *(_DWORD *)(Argument + 8) != v7 );
    _InterlockedIncrement((volatile signed __int32 *)(Argument + 12));
  }
  if ( v4 )
    _enable();
  return 0LL;
}
