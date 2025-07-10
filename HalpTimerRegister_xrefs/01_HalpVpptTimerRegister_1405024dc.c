/* Function: HalpVpptTimerRegister @ 0x1405024dc (call depth 1) */

__int64 __fastcall HalpVpptTimerRegister(_DWORD *a1, char a2)
{
  int v4; // edi
  int v5; // eax
  __int64 v6; // r8
  _DWORD v7[2]; // [rsp+20h] [rbp-69h] BYREF
  __int64 (__fastcall *v8)(); // [rsp+28h] [rbp-61h]
  __int64 (__fastcall *v9)(__int64); // [rsp+38h] [rbp-51h]
  __int64 (__fastcall *v10)(); // [rsp+40h] [rbp-49h]
  __int64 (__fastcall *v11)(); // [rsp+48h] [rbp-41h]
  __int128 *v12; // [rsp+78h] [rbp-11h]
  int v13; // [rsp+80h] [rbp-9h]
  int v14; // [rsp+84h] [rbp-5h]
  __int64 v15; // [rsp+88h] [rbp-1h]
  int v16; // [rsp+94h] [rbp+Bh]
  int v17; // [rsp+98h] [rbp+Fh]
  int v18; // [rsp+9Ch] [rbp+13h]
  int v19; // [rsp+A0h] [rbp+17h]
  int v20; // [rsp+A4h] [rbp+1Bh]
  int v21; // [rsp+A8h] [rbp+1Fh]
  int v22; // [rsp+ACh] [rbp+23h]
  __int128 v23; // [rsp+B0h] [rbp+27h] BYREF
  __int128 v24; // [rsp+C0h] [rbp+37h]
  __int128 v25; // [rsp+D0h] [rbp+47h]

  if ( !a1 )
    return 0xC000000DLL;                                // STATUS_INVALID_PARAMETER
  if ( a2 && (a1[56] & 0x8000) == 0 )
    return 0xC00000BBLL;                                // STATUS_NOT_SUPPORTED
  if ( (a1[56] & 1) != 0 )
    return 0xC00000BBLL;                                // STATUS_NOT_SUPPORTED
  v4 = a1[56] & 0xB00;
  if ( !v4 )
    return 0xC00000BBLL;                                // STATUS_NOT_SUPPORTED
  if ( _InterlockedExchange(&HalpVpptRegistered, 1) )
    return 0xC0000718LL;                                // STATUS_ALREADY_REGISTERED
  HalpVpptPhysicalTimerTarget = -1;
  *(_QWORD *)&HalpVpptPhysicalTimer = a1;
  ExtEnvInitializeSpinLock(&HalpVpptLock);
  qword_140FC0718 = (__int64)&HalpVpptQueue;
  *(_QWORD *)&HalpVpptQueue = &HalpVpptQueue;
  memset_0(v7, 0, 0x90uLL);
  v22 = 0;
  v8 = HalpVpptInitialize;
  v7[0] = 1;
  v7[1] = 0x90;
  v10 = HalpVpptArmTimer;
  v14 = 0x40;
  v11 = HalpVpptStop;
  v9 = HalpVpptAcknowledgeInterrupt;
  v5 = a1[56] & 0x8000;
  v13 = 48;
  v21 = 12;
  v15 = 10000000LL;
  v16 = v4 | v5 | 0x210031;
  v20 = a1[24];
  v19 = a1[23];
  v18 = a1[22];
  v17 = a1[21];
  v24 = 0LL;
  LODWORD(v24) = 0xFFFFFFFF;
  v12 = &v23;
  v23 = 0LL;
  v25 = 0LL;
  return HalpTimerRegister((__int64)v7, 0LL, v6);
}