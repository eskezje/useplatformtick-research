__int64 __fastcall HalpVpptAcknowledgeInterrupt(__int64 a1)
{
  __int64 InternalData; // rax
  __int64 v3; // rdx
  __int64 v5; // rcx
  unsigned __int64 InterruptTimePrecise; // rax
  unsigned __int64 v7; // rcx
  int *v8; // r8
  int *i; // rdx
  __int64 v10; // rax
  __int64 v11; // rax
  char v12; // [rsp+30h] [rbp+8h] BYREF

  byte_140FC0758 = HalpAcquireHighLevelLock(&qword_140FC0750);
  InternalData = HalpTimerGetInternalData(*(__int64 *)&HalpVpptPhysicalTimer);
  guard_dispatch_icall_no_overrides(InternalData);
  if ( *(_QWORD *)&HalpVpptQueue == a1 )
  {
    v5 = **(_QWORD **)&HalpVpptQueue;
    if ( *(int **)(*(_QWORD *)&HalpVpptQueue + 8LL) != &HalpVpptQueue
      || *(_QWORD *)(v5 + 8) != *(_QWORD *)&HalpVpptQueue )
    {
      goto LABEL_15;
    }
    *(_QWORD *)&HalpVpptQueue = **(_QWORD **)&HalpVpptQueue;
    *(_QWORD *)(v5 + 8) = &HalpVpptQueue;
    if ( !*(_QWORD *)(a1 + 0x28) )
    {
      *(_BYTE *)(a1 + 0x18) = 0;
      goto LABEL_2;
    }
    InterruptTimePrecise = RtlGetInterruptTimePrecise(&v12);
    v7 = *(_QWORD *)(a1 + 0x20);
    if ( v7 <= InterruptTimePrecise )
    {
      do
        v7 += *(_QWORD *)(a1 + 0x28);
      while ( v7 <= InterruptTimePrecise );
      *(_QWORD *)(a1 + 0x20) = v7;
    }
    v8 = *(int **)&HalpVpptQueue;
    for ( i = &HalpVpptQueue; v8 != &HalpVpptQueue; v8 = *(int **)v8 )
    {
      if ( v7 < *((_QWORD *)v8 + 4) )
        break;
      i = v8;
    }
    v10 = *(_QWORD *)i;
    if ( *(int **)(*(_QWORD *)i + 8LL) != i )
LABEL_15:
      __fastfail(3u);
    *(_QWORD *)a1 = v10;
    *(_QWORD *)(a1 + 8) = i;
    *(_QWORD *)(v10 + 8) = a1;
    *(_QWORD *)i = a1;
  }
LABEL_2:
  if ( *(int **)&HalpVpptQueue == &HalpVpptQueue )
  {
    v3 = *(_QWORD *)&HalpVpptPhysicalTimer;
    if ( *(_DWORD *)(*(_QWORD *)&HalpVpptPhysicalTimer + 0xE4LL) != 3 )
    {
      v11 = HalpTimerGetInternalData(*(__int64 *)&HalpVpptPhysicalTimer);
      guard_dispatch_icall_no_overrides(v11);
    }
  }
  else
  {
    ((void (*)(void))HalpVpptUpdatePhysicalTimer)();
  }
  LOBYTE(v3) = byte_140FC0758;
  return HalpReleaseHighLevelLock(&qword_140FC0750, v3);
}