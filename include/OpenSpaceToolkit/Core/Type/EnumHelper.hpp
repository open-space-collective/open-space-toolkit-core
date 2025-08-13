// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Type_EnumHelper__
#define __OpenSpaceToolkit_Core_Type_EnumHelper__

#include <string_view>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

/// @brief  Declares the standard enum-to-string and string-to-enum conversion functions.
/// @note   This macro should be used in a header file, within the namespace of the enum.
///         It does NOT have a dependency on magic_enum.
#define OSTK_CORE_DECLARE_ENUM_STRING_CONVERSION(EnumType, EnumName, ClassName) \
    static ostk::core::type::String StringFrom##EnumName(EnumType enumValue);   \
    static EnumType EnumName##FromString(const ostk::core::type::String& enumString);

/// @brief  Defines the implementation for enum-to-string and string-to-enum conversion functions.
/// @note   This macro should be used in a source file, within the namespace of the enum.
///         The source file MUST #include <magic_enum/magic_enum.hpp> before using this.
#define OSTK_CORE_DEFINE_ENUM_STRING_CONVERSION(EnumType, EnumName, ClassName)                          \
    ostk::core::type::String ClassName::StringFrom##EnumName(EnumType enumValue)                        \
    {                                                                                                   \
        return ostk::core::type::String(magic_enum::enum_name(enumValue));                              \
    }                                                                                                   \
                                                                                                        \
    EnumType ClassName::EnumName##FromString(const ostk::core::type::String& enumString)                \
    {                                                                                                   \
        const auto result = magic_enum::enum_cast<EnumType>(static_cast<std::string_view>(enumString)); \
        if (!result.has_value())                                                                        \
        {                                                                                               \
            throw ostk::core::error::runtime::Wrong("Enum", enumString);                                \
        }                                                                                               \
        return result.value();                                                                          \
    }

#endif
