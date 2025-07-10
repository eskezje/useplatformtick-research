/* Function: HalpTimerQueryCycleCounter @ 0x1404f4940 (call depth 1) */

ULONG_PTR *__fastcall HalpTimerQueryCycleCounter(_QWORD *a1)
{
  ULONG_PTR *result; // rax
  __int64 InternalData; // rax
  __int64 v4; // rdx
  __int64 v5; // r8

  result = HalpFindTimer(5, 0, 0, 0, 1);
  if ( result )
  {
    if ( a1 )
      *a1 = result[24];
    InternalData = HalpTimerGetInternalData((__int64)result);
    return (ULONG_PTR *)guard_dispatch_icall_no_overrides(InternalData, v4, v5);
  }
  return result;
}
