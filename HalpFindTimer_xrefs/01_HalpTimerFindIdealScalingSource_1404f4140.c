/* Function: HalpTimerFindIdealScalingSource @ 0x1404f4140 (call depth 1) */

ULONG_PTR *HalpTimerFindIdealScalingSource()
{
  ULONG_PTR *v0; // rdi
  ULONG_PTR *v1; // rbx
  ULONG_PTR *Timer; // rcx
  ULONG_PTR *v3; // rdx
  ULONG_PTR *v4; // r8
  int v5; // r9d

  v0 = 0LL;
  v1 = 0LL;
  Timer = HalpFindTimer(1, 2, 24576, 0, 0);
  if ( !Timer )
  {
    Timer = HalpFindTimer(3, 2, 24576, 0, 0);
    if ( !Timer )
    {
      v3 = (ULONG_PTR *)HalpRegisteredTimers;
      while ( 1 )
      {
        v4 = v3;
        if ( v3 == &HalpRegisteredTimers )
          break;
        Timer = v3;
        v3 = (ULONG_PTR *)*v3;
        v5 = *((_DWORD *)Timer + 46);
        if ( (v5 & 1) == 0 )
        {
          if ( Timer[22] )
            v0 = Timer;
          if ( (Timer[28] & 2) != 0 && Timer[24] )
          {
            if ( (v5 & 8) == 0 )
              return Timer;
            if ( v1 )
              v4 = v1;
            v1 = v4;
          }
        }
      }
      if ( v0 )
      {
        return v0;
      }
      else if ( v1 )
      {
        *((_DWORD *)v1 + 46) &= ~8u;
        return v1;
      }
      else
      {
        return 0LL;
      }
    }
  }
  return Timer;
}
