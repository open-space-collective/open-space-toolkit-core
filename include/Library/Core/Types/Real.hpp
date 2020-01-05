////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           Library/Core/Types/Real.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Core_Types_Real__
#define __OpenSpaceToolkit_Core_Types_Real__

#include <Library/Core/Types/Sign.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Integer.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace types
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Real type

class Real
{

    public:

        typedef double          ValueType ;

                                Real                                        ( ) = delete ;

                                Real                                        (           Real::ValueType             aReal                                       ) ;

        Real&                   operator =                                  (           Real::ValueType             aReal                                       ) ;

        bool                    operator ==                                 (   const   Real&                       aReal                                       ) const ;
        bool                    operator !=                                 (   const   Real&                       aReal                                       ) const ;
        bool                    operator <                                  (   const   Real&                       aReal                                       ) const ;
        bool                    operator <=                                 (   const   Real&                       aReal                                       ) const ;
        bool                    operator >                                  (   const   Real&                       aReal                                       ) const ;
        bool                    operator >=                                 (   const   Real&                       aReal                                       ) const ;

        bool                    operator ==                                 (   const   Real::ValueType&            aReal                                       ) const ;
        bool                    operator !=                                 (   const   Real::ValueType&            aReal                                       ) const ;
        bool                    operator <                                  (   const   Real::ValueType&            aReal                                       ) const ;
        bool                    operator <=                                 (   const   Real::ValueType&            aReal                                       ) const ;
        bool                    operator >                                  (   const   Real::ValueType&            aReal                                       ) const ;
        bool                    operator >=                                 (   const   Real::ValueType&            aReal                                       ) const ;

        Real                    operator +                                  (   const   Real&                       aReal                                       ) const ;
        Real                    operator -                                  (   const   Real&                       aReal                                       ) const ;
        Real                    operator *                                  (   const   Real&                       aReal                                       ) const ;
        Real                    operator /                                  (   const   Real&                       aReal                                       ) const ;

        Real                    operator +                                  (   const   Real::ValueType&            aReal                                       ) const ;
        Real                    operator -                                  (   const   Real::ValueType&            aReal                                       ) const ;
        Real                    operator *                                  (   const   Real::ValueType&            aReal                                       ) const ;
        Real                    operator /                                  (   const   Real::ValueType&            aReal                                       ) const ;

        Real                    operator +                                  (   const   Integer&                    anInteger                                   ) const ;
        Real                    operator -                                  (   const   Integer&                    anInteger                                   ) const ;
        Real                    operator *                                  (   const   Integer&                    anInteger                                   ) const ;
        Real                    operator /                                  (   const   Integer&                    anInteger                                   ) const ;

        Real&                   operator +=                                 (   const   Real&                       aReal                                       ) ;
        Real&                   operator -=                                 (   const   Real&                       aReal                                       ) ;
        Real&                   operator *=                                 (   const   Real&                       aReal                                       ) ;
        Real&                   operator /=                                 (   const   Real&                       aReal                                       ) ;

        Real&                   operator +=                                 (   const   Real::ValueType&            aReal                                       ) ;
        Real&                   operator -=                                 (   const   Real::ValueType&            aReal                                       ) ;
        Real&                   operator *=                                 (   const   Real::ValueType&            aReal                                       ) ;
        Real&                   operator /=                                 (   const   Real::ValueType&            aReal                                       ) ;

        friend Real             operator +                                  (   const    Real::ValueType&           aDouble,
                                                                                const    Real&                      aReal                                       ) ;
        friend Real             operator -                                  (   const    Real::ValueType&           aDouble,
                                                                                const    Real&                      aReal                                       ) ;
        friend Real             operator *                                  (   const    Real::ValueType&           aDouble,
                                                                                const    Real&                      aReal                                       ) ;
        friend Real             operator /                                  (   const    Real::ValueType&           aDouble,
                                                                                const    Real&                      aReal                                       ) ;

        Real                    operator +                                  ( ) const ;
        Real                    operator -                                  ( ) const ;

                                operator Real::ValueType                    ( ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Real&                       aReal                                       ) ;

        bool                    isDefined                                   ( ) const ;
        bool                    isZero                                      ( ) const ;
        bool                    isPositive                                  ( ) const ;
        bool                    isNegative                                  ( ) const ;
        bool                    isStrictlyPositive                          ( ) const ;
        bool                    isStrictlyNegative                          ( ) const ;
        bool                    isInfinity                                  ( ) const ;
        bool                    isPositiveInfinity                          ( ) const ;
        bool                    isNegativeInfinity                          ( ) const ;

        bool                    isInteger                                   ( ) const ;
        bool                    isFinite                                    ( ) const ;

        bool                    isNear                                      (   const   Real&                       aValue,
                                                                                const   Real&                       aTolerance                                  =   Real::Epsilon() ) const ;

        types::Sign             getSign                                     ( ) const ;

        types::String           toString                                    (   const   types::Integer&             aPrecision                                  =   types::Integer::Undefined() ) const ;

        types::Integer          toInteger                                   ( ) const ;

        Real                    abs                                         ( ) const ;

        types::Integer          floor                                       ( ) const ;

        Real                    sqrt                                        ( ) const ;

        static Real             Undefined                                   ( ) ;

        static Real             Zero                                        ( ) ;

        static Real             Pi                                          ( ) ;

        static Real             HalfPi                                      ( ) ;

        static Real             TwoPi                                       ( ) ;

        static Real             Epsilon                                     ( ) ;

        static Real             PositiveInfinity                            ( ) ;

        static Real             NegativeInfinity                            ( ) ;

        static Real             Integer                                     (   const   types::Integer&             anInteger                                   ) ;

        static Real             CanParse                                    (   const   types::String&              aString                                     ) ;

        static Real             Parse                                       (   const   types::String&              aString                                     ) ;

    private:

        enum class Type
        {

            Undefined,
            Defined,
            PositiveInfinity,
            NegativeInfinity

        } ;

        Real::Type              type_ ;
        Real::ValueType         value_ ;

                                Real                                        (   const   Real::Type&                 aType,
                                                                                const   Real::ValueType&            aReal                                       ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
