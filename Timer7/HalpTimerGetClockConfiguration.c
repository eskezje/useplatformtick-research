__int64 __fastcall HalpTimerGetClockConfiguration(__int64 a1)
{
  ULONG_PTR v1; // r9
  _DWORD *v3; // rdx
  char v4; // cl
  __int64 *v5; // rbx
  __int64 result; // rax

  v1 = HalpClockTimer;
  *(_OWORD *)a1 = 0LL;
  *(_OWORD *)(a1 + 16) = 0LL;
  v3 = (_DWORD *)(v1 + 0xE0);
  if ( *(_DWORD *)(v1 + 0xE4) == 8 || (v4 = 0, (*v3 & 1) == 0) )
  {
    v4 = 2;
    *(_BYTE *)a1 = 2;
  }
  if ( (*v3 & 1) != 0 )
  {
    v4 |= 4u;
    *(_BYTE *)a1 = v4;
  }
  if ( HalpAlwaysOnTimer )
  {
    v4 |= 1u;
    *(_BYTE *)a1 = v4;
  }
  if ( (*v3 & 0x20) != 0 )
    *(_BYTE *)a1 = v4 | 8;
  v5 = (__int64 *)(a1 + 16);
  *(_DWORD *)(a1 + 4) = *(_DWORD *)(v1 + 0xE4);
  *(_DWORD *)(a1 + 8) = *v3;
  result = HalpTimerGetClockRates(v1, (unsigned __int64 *)(a1 + 16), (_DWORD *)(a1 + 0x18));
  if ( !HalpTimerMaxIncrement )
  {
    result = *v5;
    HalpTimerMaxIncrement = *v5;
  }
  return result;
}