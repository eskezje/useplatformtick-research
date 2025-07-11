__int64 HalpHpetDiscover()
{
  __int64 AcpiTable; // rax
  __int64 v1; // rdx
  __int64 v2; // r14
  unsigned int *v3; // r15
  unsigned int v4; // esi
  unsigned int v5; // ebx
  unsigned __int64 v6; // rax
  int v7; // r12d
  int v8; // esi
  bool v9; // zf
  unsigned int v10; // esi
  unsigned int v11; // r13d
  __int64 v12; // rbx
  unsigned int *v13; // r15
  __int64 v14; // r8
  int v15; // eax
  unsigned int v16; // ebx
  int v17; // edi
  unsigned __int8 v18; // dl
  int v19; // eax
  char v20; // cl
  int v21; // r9d
  __int64 v22; // r8
  signed __int32 v24[8]; // [rsp+8h] [rbp-100h] BYREF
  int v25; // [rsp+28h] [rbp-E0h] BYREF
  unsigned int v26; // [rsp+30h] [rbp-D8h]
  __int64 v27; // [rsp+38h] [rbp-D0h] BYREF
  __int64 (__fastcall *v28)(); // [rsp+40h] [rbp-C8h]
  __int64 (__fastcall *v29)(); // [rsp+48h] [rbp-C0h]
  __int64 (__fastcall *v30)(); // [rsp+50h] [rbp-B8h]
  __int64 (__fastcall *v31)(); // [rsp+58h] [rbp-B0h]
  __int64 (__fastcall *v32)(); // [rsp+60h] [rbp-A8h]
  _OWORD *v33; // [rsp+90h] [rbp-78h]
  int v34; // [rsp+98h] [rbp-70h]
  int v35; // [rsp+9Ch] [rbp-6Ch]
  __int64 v36; // [rsp+A0h] [rbp-68h]
  int v37; // [rsp+A8h] [rbp-60h]
  int v38; // [rsp+ACh] [rbp-5Ch]
  int v39; // [rsp+B0h] [rbp-58h]
  int v40; // [rsp+B4h] [rbp-54h]
  int v41; // [rsp+B8h] [rbp-50h]
  int v42; // [rsp+BCh] [rbp-4Ch]
  int v43; // [rsp+C0h] [rbp-48h]
  int v44; // [rsp+C4h] [rbp-44h]
  __int64 v45; // [rsp+C8h] [rbp-40h]
  unsigned int *v46; // [rsp+D0h] [rbp-38h]
  unsigned __int64 v47; // [rsp+D8h] [rbp-30h]
  _OWORD v48[2]; // [rsp+E0h] [rbp-28h] BYREF
  __int64 v49; // [rsp+100h] [rbp-8h]

  LOWORD(v25) = 0;
  memset(v48, 0, sizeof(v48));
  v49 = 0LL;
  AcpiTable = HalSocGetAcpiTable(1413828680LL);
  v2 = AcpiTable;
  if ( AcpiTable )
  {
    if ( !*(_BYTE *)(AcpiTable + 40) && (int)HalSocRequestConfigurationData(1LL, v1, (char *)&v25 + 1) >= 0 )
    {
      HalpHpetPhysicalAddress = *(LARGE_INTEGER *)(v2 + 44);
      if ( !HalpHpetPhysicalAddress.HighPart || BYTE1(v25) )
      {
        v46 = (unsigned int *)HalMapIoSpace(HalpHpetPhysicalAddress, 0x400uLL, MmNonCached);
        v3 = v46;
        if ( v46 )
        {
          if ( HalRegisterPermanentAddressUsage(HalpHpetPhysicalAddress, 0x400u) >= 0 )
          {
            v4 = *v3;
            v5 = HIWORD(*v3);
            if ( v5 )
            {
              if ( v5 != 0xFFFF )
              {
                HalpHpetComparatorLatchDelay = 2;
                if ( RtlCompareMemory((const void *)(v2 + 10), "VMWARE", 6uLL) == 6 )
                  HalpHpetComparatorLatchDelay = 1;
                if ( (v4 & 0x8000) != 0 )
                  HalpHpetLegacyInterrupts = 1;
                v6 = (((unsigned __int64)v3[1] >> 1) + 1000000000000000LL) / v3[1];
                v47 = v6;
                if ( v5 == 4318 )
                {
                  HalpHpetLegacyInterrupts = 0;
                  goto LABEL_43;
                }
                v7 = 1;
                v8 = (v4 >> 8) & 0x1F;
                v9 = v8 == -1;
                v10 = v8 + 1;
                v11 = 0;
                if ( !v9 )
                {
                  v12 = (unsigned int)v6;
                  v13 = v3 + 64;
                  v45 = (unsigned int)v6;
                  while ( 1 )
                  {
                    memset_0(&v27, 0, 0x90uLL);
                    v33 = v48;
                    v49 = 0LL;
                    v28 = HalpHpetInitialize;
                    v36 = v12;
                    v30 = HalpHpetAcknowledgeInterrupt;
                    memset((char *)v48 + 4, 0, 20);
                    v27 = 0x9000000001LL;
                    v31 = HalpHpetArmTimer;
                    v32 = HalpHpetStop;
                    v15 = (v11 + 1) | (*(unsigned __int8 *)(v2 + 52) << 16);
                    LODWORD(v48[0]) = v11;
                    v44 = v15;
                    *((LARGE_INTEGER *)&v48[1] + 1) = HalpHpetPhysicalAddress;
                    v16 = *v13 & 0xFFFFBFFB;
                    v35 = 31;
                    v34 = 40;
                    v42 = 1;
                    v41 = 1;
                    v43 = 3;
                    v37 = 1;
                    v38 = 48;
                    *v13 = v16;
                    v26 = v11 + 1;
                    _InterlockedOr(v24, 0);
                    if ( (v16 & 0x10) != 0 )
                    {
                      v17 = 112;
                      BYTE12(v48[0]) = 1;
                      v38 = 112;
                    }
                    else
                    {
                      v17 = v38;
                    }
                    if ( (v16 & 0x20) != 0 )
                    {
                      *v13 = v16 | 0x100;
                      _InterlockedOr(v24, 0);
                      v16 = *v13;
                      if ( (*v13 & 0x100) == 0 )
                        goto LABEL_41;
                      v17 = v38;
                    }
                    v18 = 0;
                    LODWORD(v49) = v16;
                    if ( HalpHpetLegacyInterrupts )
                    {
                      v19 = HalSocRequestConfigurationData(2LL, 0LL, &v25);
                      v20 = v25;
                      if ( v19 < 0 )
                        v20 = 0;
                      LOBYTE(v25) = v20;
                      if ( !v11 )
                      {
                        v17 |= 0x100u;
                        v38 = v17;
                        v39 = v20 == 0 ? 2 : 0;
                        v7 |= 4u;
                        goto LABEL_39;
                      }
                      if ( v11 == 1 )
                      {
                        v39 = 8;
                        v17 |= 0x100u;
                        v38 = v17;
                        v7 |= 0x100u;
LABEL_39:
                        if ( (v17 & 0xF00) != 0 )
                          HalpTimerRegister((__int64)&v27, 0LL, v14);
                        goto LABEL_41;
                      }
                      if ( (v16 & 0x8000) != 0 )
                        goto LABEL_39;
                    }
                    else
                    {
                      v21 = ~v7 & v13[1];
                      if ( v21 )
                      {
                        while ( v18 < 0x20u )
                        {
                          v14 = (unsigned int)(1 << v18);
                          if ( ((unsigned int)v14 & v21) != 0 )
                          {
                            LOWORD(v17) = v38 | 0x200;
                            v38 |= 0x200u;
                            v40 = v18 + (unsigned __int16)HalpHpetGsiOffset;
                            v7 |= v14;
                            BYTE4(v48[0]) = v18;
                            goto LABEL_39;
                          }
                          ++v18;
                        }
                        LOWORD(v17) = v38;
                        goto LABEL_39;
                      }
                    }
LABEL_41:
                    v11 = v26;
                    v13 += 8;
                    v12 = v45;
                    if ( v26 >= v10 )
                    {
                      v3 = v46;
                      break;
                    }
                  }
                }
LABEL_43:
                memset_0(&v27, 0, 0x90uLL);
                v27 = 0x9000000001LL;
                v49 = 0LL;
                v36 = (unsigned int)v47;
                memset(v48, 0, sizeof(v48));
                LODWORD(v48[0]) = -1;
                v33 = v48;
                v28 = HalpHpetInitialize;
                v29 = HalpHpetQueryCounter;
                v30 = HalpHpetAcknowledgeInterrupt;
                v31 = HalpHpetArmTimer;
                v44 = *(unsigned __int8 *)(v2 + 52) << 16;
                v35 = 32;
                v34 = 40;
                v43 = 3;
                v37 = 1;
                v38 = 2;
                HalpTimerRegister((__int64)&v27, 0LL, v22);
              }
            }
          }
          HalpUnmapVirtualAddress(v3, 1LL, 0LL);
        }
      }
    }
  }
  return 0LL;
}