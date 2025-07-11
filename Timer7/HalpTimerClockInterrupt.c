char __fastcall HalpTimerClockInterrupt(__int64 a1, __int64 a2, __int64 a3)
{
  __int64 v3; // rdi
  unsigned __int8 v4; // si
  __int64 v5; // rax
  __int64 (__fastcall *v6)(_QWORD); // rdx
  char *v7; // rbx
  char v8; // cl
  char v9; // al
  __int64 v11; // r8
  ULONG_PTR v12; // rcx
  __int64 v13; // rdx
  struct _KPRCB *CurrentPrcb; // rax
  _QWORD *v15; // rbx
  char v16; // [rsp+30h] [rbp+8h] BYREF

  v3 = *(_QWORD *)(a1 + 136);
  v4 = *(_BYTE *)(v3 + 41);
  if ( (*(_DWORD *)(HalpClockTimer + 0xE0) & 0x10000) != 0 )
    v5 = *(_QWORD *)(HalpClockTimer + 0x48) + *(_DWORD *)(HalpClockTimer + 0x50) * KeGetPcr()->Prcb.Number;
  else
    v5 = *(_QWORD *)(HalpClockTimer + 0x48);
  v6 = *(__int64 (__fastcall **)(_QWORD))(HalpClockTimer + 0x78);
  if ( v6 == HalpHvTimerAcknowledgeInterrupt )
    HalpHvTimerAcknowledgeInterrupt(v5);
  else
    ((void (__fastcall *)(__int64, __int64 (__fastcall *)(_QWORD), __int64))guard_dispatch_icall_no_overrides)(
      v5,
      v6,
      a3);
  v7 = (char *)&HalpClockTickLog
     + 24 * (((unsigned __int8)_InterlockedExchangeAdd(&HalpClockTickLogIndex, 1u) + 1) & 0xF);
  *(_QWORD *)v7 = RtlGetInterruptTimePrecise((unsigned __int64 *)&v16);
  *((_DWORD *)v7 + 2) = KeGetPcr()->Prcb.Number;
  *((_DWORD *)v7 + 3) = KiClockTimerOwner;
  v7[16] = 0;
  v8 = KeGetCurrentPrcb()->PendingTickFlags & 1;
  v7[16] = v8;
  v9 = v8 | KeGetCurrentPrcb()->PendingTickFlags & 2;
  v7[16] = v9;
  if ( KeGetCurrentPrcb()->ClockOwner )
    v7[16] = v9 | 4;
  if ( (KeGetCurrentPrcb()->PendingTickFlags & 1) != 0 )
  {
    KeClockInterruptNotify(v3, v4, 0);
    if ( KeGetCurrentPrcb()->ClockOwner )
    {
      v12 = HalpClockTimer;
      v13 = MEMORY[0xFFFFF78000000008];
      if ( (unsigned int)(*(_DWORD *)(HalpClockTimer + 60) - MEMORY[0xFFFFF78000000008]) > 1200000000 )
      {
        BYTE1(HalpClockWorkUnion) = 1;
        *(_DWORD *)(HalpClockTimer + 60) = MEMORY[0xFFFFF78000000008] + 1200000000;
      }
      if ( HalpClockWorkUnion )
        HalpTimerClockInterruptWork();
      CurrentPrcb = KeGetCurrentPrcb();
      if ( HalpWatchdogTimer && CurrentPrcb->ClockOwner )
      {
        if ( MEMORY[0xFFFFF78000000008] - HalpTimerWatchdogLastReset > (unsigned __int64)HalpTimerWatchdogResetCount )
          ((void (__fastcall *)(ULONG_PTR, __int64, __int64))guard_dispatch_icall_no_overrides)(v12, v13, v11);
        if ( HalpTimerWatchdogResetCount == -1 )
          HalpTimerWatchdogTriggerSystemReset(0LL);
      }
      if ( SLODWORD(KeGetCurrentPrcb()->HalReserved[3]) > 0 && (KeGetCurrentPrcb()->HalReserved[3] & 1) == 0 )
      {
        LODWORD(v3) = KeGetPcr()->Prcb.Number;
        v15 = (_QWORD *)(HalpCounterSetInfo + 24 * v3);
        if ( MEMORY[0xFFFFF78000000008] - v15[2] >= 5000000uLL )
        {
          if ( (_QWORD *)*v15 != v15 )
            ((void (__fastcall *)(_QWORD, _QWORD, __int64))guard_dispatch_icall_no_overrides)(0LL, 0LL, v11);
          HalpScanForProfilingCorruption(v3);
          v15[2] = MEMORY[0xFFFFF78000000008];
        }
      }
    }
  }
  return 1;
}