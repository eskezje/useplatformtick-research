__int64 __fastcall HalpVpptArmTimer(__int64 *a1, int a2, __int64 a3)
{
  __int64 v7; // rdi
  __int64 v8; // rbp
  int v9; // esi
  __int64 *v10; // rcx
  __int64 **v11; // rax
  __int64 InterruptTimePrecise; // rax
  int *v13; // rcx
  int *i; // rdx
  __int64 v15; // rax
  char v16; // [rsp+50h] [rbp+8h] BYREF

  if ( ((a2 - 1) & 0xFFFFFFFD) != 0 )
    return 0xC00000BBLL;
  byte_140FC0758 = HalpAcquireHighLevelLock(&qword_140FC0750);
  v7 = 0LL;
  if ( *(int **)&HalpVpptQueue == &HalpVpptQueue )
  {
    v8 = 0LL;
    v9 = -1;
  }
  else
  {
    v8 = *(_QWORD *)(*(_QWORD *)&HalpVpptQueue + 0x20LL);
    v9 = *(_DWORD *)(*(_QWORD *)&HalpVpptQueue + 0x10LL);
  }
  if ( *((_BYTE *)a1 + 24) )
  {
    v10 = (__int64 *)*a1;
    if ( *(__int64 **)(*a1 + 8) != a1 )
      goto LABEL_16;
    v11 = (__int64 **)a1[1];
    if ( *v11 != a1 )
      goto LABEL_16;
    *v11 = v10;
    v10[1] = (__int64)v11;
  }
  InterruptTimePrecise = RtlGetInterruptTimePrecise(&v16);
  v13 = &HalpVpptQueue;
  if ( a2 != 3 )
    v7 = a3;
  a1[4] = InterruptTimePrecise + a3;
  a1[5] = v7;
  for ( i = *(int **)&HalpVpptQueue; i != &HalpVpptQueue; i = *(int **)i )
  {
    if ( (unsigned __int64)(InterruptTimePrecise + a3) < *((_QWORD *)i + 4) )
      break;
    v13 = i;
  }
  v15 = *(_QWORD *)v13;
  if ( *(int **)(*(_QWORD *)v13 + 8LL) != v13 )
LABEL_16:
    __fastfail(3u);
  *a1 = v15;
  a1[1] = (__int64)v13;
  *(_QWORD *)(v15 + 8) = a1;
  *(_QWORD *)v13 = a1;
  if ( *(_QWORD *)(*(_QWORD *)&HalpVpptQueue + 32LL) != v8 || *(_DWORD *)(*(_QWORD *)&HalpVpptQueue + 0x10LL) != v9 )
    HalpVpptUpdatePhysicalTimer((__int64)v13);
  *((_DWORD *)a1 + 5) = 2;
  *((_BYTE *)a1 + 24) = 1;
  LOBYTE(i) = byte_140FC0758;
  HalpReleaseHighLevelLock(&qword_140FC0750, i);
  return 0LL;
}