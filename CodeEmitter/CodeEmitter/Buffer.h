// SPDX-License-Identifier: MIT
#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <type_traits>

namespace ARMEmitter {
class Buffer {
public:
  Buffer() {
    SetBuffer(nullptr, 0);
  }

  Buffer(uint8_t* Base, uint64_t BaseSize) {
    SetBuffer(Base, BaseSize);
  }

  void SetBuffer(uint8_t* Base, uint64_t BaseSize) {
    BufferBase = Base;
    CurrentOffset = BufferBase;
    Size = BaseSize;
  }

  // The buffer is written at this offset from where its code runs (a writable
  // alias of executable memory); addresses are always those of the code.
  void SetWriteOffset(ptrdiff_t Offset) {
    WriteOffset = Offset;
  }

  // Store an instruction or data word over what was emitted at Location.
  template<typename T>
  requires (std::is_trivially_copyable_v<T>)
  void Patch(T* Location, const T& Data) {
    std::memcpy(reinterpret_cast<uint8_t*>(Location) + WriteOffset, &Data, sizeof(Data));
  }

  template<typename T>
  requires (std::is_trivially_copyable_v<T>)
  void dcn(const T& Data) {
    std::memcpy(CurrentOffset + WriteOffset, &Data, sizeof(Data));
    CurrentOffset += sizeof(Data);
  }
  void dc8(uint8_t Data) {
    dcn(Data);
  }
  void dc16(uint16_t Data) {
    dcn(Data);
  }
  void dc32(uint32_t Data) {
    dcn(Data);
  }
  void dc64(uint64_t Data) {
    dcn(Data);
  }

  void EmitString(const char* String) {
    const auto StringLength = strlen(String);
    memcpy(CurrentOffset + WriteOffset, String, StringLength);
    CurrentOffset += StringLength;
  }

  void Align(size_t Size = 4) {
    // Align the buffer to provided size.
    auto CurrentAlignment = reinterpret_cast<uint64_t>(CurrentOffset) & (Size - 1);
    if (!CurrentAlignment) {
      return;
    }
    std::memset(CurrentOffset + WriteOffset, 0, Size - CurrentAlignment);
    CurrentOffset += Size - CurrentAlignment;
  }

  template<typename T>
  T GetCursorAddress() const {
    return reinterpret_cast<T>(CurrentOffset);
  }

  static void ClearICache(void* Begin, std::size_t Length) {
    __builtin___clear_cache(static_cast<char*>(Begin), static_cast<char*>(Begin) + Length);
  }

  size_t GetCursorOffset() const {
    return static_cast<size_t>(CurrentOffset - BufferBase);
  }

  uint8_t* GetBufferBase() const {
    return BufferBase;
  }

  void CursorIncrement(size_t Size) {
    CurrentOffset += Size;
  }

  void SetCursorOffset(size_t Offset) {
    CurrentOffset = BufferBase + Offset;
  }

  uint64_t GetBufferSize() const {
    return Size;
  }

  template<typename T>
  size_t GetCursorOffsetFromAddress(const T* Address) const {
    return static_cast<size_t>(reinterpret_cast<const uint8_t*>(Address) - BufferBase);
  }

protected:

  uint8_t* BufferBase;
  uint8_t* CurrentOffset;
  uint64_t Size;
  ptrdiff_t WriteOffset {};
};
} // namespace ARMEmitter
