void *__fastcall HalpNumaInitializeStaticConfiguration(__int64 a1)
{
  __int64 v1; // r14
  void *result; // rax
  unsigned int v3; // edi
  unsigned int v4; // ebx
  __int64 v5; // rdx
  unsigned int v6; // edi
  unsigned int v7; // eax
  __int64 v8; // r8
  unsigned int v9; // r15d
  unsigned int v10; // ebx
  char v11; // r12
  int v12; // r13d
  __int64 v13; // r10
  unsigned __int64 v14; // rdi
  __int64 v15; // rsi
  __int64 v16; // rax
  unsigned __int8 *v17; // r10
  __int64 v18; // r11
  int v19; // r8d
  unsigned int v20; // ecx
  __int64 v21; // r11
  _DWORD *v22; // rax
  int v23; // r9d
  unsigned __int64 v24; // r9
  __int64 v25; // rcx
  unsigned __int64 v26; // r11
  __int64 v27; // rcx
  __int64 v28; // rcx
  _QWORD *v29; // rax
  __int64 v30; // rcx
  int v31; // eax
  int v32; // r9d
  __int64 v33; // rcx
  __int64 v34; // r10
  __int64 v35; // rdx
  unsigned int v36; // edx
  __int64 v37; // rcx
  __int64 v38; // r9
  __int64 v39; // r10
  __int64 v40; // r8
  unsigned int i; // edx
  __int64 Table; // rax
  __int64 v43; // rdx
  __int64 v44; // rcx
  __int64 v45; // r8
  __int64 v46; // r10
  unsigned int v47; // r11d
  unsigned int m; // r9d
  unsigned int v49; // edi
  int v50; // edi
  unsigned int n; // ebx
  __int16 v52; // ax
  __int64 v53; // rcx
  __int64 v54; // rax
  unsigned int *v55; // r9
  unsigned int *v56; // rsi
  __int64 v57; // rax
  unsigned int *v58; // rdi
  int v59; // ebx
  unsigned int *v60; // r12
  unsigned int v61; // r10d
  _QWORD *v62; // r15
  unsigned int v63; // r11d
  unsigned int j; // r8d
  unsigned int v65; // r11d
  unsigned int v66; // edx
  _DWORD *v67; // rax
  __int64 v68; // rdx
  unsigned int v69; // eax
  unsigned int v70; // r9d
  __int64 v71; // rcx
  __int64 v72; // rbx
  unsigned int v73; // edi
  unsigned int k; // esi
  int v75; // r15d
  int AvailableProximityId; // eax
  __int64 v77; // r10
  int v78; // r12d
  __int64 v79; // rcx
  unsigned int v80; // r11d
  int v81; // r9d
  int v82; // r9d
  __int64 v83; // rax
  __int64 v84; // rcx
  __int64 v85; // r11
  bool v86; // zf
  unsigned int v87; // [rsp+40h] [rbp-18h] BYREF
  unsigned int v88; // [rsp+44h] [rbp-14h] BYREF
  unsigned int v89[4]; // [rsp+48h] [rbp-10h] BYREF
  unsigned __int8 v91; // [rsp+A8h] [rbp+50h]
  __int64 v92; // [rsp+A8h] [rbp+50h]
  unsigned int v93; // [rsp+B8h] [rbp+60h] BYREF

  v93 = 0;
  v89[0] = 0;
  v1 = a1;
  v87 = 0;
  v88 = 0;
  HalpNumaInitializationComplete = 1;
  HalpAcpiMpst = HalpAcpiGetTable(a1, 1414746189, 0, 0);
  HalpAcpiSrat = HalpAcpiGetTable(v1, 1413567059, 0, 0);
  HalpAcpiMsct = HalpAcpiGetTable(v1, 1413698381, 0, 0);
  if ( !HalpAcpiSrat )
    return (void *)HalpInitializeConfigurationFromMadt(v1);
  v91 = *(_BYTE *)(HalpAcpiSrat + 8);
  result = (void *)HalpGetNumaProcMemoryCount(v89, &v88, &v87, &v93);
  if ( (_BYTE)result )
  {
    v3 = v87;
    v4 = v88;
    result = (void *)HalpAllocateNumaConfigData(v89[0], v88, v87, v93);
    if ( HalpNumaConfig )
    {
      if ( !v3
        || (result = (void *)HalpMmAllocateMemoryInternal(24 * v3, 1u), (HalpNumaSratMemoryRanges = result) != 0LL) )
      {
        v6 = 0;
        if ( v4 )
        {
          if ( v4 >= 4 )
          {
            v5 = HalpNumaConfig;
            if ( *(_QWORD *)HalpNumaConfig > (unsigned __int64)HalpNumaConfig
              || *(_QWORD *)HalpNumaConfig + 4 * (unsigned __int64)(v4 - 1) < HalpNumaConfig )
            {
              v7 = v4 & 0xFFFFFFFC;
              do
                v6 += 4;
              while ( v6 < v7 );
              memset_0(*(void **)HalpNumaConfig, -1, 16 * ((unsigned __int64)v7 >> 2));
            }
          }
          if ( v6 < v4 )
          {
            v5 = 4LL * v6;
            v8 = v4 - v6;
            do
            {
              *(_DWORD *)(v5 + *(_QWORD *)HalpNumaConfig) = -1;
              v5 += 4LL;
              --v8;
            }
            while ( v8 );
          }
        }
        v9 = 0;
        v10 = 0;
        v11 = 0;
        v12 = 0;
        v13 = HalpAcpiSrat + 48;
        v14 = HalpAcpiSrat + *(unsigned int *)(HalpAcpiSrat + 4);
        if ( HalpAcpiSrat + 50 <= v14 )
        {
          v15 = HalpNumaConfig;
          while ( 1 )
          {
            v16 = *(unsigned __int8 *)(v13 + 1);
            if ( (unsigned __int8)v16 < 2u || v13 + v16 > v14 )
            {
LABEL_58:
              v1 = a1;
              goto LABEL_59;
            }
            LOBYTE(v5) = v91 >= 3u;
            if ( (unsigned __int8)HalpVerifySratEntryLengthAndFlag(v13, v5) )
              break;
            v13 = v18;
LABEL_57:
            if ( v13 + 2 > v14 )
              goto LABEL_58;
          }
          if ( *(_BYTE *)(HalpAcpiSrat + 8) == 1 )
          {
            v19 = v17[2];
          }
          else if ( *v17 )
          {
            if ( *v17 == 2 )
              v19 = *((_DWORD *)v17 + 1);
            else
              v19 = *(_DWORD *)(v17 + 2);
          }
          else
          {
            v19 = v17[2] + ((v17[9] + ((v17[10] + (v17[11] << 8)) << 8)) << 8);
          }
          v20 = *(_DWORD *)(v15 + 56);
          v21 = 0LL;
          if ( v20 )
          {
            v22 = *(_DWORD **)(v15 + 24);
            do
            {
              if ( v19 == *v22 )
                break;
              v21 = (unsigned int)(v21 + 1);
              ++v22;
            }
            while ( (unsigned int)v21 < v20 );
          }
          if ( (_DWORD)v21 == v20 )
          {
            *(_DWORD *)(*(_QWORD *)(v15 + 24) + 4 * v21) = v19;
            *(_DWORD *)(*(_QWORD *)(HalpNumaConfig + 32) + 4 * v21) = v19;
            ++*(_DWORD *)(v15 + 56);
          }
          v5 = *v17;
          switch ( *v17 )
          {
            case 0u:
              goto LABEL_39;
            case 1u:
              v24 = *((_QWORD *)v17 + 1) >> 12;
              v25 = *((_QWORD *)v17 + 2) >> 12;
              v26 = v25 + v24 - 1;
              if ( v24 < HalpMinNumaPage )
                HalpMinNumaPage = *((_QWORD *)v17 + 1) >> 12;
              if ( v26 > HalpMaxNumaPage )
                HalpMaxNumaPage = v25 + v24 - 1;
              HalpNumaPageCount += v25;
              v27 = 2LL * v10;
              v5 = v10++;
              *((_QWORD *)HalpNumaMemoryRanges + v27) = v24;
              *((_DWORD *)HalpNumaMemoryRanges + 2 * v27 + 2) = v19;
              v28 = 3 * v5;
              v29 = HalpNumaSratMemoryRanges;
              *((_QWORD *)HalpNumaSratMemoryRanges + v28 + 1) = v24;
              v29[v28 + 2] = v26;
              LODWORD(v29[v28]) = v19;
              break;
            case 2u:
LABEL_39:
              if ( (_BYTE)v5 )
              {
                v23 = *((_DWORD *)v17 + 2);
              }
              else
              {
                v23 = v17[3];
                if ( v23 == 255 )
                  v23 = -1;
              }
              v5 = HalpNumaConfig;
              v30 = v9;
              *(_DWORD *)(*(_QWORD *)HalpNumaConfig + 4LL * v9++) = v23;
              *(_DWORD *)(*(_QWORD *)(v5 + 16) + 4 * v30) = v19;
              ++*(_DWORD *)(*(_QWORD *)(v5 + 40) + 4 * v21);
              if ( v91 >= 3u )
              {
                if ( *v17 )
                  v31 = *((_DWORD *)v17 + 4);
                else
                  v31 = *((_DWORD *)v17 + 3);
                if ( v11 )
                {
                  if ( v12 != v31 )
                    HalpMaximumClockDomainCount = 2;
                }
                else
                {
                  v11 = 1;
                  v12 = v31;
                }
              }
              break;
          }
          v13 = (__int64)&v17[v17[1]];
          goto LABEL_57;
        }
LABEL_59:
        HalpNumaMemoryRangeCount = v10;
        LODWORD(HalpNumaSratMemoryRangeCount) = v10;
        *(_DWORD *)(HalpNumaConfig + 60) = v9;
        qsort(HalpNumaMemoryRanges, v10, 0x10uLL, HalpNodeCostSort);
        qsort(
          HalpNumaSratMemoryRanges,
          (unsigned int)HalpNumaSratMemoryRangeCount,
          0x18uLL,
          HalpCompareNumaMemoryRanges);
        v32 = 0;
        if ( v10 > 1 )
        {
          v33 = 0LL;
          v34 = v10 - 1;
          v35 = 16LL;
          do
          {
            if ( *(_DWORD *)((char *)HalpNumaMemoryRanges + v33 + 8) != *(_DWORD *)((char *)HalpNumaMemoryRanges
                                                                                  + v35
                                                                                  + 8) )
            {
              v33 = 16LL * (unsigned int)++v32;
              *(_OWORD *)((char *)HalpNumaMemoryRanges + v33) = *(_OWORD *)((char *)HalpNumaMemoryRanges + v35);
            }
            v35 += 16LL;
            --v34;
          }
          while ( v34 );
        }
        v36 = v32 + 1;
        v37 = 2LL * (unsigned int)(v32 + 1);
        HalpNumaMemoryRangeCount = v32 + 1;
        HalpNumaMaxMemoryRangeCount = v32 + 1;
        v38 = (unsigned int)(v32 + 1);
        *((_QWORD *)HalpNumaMemoryRanges + v37) = -1LL;
        *((_DWORD *)HalpNumaMemoryRanges + 4 * v36 + 2) = 0;
        *(_QWORD *)HalpNumaMemoryRanges = 0LL;
        if ( v36 )
        {
          v39 = HalpNumaConfig;
          v40 = 0LL;
          do
          {
            for ( i = 0; i < *(_DWORD *)(v39 + 56); ++i )
            {
              if ( *(_DWORD *)((char *)HalpNumaMemoryRanges + v40 + 8) == *(_DWORD *)(*(_QWORD *)(v39 + 24) + 4LL * i) )
              {
                *(_DWORD *)((char *)HalpNumaMemoryRanges + v40 + 8) = i;
                break;
              }
            }
            v40 += 16LL;
            --v38;
          }
          while ( v38 );
        }
        if ( HalpAcpiMsct )
          HalpUpdateConfigurationFromMsct(
            HalpNumaConfig + 56,
            *(_DWORD *)(HalpNumaConfig + 64),
            HalpNumaConfig + 60,
            *(_DWORD *)(HalpNumaConfig + 68),
            (__int64)&HalpMaximumClockDomainCount,
            *(_QWORD *)(HalpNumaConfig + 24),
            *(_QWORD *)(HalpNumaConfig + 40),
            *(_QWORD *)(HalpNumaConfig + 16));
        Table = HalpAcpiGetTable(v1, 1414089811, 0, 0);
        v46 = Table;
        if ( Table )
        {
          v47 = *(_DWORD *)(Table + 36);
          v44 = v47 * v47 + 44;
          if ( (unsigned int)v44 > *(_DWORD *)(Table + 4) )
          {
LABEL_87:
            v55 = *(unsigned int **)(*(_QWORD *)(v1 + 240) + 296LL);
            v56 = v55 + 1;
            if ( !HalpAcpiSlit )
            {
              if ( v55
                && (v43 = HalpNumaConfig,
                    v57 = *v55,
                    v58 = (unsigned int *)(HalpNumaConfig + 56),
                    (_DWORD)v57 == *(_DWORD *)(HalpNumaConfig + 56)) )
              {
                v59 = 0;
                v60 = &v56[v57];
                v61 = 0;
                v62 = (_QWORD *)(HalpNumaConfig + 24);
                while ( v61 < *v58 )
                {
                  v63 = *v55;
                  for ( j = 0; j < v63; ++j )
                  {
                    v44 = *(unsigned int *)(*v62 + 4LL * v61);
                    if ( v56[j] == (_DWORD)v44 )
                    {
                      v59 = v63 * j;
                      goto LABEL_98;
                    }
                  }
                  if ( j == v63 )
                    goto LABEL_107;
LABEL_98:
                  v65 = 0;
                  v45 = 1LL;
                  while ( v65 < *v58 )
                  {
                    v66 = *v55;
                    v44 = 0LL;
                    if ( *v55 )
                    {
                      v67 = v55 + 1;
                      do
                      {
                        if ( *v67 == *(_DWORD *)(*v62 + 4LL * v65) )
                          break;
                        v44 = (unsigned int)(v44 + 1);
                        ++v67;
                      }
                      while ( (unsigned int)v44 < v66 );
                    }
                    if ( (_DWORD)v44 == v66 )
                      goto LABEL_107;
                    v45 = 1LL;
                    v68 = v65 + *(_DWORD *)(HalpNumaConfig + 64) * v61;
                    ++v65;
                    *(_WORD *)(*(_QWORD *)(HalpNumaConfig + 48) + 2 * v68) = *((_WORD *)v60 + (unsigned int)(v59 + v44));
                  }
                  v43 = HalpNumaConfig;
                  v44 = v61 * (*(_DWORD *)(HalpNumaConfig + 64) + 1);
                  ++v61;
                  *(_WORD *)(*(_QWORD *)(HalpNumaConfig + 48) + 2 * v44) = 0;
                }
              }
              else
              {
LABEL_107:
                v43 = HalpNumaConfig;
                v45 = 0LL;
                v69 = *(_DWORD *)(HalpNumaConfig + 56);
                if ( v69 )
                {
                  do
                  {
                    v70 = 0;
                    if ( v69 )
                    {
                      do
                      {
                        v71 = v70 + *(_DWORD *)(v43 + 64) * (_DWORD)v45;
                        ++v70;
                        *(_WORD *)(*(_QWORD *)(v43 + 48) + 2 * v71) = 1;
                      }
                      while ( v70 < *(_DWORD *)(v43 + 56) );
                    }
                    v44 = (unsigned int)(v45 * (*(_DWORD *)(v43 + 64) + 1));
                    v45 = (unsigned int)(v45 + 1);
                    *(_WORD *)(*(_QWORD *)(v43 + 48) + 2 * v44) = 0;
                    v69 = *(_DWORD *)(v43 + 56);
                  }
                  while ( (unsigned int)v45 < v69 );
                }
              }
            }
            if ( HalpSplitLargeNumaNodes )
            {
              v72 = HalpNumaConfig;
              v92 = HalpNumaConfig;
              HalpNumaSortProcessors(
                *(unsigned int *)(HalpNumaConfig + 60),
                *(_QWORD *)(HalpNumaConfig + 16),
                *(_QWORD *)HalpNumaConfig);
              v73 = *(_DWORD *)(v72 + 56);
              for ( k = 0; k < v73; ++k )
              {
                v75 = HalpMaximumGroupSize;
                if ( *(_DWORD *)(*(_QWORD *)(v72 + 40) + 4LL * k) > (unsigned int)HalpMaximumGroupSize )
                {
                  AvailableProximityId = HalpGetAvailableProximityId();
                  v77 = HalpNumaConfig;
                  *(_DWORD *)(v72 + 56) = v73 + 1;
                  v78 = AvailableProximityId;
                  v79 = *(_QWORD *)(v72 + 40);
                  v80 = 0;
                  v81 = *(_DWORD *)(v79 + 4LL * k);
                  *(_DWORD *)(v79 + 4LL * k) = v75;
                  v82 = v81 - v75;
                  *(_DWORD *)(*(_QWORD *)(v72 + 40) + 4LL * v73) = v82;
                  *(_DWORD *)(*(_QWORD *)(v77 + 24) + 4LL * v73) = AvailableProximityId;
                  *(_DWORD *)(*(_QWORD *)(v77 + 32) + 4LL * v73) = *(_DWORD *)(*(_QWORD *)(v77 + 32) + 4LL * k);
                  if ( v73 )
                  {
                    do
                    {
                      *(_WORD *)(*(_QWORD *)(v77 + 48) + 2LL * (v73 + *(_DWORD *)(v77 + 64) * v80)) = *(_WORD *)(*(_QWORD *)(v77 + 48) + 2LL * (*(_DWORD *)(v77 + 64) * v80 + k));
                      v83 = v80 + k * *(_DWORD *)(v77 + 64);
                      v84 = v80 + v73 * *(_DWORD *)(v77 + 64);
                      ++v80;
                      *(_WORD *)(*(_QWORD *)(v77 + 48) + 2 * v84) = *(_WORD *)(*(_QWORD *)(v77 + 48) + 2 * v83);
                    }
                    while ( v80 < v73 );
                    v72 = v92;
                  }
                  v45 = HalpNumaConfig;
                  v44 = v73 * (*(_DWORD *)(HalpNumaConfig + 64) + 1);
                  *(_WORD *)(*(_QWORD *)(HalpNumaConfig + 48) + 2 * v44) = 0;
                  v43 = (unsigned int)(*(_DWORD *)(v72 + 60) - 1);
                  if ( *(_DWORD *)(v72 + 60) != 1 )
                  {
                    do
                    {
                      if ( !v82 )
                        break;
                      v85 = *(_QWORD *)(v72 + 16);
                      v44 = *(unsigned int *)(*(_QWORD *)(v45 + 24) + 4LL * k);
                      if ( *(_DWORD *)(v85 + 4 * v43) == (_DWORD)v44 )
                      {
                        --v82;
                        *(_DWORD *)(v85 + 4 * v43) = v78;
                      }
                      v86 = (_DWORD)v43 == 1;
                      v43 = (unsigned int)(v43 - 1);
                    }
                    while ( !v86 );
                  }
                }
                v73 = *(_DWORD *)(v72 + 56);
              }
            }
            if ( HalpMaximumClockDomainCount != 1 )
              HalpTimerPlatformSourceForced = 1;
            return (void *)HalpChannelInitializeStaticConfiguration(v44, v43, v45);
          }
          v45 = HalpNumaConfig;
          for ( m = 0; m < *(_DWORD *)(v45 + 56); ++m )
          {
            v44 = m;
            v49 = *(_DWORD *)(*(_QWORD *)(v45 + 24) + 4LL * m);
            if ( v49 >= v47 )
              goto LABEL_87;
            v50 = v47 * v49;
            for ( n = 0; n < *(_DWORD *)(v45 + 56); ++n )
            {
              v44 = n;
              v43 = *(unsigned int *)(*(_QWORD *)(v45 + 24) + 4LL * n);
              if ( (unsigned int)v43 >= v47 )
                goto LABEL_87;
              v52 = *(unsigned __int8 *)((unsigned int)(v43 + v50) + v46 + 44);
              if ( (unsigned __int8)v52 < 0xAu )
                goto LABEL_87;
              v53 = n + *(_DWORD *)(v45 + 64) * m;
              *(_WORD *)(*(_QWORD *)(v45 + 48) + 2 * v53) = v52 << 7;
            }
            v43 = 1280LL;
            v54 = *(_QWORD *)(v45 + 48);
            v44 = m * (*(_DWORD *)(v45 + 64) + 1);
            if ( *(_WORD *)(v54 + 2 * v44) != 1280 )
              goto LABEL_87;
            *(_WORD *)(v54 + 2 * v44) = 0;
          }
        }
        HalpAcpiSlit = v46;
        goto LABEL_87;
      }
    }
  }
  return result;
}