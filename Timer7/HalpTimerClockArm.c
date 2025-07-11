__int64 __fastcall HalpTimerClockArm(int a1, ULONG_PTR a2, unsigned __int64 *a3)
{
  ULONG_PTR v3; // rsi
  struct _KPRCB *CurrentPrcb; // rcx
  unsigned __int64 v7; // rbx
  int v8; // r11d
  unsigned __int64 v9; // rdi
  unsigned __int64 v10; // r9
  unsigned __int64 v11; // rax
  unsigned int v12; // ecx
  unsigned __int64 v13; // r11
  unsigned __int64 v14; // rax
  __int64 v15; // rcx
  int v16; // eax
  int v17; // r10d
  unsigned __int64 v19; // rbp
  unsigned __int64 v20; // r9
  unsigned int v21; // ecx
  unsigned __int64 v22; // rbx
  unsigned __int64 v23; // rax
  __int64 InternalData; // rax
  __int64 v25; // rdx
  int v26; // eax

  v3 = HalpClockTimer;
  CurrentPrcb = KeGetCurrentPrcb();
  v7 = a2;
  if ( a2 > HalpTimerMaxIncrement )
    KeBugCheckEx(0x5Cu, 0x113uLL, 0x25uLL, a2, 0LL);
  if ( a2 < (unsigned int)HalpTimerMinIncrement )
    v7 = (unsigned int)HalpTimerMinIncrement;
  if ( (CurrentPrcb->PendingTickFlags & 2) != 0 )
    HalpTimerSwitchToNormalClock(0LL);
  v8 = *(_DWORD *)(v3 + 224);
  if ( a1 != 1 )
  {
    v19 = 0LL;
    if ( (v8 & 0x50) != 0 )
    {
      v20 = *(_QWORD *)(v3 + 192);
      if ( is_mul_ok(v20, v7) )
      {
        v21 = *(_DWORD *)(v3 + 220);
        v22 = v20 * v7 / 10000000;
        if ( v21 < 64 && v22 >= 1LL << v21 )
        {
          v9 = 0LL;
          v17 = 0xC000000D;
          goto LABEL_17;
        }
        if ( is_mul_ok(v22, 10000000000uLL) )
          v23 = v22 * (unsigned __int128)10000000000uLL / v20;
        else
          v23 = HalpTimerScaleCounter(v22, *(_QWORD *)(v3 + 192), 10000000000LL);
        *(_QWORD *)(v3 + 16) = v22;
        *(_DWORD *)(v3 + 52) = 1;
        v19 = v23 / 1000;
        InternalData = HalpTimerGetInternalData(v3);
        v26 = ((__int64 (__fastcall *)(__int64, __int64, unsigned __int64))guard_dispatch_icall_no_overrides)(
                InternalData,
                v25,
                v22);
        v17 = v26;
        if ( v26 < 0 )
          HalpTimerSetProblemEx(v3, 18, v26, (__int64)"minkernel\\hals\\lib\\timers\\common\\timersup.c", 0x30Eu);
      }
      else
      {
        v17 = 0xC0000095;
      }
    }
    else
    {
      HalpTimerSetProblemEx(v3, 17, 0, (__int64)"minkernel\\hals\\lib\\timers\\common\\timersup.c", 0x2ABu);
    }
    v9 = v19;
    goto LABEL_17;
  }
  v9 = 0LL;
  if ( (v8 & 0x20) != 0 )
  {
    v10 = *(_QWORD *)(v3 + 192);
    v11 = v10 * v7;
    if ( is_mul_ok(v10, v7) && v11 + 9999999 >= v11 )
    {
      v12 = *(_DWORD *)(v3 + 220);
      v13 = (v11 + 9999999) / 10000000;
      if ( v12 >= 0x40 || v13 < 1LL << v12 )
      {
        if ( is_mul_ok(v13, 10000000000uLL) )
          v14 = v13 * (unsigned __int128)10000000000uLL / v10;
        else
          v14 = HalpTimerScaleCounter(v13, *(_QWORD *)(v3 + 192), 10000000000LL);
        *(_QWORD *)(v3 + 16) = v13;
        *(_DWORD *)(v3 + 52) = 1;
        v9 = v14 / 1000;
        if ( (*(_DWORD *)(v3 + 0xE0) & 0x10000) != 0 )
          v15 = *(_QWORD *)(v3 + 0x48) + *(_DWORD *)(v3 + 80) * KeGetPcr()->Prcb.Number;
        else
          v15 = *(_QWORD *)(v3 + 0x48);
        v16 = ((__int64 (__fastcall *)(__int64, __int64, unsigned __int64))guard_dispatch_icall_no_overrides)(
                v15,
                3LL,
                v13);
        v17 = v16;
        if ( v16 < 0 )
          HalpTimerSetProblemEx(v3, 18, v16, (__int64)"minkernel\\hals\\lib\\timers\\common\\timersup.c", 0x30Eu);
      }
      else
      {
        v17 = -1073741811;
      }
    }
    else
    {
      v17 = -1073741675;
    }
  }
  else
  {
    HalpTimerLastProblem = 17;
    *(_QWORD *)(v3 + 264) = "minkernel\\hals\\lib\\timers\\common\\timersup.c";
    v17 = -1073741637;
    *(_QWORD *)(v3 + 252) = 17LL;
    *(_DWORD *)(v3 + 272) = 671;
  }
LABEL_17:
  *a3 = v9;
  if ( v17 < 0 )
    KeBugCheckEx(0x5Cu, 0x110uLL, v3, HalpTimerLastProblem, v17);
  return (unsigned int)v17;
}