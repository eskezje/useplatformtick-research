__int64 __fastcall HalpSetTimer(__int64 a1, int a2, unsigned __int64 a3, char a4, unsigned __int64 *a5)
{
  unsigned int v5; // r11d
  unsigned __int64 v8; // rdi
  unsigned __int64 v9; // rcx
  unsigned __int128 v10; // rax
  unsigned int v11; // ecx
  unsigned __int64 v12; // rbp
  unsigned __int64 v13; // rax
  __int64 v14; // rcx
  int v15; // eax
  int v17; // r8d
  int v18; // edx
  unsigned int v19; // [rsp+20h] [rbp-38h]

  v5 = 0;
  v8 = 0LL;
  if ( a2 == 3 )
  {
    if ( (*(_DWORD *)(a1 + 224) & 0x20) == 0 )
    {
      HalpTimerLastProblem = 17;
      *(_QWORD *)(a1 + 0x108) = "minkernel\\hals\\lib\\timers\\common\\timersup.c";
      v5 = 0xC00000BB;
      *(_QWORD *)(a1 + 0xFC) = 0x11LL;
      *(_DWORD *)(a1 + 0x110) = 0x29F;
      goto LABEL_12;
    }
    goto LABEL_3;
  }
  if ( a2 == 1 )
  {
    if ( (*(_DWORD *)(a1 + 0xE0) & 0x10) != 0 )
      goto LABEL_3;
    v19 = 692;
LABEL_29:
    v17 = 0;
    v18 = 0x11;
    goto LABEL_26;
  }
  if ( a2 != 2 )
  {
LABEL_20:
    v5 = 0xC000000D;
    goto LABEL_12;
  }
  if ( (*(_DWORD *)(a1 + 224) & 0x50) == 0 )
  {
    v19 = 0x2AB;
    goto LABEL_29;
  }
LABEL_3:
  v9 = *(_QWORD *)(a1 + 0xC0) * a3;
  if ( !is_mul_ok(*(_QWORD *)(a1 + 0xC0), a3) )
    goto LABEL_18;
  if ( a2 == 3 )
  {
    if ( *(_QWORD *)(a1 + 0xC0) * a3 + 9999999 >= v9 )
    {
      v9 = *(_QWORD *)(a1 + 0xC0) * a3 + 9999999;
      goto LABEL_5;
    }
LABEL_18:
    v5 = -1073741675;
    goto LABEL_12;
  }
LABEL_5:
  v10 = v9 * (unsigned __int128)0xD6BF94D5E57A42BDuLL;
  v11 = *(_DWORD *)(a1 + 220);
  v12 = *((_QWORD *)&v10 + 1) >> 23;
  if ( v11 < 0x40 && v12 >= 1LL << v11 )
    goto LABEL_20;
  if ( is_mul_ok(v12, 10000000000uLL) )
    v13 = v12 * (unsigned __int128)10000000000uLL / *(unsigned __int64 *)(a1 + 192);
  else
    v13 = HalpTimerScaleCounter(v12, *(_QWORD *)(a1 + 192), 10000000000LL);
  *(_QWORD *)(a1 + 16) = v12;
  *(_DWORD *)(a1 + 52) = 1;
  v8 = v13 / 1000;
  if ( a4 )
  {
    v14 = (*(_DWORD *)(a1 + 0xE0) & 0x10000) != 0
        ? *(_QWORD *)(a1 + 0x48) + *(_DWORD *)(a1 + 80) * KeGetPcr()->Prcb.Number
        : *(_QWORD *)(a1 + 0x48);
    v15 = guard_dispatch_icall_no_overrides(v14);
    v5 = v15;
    if ( v15 < 0 )
    {
      v19 = 0x30E;
      v17 = v15;
      v18 = 0x12;
LABEL_26:
      HalpTimerSetProblemEx(a1, v18, v17, (__int64)"minkernel\\hals\\lib\\timers\\common\\timersup.c", v19);
    }
  }
LABEL_12:
  *a5 = v8;
  return v5;
}