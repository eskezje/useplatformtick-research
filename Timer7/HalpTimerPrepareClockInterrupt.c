__int64 __fastcall HalpTimerPrepareClockInterrupt(__int64 a1, __int64 a2, __int64 a3, int a4)
{
  unsigned int Number; // eax
  ULONG_PTR v5; // rbx
  unsigned int v6; // ecx
  __int64 result; // rax
  __int128 v8; // [rsp+40h] [rbp-18h] BYREF

  Number = KeGetPcr()->Prcb.Number;
  v5 = HalpClockTimer;
  v8 = 0LL;
  v6 = *((_DWORD *)KiGlobalState + Number);
  *((_QWORD *)&v8 + 1) = (unsigned __int16)(v6 >> 6);
  *(_QWORD *)&v8 = 1LL << (v6 & 0x3F);
  result = HalpTimerConfigureInterrupt(
             (unsigned int)HalpClockTimer,
             0xD1u,
             13,
             a4,
             -3LL,
             0,
             &v8,
             (__int64)HalpTimerClockInterruptStub);
  if ( (int)result < 0 )
    KeBugCheckEx(0x5Cu, 0x110uLL, v5, HalpTimerLastProblem, (int)result);
  return result;
}