__int64 __fastcall ExtEnvSetVpptTarget(__int64 a1, unsigned int a2)
{
  __int64 v2; // rbx
  _DWORD *v3; // rdi
  unsigned int v4; // ecx
  unsigned int v5; // eax
  int v6; // eax
  signed int v7; // ebx
  unsigned int v8; // esi
  _DWORD *LinesForGsiRange; // rax
  int v10; // ecx
  char v11; // r14
  char v12; // al
  __int64 *v13; // rdx
  __int64 *v14; // r8
  __int64 v15; // rdx
  __int64 v16; // r8
  __int64 v17; // r9
  unsigned int v18; // r14d
  _DWORD *v19; // rax
  __int64 v20; // rax
  _QWORD *v21; // rdx
  _QWORD *v22; // rax
  _DWORD *v23; // rcx
  signed int v24; // r8d
  int v25; // ebx
  int v26; // eax
  __int64 result; // rax
  __int64 v28; // [rsp+38h] [rbp-39h] BYREF
  __int128 v29; // [rsp+40h] [rbp-31h] BYREF
  int v30; // [rsp+58h] [rbp-19h] BYREF
  int v31; // [rsp+5Ch] [rbp-15h]
  char v32; // [rsp+60h] [rbp-11h]
  int v33; // [rsp+64h] [rbp-Dh]
  int v34; // [rsp+68h] [rbp-9h]
  __int128 v35; // [rsp+70h] [rbp-1h]
  int v36; // [rsp+80h] [rbp+Fh]
  int v37; // [rsp+90h] [rbp+1Fh]

  v2 = a2;
  v29 = 0LL;
  memset_0(&v30, 0, 0x58uLL);
  v3 = (_DWORD *)HalpAlwaysOnTimer;
  v4 = *((_DWORD *)KiGlobalState + v2);
  *((_QWORD *)&v29 + 1) = (unsigned __int16)(v4 >> 6);
  *(_QWORD *)&v29 = 1LL << (v4 & 0x3F);
  if ( HalpAlwaysOnTimer && *(_DWORD *)(HalpAlwaysOnTimer + 0xE4) == 12 )
  {
    v31 = 0xD3;
    v5 = v36 & 0xC0000000 | 4;
  }
  else
  {
    v3 = (_DWORD *)HalpClockTimer;
    if ( *(_DWORD *)(HalpClockTimer + 228) != 12 )
      KeBugCheckEx(0x5Cu, 0x114uLL, 0LL, 0xFFFFFFFFC00000BBuLL, 0LL);
    v5 = v36 & 0xC0000000;
    v31 = 209;
  }
  v32 = 13;
  v36 = v5 | 0x40000000;
  v33 = v3[23];
  v34 = v3[24];
  v6 = v3[56];
  v35 = v29;
  if ( (v6 & 0x200) != 0 )
  {
    LinesForGsiRange = (_DWORD *)HalpInterruptFindLinesForGsiRange((unsigned int)v3[22], (unsigned int)(v3[22] + 1));
    if ( !LinesForGsiRange )
      KeBugCheckEx(0x5Cu, 0x114uLL, (ULONG_PTR)v3, 0xFFFFFFFFC0000225uLL, 1uLL);
    v8 = LinesForGsiRange[4];
    v7 = v10 + LinesForGsiRange[5] - LinesForGsiRange[7];
  }
  else
  {
    if ( (v6 & 0x100) == 0 )
      KeBugCheckEx(0x5Cu, 0x114uLL, (ULONG_PTR)v3, 0xFFFFFFFFC00000BBuLL, 2uLL);
    v7 = v3[21];
    if ( (unsigned int)v7 >= 8 )
    {
      v8 = 0xB001;
      v7 -= 8;
    }
    else
    {
      v8 = 0xB000;
    }
  }
  v11 = 0;
  v12 = HalpAcquireHighLevelLock(&HalpInterruptOverridesLock);
  v14 = (__int64 *)HalpInterruptOverrides;
  while ( v14 != &HalpInterruptOverrides )
  {
    v13 = v14;
    v14 = (__int64 *)*v14;
    if ( *((_DWORD *)v13 + 4) == v8 && *((_DWORD *)v13 + 5) == v7 )
    {
      v11 = 1;
      v28 = v13[3];
      v7 = HIDWORD(v28);
      v8 = v28;
      v33 = *((_DWORD *)v13 + 9);
      v34 = *((_DWORD *)v13 + 8);
      break;
    }
  }
  LOBYTE(v13) = v12;
  HalpReleaseHighLevelLock(&HalpInterruptOverridesLock, v13);
  if ( !v11 && *(_DWORD *)(HalpInterruptController + 240) == 2 && v8 - 45056 <= 1 )
  {
    v18 = v7;
    if ( v8 == 0xB001 )
      v18 = v7 + 8;
    v19 = (_DWORD *)HalpInterruptFindLinesForGsiRange(v18, v18 + 1);
    if ( v19 )
    {
      v8 = v19[4];
      v7 = v18 + v19[5] - v19[7];
    }
  }
  v20 = HalpInterruptLookupController(v8, v15, v16, v17);
  if ( !v20 )
    goto LABEL_28;
  v21 = (_QWORD *)(v20 + 0x108);
  v22 = *(_QWORD **)(v20 + 0x108);
  do
  {
    if ( v22 == v21 )
      goto LABEL_28;
    v23 = v22;
    v22 = (_QWORD *)*v22;
    v24 = v23[5];
  }
  while ( v24 > v7 || v23[6] <= v7 );
  v25 = v7 - v24;
  if ( !v23 || (v26 = v23[7], v26 == -1) )
LABEL_28:
    KeBugCheckEx(0x5Cu, 0x114uLL, (ULONG_PTR)v3, 0xFFFFFFFFC000000DuLL, 3uLL);
  v30 = 0;
  LODWORD(v28) = v25 + v26;
  v37 = v25 + v26;
  result = HalpInterruptSetDestination(&v30, &v29, &v28);
  if ( (int)result < 0 )
    KeBugCheckEx(0x5Cu, 0x114uLL, (ULONG_PTR)v3, (int)result, 4uLL);
  return result;
}