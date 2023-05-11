#include "type_map.hpp"
#include <complex>

using namespace mk;

int main() {
    // direct
    using TypeToType = TypeMap<
        TypePair<int, std::complex<int>>,
        TypePair<double, std::complex<double>>
    >;

    using ComplexInt = TypeToType::GetTypeByType<int>;
    static_assert(std::is_same_v<ComplexInt, std::complex<int>>, "Incorrect");

    using ValueToType = TypeMap<
        ValueTypePair<10, int>,
        ValueTypePair<20, double>
    >;

    using IntFromIndex = ValueToType::GetTypeByValue<10>;
    static_assert(std::is_same_v<IntFromIndex, int>, "Oopsie");

    using TypeToValue = TypeMap<
        TypeValuePair<int, 30>,
        TypeValuePair<double, 40>
    >;

    constexpr auto int_index = TypeToValue::GetValueByType<int>();
    static_assert(int_index == 30, "Oopsie");

    using ValueToValue = TypeMap<
        ValuePair<0xAA, 0xCC>,
        ValuePair<0xBB, 0xDD>
    >;

    constexpr auto get_cc = ValueToValue::GetValueByValue<0xAA>();
    static_assert(get_cc == 0xCC, "Oopsie");

    // inverse
    using InverseTypeToType = TypeToType::InverseMap;
    using IntFromComplex = InverseTypeToType::GetTypeByType<std::complex<int>>;
    static_assert(std::is_same_v<IntFromComplex, int>, "Incorrect");

    using InverseValueToType = ValueToType::InverseMap;
    constexpr auto inverse_int_index = InverseValueToType::GetValueByType<int>();
    static_assert(inverse_int_index == 10, "Incorrect");

    using InverseTypeToValue = TypeToValue::InverseMap;
    using inverse_index_int = InverseTypeToValue::GetTypeByValue<30>;
    static_assert(std::is_same_v<inverse_index_int, int>, "Incorrect");

    using InverseValueToValue = ValueToValue::InverseMap;
    constexpr auto get_aa = InverseValueToValue::GetValueByValue<0xcc>();
    static_assert(get_aa == 0xAA, "Incorrect");

    return 0;
}