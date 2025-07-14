# Research on the usage of USEPLATFORMTICK

I've been curious as to what USEPLATFORMTICK does, PRECISELY, so here I will document my findings.

As [MSDN states](https://learn.microsoft.com/en-us/windows-hardware/drivers/devtest/bcdedit--set):
**useplatformtick [ yes | no ]**
Forces the clock to be backed by a platform source, no synthetic timers are allowed. The option is available starting in Windows 8 and Windows Server 2012.

But I want to know more in depth what it means for "the clock to be backed by a platform source".

You can find the research on the usage of USEPLATFORMTICK in the [Research.md](Research.md) file. (Very inexperienced, so please correct me if I am wrong)

[Looking into to other BCDEDITS such as `tscsyncpolicy` and `useplatformclock`](Research_BCD_edits.md)