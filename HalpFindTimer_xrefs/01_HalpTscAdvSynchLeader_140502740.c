/* Function: HalpTscAdvSynchLeader @ 0x140502740 (call depth 1) */

__int64 __fastcall HalpTscAdvSynchLeader(__int64 a1)
{
  __int64 Number; // r15
  unsigned int v3; // ebx
  int v4; // r9d
  __int64 TimeStamp; // r14
  unsigned int v6; // r10d
  __int64 v7; // rax
  unsigned int v8; // r10d
  __int64 v9; // r9
  unsigned int i; // esi
  unsigned __int64 v11; // r14
  __int64 Timer; // rax
  __int64 v13; // rsi
  __int64 result; // rax
  unsigned __int64 v15; // rdx
  unsigned int v16; // [rsp+60h] [rbp+30h] BYREF
  __int64 v17; // [rsp+68h] [rbp+38h] BYREF
  __int64 v18; // [rsp+70h] [rbp+40h] BYREF

  Number = KeGetCurrentPrcb()->Number;
  v3 = 0;
  TimeStamp = HalpTscAdvSynchReadTimeStamp(Number);
  if ( HalpTscRequestedSynchronization )
  {
    if ( !HalpTscRequestedIterations )
      HalpTscRequestedIterations = 500;
    if ( *(_BYTE *)(a1 + 34) )
    {
      HalpTscAdvSynchToLeader(*(unsigned int *)(a1 + 36));
    }
    else
    {
      v17 = 0LL;
      v18 = 0LL;
      v16 = KeGetCurrentPrcb()->Number;
      HalpTscAdvSynchCalculateRemoteDeltas((unsigned int)&v17, (unsigned int)&v18, (unsigned int)&v16, v4);
      if ( v16 != KeGetCurrentPrcb()->Number )
      {
        HalpTscAdvSynchReadTimeStamp((unsigned int)Number);
        LODWORD(Number) = v6;
        v7 = HalpTscAdvSynchReadTimeStamp(v6);
        TimeStamp = v7 - v9;
        HalpTscAdvSynchToTarget(v8);
      }
      for ( i = 0; i < *(_DWORD *)(a1 + 40); ++i )
      {
        if ( i != KeGetCurrentPrcb()->Number && i != v16 )
          HalpTscAdvSynchToLeader(i);
      }
    }
  }
  v17 = 0LL;
  v18 = 0LL;
  v16 = KeGetCurrentPrcb()->Number;
  HalpTscAdvSynchCalculateRemoteDeltas((unsigned int)&v17, (unsigned int)&v18, (unsigned int)&v16, v4);
  v11 = (unsigned __int64)(1000000 * (HalpTscAdvSynchReadTimeStamp((unsigned int)Number) - TimeStamp))
      / *(_QWORD *)KeGetPcr()->HalReserved;
  Timer = HalpFindTimer(5, 0, 0, 0, 1);
  v13 = Timer;
  HalpTscMaximumComputedSpread = v18 - v17;
  if ( v18 - v17 <= (unsigned __int64)(unsigned int)HalpTscMaximumCounterSyncSpread )
  {
    result = HalpTscTraceSynchronizationSummary(KeGetCurrentPrcb()->Number, v16, v18, v17, v11);
    *(_DWORD *)(v13 + 184) |= 0x20u;
  }
  else
  {
    *(_DWORD *)(Timer + 184) &= ~0x20u;
    HalpTscSynchronizationFailureFallback = 1;
    result = HalpTscTraceStatus(&HAL_ETW_EVENT_TIMER_SYNCH_FAILED);
  }
  if ( *(_DWORD *)(a1 + 40) )
  {
    do
    {
      result = (__int64)KeGetCurrentPrcb();
      if ( v3 != *(_DWORD *)(result + 36) )
      {
        v15 = (unsigned __int64)v3 << 7;
        _InterlockedExchange((volatile __int32 *)(v15 + TscRequest), 7);
        result = *(unsigned int *)(v15 + TscRequest);
        if ( (_DWORD)result == 7 )
        {
          do
          {
            _mm_pause();
            result = TscRequest;
          }
          while ( *(_DWORD *)(v15 + TscRequest) == 7 );
        }
      }
      ++v3;
    }
    while ( v3 < *(_DWORD *)(a1 + 40) );
  }
  return result;
}
