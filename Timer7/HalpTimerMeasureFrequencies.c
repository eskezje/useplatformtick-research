void __fastcall HalpTimerMeasureFrequencies(__int64 a1)
{
  ULONG_PTR *v1; // rbx
  int v2; // r15d
  char v3; // dl
  __int64 v5; // rcx
  ULONG_PTR *v6; // rdi
  __int64 v7; // rbx
  _DWORD *v8; // rcx
  __int64 InternalData; // rax
  unsigned __int64 v10; // rax
  __int64 v11; // rax
  ULONG_PTR *v12; // rbx
  LARGE_INTEGER *v13; // rdi
  LARGE_INTEGER *v14; // r10
  LARGE_INTEGER *v15; // rcx
  __int64 v16; // rax
  unsigned __int64 v17; // rax
  unsigned __int64 v18; // r14
  __int64 v19; // rax
  unsigned __int64 v20; // rcx
  ULONG_PTR *v21; // rbx
  LARGE_INTEGER *v22; // rdi
  LARGE_INTEGER *v23; // r10
  LARGE_INTEGER *v24; // rcx
  __int64 v25; // rax
  ULONG_PTR *v26; // rbx
  __int64 v27; // r11
  int *v28; // rcx
  int v29; // edi
  unsigned __int64 v30; // rax
  unsigned __int64 v31; // rbp
  unsigned __int64 v32; // r8
  unsigned __int64 v33; // r9
  unsigned int v34; // edi
  __int64 v35; // rax

  v1 = (ULONG_PTR *)HalpRegisteredTimers;
  v2 = *(_DWORD *)(a1 + 224) & 2;
  v3 = 0;
  if ( (ULONG_PTR *)HalpRegisteredTimers != &HalpRegisteredTimers )
  {
    do
    {
      v5 = (__int64)v1;
      v1 = (ULONG_PTR *)*v1;
      if ( (!*(_QWORD *)(v5 + 192) || (*(_DWORD *)(v5 + 184) & 8) != 0) && (*(_DWORD *)(v5 + 224) & 2) != 0 )
      {
        HalpTimerInitialize(v5);
        v3 = 1;
      }
    }
    while ( v1 != &HalpRegisteredTimers );
    if ( v3 )
    {
      KeStallExecutionProcessor(0x5DCu);
      v6 = (ULONG_PTR *)HalpRegisteredTimers;
      while ( v6 != &HalpRegisteredTimers )
      {
        v7 = (__int64)v6;
        v6 = (ULONG_PTR *)*v6;
        v8 = (_DWORD *)(v7 + 184);
        if ( (!*(_QWORD *)(v7 + 192) || (*v8 & 8) != 0) && (*(_DWORD *)(v7 + 224) & 2) != 0 && (*v8 & 2) != 0 )
        {
          if ( v2 )
          {
            *(_DWORD *)(v7 + 48) = HalpTimerDetermineValidTimerPairReadLatency(v7, a1);
          }
          else
          {
            InternalData = HalpTimerGetInternalData(v7);
            *(_QWORD *)(v7 + 16) = guard_dispatch_icall_no_overrides(InternalData);
          }
        }
      }
      v10 = __readcr2();
      __writecr2(v10);
      if ( (*(_DWORD *)(a1 + 224) & 2) == 0 )
      {
        v11 = HalpTimerGetInternalData(a1);
        guard_dispatch_icall_no_overrides(v11);
      }
      v12 = (ULONG_PTR *)HalpRegisteredTimers;
      while ( v12 != &HalpRegisteredTimers )
      {
        v13 = (LARGE_INTEGER *)v12;
        v14 = (LARGE_INTEGER *)v12;
        v12 = (ULONG_PTR *)*v12;
        v15 = v13 + 23;
        if ( (!v13[24].QuadPart || (v15->LowPart & 8) != 0) && (v14[28].LowPart & 2) != 0 && (v15->LowPart & 2) != 0 )
        {
          if ( v2 )
          {
            HalpTimerReadTimerPairWithLatencyLimit(v14[6].LowPart, (__int64)v14, a1, v13 + 2, v14 + 3);
          }
          else
          {
            v16 = HalpTimerGetInternalData((__int64)v14);
            v13[2].QuadPart = guard_dispatch_icall_no_overrides(v16);
          }
        }
      }
      v17 = __readcr2();
      __writecr2(v17);
      if ( (*(_DWORD *)(a1 + 224) & 2) != 0 )
      {
        v18 = 1250000LL;
        HalpTimerStallExecutionProcessor(a1, 1250000LL, 0LL);
      }
      else
      {
        v19 = HalpTimerGetInternalData(a1);
        v18 = guard_dispatch_icall_no_overrides(v19);
      }
      v20 = __readcr2();
      __writecr2(v20);
      v21 = (ULONG_PTR *)HalpRegisteredTimers;
      while ( v21 != &HalpRegisteredTimers )
      {
        v22 = (LARGE_INTEGER *)v21;
        v23 = (LARGE_INTEGER *)v21;
        v21 = (ULONG_PTR *)*v21;
        v24 = v22 + 23;
        if ( (!v22[24].QuadPart || (v24->LowPart & 8) != 0) && (v23[28].LowPart & 2) != 0 && (v24->LowPart & 2) != 0 )
        {
          if ( v2 )
          {
            HalpTimerReadTimerPairWithLatencyLimit(v23[6].LowPart, (__int64)v23, a1, v22 + 4, v23 + 5);
          }
          else
          {
            v25 = HalpTimerGetInternalData((__int64)v23);
            v22[4].QuadPart = guard_dispatch_icall_no_overrides(v25);
          }
        }
      }
      v26 = (ULONG_PTR *)HalpRegisteredTimers;
      while ( v26 != &HalpRegisteredTimers )
      {
        v27 = (__int64)v26;
        v26 = (ULONG_PTR *)*v26;
        v28 = (int *)(v27 + 184);
        if ( (!*(_QWORD *)(v27 + 192) || (*v28 & 8) != 0) && (*(_DWORD *)(v27 + 224) & 2) != 0 )
        {
          v29 = *v28;
          if ( (*v28 & 2) != 0 )
          {
            v30 = *(_QWORD *)(v27 + 16);
            v31 = *(_QWORD *)(v27 + 32) - v30;
            v32 = *(_QWORD *)(v27 + 24);
            v33 = *(_QWORD *)(v27 + 40) - v32;
            if ( *(_QWORD *)(v27 + 32) < v30 )
              v31 += 1LL << *(_DWORD *)(v27 + 220);
            if ( *(_QWORD *)(v27 + 40) < v32 )
              v33 += 1LL << *(_DWORD *)(a1 + 220);
            if ( v2 )
              v18 = HalpTimerScaleCounter(v33, *(_QWORD *)(a1 + 192), 10000000LL);
            v34 = v29 & 0xFFFFFFF7;
            *(_DWORD *)(v27 + 184) = v34;
            *(_QWORD *)(v27 + 192) = 10000000 * v31 / v18;
            if ( v27 != a1 && (v34 & 4) == 0 )
            {
              if ( *(_QWORD *)(v27 + 136) )
              {
                v35 = HalpTimerGetInternalData(v27);
                guard_dispatch_icall_no_overrides(v35);
              }
            }
          }
        }
      }
    }
  }
}