#pragma once

#include <type_traits>
#include <tuple>

namespace mk {
    template <typename K, typename V>
    struct TypePair {
        using First = K;
        using Second = V;
    };
    template <auto k, typename V>
    struct ValueTypePair {
        constexpr static inline auto First = k;
        using Second = V;
    };
    template <typename K, auto v>
    struct TypeValuePair {
        using First = K;
        constexpr static inline auto Second = v;
    };
    template <auto k, auto v>
    struct ValuePair {
        constexpr static inline auto First = k;
        constexpr static inline auto Second = v;
    };

    template <typename T> 				T 						InverseImpl(T val);
    template <typename K, typename V> 	TypePair<V, K> 			InverseImpl(TypePair<K, V> val);
    template <auto k, typename V> 		TypeValuePair<V, k> 	InverseImpl(ValueTypePair<k, V> val);
    template <typename K, auto v> 		ValueTypePair<v, K> 	InverseImpl(TypeValuePair<K, v> val);
    template <auto k, auto v> 			ValuePair<v, k> 		InverseImpl(ValuePair<k, v> val);

    template <typename T> using Inverse = decltype(InverseImpl(std::declval<T>()));

    template <typename>
    static constexpr bool is_type_pair_v = false;
    template <typename K, typename V>
    static constexpr bool is_type_pair_v<TypePair<K, V>> = true;
    template <auto k, typename V>
    static constexpr bool is_type_pair_v<ValueTypePair<k, V>> = true;
    template <typename K, auto v>
    static constexpr bool is_type_pair_v<TypeValuePair<K, v>> = true;
    template <auto k, auto v>
    static constexpr bool is_type_pair_v<ValuePair<k, v>> = true;

    template <typename ...Pairs>
    class TypeMap final {
#ifdef __clang__
    public:
#else
    private:
#endif
        template <std::size_t n>
        using GetNthType = typename std::tuple_element<n, std::tuple<Pairs...>>::type::Second;

        template <typename Key>
        constexpr static auto GetIndex(std::size_t index) {
            static_assert(index == sizeof...(Pairs), "Unsupported type");
        }

        template <auto key>
        constexpr static auto GetIndex(std::size_t index) {
            static_assert(index == sizeof...(Pairs), "Unsupported type");
        }

        template <typename Key, typename CurrentPair, typename ...OtherPairs>
        constexpr static auto GetIndex(std::size_t index = 0) {
            constexpr bool is_same = std::is_same_v<Key, typename CurrentPair::First>;
            if constexpr (is_same)
                return index;
            else
                return GetIndex<Key, OtherPairs...>(index + 1);
        }
        template <auto key, typename CurrentPair, typename ...OtherPairs>
        constexpr static auto GetIndex(std::size_t index = 0) {
            static_assert(is_type_pair_v<CurrentPair>, "Not a TypePair");

            constexpr bool is_same = key == CurrentPair::First;
            if constexpr (is_same)
                return index;
            else
                return GetIndex<key, OtherPairs...>(index + 1);
        }

    public:
        template <typename K>
        using GetTypeByType = GetNthType<GetIndex<K, Pairs...>()>;
        template <auto k>
        using GetTypeByValue = GetNthType<GetIndex<k, Pairs...>()>;

        template <typename K>
        constexpr static auto GetValueByType() {
            constexpr auto index = GetIndex<K, Pairs...>();
            return std::tuple_element<index, std::tuple<Pairs...>>::type::Second;
        }
        template <auto k>
        constexpr static auto GetValueByValue() {
            constexpr auto index = GetIndex<k, Pairs...>();
            return std::tuple_element<index, std::tuple<Pairs...>>::type::Second;
        }

        using InverseMap = TypeMap<Inverse<Pairs>...>;
    };
}
