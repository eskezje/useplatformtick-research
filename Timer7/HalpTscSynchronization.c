int __fastcall HalpTscSynchronization(char a1, __int64 a2)
{
  ULONG_PTR *Timer; // rax
  __int64 v5; // rdx
  ULONG_PTR Context[2]; // [rsp+30h] [rbp-48h] BYREF
  __int128 v8; // [rsp+40h] [rbp-38h]
  __int128 v9; // [rsp+50h] [rbp-28h]

  *(_OWORD *)Context = 0LL;
  v8 = 0LL;
  v9 = 0LL;
  if ( qword_140FC03C8 || (unsigned __int8)HviIsXboxNanovisorPresent() )
  {
    Timer = HalpFindTimer(5, 0, 0, 0, 1);
    if ( Timer && (Timer[28] & 0x6000) == 0 )
      *((_DWORD *)Timer + 46) |= 0x20u;
  }
  else
  {
    LODWORD(Timer) = KeQueryActiveProcessorCountEx(0xFFFFu);
    if ( (unsigned int)Timer >= 2 )
    {
      LOBYTE(v5) = a1;
      HalpTscInitializeSynchronizationContext(Context, v5, a2, 0LL);
      LODWORD(Timer) = KeIpiGenericCall(HalpTscSynchronizationWorker, (ULONG_PTR)Context);
    }
  }