/* Function: HalpPmTimerDiscover @ 0x140519f90 (call depth 1) */

__int64 HalpPmTimerDiscover()
{
  __int64 AcpiTable; // rax
  __int64 v1; // rdi
  __int64 v2; // r8
  bool v3; // zf
  _DWORD v5[2]; // [rsp+20h] [rbp-69h] BYREF
  __int64 (__fastcall *v6)(); // [rsp+28h] [rbp-61h]
  _OWORD *v7; // [rsp+78h] [rbp-11h]
  int v8; // [rsp+80h] [rbp-9h]
  int v9; // [rsp+84h] [rbp-5h]
  __int64 v10; // [rsp+88h] [rbp-1h]
  int v11; // [rsp+94h] [rbp+Bh]
  int v12; // [rsp+A8h] [rbp+1Fh]
  _OWORD v13[2]; // [rsp+B0h] [rbp+27h] BYREF

  AcpiTable = HalSocGetAcpiTable(1346584902LL);
  v1 = AcpiTable;
  if ( AcpiTable && (*(_BYTE *)(AcpiTable + 8) < 5u || (*(_DWORD *)(AcpiTable + 112) & 0x100000) == 0) )
  {
    memset_0(v5, 0, 0x90uLL);
    v5[0] = 1;
    v5[1] = 144;
    memset(v13, 0, sizeof(v13));
    if ( !(unsigned int)HalpPmTimerConfigure(v1, v13, v5) )
    {
      v3 = (*(_DWORD *)(v1 + 112) & 0x100) == 0;
      v9 = 24;
      if ( !v3 )
      {
        LOBYTE(v13[0]) = 1;
        v9 = 32;
      }
      v8 = 32;
      v7 = v13;
      v10 = 3579545LL;
      v6 = HalpPmTimerInitialize;
      v11 = 2;
      v12 = 1;
      HalpTimerRegister((__int64)v5, 0LL, v2);
    }
  }
  return 0LL;
}
