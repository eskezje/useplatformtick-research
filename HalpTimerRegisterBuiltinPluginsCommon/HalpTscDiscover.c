__int64 HalpTscDiscover()
{
  int v0; // ebx
  int v1; // ecx
  __int64 v2; // rdx
  __int64 v3; // rcx
  __int64 v4; // r8
  __int64 v5; // rax
  __int64 v6; // rcx
  __int64 (__fastcall *v7)(); // rax
  __int64 v8; // r8
  __int128 v10; // [rsp+30h] [rbp-59h] BYREF
  UNICODE_STRING DestinationString; // [rsp+40h] [rbp-49h] BYREF
  _DWORD v12[2]; // [rsp+50h] [rbp-39h] BYREF
  __int64 (__fastcall *v13)(); // [rsp+58h] [rbp-31h]
  __int64 (__fastcall *v14)(); // [rsp+60h] [rbp-29h]
  int *v15; // [rsp+A8h] [rbp+1Fh]
  int v16; // [rsp+B0h] [rbp+27h]
  int v17; // [rsp+B4h] [rbp+2Bh]
  __int64 v18; // [rsp+B8h] [rbp+2Fh]
  int v19; // [rsp+C4h] [rbp+3Bh]
  int v20; // [rsp+D8h] [rbp+4Fh]
  char v21; // [rsp+F0h] [rbp+67h] BYREF
  int v22; // [rsp+F8h] [rbp+6Fh] BYREF

  v22 = 0;
  v21 = 0;
  v10 = 0LL;
  DestinationString = 0LL;
  memset_0(v12, 0, 0x90uLL);
  v18 = 0LL;
  v15 = &v22;
  v12[1] = 144;
  v0 = 7;
  v12[0] = 1;
  v17 = 64;
  v20 = 5;
  v16 = 4;
  if ( (int)HalSocRequestApi(v1, 0, 6, 16, &v10) >= 0 )
  {
    v5 = guard_dispatch_icall_no_overrides(v3, v2, v4);
    v6 = 0LL;
    if ( v5 )
      v6 = v5;
    v18 = v6;
  }
  if ( (int)HalpTscGetAttributes(&HalpTscPerformanceStateInvariant, &HalpTscIdleStateInvariant, &v21) < 0 )
  {
    v0 = 24583;
LABEL_11:
    v19 = v0;
    goto LABEL_12;
  }
  if ( !HalpTscPerformanceStateInvariant )
    v0 = 8199;
  v19 = v0;
  if ( !HalpTscIdleStateInvariant )
  {
    v0 |= 0x4000u;
    goto LABEL_11;
  }
LABEL_12:
  v13 = HalpTscInitialize;
  if ( v21 )
  {
    v7 = HalpTscQueryCounterOrdered;
    v19 = v0 | 0x1000000;
  }
  else
  {
    v7 = HalpTscQueryCounter;
  }
  v14 = v7;
  RtlInitUnicodeString(&DestinationString, L"VEN_vvvv&DEV_dddd&SUBVEN_ssss&SUBDEV_yyyy&REV_rrrr&INST_iiii&UID_uuuuuuuu");
  HalpTimerRegister((__int64)v12, &DestinationString, v8);
  return 0LL;
}