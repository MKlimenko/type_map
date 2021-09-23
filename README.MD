# Header-only library for compile-time lookup table based on types and non-type template parameters

This library is a metaprogramming utility to create lookup tables for types. This is needed mostly when working with C code. It is also quite handy when dealing with enumerator values denoting the types.

Simplest example:

```cpp
using TypeToType = TypeMap<
    TypePair<int, std::complex<int>>,
    TypePair<double, std::complex<double>>
>;

using ComplexInt = TypeToType::GetTypeByType<int>;
static_assert(std::is_same_v<ComplexInt, std::complex<int>>, "Incorrect");
```