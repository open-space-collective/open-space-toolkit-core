////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/Types/Integer.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Core_Types_Integer__
#define __Library_Core_Types_Integer__

#include <Library/Core/Types/Sign.hpp>
#include <Library/Core/Types/String.hpp>

#include <ostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace types
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Integer number

class Integer
{

    public:

        typedef int32_t         ValueType ;

                                Integer                                     ( ) = delete ;

                                Integer                                     (           Integer::ValueType          anInteger                                   ) ;
                                
                                Integer                                     (           float                                                                   ) = delete ;
                                Integer                                     (           double                                                                  ) = delete ;

        Integer&                operator =                                  (           Integer::ValueType          anInteger                                   ) ;

        bool                    operator ==                                 (   const   Integer&                    anInteger                                   ) const ;
        bool                    operator !=                                 (   const   Integer&                    anInteger                                   ) const ;
        bool                    operator <                                  (   const   Integer&                    anInteger                                   ) const ;
        bool                    operator <=                                 (   const   Integer&                    anInteger                                   ) const ;
        bool                    operator >                                  (   const   Integer&                    anInteger                                   ) const ;
        bool                    operator >=                                 (   const   Integer&                    anInteger                                   ) const ;

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

        types::String           getString                                   ( ) const ;

        static Integer          Undefined                                   ( ) ;

        static Integer          Zero                                        ( ) ;

        static Integer          PositiveInfinity                            ( ) ;

        static Integer          NegativeInfinity                            ( ) ;

        static Integer          String                                      (   const   types::String&              aString                                     ) ;

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