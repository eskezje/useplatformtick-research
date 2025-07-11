__int64 __fastcall HalpTimerConfigureInterrupt(
        __int64 a1,
        unsigned int a2,
        char a3,
        __int64 a4,
        __int64 a5,
        unsigned int a6,
        __int128 *a7,
        __int64 a8)
{
  __int128 v11; // xmm0
  __int64 v12; // rcx
  __int64 v13; // r9
  int v14; // edi
  int v15; // eax
  __int64 InternalData; // rax
  __int64 v17; // r8
  __int64 v18; // r9
  int *v19; // rcx
  int v20; // eax
  __int64 v21; // rax
  __int64 v22; // rdx
  _QWORD *v23; // r8
  int v24; // eax
  __int64 v25; // r9
  __int64 v26; // rcx
  int v27; // eax
  int v28; // eax
  int v29; // esi
  int *v30; // rdi
  unsigned int v31; // eax
  __int64 v32; // rax
  int v33; // eax
  int v34; // eax
  char v35; // di
  int v36; // r8d
  int v37; // eax
  __int64 v38; // rdx
  __int64 v40; // [rsp+40h] [rbp-A9h] BYREF
  _DWORD v41[2]; // [rsp+48h] [rbp-A1h] BYREF
  __int64 v42; // [rsp+50h] [rbp-99h] BYREF
  int FirstSetRightGroupAffinity; // [rsp+58h] [rbp-91h]
  int v44; // [rsp+5Ch] [rbp-8Dh]
  __int128 *v45; // [rsp+60h] [rbp-89h]
  __int128 v46; // [rsp+68h] [rbp-81h] BYREF
  _DWORD v47[2]; // [rsp+80h] [rbp-69h] BYREF
  char v48; // [rsp+88h] [rbp-61h]
  int v49; // [rsp+8Ch] [rbp-5Dh] BYREF
  int v50; // [rsp+90h] [rbp-59h] BYREF
  __int128 v51; // [rsp+98h] [rbp-51h]
  unsigned int v52; // [rsp+A8h] [rbp-41h]
  int v53; // [rsp+ACh] [rbp-3Dh]
  int v54; // [rsp+B0h] [rbp-39h]
  unsigned int v55; // [rsp+B4h] [rbp-35h]
  _BYTE v56[40]; // [rsp+B8h] [rbp-31h] BYREF

  v44 = 0;
  v40 = 0LL;
  v42 = 6LL;
  v46 = 0LL;
  memset_0(v47, 0, 0x58uLL);
  v11 = *a7;
  v47[1] = a2;
  v48 = a3;
  v52 = a6 & 0x3FFFFFFF | v52 & 0xC0000000 | 0x40000000;
  v51 = v11;
  FirstSetRightGroupAffinity = KeFindFirstSetRightGroupAffinity((__int64)a7);
  v45 = &v46;
  v14 = 0xC00000BB;
  LODWORD(v46) = a6 & 0x3FFFFFFF;
  v15 = *(_DWORD *)(a1 + 224);
  if ( (v15 & 0x800) != 0 )
  {
    InternalData = HalpTimerGetInternalData(a1);
    ((void (__fastcall *)(__int64, _QWORD, __int64))guard_dispatch_icall_no_overrides)(InternalData, a2, v17);
    HalpInterruptSetIdtEntry(a2, a8, a3, v18, a5);
    return 0;
  }
  if ( (v15 & 0x400) == 0 )
    goto LABEL_11;
  LOBYTE(v12) = 1;
  if ( !HalpInterruptIsMsiSupported(v12) || (*(_DWORD *)(a1 + 0xB8) & 0x50) == 0x40 )
    goto LABEL_11;
  HalpInterruptSetIdtEntry(a2, a8, a3, v13, a5);
  if ( (*(_DWORD *)(a1 + 184) & 0x40) != 0 )
    goto LABEL_9;
  v19 = *(int **)(a1 + 288);
  v49 = 0;
  v47[0] = 3;
  v50 = 1;
  v14 = HalpInterruptRemap(*v19, v19[1], (int)v19 + 8, 0, (__int64)v47, 1);
  if ( v14 >= 0 )
  {
    v20 = v53;
    *(_DWORD *)(a1 + 0xB8) |= 0x40u;
    *(_DWORD *)(a1 + 0xEC) = v20;
    *(_DWORD *)(a1 + 0xE8) = v54;
    *(_QWORD *)(a1 + 0xF0) = v55;
LABEL_9:
    v21 = HalpTimerGetInternalData(a1);
    LOBYTE(v22) = 1;
    v24 = ((__int64 (__fastcall *)(__int64, __int64, _QWORD))guard_dispatch_icall_no_overrides)(v21, v22, *v23);
    v14 = v24;
    if ( v24 >= 0 )
    {
      *(_DWORD *)(a1 + 184) |= 0x10u;
      return 0;
    }
    HalpTimerSetProblemEx(a1, 24, v24, (__int64)"minkernel\\hals\\lib\\timers\\common\\timersup.c", 0x8EEu);
    LOBYTE(v25) = 1;
    HalpTimerUnmapInterrupt(v26, a2, a6, v25);
  }
LABEL_11:
  v27 = *(_DWORD *)(a1 + 0xE0);
  if ( (v27 & 0x200) != 0 )
  {
    v28 = HalpInterruptGsiToLine(*(unsigned int *)(a1 + 88), &v40);
    v29 = v28;
    if ( v28 < 0 )
    {
      HalpTimerSetProblemEx(a1, 16, v28, (__int64)"minkernel\\hals\\lib\\timers\\common\\timersup.c", 0x164u);
      return (unsigned int)v29;
    }
    v30 = (int *)(a1 + 92);
  }
  else
  {
    if ( (v27 & 0x100) == 0 )
    {
      HalpTimerSetProblemEx(a1, 17, v14, (__int64)"minkernel\\hals\\lib\\timers\\common\\timersup.c", 0x173u);
      return 0xC000000D;
    }
    v31 = *(_DWORD *)(a1 + 0x54);
    if ( v31 >= 8 )
    {
      LODWORD(v40) = 0xB001;
      v31 -= 8;
    }
    else
    {
      LODWORD(v40) = 0xB000;
    }
    v30 = (int *)(a1 + 0x5C);
    HIDWORD(v40) = v31;
    if ( !*(_DWORD *)(a1 + 0x5C) )
    {
      *v30 = 1;
      *(_DWORD *)(a1 + 0x60) = 1;
    }
  }
  HalpInterruptSetIdtEntry(a2, a8, a3, v13, a5);
  if ( (*(_DWORD *)(a1 + 184) & 0x10) == 0 )
    goto LABEL_27;
  v32 = HalpTimerGetInternalData(a1);
  v33 = ((__int64 (__fastcall *)(__int64, _QWORD, _QWORD))guard_dispatch_icall_no_overrides)(v32, 0LL, 0LL);
  v29 = v33;
  if ( v33 < 0 )
  {
    HalpTimerSetProblemEx(a1, 24, v33, (__int64)"minkernel\\hals\\lib\\timers\\common\\timersup.c", 0x18Eu);
    return (unsigned int)v29;
  }
  *(_DWORD *)(a1 + 0xB8) &= ~0x10u;
  if ( (*(_DWORD *)(a1 + 0xB8) & 0x10) == 0 )
  {
LABEL_27:
    if ( a2 == 0xD1 )
    {
      HalpTimerCriticalClockSource[0] = v40;
      HalpTimerCriticalClockSourceCount = 1;
    }
  }
  v34 = *(_DWORD *)(a1 + 96);
  v47[0] = 0;
  v50 = v34;
  v49 = *v30;
  HalpInterruptApplyOverrides((__int64)&v40, &v49, &v50);
  v29 = HalpInterruptLineToGsi(&v40, v56);
  if ( v29 >= 0 )
  {
    if ( (*(_DWORD *)(a1 + 0xB8) & 0x40) == 0 )
    {
      v29 = HalpInterruptRemap(
              **(_DWORD **)(a1 + 0x120),
              *(_DWORD *)(*(_QWORD *)(a1 + 0x120) + 4LL),
              (unsigned int)*(_QWORD *)(a1 + 0x120) + 8,
              0,
              (__int64)v47,
              1);
      if ( v29 < 0 )
        return (unsigned int)v29;
      *(_DWORD *)(a1 + 184) |= 0x40u;
    }
    v41[0] = -1;
    v41[1] = 1;
    v35 = HalpAcquireHighLevelLock(&HalpInterruptLock);
    LOBYTE(v36) = a3;
    v37 = HalpInterruptSetLineState((unsigned int)&v40, a2, v36, v50, v49, (__int64)&v42, (__int64)v41);
    LOBYTE(v38) = v35;
    v29 = v37;
    HalpReleaseHighLevelLock(&HalpInterruptLock, v38);
    if ( v29 >= 0 )
      return 0;
  }
  return (unsigned int)v29;
}