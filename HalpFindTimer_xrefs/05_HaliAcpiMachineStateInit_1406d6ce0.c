/* Function: HaliAcpiMachineStateInit @ 0x1406d6ce0 (call depth 5) */

int __fastcall HaliAcpiMachineStateInit(_BYTE *a1)
{
  bool v2; // di
  int v3; // eax
  _DWORD *v4; // rdx
  __int64 (__fastcall *v5)(unsigned int, __int64, __int64, int, volatile signed __int32 *); // rax
  __int64 v6; // rcx
  __int64 v7; // rax
  __int64 v8; // rdx
  __int64 v9; // r8
  char v10; // cl
  int v11; // eax
  unsigned int v12; // eax
  __int64 v13; // rdx
  __int64 v14; // r8
  char v15; // cl
  int v16; // eax
  unsigned int v17; // eax
  __int64 v18; // rdx
  __int64 v19; // r8
  __int64 v20; // rcx
  unsigned __int64 v21; // rcx
  int v22; // ecx
  int v23; // eax
  unsigned int v24; // eax
  int v25; // ecx
  int v26; // eax
  unsigned int v27; // eax
  __int64 v28; // rdx
  __int64 v29; // r8
  __int128 InputBuffer; // [rsp+30h] [rbp-20h] BYREF
  __int64 v32; // [rsp+40h] [rbp-10h]

  v32 = 0LL;
  v2 = 0;
  InputBuffer = 0LL;
  HalpWakeupState = 1;
  v3 = HalpInterruptModel();
  *v4 = v3;
  if ( a1[9] && !HalpDisableHibernate )
    v2 = (unsigned __int8)HalpIsXboxNanovisorPresent() == 0;
  v5 = HaliAcpiSleep;
  if ( *a1 )
  {
    v6 = a1[2] & 0xF;
    *((_QWORD *)&InputBuffer + 1) = HaliAcpiSleep;
    v7 = a1[1] & 0xF;
    BYTE4(InputBuffer) = 1;
    v32 = v7 | (16 * (v6 | 0x510));
    ZwPowerInformation(SystemPowerStateHandler, &InputBuffer, 0x18u, 0LL, 0);
    if ( HalpHvSleepEnlightenedCpuManager )
    {
      LOBYTE(v9) = a1[2];
      LOBYTE(v8) = a1[1];
      HalpHvSetSleepStateProperty(1LL, v8, v9);
    }
    v5 = HaliAcpiSleep;
  }
  if ( !HalpWakeVector )
    goto LABEL_22;
  if ( a1[3] )
  {
    v10 = a1[4];
    *((_QWORD *)&InputBuffer + 1) = HaliAcpiSleep;
    v11 = a1[5] & 0xF;
    LODWORD(InputBuffer) = 1;
    BYTE4(InputBuffer) = 1;
    v12 = v10 & 0xF | (16 * (v11 | 0x520));
    if ( !HalpHvSleepEnlightenedCpuManager )
      v12 |= 0x12000u;
    v32 = v12;
    LODWORD(v5) = ZwPowerInformation(SystemPowerStateHandler, &InputBuffer, 0x18u, 0LL, 0);
    if ( HalpHvSleepEnlightenedCpuManager )
    {
      LOBYTE(v14) = a1[5];
      LOBYTE(v13) = a1[4];
      LODWORD(v5) = HalpHvSetSleepStateProperty(2LL, v13, v14);
    }
  }
  if ( !a1[6] )
    goto LABEL_22;
  v15 = a1[7];
  *((_QWORD *)&InputBuffer + 1) = HaliAcpiSleep;
  v16 = a1[8] & 0xF;
  LODWORD(InputBuffer) = 2;
  BYTE4(InputBuffer) = 1;
  v17 = v15 & 0xF | (16 * (v16 | 0x530));
  if ( !HalpHvSleepEnlightenedCpuManager )
    v17 |= 0x32000u;
  v32 = v17;
  LODWORD(v5) = ZwPowerInformation(SystemPowerStateHandler, &InputBuffer, 0x18u, 0LL, 0);
  if ( HalpHvSleepEnlightenedCpuManager )
  {
    LOBYTE(v19) = a1[8];
    LOBYTE(v18) = a1[7];
    LODWORD(v5) = HalpHvSetSleepStateProperty(3LL, v18, v19);
  }
  if ( a1[6] )
  {
    if ( !v2 )
      goto LABEL_26;
    v20 = a1[8] & 0xF | 0x3740LL;
    BYTE4(InputBuffer) = (unsigned __int8)dword_140FBFFB0 >> 7;
    v21 = a1[7] & 0xF | (unsigned __int64)(16 * v20);
    LODWORD(InputBuffer) = 6;
    v32 = v21;
    *((_QWORD *)&InputBuffer + 1) = HaliAcpiSleep;
    ZwPowerInformation(SystemPowerStateHandler, &InputBuffer, 0x18u, 0LL, 0);
  }
  else
  {
LABEL_22:
    if ( !v2 )
      goto LABEL_26;
  }
  v22 = a1[10] & 0xF;
  BYTE4(InputBuffer) = (unsigned __int8)dword_140FBFFB0 >> 7;
  v23 = a1[11] & 0xF;
  LODWORD(InputBuffer) = 3;
  *((_QWORD *)&InputBuffer + 1) = HaliAcpiSleep;
  v24 = v22 | (16 * (v23 | 0x540));
  if ( !HalpHvSecureCpuResume )
    v24 |= 0x10000u;
  v32 = v24;
  LODWORD(v5) = ZwPowerInformation(SystemPowerStateHandler, &InputBuffer, 0x18u, 0LL, 0);
LABEL_26:
  if ( !a1[12] )
  {
    if ( !HalFirmwareTypeEfi )
      goto LABEL_32;
    goto LABEL_31;
  }
  if ( (HalpPlatformFlags & 1) == 0 )
  {
LABEL_31:
    HalpShutdownContext = 0;
    v32 = 0LL;
    *(_QWORD *)&InputBuffer = 4LL;
    *((_QWORD *)&InputBuffer + 1) = HalpLegacyShutdown;
    LODWORD(v5) = ZwPowerInformation(SystemPowerStateHandler, &InputBuffer, 0x18u, 0LL, 0);
    goto LABEL_32;
  }
  v25 = a1[13] & 0xF;
  v26 = a1[14] & 0xF;
  LODWORD(InputBuffer) = 4;
  BYTE4(InputBuffer) = 0;
  v27 = v25 | (16 * (v26 | 0x850));
  *((_QWORD *)&InputBuffer + 1) = HaliAcpiSleep;
  v32 = v27;
  HalpShutdownContext = v27;
  LODWORD(v5) = ZwPowerInformation(SystemPowerStateHandler, &InputBuffer, 0x18u, 0LL, 0);
  if ( !HalpHvSleepEnlightenedCpuManager )
    return (int)v5;
  LOBYTE(v29) = a1[14];
  LOBYTE(v28) = a1[13];
  LODWORD(v5) = HalpHvSetSleepStateProperty(5LL, v28, v29);
LABEL_32:
  if ( HalpHvSleepEnlightenedCpuManager )
    LODWORD(v5) = HalpHvSetSleepStateProperty(6LL, 0LL, 0LL);
  return (int)v5;
}
