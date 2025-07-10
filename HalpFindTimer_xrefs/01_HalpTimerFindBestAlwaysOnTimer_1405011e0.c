/* Function: HalpTimerFindBestAlwaysOnTimer @ 0x1405011e0 (call depth 1) */

ULONG_PTR *__fastcall HalpTimerFindBestAlwaysOnTimer(char a1)
{
  ULONG_PTR *result; // rax

  if ( a1 )
  {
    result = HalpFindTimer(0, 32770, 24576, 0, 0);
    if ( !result )
      return HalpFindTimer(0, 32770, 28416, 0, 1);
  }
  else
  {
    result = HalpFindTimer(0, 32800, 24576, 3840, 0);
    if ( !result )
    {
      result = HalpFindTimer(0, 32832, 24576, 3840, 0);
      if ( !result )
        return HalpFindTimer(0, 32784, 24576, 3840, 0);
    }
  }
  return result;
}
