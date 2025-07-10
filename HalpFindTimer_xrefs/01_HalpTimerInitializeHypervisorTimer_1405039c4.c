/* Function: HalpTimerInitializeHypervisorTimer @ 0x1405039c4 (call depth 1) */

__int64 HalpTimerInitializeHypervisorTimer()
{
  __int64 result; // rax
  __int64 v5; // rbx
  int v6; // esi
  unsigned int *v7; // r12
  int v8; // r14d
  _DWORD *v9; // rdx
  unsigned int v10; // ecx
  int v11; // eax
  unsigned int v12; // eax
  __int64 v13; // rdx
  __int64 v14; // r9
  unsigned int v15; // eax
  __int64 v16; // rax
  int v17; // r8d
  _BYTE v18[4]; // [rsp+38h] [rbp-39h] BYREF
  int v19; // [rsp+3Ch] [rbp-35h] BYREF
  __int64 v20; // [rsp+40h] [rbp-31h] BYREF
  int v21; // [rsp+48h] [rbp-29h] BYREF
  unsigned __int64 v22; // [rsp+50h] [rbp-21h] BYREF
  _DWORD v23[6]; // [rsp+58h] [rbp-19h] BYREF
  __int64 v24; // [rsp+70h] [rbp-1h]
  __int64 v25; // [rsp+78h] [rbp+7h]
  __int64 v26; // [rsp+80h] [rbp+Fh]
  __int64 v27; // [rsp+88h] [rbp+17h]
  __int128 v28; // [rsp+90h] [rbp+1Fh]

  v22 = 0LL;
  v28 = 0LL;
  v20 = 0LL;
  v18[0] = 0;
  result = HalpIsPartitionCpuManager();
  if ( (_BYTE)result )
  {
    if ( qword_140FC0400 )
    {
      _RAX = 1073741830LL;
      __asm { cpuid }
      if ( (result & 0x100) != 0 )
      {
        result = (__int64)HalpFindTimer(3, 32, 24576, 3840, 0);
        v5 = result;
        if ( result )
        {
          result = HalpTimerInitialize(result);
          if ( (int)result >= 0 )
          {
            *(_DWORD *)(v5 + 184) |= 4u;
            HalpHypervisorHpet = v5;
            result = HalpTimerTestHypervisorTimer(v5, v18);
            HalpHypervisorHpet = 0LL;
            if ( (int)result >= 0 )
            {
              v6 = 1;
              v7 = *(unsigned int **)(v5 + 72);
              v8 = 0;
              if ( v18[0] )
              {
                v9 = *(_DWORD **)(v5 + 288);
                v10 = v9[1];
                HIWORD(v19) = *v9 >> 8;
                BYTE1(v19) = *(_BYTE *)v9;
                LOBYTE(v19) = (8 * *((_BYTE *)v9 + 4)) | (v10 >> 5) & 7;
                HalpHvBuildDeviceId(&v19, v9 + 2, 0LL, &v22);
              }
              else
              {
                v11 = *(_DWORD *)(v5 + 224);
                if ( (v11 & 0x200) != 0 )
                {
                  result = HalpInterruptGsiToLine(*(unsigned int *)(v5 + 88), &v20);
                  if ( (int)result < 0 )
                    return result;
                }
                else if ( (v11 & 0x100) != 0 )
                {
                  v12 = *(_DWORD *)(v5 + 84);
                  if ( v12 >= 8 )
                  {
                    LODWORD(v20) = 45057;
                    v12 -= 8;
                  }
                  else
                  {
                    LODWORD(v20) = 45056;
                  }
                  HIDWORD(v20) = v12;
                }
                v19 = *(_DWORD *)(v5 + 96);
                v21 = *(_DWORD *)(v5 + 92);
                HalpInterruptApplyOverrides(&v20, &v21, &v19);
                v6 = v19;
                v8 = v21;
                v22 = 0x8000000000000000uLL;
                LOBYTE(v22) = v20;
              }
              result = guard_dispatch_icall_no_overrides(*v7);
              if ( (int)result >= 0 )
              {
                if ( v18[0] )
                {
                  *(_DWORD *)(v5 + 236) = 0;
                  *(_DWORD *)(v5 + 232) = DWORD2(v28);
                  *(_QWORD *)(v5 + 240) = HIDWORD(v28);
                  v15 = *(_DWORD *)(v5 + 184) | 0x10;
LABEL_25:
                  HalpHypervisorHpet = v5;
                  *(_DWORD *)(v5 + 184) = v15 | 0x40;
                  return HalpTimerEnableHypervisorTimer();
                }
                v23[4] = -1;
                v25 = *((_QWORD *)&v28 + 1);
                v23[1] = 0;
                v24 = 8LL;
                v26 = 0LL;
                v27 = 212LL;
                v23[0] = v8;
                v23[2] = v6;
                v23[3] = 0;
                v23[5] = 1;
                v16 = HalpInterruptLookupController((unsigned int)v20, v13, 1LL, v14);
                if ( !v16 )
                  return HalpInterruptSetProblemEx(
                           0,
                           17,
                           v17,
                           (unsigned int)"minkernel\\hals\\lib\\interrupts\\common\\connect.c",
                           3268);
                result = HalpInterruptSetRemappedLineStateInternal(v16, &v20, v23);
                if ( (int)result >= 0 )
                {
                  v15 = *(_DWORD *)(v5 + 184) & 0xFFFFFFEF;
                  goto LABEL_25;
                }
              }
            }
          }
        }
      }
    }
  }
  return result;
}
