__int64 __fastcall HalpVpptInitialize(__int64 a1)
{
  if ( *(_DWORD *)(a1 + 0x10) == -1 )
    *(_DWORD *)(a1 + 0x10) = KeGetPcr()->Prcb.Number;
  *(_DWORD *)(a1 + 0x14) = 1;
  return 0LL;
}