__int64 __fastcall HalSocRequestApi(__int64 a1, __int64 a2, int a3, __int64 a4, void *a5)
{
  unsigned int v5; // ebx
  unsigned int v6; // r11d
  __int64 *v8; // r14
  char v9; // r10
  __int64 v10; // r8
  __int64 (__fastcall **v11)(); // rsi
  unsigned int v12; // edi
  __int64 v14; // r8
  _QWORD *i; // rax
  __int64 *MemoryInternal; // rax
  __int64 (__fastcall *v17)(); // [rsp+20h] [rbp-38h] BYREF
  __int128 v18; // [rsp+28h] [rbp-30h] BYREF
  __int128 v19; // [rsp+38h] [rbp-20h] BYREF

  v5 = 0;
  v17 = 0LL;
  v6 = a4;
  v8 = 0LL;
  v9 = 0;
  v19 = 0LL;
  v18 = 0LL;
  v10 = (unsigned int)(a3 - 2);
  if ( (_DWORD)v10 )
  {
    v14 = (unsigned int)(v10 - 1);
    if ( (_DWORD)v14 )
    {
      v10 = (unsigned int)(v14 - 1);
      if ( !(_DWORD)v10 )
      {
        v12 = 8;
        v17 = (__int64 (__fastcall *)())HalpSocApiAllocatePhysicalMemory;
        v11 = &v17;
        goto LABEL_4;
      }
      v10 = (unsigned int)(v10 - 1);
      if ( !(_DWORD)v10 )
      {
        v11 = (__int64 (__fastcall **)())&v19;
        v19 = xmmword_140FC03A8;
        v8 = &HalpTimerHvApicCallbackList;
        v9 = 1;
        goto LABEL_3;
      }
      if ( (_DWORD)v10 != 1 )
      {
        HalpTimerLastProblem = 27;
        return 0xC000000D;
      }
      if ( (unsigned __int8)((__int64 (__fastcall *)(__int64, __int64, __int64, __int64, __int64 (__fastcall *)()))HalpHvIsFrequencyAvailable)(
                              a1,
                              a2,
                              v10,
                              a4,
                              v17) )
      {
        *(_QWORD *)&v18 = HalpHvGetTscFrequency;
        v11 = (__int64 (__fastcall **)())&v18;
        *((_QWORD *)&v18 + 1) = HalpHvGetApicFrequency;
        goto LABEL_3;
      }
    }
    else if ( (unsigned __int8)HalpTimerIsHypervisorReferenceAvailable(a1, a2, v14, a4, v17) )
    {
      v11 = (__int64 (__fastcall **)())&HalpTimerHypervisorReferenceTime;
      HalpTimerHypervisorReferenceTime = qword_140FC03C8;
      v8 = (__int64 *)&HalpTimerHvReferenceCallbackList;
      v12 = 8;
      v9 = 1;
      goto LABEL_4;
    }
    return 0xC00000BB;
  }
  v11 = &HalpTimerPcCpuApi;
LABEL_3:
  v12 = 16;
LABEL_4:
  if ( !a5 || v6 > v12 )
  {
    HalpTimerLastProblem = 28;
    return 0xC000000D;
  }
  if ( v6 < v12 )
  {
    v5 = 0xC0000023;
    HalpTimerLastProblem = 28;
    return v5;
  }
  if ( v9 )
  {
    if ( a2 )
    {
      for ( i = (_QWORD *)*v8; i; i = (_QWORD *)*i )
      {
        if ( i[1] == a2 )
          goto LABEL_8;
      }
      MemoryInternal = (__int64 *)((__int64 (__fastcall *)(__int64, __int64, __int64))HalpMmAllocateMemoryInternal)(
                                    16LL,
                                    1LL,
                                    v10);
      if ( !MemoryInternal )
        return 0xC0000017;
      MemoryInternal[1] = a2;
      *MemoryInternal = *v8;
      *v8 = (__int64)MemoryInternal;
      goto LABEL_8;
    }
    return 0xC000000D;
  }
LABEL_8:
  memmove(a5, v11, v12);
  return v5;
}