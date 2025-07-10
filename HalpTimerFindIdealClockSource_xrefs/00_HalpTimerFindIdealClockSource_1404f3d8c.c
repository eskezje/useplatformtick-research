/* Function: HalpTimerFindIdealClockSource @ 0x1404f3d8c (call depth 0) */

__int64 HalpTimerFindIdealClockSource()
{
  char v0; // si
  __int64 v1; // rbx
  char v2; // di
  __int64 Timer; // rax
  int v4; // ecx

  v0 = HalpHvPresent;
  v1 = 0LL;
  if ( !HalpHvPresent || !HalpHvCpuManager )
  {
LABEL_5:
    v2 = HalpTimerPlatformClockSourceForced;
    if ( HalpTimerPlatformClockSourceForced )
      goto LABEL_7;
    Timer = (__int64)HalpFindTimer(8, 0x60, 0x6000, 0xF00, 0);
    if ( !Timer )
      goto LABEL_7;
LABEL_26:
    v4 = *(_DWORD *)(Timer + 0xE0);
    if ( (v4 & 0x50) != 0 )
      return Timer & -(__int64)((v4 & 0x20) != 0);
    return v1;
  }
  v2 = HalpTimerPlatformClockSourceForced;
  if ( !HalpTimerPlatformClockSourceForced )
  {
    Timer = (__int64)HalpFindTimer(11, 0x220, 0, 0x50, 0);
    if ( Timer )
      goto LABEL_26;
    goto LABEL_5;
  }
LABEL_7:
  Timer = (__int64)HalpFindTimer(11, 0x220, 0, 0x50, 0);
  if ( Timer )
    goto LABEL_26;
  if ( !v2 && !v0 && HalpProfileInterface != &DefaultProfileInterface )
  {
    Timer = (__int64)HalpFindTimer(0, 0x21, 0x6000, 0xF00, 0);
    if ( Timer )
      goto LABEL_26;
  }
  Timer = (__int64)HalpFindTimer(3, 0x160, 0, 0, 0);
  if ( Timer )
    goto LABEL_26;
  Timer = (__int64)HalpFindTimer(3, 0x30, 0, 0x100, 0);
  if ( Timer )
    goto LABEL_26;
  Timer = (__int64)HalpFindTimer(3, 0x60, 0, 0xF00, 0);
  if ( Timer )
    goto LABEL_26;
  Timer = (__int64)HalpFindTimer(3, 0x30, 0, 0xF00, 0);
  if ( Timer )
    goto LABEL_26;
  Timer = (__int64)HalpFindTimer(0, 0x8060, 0x6000, 0xF00, 0);
  if ( Timer )
  {
    if ( *(_QWORD *)(Timer + 0xC0) >= 2000uLL )
      goto LABEL_26;
  }
  Timer = (__int64)HalpFindTimer(0, 0x8030, 0x6000, 0xF00, 0);
  if ( Timer )
  {
    if ( *(_QWORD *)(Timer + 0xC0) >= 2000uLL )
      goto LABEL_26;
  }
  Timer = (__int64)HalpFindTimer(0, 0x260, 0xE000, 0, 0);
  if ( Timer )
  {
    if ( *(_QWORD *)(Timer + 0xC0) >= 2000uLL )
      goto LABEL_26;
  }
  Timer = (__int64)HalpFindTimer(0, 0x60, 0xE000, 0xF00, 0);
  if ( Timer )
  {
    if ( *(_QWORD *)(Timer + 0xC0) >= 2000uLL )
      goto LABEL_26;
  }
  Timer = (__int64)HalpFindTimer(0, 0x30, 0xE000, 0xF00, 0);
  if ( Timer )
  {
    if ( *(_QWORD *)(Timer + 0xC0) >= 2000uLL )
      goto LABEL_26;
  }
  return v1;
}
