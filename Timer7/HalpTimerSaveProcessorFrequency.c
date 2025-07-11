ULONG_PTR *HalpTimerSaveProcessorFrequency()
{
  KPCR *Pcr; // rbx
  ULONG_PTR *Timer; // rax
  unsigned __int64 v2; // rcx
  ULONG_PTR *result; // rax

  Pcr = KeGetPcr();
  Timer = HalpFindTimer(5, 0, 0, 0, 1);
  if ( Timer )
  {
    *(_QWORD *)Pcr->HalReserved = 10000 * ((Timer[24] + 5000) / 10000);
    v2 = 1000000 * ((Timer[24] + 500000) / 1000000);
    Pcr->StallScaleFactor = v2 / 1000000;
    KeGetCurrentPrcb()->MHz = v2 / 1000000;
  }
  result = HalpFindTimer(7, 0, 0, 0, 1);
  if ( result )
  {
    result = (ULONG_PTR *)(10000 * (unsigned int)((result[24] + 5000) / 10000));
    Pcr->HalReserved[3] = (unsigned int)result;
  }
  return result;
}