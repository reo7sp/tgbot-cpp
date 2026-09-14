# Repository workflow

- Use the repository's `make` targets for formatting, linting, generation, builds, and tests whenever a matching target exists.
- Run `make api-generate` after changing the API schema, code generator, or generator configuration.
- Run `make format` and `make lint`; do not invoke `clang-format` directly on generated files. `ApiMethods.cpp` and `ApiMethods.inc.h` require the dedicated formatting commands encoded in the `Makefile`.
- Run the complete build and test suite with `make test`. It installs the required dependencies, builds the C++ library and tests, runs the C++ tests, and runs the API codegen tests.
- Do not split a normal full verification into `make build-with-test`, `make test-only`, and `make test-api-codegen`; those targets are implementation details or for deliberately narrow reruns after `make test` has already built their prerequisites.
- Do not override `BUILD_DIR` for normal builds or tests. The Conan layout writes its toolchain to the repository's standard build directory, so a custom `BUILD_DIR` can make CMake look for a toolchain that Conan did not place there.
- Preserve public source compatibility when updating the Telegram Bot API. Do not reorder, remove, or change the types or defaults of existing positional `Api` method parameters, and do not remove existing fields from `*Args` structs. Append new optional parameters or expose them through `*Args`; when Telegram replaces parameters, keep the legacy API and translate it to the new wire representation. Add regression tests for the preserved signatures and translation.
