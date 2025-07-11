__int64 HalpApicTimerStop()
{
  HalpApicTimerInitialize();
  return guard_dispatch_icall_no_overrides(896LL);
}