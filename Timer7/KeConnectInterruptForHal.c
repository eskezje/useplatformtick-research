__int64 __fastcall KeConnectInterruptForHal(__int64 a1)
{
  __int64 v1; // rdi
  unsigned __int8 CurrentIrql; // bl
  __int64 v3; // rdx
  __int64 v4; // rax
  __int64 result; // rax

  v1 = a1;
  CurrentIrql = KeGetCurrentIrql();
  v3 = 15LL;
  __writecr8(0xFuLL);
  if ( KiIrqlFlags )
  {
    LOBYTE(a1) = CurrentIrql;
    KiRaiseIrqlProcessIrqlFlags(a1, 15LL);
  }
  v4 = *(unsigned int *)(v1 + 88);
  *(_BYTE *)(v1 + 95) = 1;
  KeGetCurrentPrcb()->InterruptObject[v4] = (void *)v1;
  if ( KiIrqlFlags )
  {
    LOBYTE(v3) = CurrentIrql;
    KiLowerIrqlProcessIrqlFlags(KeGetCurrentIrql(), v3);
  }
  result = CurrentIrql;
  __writecr8(CurrentIrql);
  return result;
}