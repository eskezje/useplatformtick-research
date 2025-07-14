LARGE_INTEGER __stdcall KeQueryPerformanceCounter(PLARGE_INTEGER PerformanceFrequency)
{
  __int64 v2; // rsi
  unsigned __int64 v3; // rbx
  signed __int64 v4; // rdx
  unsigned __int64 v5; // rax
  int v6; // r8d
  __int64 v7; // rdx
  signed __int64 v8; // rdx
  __int64 v9; // r14
  LARGE_INTEGER result; // rax
  __int64 v11; // rcx
  __int64 v12; // rdi
  __int64 InternalData; // rax
  unsigned __int64 v14; // r10
  signed __int64 v15; // rax
  int v16; // r9d
  unsigned __int64 v17; // rcx
  __int64 v18; // rdx
  __int64 v19; // r8
  __int64 v20; // rcx
  unsigned __int64 v21; // r8
  __int64 v22; // r8
  LONGLONG v23; // r8
  __int64 v24; // rdx
  int v25; // ecx
  unsigned __int64 v26; // rax
  int v27; // r9d
  signed __int64 v28; // rdx
  __int64 v29; // r14
  __int64 v30; // rdi
  __int64 v31; // rax
  unsigned __int64 v32; // r10
  signed __int64 v33; // rax
  int v34; // r9d
  unsigned __int64 v35; // rcx
  __int64 v36; // rdx
  __int64 v37; // r8
  __int64 v38; // rcx
  unsigned __int64 v39; // r8
  __int64 v40; // rcx
  signed __int64 v41; // rcx
  signed __int32 v42[8]; // [rsp+0h] [rbp-48h] BYREF
  signed __int64 v43; // [rsp+58h] [rbp+10h] BYREF
  signed __int64 v44; // [rsp+60h] [rbp+18h] BYREF

  v2 = HalpPerformanceCounter;
  if ( *(_DWORD *)(HalpPerformanceCounter + 0xE4) != 5 )
  {
    v3 = *(_QWORD *)(HalpPerformanceCounter + 0xC0);
    if ( *(_DWORD *)(HalpPerformanceCounter + 0xDC) != 64 )
    {
      do
      {
        v9 = *(_QWORD *)(v2 + 0xD0);
        do
        {
          v12 = *(_QWORD *)(v2 + 0xC8);
          InternalData = HalpTimerGetInternalData(v2);
          v14 = guard_dispatch_icall_no_overrides(InternalData);
          _InterlockedOr(v42, 0);
          v15 = *(_QWORD *)(v2 + 0xC8);
        }
        while ( v12 != v15 );
      }
      while ( v9 != *(_QWORD *)(v2 + 0xD0) );
      v16 = *(_DWORD *)(v2 + 0xDC);
      v17 = v12 ^ v14;
      if ( _bittest64((const __int64 *)&v17, (unsigned __int8)(v16 - 1)) )
      {
        if ( v16 == 64 )
          v19 = 0xFFFFFFFFFFFFFFFFuLL;
        else
          v19 = (1LL << v16) - 1;
        v20 = 0LL;
        if ( v16 != 64 )
          v20 = 1LL << v16;
        v21 = v12 & v19;
        v8 = v14 | v12 ^ v21;
        if ( v14 < v21 )
          v8 += v20;
        _InterlockedCompareExchange64((volatile signed __int64 *)(v2 + 200), v8, v15);
      }
      else
      {
        if ( v16 == 64 )
          v18 = 0xFFFFFFFFFFFFFFFFuLL;
        else
          v18 = (1LL << v16) - 1;
        v8 = v14 | v12 & ~v18;
      }
      goto LABEL_15;
    }
    if ( (*(_DWORD *)(HalpPerformanceCounter + 0xE0) & 0x10000) != 0 )
      v4 = *(_QWORD *)(HalpPerformanceCounter + 0x48)
         + *(_DWORD *)(HalpPerformanceCounter + 0x50) * KeGetPcr()->Prcb.Number;
    else
      v4 = *(_QWORD *)(HalpPerformanceCounter + 0x48);
    if ( *(__int64 (__fastcall **)(__int64, __int64))(HalpPerformanceCounter + 0x70) == HalpHvCounterQueryCounter )
    {
      v5 = HalpHvTimerApi;
      if ( !HalpHvTimerApi )
      {
        v8 = __readmsr(0x40000020u);
LABEL_14:
        v9 = *(_QWORD *)(v2 + 208);
LABEL_15:
        result.QuadPart = v9 + v8;
        goto LABEL_16;
      }
      if ( (__int64 (__fastcall *)())HalpHvTimerApi == HvlGetReferenceTimeUsingTscPage )
      {
        v44 = 0LL;
        while ( 1 )
        {
          v6 = *(_DWORD *)HvlpReferenceTscPage;
          if ( !*(_DWORD *)HvlpReferenceTscPage )
            break;
          if ( MEMORY[0xFFFFF78000000294] )
          {
            __asm { rdtscp }
          }
          else
          {
            if ( KeGetCurrentPrcb()->CpuVendor == 2 )
            {
              _mm_lfence();
            }
            else if ( KeGetCurrentPrcb()->CpuVendor == 1 )
            {
              _mm_mfence();
            }
            v5 = __rdtsc();
            LODWORD(v4) = HIDWORD(v5);
            v5 = (unsigned int)v5;
            v4 = (unsigned int)v4;
          }
          v7 = ((v5 | (v4 << 32)) * (unsigned __int128)*((unsigned __int64 *)HvlpReferenceTscPage + 1)) >> 64;
          v5 = (unsigned __int64)HvlpReferenceTscPage;
          v4 = *((_QWORD *)HvlpReferenceTscPage + 2) + v7;
          v44 = v4;
          if ( *(_DWORD *)HvlpReferenceTscPage == v6 )
            goto LABEL_13;
        }
        HvlpGetRegister64(589828LL, &v44);
LABEL_13:
        v8 = v44;
        goto LABEL_14;
      }
      v41 = 0LL;
    }
    else
    {
      v41 = v4;
    }
    v8 = guard_dispatch_icall_no_overrides(v41);
    goto LABEL_14;
  }
  v3 = 10000000LL;
  if ( !HalpTimerReferencePage )
  {
    if ( *(_DWORD *)(HalpPerformanceCounter + 0xDC) != 64 )
    {
      do
      {
        v29 = *(_QWORD *)(v2 + 0xD0);
        do
        {
          v30 = *(_QWORD *)(v2 + 0xC8);
          v31 = HalpTimerGetInternalData(v2);
          v32 = guard_dispatch_icall_no_overrides(v31);
          _InterlockedOr(v42, 0);
          v33 = *(_QWORD *)(v2 + 0xC8);
        }
        while ( v30 != v33 );
      }
      while ( v29 != *(_QWORD *)(v2 + 0xD0) );
      v34 = *(_DWORD *)(v2 + 0xDC);
      v35 = v30 ^ v32;
      if ( _bittest64((const __int64 *)&v35, (unsigned __int8)(v34 - 1)) )
      {
        if ( v34 == 64 )
          v37 = 0xFFFFFFFFFFFFFFFFuLL;
        else
          v37 = (1LL << v34) - 1;
        v38 = 0LL;
        if ( v34 != 64 )
          v38 = 1LL << v34;
        v39 = v30 & v37;
        v28 = v32 | v30 ^ v39;
        if ( v32 < v39 )
          v28 += v38;
        _InterlockedCompareExchange64((volatile signed __int64 *)(v2 + 200), v28, v33);
      }
      else
      {
        if ( v34 == 64 )
          v36 = 0xFFFFFFFFFFFFFFFFuLL;
        else
          v36 = (1LL << v34) - 1;
        v28 = v32 | v30 & ~v36;
      }
      goto LABEL_57;
    }
    v24 = HalpTimerGetInternalData(HalpPerformanceCounter);
    if ( *(__int64 (__fastcall **)(__int64, __int64))(v2 + 0x70) == HalpHvCounterQueryCounter )
    {
      if ( !HalpHvTimerApi )
      {
        v28 = __readmsr(0x40000020u);
LABEL_56:
        v29 = *(_QWORD *)(v2 + 0xD0);
LABEL_57:
        result.QuadPart = HalpTimerScaleCounter(v29 + v28, *(_QWORD *)(v2 + 0xC0), 10000000LL);
        goto LABEL_16;
      }
      if ( (__int64 (__fastcall *)())HalpHvTimerApi == HvlGetReferenceTimeUsingTscPage )
      {
        v25 = 0;
        v43 = 0LL;
        while ( 1 )
        {
          v26 = (unsigned __int64)HvlpReferenceTscPage;
          v27 = *(_DWORD *)HvlpReferenceTscPage;
          if ( !*(_DWORD *)HvlpReferenceTscPage )
            break;
          if ( MEMORY[0xFFFFF78000000294] )
          {
            __asm { rdtscp }
            LODWORD(v43) = v25;
          }
          else
          {
            if ( KeGetCurrentPrcb()->CpuVendor == 2 )
            {
              _mm_lfence();
            }
            else if ( KeGetCurrentPrcb()->CpuVendor == 1 )
            {
              _mm_mfence();
            }
            v26 = __rdtsc();
            LODWORD(v24) = HIDWORD(v26);
            v26 = (unsigned int)v26;
            v24 = (unsigned int)v24;
          }
          v24 = *((_QWORD *)HvlpReferenceTscPage + 2)
              + (((v26 | (v24 << 32)) * (unsigned __int128)*((unsigned __int64 *)HvlpReferenceTscPage + 1)) >> 64);
          v43 = v24;
          v25 = *(_DWORD *)HvlpReferenceTscPage;
          if ( *(_DWORD *)HvlpReferenceTscPage == v27 )
            goto LABEL_55;
        }
        HvlpGetRegister64(0x90004LL, &v43);
LABEL_55:
        v28 = v43;
        goto LABEL_56;
      }
      v40 = 0LL;
    }
    else
    {
      v40 = v24;
    }
    v28 = guard_dispatch_icall_no_overrides(v40);
    goto LABEL_56;
  }
  if ( (*(_DWORD *)(HalpPerformanceCounter + 0xE0) & 0x10000) != 0 )
    v11 = *(_QWORD *)(HalpPerformanceCounter + 0x48)
        + *(_DWORD *)(HalpPerformanceCounter + 0x50) * KeGetPcr()->Prcb.Number;
  else
    v11 = *(_QWORD *)(HalpPerformanceCounter + 0x48);
  result.QuadPart = MEMORY[0xFFFFF780000003B8]
                  + (((unsigned __int64)guard_dispatch_icall_no_overrides(v11)
                    * (unsigned __int128)*((unsigned __int64 *)HalpTimerReferencePage + 1)) >> 64);
LABEL_16:
  if ( v2 == HalpOriginalPerformanceCounter || !HalpOriginalPerformanceCounter )
  {
    if ( PerformanceFrequency )
      PerformanceFrequency->QuadPart = v3;
  }
  else
  {
    v22 = *(_QWORD *)(HalpOriginalPerformanceCounter + 0xC0);
    if ( *(_DWORD *)(HalpOriginalPerformanceCounter + 0xE4) == 5 )
      v22 = 10000000LL;
    result.QuadPart = HalpTimerScaleCounter(result.QuadPart, v3, v22);
    if ( PerformanceFrequency )
      PerformanceFrequency->QuadPart = v23;
  }
  return result;
}