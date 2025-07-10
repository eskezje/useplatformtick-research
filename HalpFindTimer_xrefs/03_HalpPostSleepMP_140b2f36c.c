/* Function: HalpPostSleepMP @ 0x140b2f36c (call depth 3) */

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
