void HalpTimerTraceTimingHardware()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  char v8; // al
  __int64 v9; // [rsp+30h] [rbp-D0h] BYREF
  int v10; // [rsp+38h] [rbp-C8h] BYREF
  int v11; // [rsp+3Ch] [rbp-C4h] BYREF
  __int64 v12; // [rsp+40h] [rbp-C0h] BYREF
  __int64 v13; // [rsp+48h] [rbp-B8h] BYREF
  int v14; // [rsp+50h] [rbp-B0h] BYREF
  _BYTE v15[32]; // [rsp+60h] [rbp-A0h] BYREF
  char *v16; // [rsp+80h] [rbp-80h]
  __int64 v17; // [rsp+88h] [rbp-78h]
  int *v18; // [rsp+90h] [rbp-70h]
  __int64 v19; // [rsp+98h] [rbp-68h]
  int *v20; // [rsp+A0h] [rbp-60h]
  __int64 v21; // [rsp+A8h] [rbp-58h]
  __int64 *v22; // [rsp+B0h] [rbp-50h]
  __int64 v23; // [rsp+B8h] [rbp-48h]
  char *v24; // [rsp+C0h] [rbp-40h]
  __int64 v25; // [rsp+C8h] [rbp-38h]
  __int64 *v26; // [rsp+D0h] [rbp-30h]
  __int64 v27; // [rsp+D8h] [rbp-28h]
  char *v28; // [rsp+E0h] [rbp-20h]
  __int64 v29; // [rsp+E8h] [rbp-18h]
  int *v30; // [rsp+F0h] [rbp-10h]
  __int64 v31; // [rsp+F8h] [rbp-8h]
  __int64 *v32; // [rsp+100h] [rbp+0h]
  __int64 v33; // [rsp+108h] [rbp+8h]

  if ( (unsigned int)dword_140E03B08 > 5 && (unsigned __int8)tlgKeywordOn(&dword_140E03B08, 0x400000000000LL) )
  {
    v17 = 4LL;
    v19 = 4LL;
    v0 = *(_DWORD *)(HalpClockTimer + 0xE4);
    v16 = (char *)&v9 + 4;
    HIDWORD(v9) = v0;
    v1 = *(_DWORD *)(HalpPerformanceCounter + 0xE4);
    v18 = &v10;
    v10 = v1;
    if ( HalpAlwaysOnTimer )
      v2 = *(_DWORD *)(HalpAlwaysOnTimer + 0xE4);
    else
      v2 = 0;
    v11 = v2;
    v20 = &v11;
    v21 = 4LL;
    if ( *(_QWORD *)&HalpVpptPhysicalTimer )
      v3 = *(_DWORD *)(*(_QWORD *)&HalpVpptPhysicalTimer + 0xE4LL);
    else
      v3 = 0;
    LODWORD(v12) = v3;
    v22 = &v12;
    v23 = 4LL;
    if ( HalpAlwaysOnCounter )
      v4 = *(_DWORD *)(HalpAlwaysOnCounter + 0xE4);
    else
      v4 = 0;
    HIDWORD(v12) = v4;
    v24 = (char *)&v12 + 4;
    v25 = 4LL;
    if ( HalpWatchdogTimer )
      v5 = *(_DWORD *)(HalpWatchdogTimer + 0xE4);
    else
      v5 = 0;
    LODWORD(v13) = v5;
    v26 = &v13;
    v27 = 4LL;
    if ( HalpAuxiliaryCounter )
      v6 = *(_DWORD *)(HalpAuxiliaryCounter + 0xE4);
    else
      v6 = 0;
    HIDWORD(v13) = v6;
    v28 = (char *)&v13 + 4;
    v7 = 0;
    v29 = 4LL;
    if ( HalpStallCounter )
      v7 = *(_DWORD *)(HalpStallCounter + 228);
    v14 = v7;
    v30 = &v14;
    v31 = 4LL;
    if ( (KeFeatureBits2 & 0x800000) == 0
      || qword_140FC03C0
      || (*(_DWORD *)(HalpStallCounter + 0xE0) & 0x6000) != 0
      || (v8 = 1, *(_DWORD *)(HalpStallCounter + 0xE4) != 5) )
    {
      v8 = 0;
    }
    LOBYTE(v9) = v8;
    v33 = 1LL;
    v32 = &v9;
    tlgWriteTransfer_EtwWriteTransfer(&dword_140E03B08, byte_140041BB9, 0LL, 0LL, 11, v15, v9, v10, v12, v13);
  }
  if ( HalpDiagnosticEventsRegistered )
  {
    if ( *(_DWORD *)(HalpClockTimer + 228) == 12 )
      EtwWrite(HalpDiagnosticEventHandle, &HAL_ETW_EVENT_PLATFORM_CLOCK_TIMER, 0LL, 0, 0LL);
    if ( (MEMORY[0xFFFFF780000003C6] & 1) == 0 )
      EtwWrite(HalpDiagnosticEventHandle, &HAL_ETW_EVENT_NO_QPC_BYPASS, 0LL, 0, 0LL);
  }
}