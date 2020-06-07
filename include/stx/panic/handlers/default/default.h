/**
 * @file default.h
 * @author Basit Ayantunde <rlamarrr@gmail.com>
 * @version  0.0.1
 * @date 2020-05-22
 *
 * @copyright MIT License
 *
 * Copyright (c) 2020 Basit Ayantunde
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#pragma once

#include <mutex>   // mutex NOLINT
#include <thread>  // thread::id NOLINT

#if defined(STX_ENABLE_PANIC_BACKTRACE)
#include "stx/backtrace.h"
#endif

namespace stx {

// probably too much, but enough
// this will at least hold a formatted uint128_t (40 digits)

namespace internal {
namespace panic_util {
constexpr int kFormatBufferSize = 256;
constexpr auto kThreadIdHash = std::hash<std::thread::id>{};
}  // namespace panic_util
}  // namespace internal

// this should be made thread-safe.
inline void panic_default(
    std::string_view info, ReportPayload const& payload,
    SourceLocation location = SourceLocation::current()) noexcept {
  using namespace internal::panic_util;  // NOLINT

  static std::mutex stderr_lock;

  char log_buffer[kFormatBufferSize];

  auto thread_id_hash = kThreadIdHash(std::this_thread::get_id());

  stderr_lock.lock();

  std::fputs("\nthread with hash: '", stderr);

  std::snprintf(log_buffer, kFormatBufferSize, "%zu", thread_id_hash);
  std::fputs(log_buffer, stderr);

  std::fputs("' panicked with: '", stderr);

  for (char c : info) {
    std::fputc(c, stderr);
  }

  if (!payload.data().empty()) {
    std::fputc(':', stderr);
    std::fputc(' ', stderr);

    for (auto c : payload.data()) {
      std::fputc(c, stderr);
    }
  }

  std::fputc('\'', stderr);

  std::fputs(" at function: '", stderr);

  std::fputs(location.function_name(), stderr);

  std::fputs("' [", stderr);

  std::fputs(location.file_name(), stderr);

  std::fputc(':', stderr);

  if (location.line() != 0) {
    std::snprintf(log_buffer, kFormatBufferSize, "%d", location.line());
    std::fputs(log_buffer, stderr);
  } else {
    std::fputs("unknown", stderr);
  }

  std::fputc(':', stderr);

  if (location.column() != 0) {
    std::snprintf(log_buffer, kFormatBufferSize, "%d", location.column());
    std::fputs(log_buffer, stderr);
  } else {
    std::fputs("unknown", stderr);
  }

  std::fputs("]\n", stderr);

  std::fflush(stderr);

#if defined(STX_ENABLE_PANIC_BACKTRACE)
  // assumes the presence of an operating system

  std::fputs(
      "\nBacktrace:\nip: Instruction Pointer,  sp: Stack "
      "Pointer\n\n",
      stderr);

  int frames = backtrace::trace(

    std::fprintf(stderr, "#%d\t\t", i);

    frame.symbol.as_ref().match(
        [](Ref<backtrace::Symbol> sym) {
          for (char c : sym.get().raw()) {
            std::fputc(c, stderr);
          }
        },
        print_none);

    std::fputs("\t (ip: ", stderr);

    frame.ip.as_ref().match(print_ptr, print_none);

    std::fputs(", sp: ", stderr);

    frame.sp.as_ref().match(print_ptr, print_none);

    std::fputs(")\n", stderr);

        return false;
      },
      1);

  if (frames <= 0) {
    std::fputs(
        R"(WARNING >> The stack frames couldn't be identified, debug information was possibly stripped, unavailable, or elided by compiler
)",
        stderr);
  }

  std::fputs("\n", stderr);

#endif

  // other threads will still be able to log for some nanoseconds
  stderr_lock.unlock();
}
}  // namespace stx
