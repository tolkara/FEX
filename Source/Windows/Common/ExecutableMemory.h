// SPDX-License-Identifier: MIT
#pragma once
#include <FEXCore/Utils/AllocatorHooks.h>

#include <windef.h>
#include <winternl.h>

namespace FEX::Windows {
// Where executable memory is written: Wine says whether the memory it gives
// for code is written through an alias at a constant offset from where it
// runs (an iPadOS host); if it cannot tell, code is written in place.
inline void InitExecutableWriteOffset() {
  ULONG_PTR Offset {};
  if (NT_SUCCESS(NtQueryVirtualMemory(NtCurrentProcess(), nullptr, MemoryWineJitWriteOffset, &Offset, sizeof(Offset), nullptr))) {
    FEXCore::Allocator::ExecutableWriteOffset = static_cast<ptrdiff_t>(Offset);
  }
}
} // namespace FEX::Windows
