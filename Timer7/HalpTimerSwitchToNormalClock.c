__int64 __fastcall HalpTimerSwitchToNormalClock(__int64 a1)
{
  char v1; // si
  unsigned __int8 CurrentIrql; // di
  struct _KPRCB *CurrentPrcb; // rbx
  __int64 InternalData; // rax
  __int64 v5; // rdx
  __int64 result; // rax
  char v7; // [rsp+40h] [rbp+8h] BYREF
  unsigned __int64 v8; // [rsp+48h] [rbp+10h] BYREF
  char v9; // [rsp+50h] [rbp+18h] BYREF

  LODWORD(v8) = 0;
  v1 = a1;
  v7 = 0;
  CurrentIrql = KeGetCurrentIrql();
  __writecr8(0xFuLL);
  if ( KiIrqlFlags )
  {
    LOBYTE(a1) = CurrentIrql;
    KiRaiseIrqlProcessIrqlFlags(a1, 15LL);
  }
  CurrentPrcb = KeGetCurrentPrcb();
  InternalData = HalpTimerGetInternalData(HalpAlwaysOnTimer);
  guard_dispatch_icall_no_overrides(InternalData);
  CurrentPrcb->PendingTickFlags &= ~2u;
  if ( v1 )
  {
    KeGetClockTimerResolution(&v8, &v9, &v7);
    if ( !v7 )
      HalpTimerClockArm(0, (unsigned int)v8, &v8);
  }
  if ( KiIrqlFlags )
  {
    LOBYTE(v5) = CurrentIrql;
    KiLowerIrqlProcessIrqlFlags(KeGetCurrentIrql(), v5);
  }
  result = CurrentIrql;
  __writecr8(CurrentIrql);
  return result;
}