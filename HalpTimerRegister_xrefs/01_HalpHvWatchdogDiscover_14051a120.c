/* Function: HalpHvWatchdogDiscover @ 0x14051a120 (call depth 1) */

__int64 __fastcall HalpHvWatchdogDiscover(__int64 a1)
{
  __int64 v6; // r8
  _DWORD v8[2]; // [rsp+20h] [rbp-59h] BYREF
  __int64 (__fastcall *v9)(); // [rsp+28h] [rbp-51h]
  __int64 (__fastcall *v10)(); // [rsp+40h] [rbp-39h]
  __int64 (__fastcall *v11)(); // [rsp+48h] [rbp-31h]
  __int64 v12; // [rsp+78h] [rbp-1h]
  int v13; // [rsp+80h] [rbp+7h]
  int v14; // [rsp+84h] [rbp+Bh]
  __int64 v15; // [rsp+88h] [rbp+Fh]
  int v16; // [rsp+94h] [rbp+1Bh]
  int v17; // [rsp+A8h] [rbp+2Fh]
  __int128 v18; // [rsp+B0h] [rbp+37h]

  if ( !HalpTimerWatchdogPhysicalOnly )
  {
    if ( (unsigned __int8)HalpIsMicrosoftCompatibleHvLoaded(a1) )
    {
      if ( (HalpEnlightenment & 0x20) == 0 )
      {
        _RAX = 1073741827LL;
        __asm { cpuid }
        v18 = __PAIR64__(_RBX, _RAX);
        if ( (_RDX & 0x400000) != 0 && (v18 & 0x100000000008LL) == 0x100000000008LL )
        {
          memset_0(v8, 0, 0x90uLL);
          v12 = 0LL;
          v13 = 0;
          v9 = HalpHvWatchdogInitialize;
          v8[0] = 1;
          v10 = HalpHvWatchdogArm;
          v11 = HalpHvWatchdogStop;
          v8[1] = 144;
          v14 = 64;
          v15 = 10000000LL;
          v17 = 8;
          v16 = 163872;
          HalpTimerRegister((__int64)v8, 0LL, v6);
        }
      }
    }
  }
  return 0LL;
}
