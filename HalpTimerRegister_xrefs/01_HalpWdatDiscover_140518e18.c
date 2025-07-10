/* Function: HalpWdatDiscover @ 0x140518e18 (call depth 1) */

__int64 HalpWdatDiscover()
{
  __int64 AcpiTable; // rbx
  __int64 v1; // rcx
  __int64 v2; // rax
  int v3; // ecx
  __int64 v4; // rdi
  char v5; // si
  unsigned int v6; // r15d
  unsigned int v7; // r8d
  unsigned int v8; // r12d
  int v9; // r14d
  unsigned __int64 i; // rdx
  int v11; // eax
  int v12; // edx
  int v13; // ecx
  __int64 v14; // r8
  unsigned __int64 v15; // rcx
  int v17; // [rsp+38h] [rbp-D0h] BYREF
  int v18; // [rsp+3Ch] [rbp-CCh] BYREF
  int v19; // [rsp+40h] [rbp-C8h] BYREF
  __int64 v20; // [rsp+48h] [rbp-C0h] BYREF
  _QWORD v21[11]; // [rsp+50h] [rbp-B8h] BYREF
  int v22; // [rsp+A8h] [rbp-60h]
  int v23; // [rsp+ACh] [rbp-5Ch]
  __int64 v24; // [rsp+B0h] [rbp-58h]
  int v25; // [rsp+BCh] [rbp-4Ch]
  int v26; // [rsp+D0h] [rbp-38h]
  int v27; // [rsp+D4h] [rbp-34h]
  _BYTE v28[8]; // [rsp+D8h] [rbp-30h] BYREF
  __int64 v29; // [rsp+E0h] [rbp-28h]
  unsigned int v30; // [rsp+E8h] [rbp-20h]
  unsigned int v31; // [rsp+ECh] [rbp-1Ch]
  unsigned int v32; // [rsp+F0h] [rbp-18h]
  __int128 v33; // [rsp+148h] [rbp+40h] BYREF

  v19 = 0;
  v18 = 0;
  memset_0(v21, 0, 0x88uLL);
  memset_0(v28, 0, 0x70uLL);
  v20 = 0x9000000001LL;
  v33 = 0LL;
  AcpiTable = 0LL;
  LOBYTE(v17) = 0;
  if ( !(unsigned __int8)HalpIsMicrosoftCompatibleHvLoaded(v1)
    || !HalpHvCpuManager
    || (HviGetHardwareFeatures(&v33), (v33 & 0x2000000) == 0) )
  {
    AcpiTable = HalSocGetAcpiTable(1413563479LL);
  }
  v2 = HalSocGetAcpiTable(1414677591LL);
  v4 = v2;
  if ( AcpiTable )
  {
    if ( (*(_BYTE *)(AcpiTable + 60) & 1) != 0 )
    {
      v5 = 1;
      v6 = *(_DWORD *)(AcpiTable + 52);
      v7 = *(_DWORD *)(AcpiTable + 56);
      v8 = *(_DWORD *)(AcpiTable + 48);
      v9 = (*(_DWORD *)(AcpiTable + 64) << 6) + 112;
      for ( i = 0LL; (unsigned int)i < *(_DWORD *)(AcpiTable + 64); i = (unsigned int)(i + 1) )
      {
        v3 = 3 * i;
        if ( *(_BYTE *)(AcpiTable + 24 * i + 68) == 6 )
          goto LABEL_15;
      }
      goto LABEL_28;
    }
    return 0LL;
  }
  if ( !v2 )
    return 0LL;
  v29 = v2;
  v11 = HalpWdatProcessWdrtInternalData(v2, v28, &v18, &v17);
  v5 = v17;
  if ( v11 >= 0 )
  {
    if ( !(_BYTE)v17 )
      return 0LL;
    v8 = v32;
    v7 = v31;
    v6 = v30;
    v9 = v18;
LABEL_15:
    if ( v8 && v6 >= v7 )
    {
      v25 = 163872;
      LOBYTE(v3) = 32;
      if ( (int)HalpWdatExecuteActionBeforeInitialize(v3, i, (unsigned int)&v19, AcpiTable, v4) >= 0 && v19 == 1 )
      {
        v25 = 426016;
        LOBYTE(v13) = 33;
        HalpWdatExecuteActionBeforeInitialize(v13, v12, 0, AcpiTable, v4);
      }
      v15 = v8 * (unsigned __int64)v6 / 0x3E8;
      if ( v15 > 0x12C436C73CE5LL )
      {
        v23 = 64;
LABEL_26:
        v21[2] = 0LL;
        v21[10] = 0LL;
        v27 = 0;
        v21[0] = HalpWdatInitialize;
        v21[3] = HalpWdatArmTimer;
        v21[4] = HalpWdatStop;
        v24 = 894000LL;
        v22 = v9;
        v26 = 13;
        HalpTimerRegister((__int64)&v20, 0LL, v14);
        goto LABEL_27;
      }
      i = 894000 * v15;
      v3 = 63;
      v23 = 63;
      do
      {
        if ( (1LL << v3) - 1 < i )
          break;
        --v3;
      }
      while ( v3 );
      v23 = v3;
      if ( v3 )
        goto LABEL_26;
    }
  }
LABEL_27:
  if ( v5 )
  {
LABEL_28:
    LOBYTE(v3) = 11;
    HalpWdatExecuteActionBeforeInitialize(v3, i, 0, AcpiTable, v4);
  }
  return 0LL;
}
