// SPDX-License-Identifier: MIT
#pragma once

#ifdef FEX_TEB_TSD_OFFSET
// arm64 Darwin hosts: the kernel does not preserve x18, so Wine keeps the TEB in a pthread TSD slot
// reached through TPIDRRO_EL0 (its -D__WINE_TEB_TSD_OFFSET). Read it from there instead of x18.
// Anything that includes <windows.h> gets the x18 version of NtCurrentTeb(), so C code that is not built
// against this directory's headers (rpmalloc) has this header force-included.
#include <windows.h>

#define FEX_TEB_TSD_STR_(x) #x
#define FEX_TEB_TSD_STR(x) FEX_TEB_TSD_STR_(x)
static inline struct _TEB* FEXCurrentTeb(void) {
  struct _TEB* Teb;
  __asm__("mrs %0, tpidrro_el0\n\tldr %0, [%0, #" FEX_TEB_TSD_STR(FEX_TEB_TSD_OFFSET) "]" : "=r"(Teb));
  return Teb;
}
#define NtCurrentTeb() FEXCurrentTeb()
#endif
