/* Function: HalpTimerFindIdealWatchdog @ 0x1404f4220 (call depth 1) */

ULONG_PTR *HalpTimerFindIdealWatchdog()
{
  int v0; // edi
  ULONG_PTR *Timer; // rax
  ULONG_PTR *v2; // rbx
  ULONG_PTR *v3; // rcx
  ULONG_PTR *v4; // rax
  int v6; // [rsp+40h] [rbp+8h] BYREF
  unsigned __int64 v7; // [rsp+48h] [rbp+10h] BYREF

  v7 = 0LL;
  v0 = 11;
  while ( 1 )
  {
    while ( 1 )
    {
      Timer = HalpFindTimer(v0, 163872, 0, 0, 4);
      v2 = Timer;
      if ( Timer )
        break;
      if ( !v0 )
        goto LABEL_10;
      v0 = 0;
    }
    if ( Timer[24] )
    {
      HalpTimerGetClockRates((__int64)Timer, &v7, &v6);
      if ( v7 >= 0x11E1A300 && (v7 >= 0xB2D05E00 || *((_DWORD *)v2 + 57) != 8 && (v2[28] & 0x80000) != 0) )
        break;
    }
  }
LABEL_10:
  v3 = (ULONG_PTR *)HalpRegisteredTimers;
  while ( v3 != &HalpRegisteredTimers )
  {
    v4 = v3;
    v3 = (ULONG_PTR *)*v3;
    *((_DWORD *)v4 + 46) &= ~0x100u;
  }
  return v2;
}
