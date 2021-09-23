#include "type_map.hpp"
#include <complex>

using namespace mk;

int main() {
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
	
	return 0;
}