__int64 __fastcall KeGetClockTimerResolution(_DWORD *a1, unsigned int *a2, _BYTE *a3)
{
  struct _KPRCB *CurrentPrcb; // r9
  __int64 result; // rax
  bool v5; // zf

  CurrentPrcb = KeGetCurrentPrcb();
  v5 = KiClockTimerPerCpuTickScheduling == 0;
  *a3 = 0;
  if ( v5 )
  {
    v5 = KiClockOwnerOneShotRequestState == 1;
    *a2 = KeTimeIncrement;
    result = (unsigned int)KiLastRequestedTimeIncrement;
    *a1 = KiLastRequestedTimeIncrement;
  }
  else
  {
    *a2 = CurrentPrcb->ClockTimerState.TimeIncrement;
    result = CurrentPrcb->ClockTimerState.LastRequestedTimeIncrement;
    *a1 = result;
    v5 = CurrentPrcb->ClockTimerState.OneShotState == KClockTimerOneShotArmed;
  }
  if ( v5 )
    *a3 = 1;
  return result;
}