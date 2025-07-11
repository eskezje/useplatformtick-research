unsigned __int64 __fastcall HalpTimerGetClockRates(__int64 a1, unsigned __int64 *a2, _DWORD *a3)
{
  unsigned __int64 v3; // r10
  unsigned int v5; // ecx
  unsigned __int64 v7; // rax
  unsigned __int64 v8; // rcx
  unsigned __int64 result; // rax
  unsigned __int64 v10; // rdx

  v3 = *(_QWORD *)(a1 + 0xC0);
  v5 = *(_DWORD *)(a1 + 0xDC);
  if ( v5 <= 40 )
    v7 = 10000000 * (1LL << v5) - 10000000;
  else
    v7 = 0x9896800000000000uLL;
  v8 = v7 / v3;
  result = *(unsigned int *)(a1 + 0xE0);
  if ( (result & 128u) == 0LL )
  {
    result = 10000000 / v3;
    v10 = 10000000 / v3;
  }
  else
  {
    LODWORD(v10) = v8;
    v8 = (unsigned int)v8 * (unsigned __int64)*(unsigned int *)(a1 + 216);
  }
  *a2 = v8;
  *a3 = v10;
  return result;
}