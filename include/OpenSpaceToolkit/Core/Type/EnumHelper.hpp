// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Type_EnumHelper__
#define __OpenSpaceToolkit_Core_Type_EnumHelper__

#include <magic_enum.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <optional>
#include <string_view>

/// @brief Macro to define enum to string and string to enum conversion functions.
///
/// This macro should be invoked within the namespace of the EnumType.
/// For example:
/// namespace ostk { namespace core { namespace type {
/// enum class MyEnum { A, B, C };
/// OSTK_CORE_DEFINE_ENUM_STRING_CONVERSION(MyEnum)
/// }}}
/// This will define:
/// ostk::core::type::String StringFromEnum(MyEnum val) { ... }
/// std::optional<MyEnum> EnumFromString(const ostk::core::type::String& str) { ... }
/// in the ostk::core::type namespace.
#define OSTK_CORE_DEFINE_ENUM_STRING_CONVERSION(EnumType)                                   \
    inline ostk::core::type::String StringFromEnum(EnumType enumValue)                      \
    {                                                                                       \
        return ostk::core::type::String(magic_enum::enum_name(enumValue));                  \
    }                                                                                       \
                                                                                            \
    inline std::optional<EnumType> EnumFromString(const ostk::core::type::String& enumString)\
    {                                                                                       \
        return magic_enum::enum_cast<EnumType>(static_cast<std::string_view>(enumString));  \
    }

#endif // __OpenSpaceToolkit_Core_Type_EnumHelper__
