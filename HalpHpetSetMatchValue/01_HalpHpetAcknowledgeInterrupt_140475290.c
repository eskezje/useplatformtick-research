/* Function: HalpHpetAcknowledgeInterrupt @ 0x140475290 (call depth 1) */

void __fastcall HalpHpetAcknowledgeInterrupt(__int64 a1)
{
  if ( *(_DWORD *)(a1 + 8) == 1 )
  {
    HalpHpetSetMatchValue((int *)a1, *(_DWORD *)(a1 + 20), 1);
  }
  else if ( *(_DWORD *)(a1 + 8) == 2 && !*(_BYTE *)(a1 + 12) )
  {
    HalSetTimerProblem(a1, 2, 0);
  }
}
