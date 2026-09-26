# Tolkara's downstream FEX fork

This branch (`tolkara/darwin-arm64`) is FEX with changes to its Windows-side
emulator modules (`libarm64ecfex.dll`, `libwow64fex.dll`) for running under
Wine on arm64 Darwin (macOS and, under Tolkara, iPadOS). It is maintained by
the Tolkara project (https://github.com/tolkara) as a downstream fork.

**Not for upstream submission.** The changes on this branch were written
with an LLM-based coding tool. FEX's CONTRIBUTING.md says: "No AI/ML/LLM/etc
code contributions." Out of respect for that rule, nothing on this branch is
to be submitted to FEX-Emu or to any other upstream. It exists only so that
Tolkara can carry a Windows runtime while the projects concerned settle how
x86 programs run on arm64 Darwin. The commits follow FEX's coding style
(clang-format) and are kept small so that the branch stays reviewable and
rebaseable, not to prepare them for upstream.

FEX is MIT licensed; see LICENSE. The changes here are under the same licence.
