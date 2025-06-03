Here's the commented version of the code:

```c++
// Copyright 2025 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_SWITCH_H
#define GRPC_SRC_CORE_LIB_PROMISE_SWITCH_H

#include <grpc/support/port_platform.h>

#include <memory>
#include <utility>

#include "src/core/lib/promise/detail/promise_factory.h"
#include "src/core/lib/promise/detail/promise_variant.h"
#include "src/core/lib/promise/if.h"
#include "src/core/util/crash.h"

namespace grpc_core {

namespace promise_detail {
// Case represents a single case in a switch statement.
// D is the discriminator value, F is the promise factory type.
template <auto D, typename F>
struct Case {
  using Factory = OncePromiseFactory<void, F>;
  explicit Case(F f) : factory(std::move(f)) {}
  Factory factory;
  static constexpr const decltype(D) kDiscriminator = D;
};

// Default represents the default case in a switch statement.
template <typename F>
struct Default {
  using Factory = OncePromiseFactory<void, F>;
  explicit Default(F f) : factory(std::move(f)) {}
  Factory factory;
};

// Base case for switch construction - handles only the default case
template <typename Promise, typename D, typename FD>
Promise ConstructSwitchPromise(D discriminator, Default<FD>& default_case) {
  switch (discriminator) {
    default:
      return default_case.factory.Make();
  }
}

// Recursive template functions for constructing switch statements with increasing
// numbers of cases. Each version handles one additional case before falling back
// to the default case.

// Version with 1 case + default
template <typename Promise, typename D, typename F0, D d0, typename FD>
Promise ConstructSwitchPromise(D discriminator, Case<d0, F0>& case_0,
                               Default<FD>& default_case) {
  switch (discriminator) {
    case Case<d0, F0>::kDiscriminator:
      return case_0.factory.Make();
    default:
      return default_case.factory.Make();
  }
}

// Version with 2 cases + default
template <typename Promise, typename D, typename F0, D d0, typename F1, D d1,
          typename FD>
Promise ConstructSwitchPromise(D discriminator, Case<d0, F0>& case_0,
                               Case<d1, F1>& case_1,
                               Default<FD>& default_case) {
  switch (discriminator) {
    case Case<d0, F0>::kDiscriminator:
      return case_0.factory.Make();
    case Case<d1, F1>::kDiscriminator:
      return case_1.factory.Make();
    default:
      return default_case.factory.Make();
  }
}

// [Similar versions with 3-18 cases omitted for brevity - they follow the same pattern]

// Version with 18 cases + default (maximum supported)
template <typename Promise, typename D, typename F0, D d0, typename F1, D d1,
          typename F2, D d2, typename F3, D d3, typename F4, D d4, typename F5,
          D d5, typename F6, D d6, typename F7, D d7, typename F8, D d8,
          typename F9, D d9, typename F10, D d10, typename F11, D d11,
          typename F12, D d12, typename F13, D d13, typename F14, D d14,
          typename F15, D d15, typename F16, D d16, typename F17, D d17,
          typename F18, D d18, typename FD>
Promise ConstructSwitchPromise(D discriminator, Case<d0, F0>& case_0,
                               Case<d1, F1>& case_1, Case<d2, F2>& case_2,
                               Case<d3, F3>& case_3, Case<d4, F4>& case_4,
                               Case<d5, F5>& case_5, Case<d6, F6>& case_6,
                               Case<d7, F7>& case_7, Case<d8, F8>& case_8,
                               Case<d9, F9>& case_9, Case<d10, F10>& case_10,
                               Case<d11, F11>& case_11, Case<d12, F12>& case_12,
                               Case<d13, F13>& case_13, Case<d14, F14>& case_14,
                               Case<d15, F15>& case_15, Case<d16, F16>& case_16,
                               Case<d17, F17>& case_17, Case<d18, F18>& case_18,
                               Default<FD>& default_case) {
  switch (discriminator) {
    case Case<d0, F0>::kDiscriminator:
      return case_0.factory.Make();
    case Case<d1, F1>::kDiscriminator:
      return case_1.factory.Make();
    case Case<d2, F2>::kDiscriminator:
      return case_2.factory.Make();
    case Case<d3, F3>::kDiscriminator:
      return case_3.factory.Make();
    case Case<d4, F4>::kDiscriminator:
      return case_4.factory.Make();
    case Case<d5, F5>::kDiscriminator:
      return case_5.factory.Make();
    case Case<d6, F6>::kDiscriminator:
      return case_6.factory.Make();
    case Case<d7, F7>::kDiscriminator:
      return case_7.factory.Make();
    case Case<d8, F8>::kDiscriminator:
      return case_8.factory.Make();
    case Case<d9, F9>::kDiscriminator:
      return case_9.factory.Make();
    case Case<d10, F10>::kDiscriminator:
      return case_10.factory.Make();
    case Case<d11, F11>::kDiscriminator:
      return case_11.factory.Make();
    case Case<d12, F12>::kDiscriminator:
      return case_12.factory.Make();
    case Case<d13, F13>::kDiscriminator:
      return case_13.factory.Make();
    case Case<d14, F14>::kDiscriminator:
      return case_14.factory.Make();
    case Case<d15, F15>::kDiscriminator:
      return case_15.factory.Make();
    case Case<d16, F16>::kDiscriminator:
      return case_16.factory.Make();
    case Case<d17, F17>::kDiscriminator:
      return case_17.factory.Make();
    case Case<d18, F18>::kDiscriminator:
      return case_18.factory.Make();
    default:
      return default_case.factory.Make();
  }
}

// Implementation function for Switch that constructs the appropriate promise variant
// based on the discriminator value and cases provided.
template <typename D, typename... Cases>
auto SwitchImpl(D discriminator, Cases&... cases) {
  using Promise = std::variant<typename Cases::Factory::Promise...>;
  return PromiseVariant<Promise>(
      ConstructSwitchPromise<Promise>(discriminator, cases...));
}

}  // namespace promise_detail

// Helper function to create a Case object
template <auto kDiscriminator, typename PromiseFactory>
auto Case(PromiseFactory f) {
  return promise_detail::Case<kDiscriminator, PromiseFactory>{std::move(f)};
}

// Helper function to create a Default case object
template <typename PromiseFactory>
auto Default(PromiseFactory f) {
  return promise_detail::Default<PromiseFactory>{std::move(f)};
}

// Main Switch function that provides a promise-based switch statement.
// Takes a discriminator value and a set of cases, returns a promise variant
// that will execute the appropriate case based on the discriminator value.
template <typename D, typename... C>
auto Switch(D discriminator, C... cases) {
  return promise_detail::SwitchImpl(discriminator, cases...);
}

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_LIB_PROMISE_SWITCH_H
```

Key points about the implementation:

1. The code provides a promise-based switch statement implementation that works similarly to a regular C++ switch statement but returns promises.

2. It uses template metaprogramming to generate switch statements with varying numbers of cases (from 1 to 18 cases plus a default).

3. The `Case` template represents a single case in the switch, storing both the discriminator value and the promise factory for that case.

4. The `Default` template represents the default case.

5. The `Switch` function is the main entry point that uses `SwitchImpl` to construct the appropriate promise variant based on the discriminator value.

6. The implementation supports up to 18 cases (plus default) through a series of template specializations.

7. Each case's promise is created through the factory's `Make()` method when the discriminator matches.

8. The result is wrapped in a `PromiseVariant` which likely provides additional promise-related functionality.