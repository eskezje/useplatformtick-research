__int64 HalpBlkInitializeVirtualAddressSpace()
{
  int ShadowCode; // ebx
  __int64 v1; // r8

  ShadowCode = HalpBlkInitializePageTables();
  if ( ShadowCode >= 0 )
  {
    ShadowCode = HalpBlkAllocateShadowCode();
    if ( ShadowCode >= 0 )
    {
      ShadowCode = HalpBlkAllocateShadowData();
      if ( ShadowCode >= 0 )
      {
        ShadowCode = 0;
        if ( !HalpApicX2Mode && !HalpApicUsingMsrs )
        {
          v1 = HalpLocalApic;
          if ( !HalpLocalApic )
          {
            ShadowCode = 0xC000000E;
            goto LABEL_12;
          }
          ShadowCode = HalpBlkAddVirtualMapping(
                         HalpBlkRootPageTablePa,
                         HalpLocalApicPhysical.LowPart,
                         HalpLocalApic,
                         0,
                         4);
        }
        if ( ShadowCode >= 0 )
        {
          ShadowCode = HalpBlkAddVirtualMapping(
                         HalpBlkRootPageTablePa,
                         (_DWORD)HalpLowStubPhysicalAddress,
                         HalpLowStub,
                         1,
                         4);
          if ( ShadowCode >= 0 )
            ShadowCode = HalpBlkAddVirtualMapping(
                           HalpBlkTiledMemoryMapPa,
                           (_DWORD)HalpLowStubPhysicalAddress,
                           (_DWORD)HalpLowStubPhysicalAddress,
                           1,
                           64);
        }
      }
    }
  }
LABEL_12:
  if ( HalpBlkPageTableVaWindow )
  {
    LOBYTE(v1) = 1;
    HalpUnmapVirtualAddress(HalpBlkPageTableVaWindow, 1LL, v1);
    HalpBlkPageTableVaWindow = 0LL;
  }
  return (unsigned int)ShadowCode;
}