__int64 __fastcall HalpTimerRegister(__int64 a1, UNICODE_STRING *p_DestinationString, __int64 a3)
{
  unsigned int v3; // ebx
  int v6; // ecx
  __int64 v7; // rdx
  __int64 v8; // rcx
  unsigned int MaximumProcessorCount; // r12d
  unsigned int v10; // ebp
  unsigned int v11; // r14d
  void *MemoryInternal; // rax
  __int64 v13; // rsi
  unsigned __int64 v14; // r14
  unsigned __int64 v15; // rcx
  __int128 v16; // xmm0
  unsigned int i; // ebp
  __int64 v18; // rcx
  __int64 *v19; // rax
  UNICODE_STRING DestinationString; // [rsp+20h] [rbp-F8h] BYREF
  WCHAR SourceString[80]; // [rsp+30h] [rbp-E8h] BYREF

  v3 = 0;
  DestinationString = 0LL;
  if ( !HalpTimerRegistrationAllowed )
    return 0xC0000189;
  if ( *(_DWORD *)a1 != 1 )
    return 0xC000000D;
  if ( *(_DWORD *)(a1 + 4) != 0x90 )
    return 0xC000000D;
  v6 = *(_DWORD *)(a1 + 0x74);
  if ( (v6 & 0xFE000000) != 0
    || (v6 & 0x400000) != 0
    || !*(_DWORD *)(a1 + 136)
    || (v6 & 0x400) != 0 && !*(_QWORD *)(a1 + 0x38) )
  {
    return 0xC000000D;
  }
  if ( (v6 & 0x1000) != 0 || (v6 & 0x80u) != 0 )
    return 0xC00000BB;
  v7 = 2048LL;
  if ( (v6 & 0x800) != 0 && !*(_QWORD *)(a1 + 72) )
    return 0xC000000D;
  if ( (v6 & 0x801) == 0x800 )
    return 0xC00000BB;
  if ( (v6 & 0xF00) != 0 && !*(_QWORD *)(a1 + 40) )
    return 0xC000000D;
  if ( (v6 & 2) != 0 && !*(_QWORD *)(a1 + 16) )
    return 0xC000000D;
  v8 = v6 & 0x10001;
  if ( (_DWORD)v8 == 0x10000 )
    return 0xC000000D;
  if ( !p_DestinationString )
  {
    HalpTimerBuildKnownResourceIdString(a1, 75, SourceString);
    p_DestinationString = &DestinationString;
    RtlInitUnicodeString(&DestinationString, SourceString);
  }
  if ( (*(_DWORD *)(a1 + 116) & 0x10000) != 0 )
  {
    MaximumProcessorCount = ((__int64 (__fastcall *)(__int64, __int64))HalQueryMaximumProcessorCount)(v8, v7);
    v10 = (*(_DWORD *)(a1 + 96) + 7) & 0xFFFFFFF8;
  }
  else
  {
    v10 = *(_DWORD *)(a1 + 96);
    MaximumProcessorCount = 1;
  }
  v11 = (((MaximumProcessorCount * v10 + 351) & 0xFFFFFFF8) + 9 + p_DestinationString->Length) & 0xFFFFFFF8;
  MemoryInternal = (void *)((__int64 (__fastcall *)(_QWORD, __int64, __int64))HalpMmAllocateMemoryInternal)(
                             v11,
                             1LL,
                             a3);
  v13 = (__int64)MemoryInternal;
  if ( MemoryInternal )
  {
    memset_0(MemoryInternal, 0, v11);
    v14 = (v13 + 0x12F) & 0xFFFFFFFFFFFFFFF8uLL;
    *(_QWORD *)(v13 + 288) = v14;
    v15 = (v14 + 0x37) & 0xFFFFFFFFFFFFFFF8uLL;
    *(_QWORD *)(v13 + 0x48) = v15;
    *(_QWORD *)(v14 + 0x20) = (MaximumProcessorCount * v10 + v15 + 7) & 0xFFFFFFFFFFFFFFF8uLL;
    *(_QWORD *)(v13 + 0xC0) = *(_QWORD *)(a1 + 0x68);
    *(_OWORD *)(v13 + 0x68) = *(_OWORD *)(a1 + 8);
    *(_OWORD *)(v13 + 0x78) = *(_OWORD *)(a1 + 0x18);
    *(_OWORD *)(v13 + 0x88) = *(_OWORD *)(a1 + 0x28);
    *(_OWORD *)(v13 + 0x98) = *(_OWORD *)(a1 + 0x38);
    v16 = *(_OWORD *)(a1 + 0x48);
    *(_DWORD *)(v13 + 0x50) = v10;
    *(_OWORD *)(v13 + 0xA8) = v16;
    *(_DWORD *)(v13 + 0xDC) = *(_DWORD *)(a1 + 0x64);
    *(_DWORD *)(v13 + 0xE0) = *(_DWORD *)(a1 + 0x74);
    *(_DWORD *)(v13 + 0x54) = *(_DWORD *)(a1 + 0x78);
    *(_DWORD *)(v13 + 0x58) = *(_DWORD *)(a1 + 0x7C);
    *(_DWORD *)(v13 + 0x60) = *(_DWORD *)(a1 + 0x84);
    *(_DWORD *)(v13 + 0x5C) = *(_DWORD *)(a1 + 0x80);
    *(_DWORD *)(v13 + 0xE4) = *(_DWORD *)(a1 + 0x88);
    *(_DWORD *)(v13 + 0xD8) = *(_DWORD *)(a1 + 0x70);
    if ( *(_DWORD *)(a1 + 0x60) )
    {
      if ( *(_QWORD *)(a1 + 0x58) )
      {
        for ( i = 0; i < MaximumProcessorCount; ++i )
          memmove(
            (void *)(*(_QWORD *)(v13 + 0x48) + *(_DWORD *)(v13 + 80) * i),
            *(const void **)(a1 + 0x58),
            *(unsigned int *)(a1 + 0x60));
      }
    }
    *(_DWORD *)(v13 + 0x11C) = *(_DWORD *)(a1 + 140);
    *(_WORD *)(v14 + 0x18) = 0;
    *(_WORD *)(v14 + 0x1A) = p_DestinationString->Length + 2;
    RtlCopyUnicodeString((PUNICODE_STRING)(v14 + 0x18), p_DestinationString);
    if ( (*(_DWORD *)(a1 + 0x74) & 0x400) != 0 )
    {
      *(_QWORD *)(v14 + 0xC) = 0LL;
      *(_DWORD *)(v14 + 8) = 0;
      *(_DWORD *)v14 = 0;
      *(_DWORD *)(v14 + 4) = 0;
      if ( *(_DWORD *)(a1 + 0x88) == 3 )
      {
        LOBYTE(v18) = *(_BYTE *)(a1 + 142);
        ((void (__fastcall *)(__int64, unsigned __int64, unsigned __int64))HalpPciGetHpetInterruptSource)(
          v18,
          v14 + 8,
          (v13 + 0x12F) & 0xFFFFFFFFFFFFFFF8uLL);
      }
    }
    v19 = (__int64 *)qword_140FC2588;
    if ( *(ULONG_PTR **)qword_140FC2588 != &HalpRegisteredTimers )
      __fastfail(3u);
    LODWORD(HalpRegisteredTimerCount) = HalpRegisteredTimerCount + 1;
    *(_QWORD *)v13 = &HalpRegisteredTimers;
    *(_QWORD *)(v13 + 8) = v19;
    *v19 = v13;
    qword_140FC2588 = v13;
    if ( (*(_DWORD *)(v13 + 0xE0) & 0x100000) != 0 )
      HalpTimerAuxiliaryClockEnabled = 1;
  }
  else
  {
    return 0xC000009A;
  }
  return v3;
}