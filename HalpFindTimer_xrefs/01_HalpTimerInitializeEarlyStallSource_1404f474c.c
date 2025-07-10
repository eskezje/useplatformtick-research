/* Function: HalpTimerInitializeEarlyStallSource @ 0x1404f474c (call depth 1) */

__int64 __fastcall HalpTimerInitializeEarlyStallSource(__int64 a1)
{
  int v2; // r10d
  ULONG_PTR *Timer; // rax
  ULONG_PTR *v4; // rbx
  unsigned int v5; // eax
  bool v6; // zf
  unsigned __int64 v7; // rcx

  LODWORD(HalpRegisteredTimerCount) = 0;
  HalpTimerLoaderBlock = a1;
  qword_140FC2588 = (__int64)&HalpRegisteredTimers;
  HalpRegisteredTimers = (ULONG_PTR)&HalpRegisteredTimers;
  v2 = HalpTimerRegisterBuiltinPluginsCommon(0);
  if ( v2 >= 0 )
  {
    if ( (_DWORD)HalpRegisteredTimerCount && (Timer = HalpFindTimer(0, 2, 0, 0, 1), (v4 = Timer) != 0LL) )
    {
      HalpPerformanceCounter = (ULONG_PTR)Timer;
      HalpStallCounter = (__int64)Timer;
      v2 = HalpTimerInitialize((__int64)Timer);
      if ( v2 >= 0 )
      {
        v5 = v4[23] & 0xFFFFFFFB;
        v6 = v4[24] == 0;
        *((_DWORD *)v4 + 46) = v5;
        if ( v6 )
        {
          *((_DWORD *)v4 + 46) = v5 | 8;
          v7 = *(_QWORD *)(*(_QWORD *)(a1 + 240) + 2496LL);
          v4[24] = v7;
          if ( v7 < 0x3E8 )
          {
            v4[24] = 15625000LL;
            HalpTimerSetProblemEx(
              (_DWORD)v4,
              40,
              0,
              (unsigned int)"minkernel\\hals\\lib\\timers\\common\\timer.c",
              1193);
          }
        }
        else
        {
          HalpTimerProcessorFrequencyKnown = 1;
        }
      }
    }
    else
    {
      v2 = -1073741823;
      HalpTimerLastProblem = 21;
    }
  }
  else
  {
    HalpTimerLastProblem = 14;
  }
  return (unsigned int)v2;
}
