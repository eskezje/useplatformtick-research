__int64 HalpArtDiscover()
{
  __int64 v0; // r8
  UNICODE_STRING DestinationString; // [rsp+20h] [rbp-69h] BYREF
  _DWORD v3[2]; // [rsp+30h] [rbp-59h] BYREF
  __int64 (__fastcall *v4)(); // [rsp+38h] [rbp-51h]
  __int64 (__fastcall *v5)(); // [rsp+40h] [rbp-49h]
  __int64 *v6; // [rsp+88h] [rbp-1h]
  int v7; // [rsp+90h] [rbp+7h]
  int v8; // [rsp+94h] [rbp+Bh]
  __int64 v9; // [rsp+98h] [rbp+Fh]
  int v10; // [rsp+A4h] [rbp+1Bh]
  int v11; // [rsp+B8h] [rbp+2Fh]
  __int64 v12; // [rsp+C0h] [rbp+37h] BYREF
  int v13; // [rsp+C8h] [rbp+3Fh] BYREF

  v12 = 0LL;
  v13 = 0;
  DestinationString = 0LL;
  if ( (unsigned __int8)HalpArtAvailable(&v12, &v13) )
  {
    memset_0(v3, 0, 0x90uLL);
    v9 = 0LL;
    v6 = &v12;
    v3[0] = 1;
    v4 = HalpArtInitialize;
    v3[1] = 0x90;
    v5 = HalpArtQueryCounter;
    v8 = 0x40;
    v11 = 0xF;
    v10 = 0x108003;
    v7 = 12;
    RtlInitUnicodeString(
      &DestinationString,
      L"VEN_vvvv&DEV_dddd&SUBVEN_ssss&SUBDEV_yyyy&REV_rrrr&INST_iiii&UID_uuuuuuuu");
    HalpTimerRegister((__int64)v3, &DestinationString, v0);
    HalpTimerAuxiliaryClockEnabled = 1;
  }
  return 0LL;
}