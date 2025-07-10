/* Function: HalpTimerFindIdealPerformanceCounterSource @ 0x1404f3ff0 (call depth 1) */

__int64 HalpTimerFindIdealPerformanceCounterSource()
{
  int v0; // ebx
  __int64 result; // rax

  if ( HalpTimerPlatformSourceForced )
    goto SelectPlatform;
  if ( (unsigned __int8)HalpIsHvPresent() )
    goto LABEL_19;
  v0 = 0x2000;
  if ( (unsigned __int8)HalpTimerDeepestIdleState > 1u )
    v0 = 24576;
  result = HalpFindTimer(5, 3, v0, 0, 0);
  if ( !result )
  {
    result = HalpFindTimer(10, 3, v0, 0, 0);
    if ( !result )
    {
LABEL_19:
      if ( !HalpHvCpuManager || qword_140FC03C8 || (result = HalpFindTimer(3, 2, 24576, 0, 0)) == 0 )
      {
        result = HalpFindTimer(8, 2, 0, 0, 0);
        if ( !result )
        {
SelectPlatform:
          result = HalpFindTimer(11, 2, 24576, 0, 0);
          if ( !result )
          {
            result = HalpFindTimer(3, 2, 24576, 0, 0);
            if ( !result )
            {
              result = HalpFindTimer(1, 2, 24576, 0, 0);
              if ( !result )
              {
                if ( (unsigned __int8)HalpIsHvPresent() )
                  return 0LL;
                result = HalpFindTimer(0, 2, 24576, 0, 0);
                if ( !result )
                  return 0LL;
              }
            }
          }
        }
      }
    }
  }
  return result;
}
