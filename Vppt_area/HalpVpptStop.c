__int64 __fastcall HalpVpptStop(__int64 a1)
{
  __int64 v2; // rdx
  __int64 v3; // rcx
  __int64 *v4; // rax
  bool v5; // dl
  __int64 InternalData; // rax

  byte_140FC0758 = HalpAcquireHighLevelLock(&qword_140FC0750);
  if ( *(_BYTE *)(a1 + 0x18) )
  {
    v3 = *(_QWORD *)a1;
    v4 = *(__int64 **)(a1 + 8);
    v5 = *(_QWORD *)&HalpVpptQueue == a1;
    if ( *(_QWORD *)(*(_QWORD *)a1 + 8LL) != a1 || *v4 != a1 )
      __fastfail(3u);
    *v4 = v3;
    *(_QWORD *)(v3 + 8) = v4;
    if ( v4 == (__int64 *)v3 )
    {
      v2 = *(_QWORD *)&HalpVpptPhysicalTimer;
      if ( *(_DWORD *)(*(_QWORD *)&HalpVpptPhysicalTimer + 0xE4LL) != 3 )
      {
        InternalData = HalpTimerGetInternalData(*(__int64 *)&HalpVpptPhysicalTimer);
        guard_dispatch_icall_no_overrides(InternalData);
      }
    }
    else if ( v5 )
    {
      HalpVpptUpdatePhysicalTimer(v3);
    }
  }
  *(_DWORD *)(a1 + 0x14) = 0;
  *(_BYTE *)(a1 + 0x18) = 0;
  LOBYTE(v2) = byte_140FC0758;
  return HalpReleaseHighLevelLock(&qword_140FC0750, v2);
}