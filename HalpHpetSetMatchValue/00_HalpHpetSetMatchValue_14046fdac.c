/* Function: HalpHpetSetMatchValue @ 0x14046fdac (call depth 0) */

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
