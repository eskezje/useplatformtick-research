int HalpApicDiscover()
{
  __int64 AcpiTable; // rbx
  int result; // eax
  LARGE_INTEGER v2; // rcx
  __int64 v3; // rdi
  unsigned __int64 v4; // rsi
  __int64 v5; // rcx
  __int64 v6; // r8

  HalpLocalApicPhysical.QuadPart = 0LL;
  AcpiTable = HalSocGetAcpiTable(0x43495041u);
  if ( !AcpiTable )
    return 0xC0000182;
  result = HalpApicSetupRegisterAccess();
  if ( result >= 0 )
  {
    v2.QuadPart = *(unsigned int *)(AcpiTable + 36);
    HalpLocalApicPhysical = v2;
    result = HalRegisterPermanentAddressUsage(v2, 0x400u);
    if ( result >= 0 )
    {
      v3 = AcpiTable + 44;
      v4 = AcpiTable + *(unsigned int *)(AcpiTable + 4);
      while ( v3 + 2 <= v4 )
      {
        v5 = *(unsigned __int8 *)(v3 + 1);
        if ( (unsigned __int8)v5 < 2u || v3 + v5 > v4 )
          break;
        v6 = v3;
        v3 += v5;
        if ( *(_BYTE *)v6 == 1 && (_BYTE)v5 == 12 )
          ((void (__fastcall *)(LARGE_INTEGER))HalpApicRegisterIoUnit)((LARGE_INTEGER)*(unsigned int *)(v6 + 4));
      }
      return 0;
    }
  }
  return result;
}