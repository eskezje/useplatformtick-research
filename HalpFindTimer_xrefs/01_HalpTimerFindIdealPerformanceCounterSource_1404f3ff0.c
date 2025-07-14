ULONG_PTR *HalpTimerFindIdealPerformanceCounterSource()
{
  int v0; // ebx
  ULONG_PTR *result; // rax

  if ( HalpTimerPlatformSourceForced )
    goto SelectPlatform;
  if ( HalpIsHvPresent() )
    goto LABEL_19;
  v0 = 0x2000;
  if ( (unsigned __int8)HalpTimerDeepestIdleState > 1u )
    v0 = 0x6000;
  result = HalpFindTimer(5, 3, v0, 0, 0);
  if ( !result )
  {
    result = HalpFindTimer(10, 3, v0, 0, 0);
    if ( !result )
    {
LABEL_19:
      if ( !HalpHvCpuManager || qword_140FC03C8 || (result = HalpFindTimer(3, 2, 0x6000, 0, 0)) == 0LL )
      {
        result = HalpFindTimer(8, 2, 0, 0, 0);
        if ( !result )
        {
SelectPlatform:
          result = HalpFindTimer(11, 2, 0x6000, 0, 0);
          if ( !result )
          {
            result = HalpFindTimer(3, 2, 0x6000, 0, 0);
            if ( !result )
            {
              result = HalpFindTimer(1, 2, 0x6000, 0, 0);
              if ( !result )
              {
                if ( HalpIsHvPresent() )
                  return 0LL;
                result = HalpFindTimer(0, 2, 0x6000, 0, 0);
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