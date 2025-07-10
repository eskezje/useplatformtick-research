__int64 HalpTimerInitializeVpptClockTimer()
{
  __int64 result; // rax

  result = HalpClockTimer;
  if ( *(_DWORD *)(HalpClockTimer + 0xE4) == 12 )
    return HalpVpptInitializePhysicalTimer();
  return result;
}