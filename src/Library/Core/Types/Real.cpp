////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/Types/Real.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Error.hpp>

#include <boost/lexical_cast.hpp>

#include <limits>
#include <iomanip>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace types
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Real::Real                                  (           Real::ValueType             aReal                                       )
                                :   type_(Real::Type::Defined),
                                    value_(aReal)
{

}

Real&                           Real::operator =                            (           Real::ValueType             aReal                                       )
{

    type_ = Real::Type::Defined ;
    value_ = aReal ;

    return (*this) ;

}

bool                            Real::operator ==                           (   const   Real&                       aReal                                       ) const
{
    return (type_ == Real::Type::Defined) && (aReal.type_ == Real::Type::Defined) && (value_ == aReal.value_) ;
}

bool                            Real::operator !=                           (   const   Real&                       aReal                                       ) const
{
    return (type_ == Real::Type::Defined) && (aReal.type_ == Real::Type::Defined) && (value_ != aReal.value_) ;
}

bool                            Real::operator <                            (   const   Real&                       aReal                                       ) const
{
    return (type_ == Real::Type::Defined) && (aReal.type_ == Real::Type::Defined) && (value_ < aReal.value_) ;
}

bool                            Real::operator <=                           (   const   Real&                       aReal                                       ) const
{
    return (type_ == Real::Type::Defined) && (aReal.type_ == Real::Type::Defined) && (value_ <= aReal.value_) ;
}

bool                            Real::operator >                            (   const   Real&                       aReal                                       ) const
{
    return (type_ == Real::Type::Defined) && (aReal.type_ == Real::Type::Defined) && (value_ > aReal.value_) ;
}

bool                            Real::operator >=                           (   const   Real&                       aReal                                       ) const
{
    return (type_ == Real::Type::Defined) && (aReal.type_ == Real::Type::Defined) && (value_ >= aReal.value_) ;
}

bool                            Real::operator ==                           (   const   Real::ValueType&            aReal                                       ) const
{
    return (type_ == Real::Type::Defined) && (value_ == aReal) ;
}

bool                            Real::operator !=                           (   const   Real::ValueType&            aReal                                       ) const
{
    return (type_ == Real::Type::Defined) && (value_ != aReal) ;
}

bool                            Real::operator <                            (   const   Real::ValueType&            aReal                                       ) const
{
    return (type_ == Real::Type::Defined) && (value_ < aReal) ;
}

bool                            Real::operator <=                           (   const   Real::ValueType&            aReal                                       ) const
{
    return (type_ == Real::Type::Defined) && (value_ <= aReal) ;
}

bool                            Real::operator >                            (   const   Real::ValueType&            aReal                                       ) const
{
    return (type_ == Real::Type::Defined) && (value_ > aReal) ;
}

bool                            Real::operator >=                           (   const   Real::ValueType&            aReal                                       ) const
{
    return (type_ == Real::Type::Defined) && (value_ >= aReal) ;
}

Real                            Real::operator +                            (   const   Real&                       aReal                                       ) const
{

    if ((type_ != Real::Type::Undefined) && (aReal.type_ != Real::Type::Undefined))
    {

        if ((type_ == Real::Type::PositiveInfinity) && (aReal.type_ == Real::Type::PositiveInfinity))
        {
            return Real::PositiveInfinity() ;
        }
        else if ((type_ == Real::Type::NegativeInfinity) && (aReal.type_ == Real::Type::NegativeInfinity))
        {
            return Real::NegativeInfinity() ;
        }
        else if ((type_ == Real::Type::Defined) || (aReal.type_ == Real::Type::Defined))
        {

            if (type_ != Real::Type::Defined)
            {
                return (*this) ;
            }
            else if (aReal.type_ != Real::Type::Defined)
            {
                return aReal ;
            }

            // [TBC] Use __builtin_add_overflow instead?

            if ((aReal.value_ > 0.0) && (value_ >= (std::numeric_limits<Real::ValueType>::max() - aReal.value_))) // Addition would overflow
            {
                return (value_ != 0.0) ? Real::PositiveInfinity() : aReal ;
            }

            if ((aReal.value_ < 0.0) && (value_ <= (std::numeric_limits<Real::ValueType>::lowest() - aReal.value_))) // Addition would underflow
            {
                return (value_ != 0.0) ? Real::NegativeInfinity() : aReal ;
            }

            return Real(value_ + aReal.value_) ;

        }

    }

    return Real::Undefined() ;

}

Real                            Real::operator -                            (   const   Real&                       aReal                                       ) const
{

    if ((type_ != Real::Type::Undefined) && (aReal.type_ != Real::Type::Undefined))
    {

        if ((type_ == Real::Type::PositiveInfinity) && (aReal.type_ == Real::Type::NegativeInfinity))
        {
            return Real::PositiveInfinity() ;
        }
        else if ((type_ == Real::Type::NegativeInfinity) && (aReal.type_ == Real::Type::PositiveInfinity))
        {
            return Real::NegativeInfinity() ;
        }
        else if ((type_ == Real::Type::Defined) || (aReal.type_ == Real::Type::Defined))
        {

            if (type_ != Real::Type::Defined)
            {
                return (*this) ;
            }
            else if (aReal.type_ != Real::Type::Defined)
            {

                if (aReal.type_ == Real::Type::PositiveInfinity)
                {
                    return Real::NegativeInfinity() ;
                }

                return Real::PositiveInfinity() ;

            }

            if ((aReal.value_ < 0.0) && (value_ >= (std::numeric_limits<Real::ValueType>::max() + aReal.value_))) // Subtraction would overflow
            {
                return (value_ != 0.0) ? Real::PositiveInfinity() : -aReal ;
            }

            if ((aReal.value_ > 0.0) && (value_ <= (std::numeric_limits<Real::ValueType>::lowest() + aReal.value_))) // Subtraction would underflow
            {
                return (value_ != 0.0) ? Real::NegativeInfinity() : -aReal ;
            }

            return Real(value_ - aReal.value_) ;

        }

    }

    return Real::Undefined() ;

}

Real                            Real::operator *                            (   const   Real&                       aReal                                       ) const
{

    if ((type_ != Real::Type::Undefined) && (aReal.type_ != Real::Type::Undefined))
    {

        if (type_ == Real::Type::PositiveInfinity)
        {

            if (aReal.isStrictlyPositive())
            {
                return Real::PositiveInfinity() ;
            }
            else if (aReal.isStrictlyNegative())
            {
                return Real::NegativeInfinity() ;
            }
            
            return Real::Undefined() ;

        }
        else if (type_ == Real::Type::NegativeInfinity)
        {
            
            if (aReal.isStrictlyPositive())
            {
                return Real::NegativeInfinity() ;
            }
            else if (aReal.isStrictlyNegative())
            {
                return Real::PositiveInfinity() ;
            }
            
            return Real::Undefined() ;

        }
        else if (aReal.type_ == Real::Type::PositiveInfinity)
        {
            
            if (this->isStrictlyPositive())
            {
                return Real::PositiveInfinity() ;
            }
            else if (this->isStrictlyNegative())
            {
                return Real::NegativeInfinity() ;
            }
            
            return Real::Undefined() ;
            
        }
        else if (aReal.type_ == Real::Type::NegativeInfinity)
        {
            
            if (this->isStrictlyPositive())
            {
                return Real::NegativeInfinity() ;
            }
            else if (this->isStrictlyNegative())
            {
                return Real::PositiveInfinity() ;
            }
            
            return Real::Undefined() ;

        }
        else
        {

            if (this->isZero() || aReal.isZero())
            {
                return Real::Zero() ;
            }
            
            // Check for -1 for two's complement machines
            
            if ((value_ < 0.0) && (aReal.value_ == std::numeric_limits<Real::ValueType>::lowest())) // Multiplication can overflow
            {
                return Real::PositiveInfinity() ;
            }
            
            if ((aReal.value_ < 0.0) && (value_ == std::numeric_limits<Real::ValueType>::lowest())) // Multiplication can overflow
            {
                return Real::PositiveInfinity() ;
            }
            
            if ((this->getSign() == aReal.getSign()) && (std::abs(value_) > (std::numeric_limits<Real::ValueType>::max() / std::abs(aReal.value_)))) // Multiplication would overflow
            {
                return Real::PositiveInfinity() ;
            }

            if ((value_ == +1) && (aReal.value_ == std::numeric_limits<Real::ValueType>::lowest()))
            {
                return Real(std::numeric_limits<Real::ValueType>::lowest()) ;
            }

            if ((value_ == -1) && (aReal.value_ == std::numeric_limits<Real::ValueType>::lowest()))
            {
                return Real::PositiveInfinity() ;
            }
            
            if ((aReal.value_ != -1) && (this->getSign() != aReal.getSign()) && ((-std::abs(value_)) < (std::numeric_limits<Real::ValueType>::lowest() / std::abs(aReal.value_)))) // Multiplication would underflow
            {
                return Real::NegativeInfinity() ;
            }
            
            return Real(value_ * aReal.value_) ;

        }

    }

    return Real::Undefined() ;

}

Real                            Real::operator /                            (   const   Real&                       aReal                                       ) const
{

    if (aReal.isZero())
    {
        return Real::Undefined() ;
    }

    if ((type_ != Real::Type::Undefined) && (aReal.type_ != Real::Type::Undefined))
    {

        if (type_ == Real::Type::PositiveInfinity)
        {

            if (aReal.isInfinity())
            {
                return Real::Undefined() ;
            }
            else if (aReal.isStrictlyPositive())
            {
                return Real::PositiveInfinity() ;
            }
            else if (aReal.isStrictlyNegative())
            {
                return Real::NegativeInfinity() ;
            }
            
            return Real::Undefined() ;

        }
        else if (type_ == Real::Type::NegativeInfinity)
        {
            
            if (aReal.isInfinity())
            {
                return Real::Undefined() ;
            }
            else if (aReal.isStrictlyPositive())
            {
                return Real::NegativeInfinity() ;
            }
            else if (aReal.isStrictlyNegative())
            {
                return Real::PositiveInfinity() ;
            }
            
            return Real::Undefined() ;

        }
        else
        {

            if (this->isZero() || aReal.isInfinity())
            {
                return Real::Zero() ;
            }
            else
            {

                if ((value_ == std::numeric_limits<Real::ValueType>::lowest()) && (aReal.value_ == -1))
                {
                    return Real::PositiveInfinity() ;
                }
                
                return Real(value_ / aReal.value_) ;

            }

        }

    }

    return Real::Undefined() ;

}

Real                            Real::operator +                            (   const   Real::ValueType&            aReal                                       ) const
{
    return (*this) + Real(aReal) ;
}

Real                            Real::operator -                            (   const   Real::ValueType&            aReal                                       ) const
{
    return (*this) - Real(aReal) ;
}

Real                            Real::operator *                            (   const   Real::ValueType&            aReal                                       ) const
{
    return (*this) * Real(aReal) ;
}

Real                            Real::operator /                            (   const   Real::ValueType&            aReal                                       ) const
{
    return (*this) / Real(aReal) ;
}

Real&                           Real::operator +=                           (   const   Real&                       aReal                                       )
{

    (*this) = (*this) + aReal ;

    return (*this) ;

}

Real&                           Real::operator -=                           (   const   Real&                       aReal                                       )
    {

    (*this) = (*this) - aReal ;

    return (*this) ;

}

Real&                           Real::operator *=                           (   const   Real&                       aReal                                       )
    {

    (*this) = (*this) * aReal ;

    return (*this) ;

}

Real&                           Real::operator /=                           (   const   Real&                       aReal                                       )
    {

    (*this) = (*this) / aReal ;

    return (*this) ;

}

Real&                           Real::operator +=                           (   const   Real::ValueType&            aReal                                       )
{

    (*this) = (*this) + Real(aReal) ;

    return (*this) ;

}

Real&                           Real::operator -=                           (   const   Real::ValueType&            aReal                                       )
{

    (*this) = (*this) - Real(aReal) ;

    return (*this) ;

}

Real&                           Real::operator *=                           (   const   Real::ValueType&            aReal                                       )
{

    (*this) = (*this) * Real(aReal) ;

    return (*this) ;

}

Real&                           Real::operator /=                           (   const   Real::ValueType&            aReal                                       )
{

    (*this) = (*this) / Real(aReal) ;

    return (*this) ;

}

Real                            operator +                                  (   const   Real::ValueType&            anInt,
                                                                                const   Real&                       aReal                                       )
{
    return Real(anInt) + aReal ;
}

Real                            operator -                                  (   const   Real::ValueType&            anInt,
                                                                                const   Real&                       aReal                                       )
{
    return Real(anInt) - aReal ;
}

Real                            operator *                                  (   const   Real::ValueType&            anInt,
                                                                                const   Real&                       aReal                                       )
{
    return Real(anInt) * aReal ;
}

Real                            operator /                                  (   const   Real::ValueType&            anInt,
                                                                                const   Real&                       aReal                                       )
{
    return Real(anInt) / aReal ;
}

Real                            Real::operator +                            ( ) const
{
    return (*this) ;
}

Real                            Real::operator -                            ( ) const
{
    
    switch (type_)
    {
    
        case Real::Type::Defined:
        {

            if (value_ == std::numeric_limits<Real::ValueType>::lowest())
            {
                return Real::PositiveInfinity() ;
            }
            
            return Real(-value_) ;

        }

        case Real::Type::Undefined:
            return Real::Undefined() ;

        case Real::Type::PositiveInfinity:
            return Real::NegativeInfinity() ;
        
        case Real::Type::NegativeInfinity:
            return Real::PositiveInfinity() ;
        
        default:
            break ;

    }

    return Real::Undefined() ;

}

                                Real::operator Real::ValueType        ( ) const
{

    if (type_ != Real::Type::Defined)
    {
        throw library::core::error::runtime::Undefined("Real") ;
    }
    
    return value_ ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Real&                       aReal                                       )
{

    (void) aReal ;

    switch (aReal.type_)
    {

        case Real::Type::Undefined:
            anOutputStream << "Undefined" ;
            break ;

        case Real::Type::Defined:
            anOutputStream << aReal.value_ ;
            break ;

        case Real::Type::PositiveInfinity:
            anOutputStream << "+Inf" ;
            break ;

        case Real::Type::NegativeInfinity:
            anOutputStream << "-Inf" ;
            break ;

    }

    // library::core::utilities::Output::Header(anOutputStream, "Real") ;

    // library::core::utilities::Output::Line(anOutputStream) << "Type:" << aReal.type_ ;
    // library::core::utilities::Output::Line(anOutputStream) << "Value:" << aReal.value_ ;

    // library::core::utilities::Output::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Real::isDefined                             ( ) const
{
    return type_ != Real::Type::Undefined ;
}

bool                            Real::isZero                                ( ) const
{
    return (type_ == Real::Type::Defined) && (value_ == 0.0) ;
}

bool                            Real::isPositive                            ( ) const
{
    return ((type_ == Real::Type::Defined) && (value_ >= 0.0)) || this->isPositiveInfinity() ;
}

bool                            Real::isNegative                            ( ) const
{
    return ((type_ == Real::Type::Defined) && (value_ <= 0.0)) || this->isNegativeInfinity() ;
}

bool                            Real::isStrictlyPositive                    ( ) const
{
    return ((type_ == Real::Type::Defined) && (value_ > 0.0)) || this->isPositiveInfinity() ;
}

bool                            Real::isStrictlyNegative                    ( ) const
{
    return ((type_ == Real::Type::Defined) && (value_ < 0.0)) || this->isNegativeInfinity() ;
}

bool                            Real::isInfinity                            ( ) const
{
    return this->isPositiveInfinity() || this->isNegativeInfinity() ;
}

bool                            Real::isPositiveInfinity                    ( ) const
{
    return type_ == Real::Type::PositiveInfinity ;
}

bool                            Real::isNegativeInfinity                    ( ) const
{
    return type_ == Real::Type::NegativeInfinity ;
}

bool                            Real::isInteger                             ( ) const
{

    if (this->isFinite())
    {
        
        double intpart ;
    
        return std::modf(value_, &intpart) == 0.0 ;

    }

    return false ;

}

bool                            Real::isFinite                              ( ) const
{
    return type_ == Real::Type::Defined ;
}

types::Sign                     Real::getSign                               ( ) const
{

    switch (type_)
    {

        case Real::Type::Undefined:
            return types::Sign::Undefined ;

        case Real::Type::Defined:
        {

            if (value_ > 0.0)
            {
                return types::Sign::Positive ;
            }
            else if (value_ < 0.0)
            {
                return types::Sign::Negative ;
            }
            
            return types::Sign::None ;

        }

        case Real::Type::PositiveInfinity:
            return types::Sign::Positive ;

        case Real::Type::NegativeInfinity:
            return types::Sign::Negative ;

        default:
           return types::Sign::Undefined ; 

    }

    return types::Sign::Undefined ;

}

types::String                   Real::toString                             ( ) const
{

    switch (type_)
    {

        case Real::Type::Undefined:
            return "Undefined" ;

        case Real::Type::Defined:
        {

            if (this->isInteger())
            {
                return boost::lexical_cast<std::string>(value_) + ".0" ;
            }

            std::ostringstream stringStream ;

            // stringStream << std::fixed << std::setprecision(2) ;

            stringStream << value_ ;

            return stringStream.str() ;

            // return boost::lexical_cast<std::string>(value_) ;

        }

        case Real::Type::PositiveInfinity:
            return "+Inf" ;

        case Real::Type::NegativeInfinity:
            return "-Inf" ;

    }

    return types::String::Empty() ;

}

types::Integer                  Real::toInteger                         ( ) const
{

    if (this->isInteger())
    {
        return types::Integer(static_cast<types::Integer::ValueType>(value_)) ;
    }

    throw library::core::error::RuntimeError("Real is not integer.") ;

    return types::Integer::Undefined() ;

}

Real                            Real::abs                                   ( ) const
{

    switch (type_)
    {

        case Real::Type::Undefined:
            return Real::Undefined() ;

        case Real::Type::Defined:
            return Real(Real::Type::Defined, std::abs(value_)) ;

        case Real::Type::PositiveInfinity:
        case Real::Type::NegativeInfinity:
            return Real::PositiveInfinity() ;

        default:
            throw library::core::error::runtime::Undefined("Type") ;
            break ;

    }

    return Real::Undefined() ;

}

Real                            Real::sqrt                                  ( ) const
{

    switch (type_)
    {

        case Real::Type::Undefined:
            return Real::Undefined() ;

        case Real::Type::Defined:
        {

            if (this->isStrictlyNegative())
            {
                return Real::Undefined() ;
            }

            return Real(Real::Type::Defined, std::sqrt(value_)) ;

        } 

        case Real::Type::PositiveInfinity:
            return Real::PositiveInfinity() ;

        case Real::Type::NegativeInfinity:
            return Real::Undefined() ;

        default:
            throw library::core::error::runtime::Undefined("Type") ;
            break ;

    }

    return Real::Undefined() ;

}

Real                            Real::Undefined                             ( )
{
    return Real(Real::Type::Undefined, 0.0) ;
}

Real                            Real::Zero                                  ( )
{
    return Real(Real::Type::Defined, 0.0) ;
}

Real                            Real::Pi                                    ( )
{
    return Real(Real::Type::Defined, M_PI) ;
}

Real                            Real::HalfPi                                ( )
{
    return Real(Real::Type::Defined, M_PI / 2.0) ;
}

Real                            Real::TwoPi                                 ( )
{
    return Real(Real::Type::Defined, 2.0 * M_PI) ;
}

Real                            Real::Epsilon                               ( )
{
    return Real(Real::Type::Defined, 1e-15) ;
}

Real                            Real::PositiveInfinity                      ( )
{
    return Real(Real::Type::PositiveInfinity, std::numeric_limits<Real::ValueType>::max()) ;
}

Real                            Real::NegativeInfinity                      ( )
{
    return Real(Real::Type::NegativeInfinity, std::numeric_limits<Real::ValueType>::lowest()) ;
}

Real                            Real::Integer                               (   const   types::Integer&             anInteger                                   )
{

    if (anInteger.isDefined())
    {
        return Real(Real::Type::Defined, anInteger) ;
    }
    
    return Real::Undefined() ;

}

Real                            Real::Parse                                 (   const   types::String&              aString                                     )
{

    if (aString.isEmpty() || (aString == "Undefined"))
    {
        return Real::Undefined() ;
    }

    if ((aString == "Inf") || (aString == "+Inf"))
    {
        return Real::PositiveInfinity() ;
    }

    if (aString == "-Inf")
    {
        return Real::NegativeInfinity() ;
    }

    try
    {
        return Real(boost::lexical_cast<Real::ValueType>(aString)) ;
    }
    catch (const boost::bad_lexical_cast&)
    {
        throw library::core::error::RuntimeError("Cannot cast string [" + aString + "] to Real.") ;
    }

    return Real::Undefined() ;
    
}

// Real                             Real::Object                             (   const   ctnr::Object&               anObject                                   )
// {
    
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Real::Real                                  (   const   Real::Type&                 aType,
                                                                                const   Real::ValueType&            aReal                                       )
                                :   type_(aType),
                                    value_(aReal)
{
    
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////