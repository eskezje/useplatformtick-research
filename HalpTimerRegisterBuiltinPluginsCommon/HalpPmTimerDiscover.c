__int64 __fastcall HalpPmTimerConfigure(__int64 a1, __int64 a2, __int64 a3)
{
  unsigned int v3; // r9d
  __int64 v4; // rax
  __int64 v5; // rax

  v3 = -1073741637;
  if ( *(_BYTE *)(a1 + 8) >= 5u && *(_BYTE *)(a1 + 91) )
  {
    if ( *(_BYTE *)(a1 + 208) )
    {
      if ( *(_BYTE *)(a1 + 208) == 1 )
      {
        *(_BYTE *)(a2 + 1) = 0;
        v4 = *(unsigned int *)(a1 + 212);
        *(_QWORD *)(a2 + 8) = v4;
        *(_QWORD *)(a3 + 16) = HalpPmTimerQueryCounterIoPort;
        return v4 == 0 ? 0xC00000BB : 0;
      }
    }
    else
    {
      *(_BYTE *)(a2 + 1) = 1;
      *(_DWORD *)(a2 + 28) = *(unsigned __int8 *)(a1 + 91);
      *(_QWORD *)(a2 + 16) = *(_QWORD *)(a1 + 208);
      *(_DWORD *)(a2 + 24) = *(_DWORD *)(a1 + 216);
      *(_QWORD *)(a3 + 16) = HalpPmTimerQueryCounterMemory;
      return *(_QWORD *)(a2 + 20) == 0LL ? 0xC00000BB : 0;
    }
  }
  else if ( *(_DWORD *)(a1 + 76) )
  {
    *(_BYTE *)(a2 + 1) = 0;
    v3 = 0;
    v5 = *(unsigned int *)(a1 + 76);
    *(_QWORD *)(a3 + 16) = HalpPmTimerQueryCounterIoPort;
    *(_QWORD *)(a2 + 8) = v5;
  }
  return v3;
}