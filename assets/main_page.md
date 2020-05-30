@mainpage

# What is STX?

STX is a collection of libraries and utilities designed to make working with C++ easier and less error-prone. This includes but is not limited to well-proven and widely adopted paradigms, data-structures, and designs from other prominent projects and programming languages accross the software engineering community.

At the core, all STX libraries are `no_std` .

# Primary Goals

- Unifying community efforts, and reducing code duplication
- Providing deterministic and convenient error-handling facilities
- Providing clean libraries that avoids quarks and complexities
- Portability
- Suitability for real-time systems, operating systems, embedded systems, and safety-critical systems
- Efficiency

# STX Libraries

## Panic Library

See guide on @ref Panicking

The panic library provides:

- panicking:

  - `stx::panic` : signals an abnormal flow/error in the program.

- runtime panic hooks

- optional panic backtraces

- error reporting
- panic handlers:

  - `stx::panic_default` : The default panic handler that prints the error message and panic location data, and afterwards aborts the program.
  - `stx::panic_halt` : A panic handler that causes the current calling thread, to halt by entering an infinite loop.
  - `stx::panic_abort` : A panic handler that causes the abort instruction to be executed.

## Error and Optional-Value Handling Library

These monadic types not only make error handling easer but also make the paths more obvious to the compiler for optimizations. Their monadic nature makes it easy to operate on them as pipelines and in the process eliminate redundant error-handling logic code.

- `stx::Result<T, E>` : Type for relaying the result of a function that can fail or succeed. (with monadic extensions).
- `stx::Option<T>` : Type for **safe** optional values (with monadic extensions).

## Backtracing Library

The backtracing library is useful for manually querying/viewing information of active stack frames. It makes debugging easier by making it easier to get stackframe information programmartically or automatically (panics) without having to inspect core dumps or step into a debugger in which errors might not be reproducible (especially for embedded systems).
The backtrace library is disabled by default as not all platforms support them, It can be enabled.

- Fatal signal backtraces for `SIGSEGV` , `SIGFPE` , and `SIGILL` .
- Manual stack backtraces.

# Why STX?

STX is partially an effort to bring a more convenient and usable error-handling model to the C++ ecosystem. Whilst also sampling ideas from various error-handling model implementations duplicated across the community, Most of the basic facilities for which these libraries provide.

Here is a list of C++ projects with a similar error-handling model:

- Boost's [`expected`](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4109.pdf) and [`outcome`](https://www.boost.org/doc/libs/1_70_0/libs/outcome/doc/html/index.html)
- Simon Brand's [`tl::optional`](https://github.com/TartanLlama/optional)
- Abseil's [`Status` , `StatusCode`](https://github.com/abseil/abseil-cpp/tree/master/absl/status), and [`RawLog`](https://github.com/abseil/abseil-cpp/blob/master/absl/base/internal/raw_logging.cc)
- Tensorflow Lite Micro's [`ErrorReporter`](https://github.com/tensorflow/tensorflow/blob/master/tensorflow/lite/core/api/error_reporter.h)
- Tensorflow's [`Status` , `Code`](https://github.com/tensorflow/tensorflow/blob/master/tensorflow/core/platform/status.h), [`Logging`](https://github.com/tensorflow/tensorflow/blob/master/tensorflow/core/platform/default/logging.cc), [`ENSURE_OK` , `CHECK_OK` , `DCHECK_OK` , `QCHECK_OK`](https://github.com/tensorflow/tensorflow/blob/master/tensorflow/core/platform/status.h), and other error handling macros
- Mozilla's [`Result<T, E>`](https://searchfox.org/mozilla-central/source/mfbt/Result.h), [`Maybe<T>`](https://searchfox.org/mozilla-central/source/mfbt/Maybe.h), [`MaybeOneOf<A, B>`](https://searchfox.org/mozilla-central/source/mfbt/MaybeOneOf.h), and [`NotNull<T*>`](https://searchfox.org/mozilla-central/source/mfbt/NotNull.h)
- Google Pigweed's [`Result<T, Status>`](https://pigweed.googlesource.com/pigweed/pigweed/+/refs/heads/master/pw_result/), [`Status`](https://pigweed.googlesource.com/pigweed/pigweed/+/refs/heads/master/pw_status/)
- Simdjson's [`error_code` , `result`](https://github.com/simdjson/simdjson/blob/master/include/simdjson/error.h)
- MBED OS' [`Error`](https://github.com/ARMmbed/mbed-os/blob/master/platform/source/mbed_error.c)
- LLVM's [`Error` , `Expected`](https://github.com/llvm/llvm-project/blob/master/llvm/include/llvm/Support/Error.h), [`ErrorOr`](https://github.com/llvm/llvm-project/blob/master/llvm/include/llvm/Support/ErrorOr.h), [`ErrorHandling`](https://github.com/llvm/llvm-project/blob/master/llvm/lib/Support/ErrorHandling.cpp)
- Fuchsia OS - Zircon Common Library' s [`Result`](https://fuchsia.googlesource.com/fuchsia/+/refs/heads/master/zircon/system/ulib/zxc/) and [`Status`](https://fuchsia.googlesource.com/fuchsia/+/refs/heads/master/zircon/system/ulib/zxc/)
- P-ranav's [`Result<T, E>`](https://github.com/p-ranav/result/blob/master/include/result/result.hpp)

# FAQs

- xpc_error_code