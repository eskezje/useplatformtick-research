__int64 __fastcall HalpArtInitialize(_DWORD *a1)
{
  struct _KPRCB *CurrentPrcb; // rax
  int v3; // edi

  CurrentPrcb = KeGetCurrentPrcb();
  v3 = ~(CurrentPrcb->CoresPerPhysicalProcessor * CurrentPrcb->LogicalProcessorsPerCore - 1);
  if ( !HalpArtAvailable() || (v3 & a1[2]) != 0 || *a1 || a1[1] )
    HalpTimerAuxiliaryClockEnabled = 0;
  else
    HalUpdateTimerCapabilities(a1, 0LL, 0LL);
  return 0LL;
}