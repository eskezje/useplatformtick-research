__int64 __fastcall HalpHvDiscover(int a1)
{
  __int64 v1; // rdx
  __int64 v2; // r8
  __int64 v3; // rdx
  __int64 v4; // rcx
  int MaximumProcessorCount; // eax
  __int64 v6; // r8
  int v8; // [rsp+30h] [rbp-39h] BYREF
  int v9; // [rsp+34h] [rbp-35h]
  __int64 (__fastcall *v10)(); // [rsp+38h] [rbp-31h]
  __int64 (__fastcall *v11)(); // [rsp+40h] [rbp-29h]
  __int64 (__fastcall *v12)(); // [rsp+48h] [rbp-21h]
  __int64 (__fastcall *v13)(); // [rsp+50h] [rbp-19h]
  __int64 (__fastcall *v14)(); // [rsp+58h] [rbp-11h]
  __int64 (__fastcall *v15)(); // [rsp+78h] [rbp+Fh]
  __int64 v16; // [rsp+88h] [rbp+1Fh]
  int v17; // [rsp+90h] [rbp+27h]
  int v18; // [rsp+94h] [rbp+2Bh]
  __int64 v19; // [rsp+98h] [rbp+2Fh]
  int v20; // [rsp+A4h] [rbp+3Bh]
  int v21; // [rsp+B8h] [rbp+4Fh]
  char v22; // [rsp+D0h] [rbp+67h] BYREF

  v22 = 0;
  if ( (int)HalSocRequestApi(a1, (int)HalpHvCounterUpdateCallback, 3, 8, &HalpHvTimerApi) >= 0 )
  {
    memset_0(&v8, 0, 0x90uLL);
    v8 = 1;
    v10 = PdcCreateWatchdogAroundClientCall;
    v9 = 144;
    v11 = HalpHvCounterQueryCounter;
    v18 = 64;
    v21 = 8;
    v20 = 2;
    v19 = 10000000LL;
    HalpTimerRegister((__int64)&v8, 0LL, v2);
  }
  if ( (int)HalSocRequestConfigurationData(3LL, v1, &v22) >= 0 && v22 )
  {
    memset_0(&v8, 0, 0x90uLL);
    v16 = 0LL;
    v8 = 1;
    v9 = 144;
    MaximumProcessorCount = HalQueryMaximumProcessorCount(v4, v3);
    v18 = 64;
    v19 = 10000000LL;
    v21 = 8;
    v20 = 34913;
    v10 = HalpHvTimerInitialize;
    v11 = HalpHvCounterQueryCounter;
    v15 = HalpHvTimerSetInterruptVector;
    v13 = HalpHvTimerArm;
    v12 = HalpHvTimerAcknowledgeInterrupt;
    v17 = 24 * MaximumProcessorCount;
    v14 = HalpHvTimerStop;
    HalpTimerRegister((__int64)&v8, 0LL, v6);
  }
  return 0LL;
}