__int64 __fastcall HalpTimerGetInternalData(__int64 a1)
{
  if ( (*(_DWORD *)(a1 + 0xE0) & 0x10000) != 0 )
    return *(_QWORD *)(a1 + 0x48) + *(_DWORD *)(a1 + 0x50) * KeGetPcr()->Prcb.Number;
  else
    return *(_QWORD *)(a1 + 0x48);
}