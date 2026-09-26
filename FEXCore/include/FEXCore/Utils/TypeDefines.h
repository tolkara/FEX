// SPDX-License-Identifier: MIT
#pragma once
#include <cstddef>

namespace FEXCore::Utils {
// FEX assumes an operating page size of 4096
// To work around build systems that build on a 16k/64k page size, define our page size here
// Don't use the system provided PAGE_SIZE define because of this.
constexpr size_t FEX_PAGE_SIZE = 4096;
constexpr size_t FEX_PAGE_SHIFT = 12;
// Size of a guard region. Protection changes only take effect at the host's page granularity, and Apple silicon
// hosts have 16K pages, so a guard needs to cover a whole host page to trap on every host FEX runs on.
constexpr size_t FEX_GUARD_SIZE = 16384;
constexpr size_t FEX_PAGE_MASK = ~(FEX_PAGE_SIZE - 1);
} // namespace FEXCore::Utils
