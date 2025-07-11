char __fastcall HalpApicTimerIsInvariant(__int64 a1)
{
  if ( (int)HalSocRequestApi(a1, 0LL, 2, 16LL, &HalpApicTimerCpuApi) >= 0 )
    guard_dispatch_icall_no_overrides(0LL);
  return 0;
}