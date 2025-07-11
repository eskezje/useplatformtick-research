__int64 __fastcall HalpTimerClockActivate(__int64 a1, __int64 a2, __int64 a3, int a4)
{
  int v4; // r8d
  int v5; // r9d
  __int64 result; // rax
  __int64 InternalData; // rax
  __int64 v8; // r8
  __int16 v9; // [rsp+30h] [rbp-8h]

  if ( (_BYTE)a1 )
  {
    HalpTimerPrepareClockInterrupt(a1, a2, a3, a4);
    _disable();
    LOBYTE(v4) = 13;
    result = HalpInterruptSetIdtEntry(209u, (int)HalpTimerClockInterrupt, v4, v5, -3LL);
    if ( (v9 & 0x200) != 0 )
      _enable();
  }
  else
  {
    result = *(unsigned int *)(HalpClockTimer + 0xE0);
    if ( (result & 1) != 0 && (result & 0x800) != 0 )
    {
      InternalData = HalpTimerGetInternalData(HalpClockTimer);
      return ((__int64 (__fastcall *)(__int64, __int64, __int64))guard_dispatch_icall_no_overrides)(
               InternalData,
               209LL,
               v8);
    }
  }
  return result;
}