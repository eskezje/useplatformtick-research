__int64 HalpInterruptModel()
{
  __int64 result; // rax

  if ( !HalpInterruptController )
    return 1LL;
  result = 2LL;
  if ( *(_DWORD *)(HalpInterruptController + 0xF0) == 2 )
    return 1LL;
  if ( *(_DWORD *)(HalpInterruptController + 0xF0) != 3 )
  {
    if ( *(_DWORD *)(HalpInterruptController + 0xF0) == 4 )
    {
      return 3LL;
    }
    else if ( *(_DWORD *)(HalpInterruptController + 0xF0) == 6 )
    {
      return 4LL;
    }
    else
    {
      return 0x1000LL;
    }
  }
  return result;
}