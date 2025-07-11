char HalpTimerClockInterruptStub()
{
  __int64 InternalData; // rax
  __int64 v1; // rdx
  __int64 v2; // r8
  char result; // al

  InternalData = HalpTimerGetInternalData(HalpClockTimer);
  guard_dispatch_icall_no_overrides(InternalData, v1, v2);
  result = 1;
  ++*(_DWORD *)(HalpClockTimer + 0x40);
  return result;
}