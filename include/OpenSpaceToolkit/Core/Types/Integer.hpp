////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           OpenSpaceToolkit/Core/Types/Integer.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Core_Types_Integer__
#define __OpenSpaceToolkit_Core_Types_Integer__

#include <OpenSpaceToolkit/Core/Types/Sign.hpp>
#include <OpenSpaceToolkit/Core/Types/Index.hpp>
#include <OpenSpaceToolkit/Core/Types/Size.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <ostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace core
{
namespace types
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef int8_t Int8 ;
typedef int16_t Int16 ;
typedef int32_t Int32 ;
typedef int64_t Int64 ;

typedef uint8_t Uint8 ;
typedef uint16_t Uint16 ;
typedef uint32_t Uint32 ;
typedef uint64_t Uint64 ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Real ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Integer type

class Integer
{

    public:

        typedef int32_t         ValueType ;  // ValueType defined to int32_t for now, could be switched to something else if needed.

        /// @brief              Default constructor (disabled)

                                Integer                                     ( ) = delete ;

        /// @brief              Constructor
        ///
        /// @code
        ///                     Integer integer(123) ;
        /// @endcode
        ///
        /// @param              [in] anInteger An integer

                                Integer                                     (           Integer::ValueType          anInteger                                   ) ;

        /// @brief              Float constructor (disabled)

                                Integer                                     (           float                                                                   ) = delete ;

        /// @brief              Double constructor (disabled)

                                Integer                                     (           double                                                                  ) = delete ;

        /// @brief              Copy assignment operator
        ///
        /// @param              [in] anInteger An integer
        /// @return             Reference to integer

        Integer&                operator =                                  (           Integer::ValueType          anInteger                                   ) ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Integer(123) == Integer(123) ; // True
        /// @endcode
        ///
        /// @param              [in] anInteger An integer
        /// @return             True if integers are equal

        bool                    operator ==                                 (   const   Integer&                    anInteger                                   ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Integer(123) != Integer(456) ; // True
        /// @endcode
        ///
        /// @param              [in] anInteger An integer
        /// @return             True if integers are not equal

        bool                    operator !=                                 (   const   Integer&                    anInteger                                   ) const ;

        /// @brief              Less than operator
        ///
        /// @code
        ///                     Integer(123) < Integer(456) ; // True
        /// @endcode
        ///
        /// @param              [in] anInteger An integer
        /// @return             True if lhs integer is less than rhs integer

        bool                    operator <                                  (   const   Integer&                    anInteger                                   ) const ;

        /// @brief              Less than or equal to operator
        ///
        /// @code
        ///                     Integer(123) <= Integer(456) ; // True
        /// @endcode
        ///
        /// @param              [in] anInteger An integer
        /// @return             True if lhs integer is less than or equal to rhs integer

        bool                    operator <=                                 (   const   Integer&                    anInteger                                   ) const ;

        /// @brief              Greater than operator
        ///
        /// @code
        ///                     Integer(456) > Integer(123) ; // True
        /// @endcode
        ///
        /// @param              [in] anInteger An integer
        /// @return             True if lhs integer is greater than rhs integer

        bool                    operator >                                  (   const   Integer&                    anInteger                                   ) const ;

        /// @brief              Greater than or equal to operator
        ///
        /// @code
        ///                     Integer(456) >= Integer(123) ; // True
        /// @endcode
        ///
        /// @param              [in] anInteger An integer
        /// @return             True if lhs integer is greater than or equal to rhs integer

        bool                    operator >=                                 (   const   Integer&                    anInteger                                   ) const ;

        /// @brief              Equal to ValueType operator
        ///
        /// @code
        ///                     Integer(123) == 123 ; // True
        /// @endcode
        ///
        /// @param              [in] anInteger An integer (ValueType)
        /// @return             True if integer is equal to ValueType

        bool                    operator ==                                 (   const   Integer::ValueType&         anInteger                                   ) const ;
        bool                    operator !=                                 (   const   Integer::ValueType&         anInteger                                   ) const ;
        bool                    operator <                                  (   const   Integer::ValueType&         anInteger                                   ) const ;
        bool                    operator <=                                 (   const   Integer::ValueType&         anInteger                                   ) const ;
        bool                    operator >                                  (   const   Integer::ValueType&         anInteger                                   ) const ;
        bool                    operator >=                                 (   const   Integer::ValueType&         anInteger                                   ) const ;

        Integer                 operator +                                  (   const   Integer&                    anInteger                                   ) const ;
        Integer                 operator -                                  (   const   Integer&                    anInteger                                   ) const ;
        Integer                 operator *                                  (   const   Integer&                    anInteger                                   ) const ;
        Integer                 operator /                                  (   const   Integer&                    anInteger                                   ) const ;
        Integer                 operator %                                  (   const   Integer&                    anInteger                                   ) const ;

        Integer                 operator +                                  (   const   Integer::ValueType&         anInteger                                   ) const ;
        Integer                 operator -                                  (   const   Integer::ValueType&         anInteger                                   ) const ;
        Integer                 operator *                                  (   const   Integer::ValueType&         anInteger                                   ) const ;
        Integer                 operator /                                  (   const   Integer::ValueType&         anInteger                                   ) const ;
        Integer                 operator %                                  (   const   Integer::ValueType&         anInteger                                   ) const ;

        Real                    operator +                                  (   const   Real&                       aReal                                       ) const ;
        Real                    operator -                                  (   const   Real&                       aReal                                       ) const ;
        Real                    operator *                                  (   const   Real&                       aReal                                       ) const ;
        Real                    operator /                                  (   const   Real&                       aReal                                       ) const ;

        Integer&                operator +=                                 (   const   Integer&                    anInteger                                   ) ;
        Integer&                operator -=                                 (   const   Integer&                    anInteger                                   ) ;
        Integer&                operator *=                                 (   const   Integer&                    anInteger                                   ) ;
        Integer&                operator /=                                 (   const   Integer&                    anInteger                                   ) ;
        Integer&                operator %=                                 (   const   Integer&                    anInteger                                   ) ;

        Integer&                operator +=                                 (   const   Integer::ValueType&         anInteger                                   ) ;
        Integer&                operator -=                                 (   const   Integer::ValueType&         anInteger                                   ) ;
        Integer&                operator *=                                 (   const   Integer::ValueType&         anInteger                                   ) ;
        Integer&                operator /=                                 (   const   Integer::ValueType&         anInteger                                   ) ;
        Integer&                operator %=                                 (   const   Integer::ValueType&         anInteger                                   ) ;

        friend Integer          operator +                                  (   const   Integer::ValueType&         anInt,
                                                                                const   Integer&                    anInteger                                   ) ;
        friend Integer          operator -                                  (   const   Integer::ValueType&         anInt,
                                                                                const   Integer&                    anInteger                                   ) ;
        friend Integer          operator *                                  (   const   Integer::ValueType&         anInt,
                                                                                const   Integer&                    anInteger                                   ) ;
        friend Integer          operator /                                  (   const   Integer::ValueType&         anInt,
                                                                                const   Integer&                    anInteger                                   ) ;
        friend Integer          operator %                                  (   const   Integer::ValueType&         anInt,
                                                                                const   Integer&                    anInteger                                   ) ;

        Integer                 operator +                                  ( ) const ;
        Integer                 operator -                                  ( ) const ;

        Integer&                operator ++                                 ( ) ;
        Integer&                operator --                                 ( ) ;

        Integer                 operator ++                                 (           int                         anInteger                                   ) ;
        Integer                 operator --                                 (           int                         anInteger                                   ) ;

                                operator Integer::ValueType                 ( ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Integer&                    anInteger                                   ) ;

        bool                    isDefined                                   ( ) const ;
        bool                    isZero                                      ( ) const ;
        bool                    isPositive                                  ( ) const ;
        bool                    isNegative                                  ( ) const ;
        bool                    isStrictlyPositive                          ( ) const ;
        bool                    isStrictlyNegative                          ( ) const ;
        bool                    isInfinity                                  ( ) const ;
        bool                    isPositiveInfinity                          ( ) const ;
        bool                    isNegativeInfinity                          ( ) const ;

        bool                    isFinite                                    ( ) const ;
        bool                    isEven                                      ( ) const ;
        bool                    isOdd                                       ( ) const ;

        types::Sign             getSign                                     ( ) const ;

        types::String           toString                                    ( ) const ;

        Integer::ValueType      toInt                                       ( ) const ;

        static Integer          Undefined                                   ( ) ;

        static Integer          Zero                                        ( ) ;

        static Integer          PositiveInfinity                            ( ) ;

        static Integer          NegativeInfinity                            ( ) ;

        static Integer          Int8                                        (           types::Int8                 anInteger                                   ) ;

        static Integer          Int16                                       (           types::Int16                anInteger                                   ) ;

        static Integer          Int32                                       (           types::Int32                anInteger                                   ) ;

        static Integer          Int64                                       (           types::Int64                anInteger                                   ) ;

        static Integer          Uint8                                       (           types::Uint8                anInteger                                   ) ;

        static Integer          Uint16                                      (           types::Uint16               anInteger                                   ) ;

        static Integer          Uint32                                      (           types::Uint32               anInteger                                   ) ;

        static Integer          Uint64                                      (           types::Uint64               anInteger                                   ) ;

        static Integer          Index                                       (   const   types::Index&               anIndex                                     ) ;

        static Integer          Size                                        (   const   types::Size&                aSize                                       ) ;

        static bool             CanParse                                    (           char                        aCharacter                                  ) ;

        static bool             CanParse                                    (   const   types::String&              aString                                     ) ;

        static Integer          Parse                                       (           char                        aCharacter                                  ) ;

        static Integer          Parse                                       (   const   types::String&              aString                                     ) ;

    private:

        enum class Type
        {

            Undefined,
            Defined,
            PositiveInfinity,
            NegativeInfinity

        } ;

        Integer::Type           type_ ;
        Integer::ValueType      value_ ;

                                Integer                                     (   const   Integer::Type&              aType,
                                                                                const   Integer::ValueType&         anInteger                                   ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
