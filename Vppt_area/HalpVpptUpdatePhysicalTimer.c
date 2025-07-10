__int64 __fastcall HalpVpptUpdatePhysicalTimer(__int64 a1)
{
  int v1; // ebx
  unsigned __int64 v2; // rdi
  unsigned __int64 InterruptTimePrecise; // rax
  unsigned __int64 v4; // r8
  unsigned __int64 v5; // rbx
  __int64 result; // rax
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  __int64 InternalData; // rax
  __int64 v11; // rax
  char v12; // [rsp+40h] [rbp+8h] BYREF

  v1 = *(_DWORD *)(*(_QWORD *)&HalpVpptQueue + 0x10LL);
  v2 = *(_QWORD *)(*(_QWORD *)&HalpVpptQueue + 0x20LL);
  if ( HalpVpptPhysicalTimerTarget != v1 )
  {
    if ( *(_DWORD *)(*(_QWORD *)&HalpVpptPhysicalTimer + 0xE4LL) != 3 )
    {
      InternalData = HalpTimerGetInternalData(*(__int64 *)&HalpVpptPhysicalTimer);
      guard_dispatch_icall_no_overrides(InternalData);
      if ( (*(_DWORD *)(*(_QWORD *)&HalpVpptPhysicalTimer + 0xE0LL) & 0x200000) == 0 )
      {
        v11 = HalpTimerGetInternalData(*(__int64 *)&HalpVpptPhysicalTimer);
        guard_dispatch_icall_no_overrides(v11);
      }
    }
    if ( HalpVpptPhysicalTimerTarget != v1 )
    {
      v8 = ExtEnvSetVpptTarget(a1, v1);
      if ( v8 < 0 )
        ExtEnvCriticalFailure(v9, 276, HalpVpptPhysicalTimerTarget, v1, v8);
      HalpVpptPhysicalTimerTarget = v1;
    }
  }
  InterruptTimePrecise = RtlGetInterruptTimePrecise(&v12);
  v4 = 0LL;
  if ( InterruptTimePrecise <= v2 )
    v4 = v2 - InterruptTimePrecise;
  v5 = 10000000uLL / *(_QWORD *)(*(_QWORD *)&HalpVpptPhysicalTimer + 0xC0LL);
  if ( v5 < 5000 )
    v5 = 5000LL;
  if ( v4 >= v5 )
    v5 = v4;
  result = HalpSetTimerAnyMode(*(_QWORD *)&HalpVpptPhysicalTimer, v5, v4, (unsigned __int64 *)&v12);
  if ( (int)result < 0 )
    ExtEnvCriticalFailure(v7, 277, HalpVpptPhysicalTimer, v5, (int)result);
  return result;
}