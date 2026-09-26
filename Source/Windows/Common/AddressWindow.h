// SPDX-License-Identifier: MIT
#pragma once

#include <cstdint>

// A 32-bit guest whose address space cannot sit at identity (arm64 Darwin hosts have nothing below 4 GB)
// lives at a 4 GB-aligned host window: guest address g is host address (Base | g), and the low half of a
// host address in the window is the guest address. Base stays 0 where the guest is at identity.
namespace FEX::Windows::AddressWindow {
inline uint64_t Base {};

static inline uint64_t ToHost(uint64_t Guest) {
  return Guest | Base;
}

static inline uint64_t ToGuest(uint64_t Host) {
  return Base ? (Host & 0xffff'ffffULL) : Host;
}
} // namespace FEX::Windows::AddressWindow
