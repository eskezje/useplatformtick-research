/* Function: HalpHpetArmTimer @ 0x14046fd60 (call depth 1) */

__int64 __fastcall HalpHpetArmTimer(__int64 a1, int a2, unsigned __int64 a3)
{
  __int64 v4; // rdx

  if ( a3 < 0x80000000 )
  {
    *(_DWORD *)(a1 + 8) = a2;
    v4 = HalpHpetBaseAddress;
    *(_DWORD *)(a1 + 16) = a3;
    return HalpHpetSetMatchValue((int *)a1, *(_DWORD *)(v4 + 0xF0), 0);
  }
  else
  {
    HalSetTimerProblem(a1, 4, 0);
    return 0xC000000DLL;
  }
}
