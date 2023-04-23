////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/julia/src/OpenSpaceToolkitCorePy.cxx
/// @author         Remy Derollez <remy@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #include <OpenSpaceToolkitCorePy/FileSystem.cpp>
// #include <OpenSpaceToolkitCorePy/Containers.cpp>
// #include <OpenSpaceToolkitCorePy/Types.cpp>

#include "jlcxx/jlcxx.hpp"
#include "jlcxx/functions.hpp"

#include <OpenSpaceToolkit/Core/Types/Sign.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// https://github.com/JuliaInterop/CxxWrap.jl

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::String ;
using ostk::core::types::Sign ;
using ostk::core::types::Integer ;
using ostk::core::types::Real ;

// Case and naming conventions to be used
// https://docs.julialang.org/en/v1/manual/style-guide/#Use-naming-conventions-consistent-with-Julia-base/

// C++ code defining classes
struct World
{
  World(const std::string& message = "default hello") : msg(message){}
  void set(const std::string& msge) { this->msg = msge; }
  std::string greet() { return msg; }
  std::string msg;
  ~World() { std::cout << "Destroying World with message " << msg << std::endl; }
};

// https://github.com/JuliaInterop/CxxWrap.jl/issues/271
namespace jlcxx
{
  // template<> struct IsMirroredType<Sign> : std::false_type { };
  template<> struct IsMirroredType<String> : std::false_type { } ;
  template<> struct IsMirroredType<Integer> : std::false_type { } ;
  template<> struct IsMirroredType<Real> : std::false_type { } ;
}

// Seems to be needed to mirror types directly without exposing the Integer type
// template<> struct IsMirroredType<Integer> : std::false_type { };

// C++ code to expose classes and their members to Julia in a Module
JLCXX_MODULE OpenSpaceToolkitCore(jlcxx::Module& Core)
{

  // Dummy Example for World
  Core.add_type<World>("World")
    .constructor<const std::string&>()
    .method("set", &World::set)
    .method("greet", &World::greet);

  // Sign
  Core.add_bits<Sign>("Sign", jlcxx::julia_type("CppEnum")) ;

  // String
  Core.add_type<String>("String")

    .constructor<std::string>()

    .method("is_empty", &String::isEmpty)
    .method("is_uppercase", &String::isUppercase)
    .method("is_lowercase", &String::isLowercase)
    // .method("match", &String::match)

    .method("get_length", &String::getLength)
    .method("get_first", &String::getFirst)
    .method("get_last", &String::getLast)
    .method("get_head", &String::getHead)
    .method("get_tail", &String::getTail)
    .method("get_substring", &String::getSubstring) ;

  // Integer
  Core.add_type<Integer>("Integer")

    // add constructor
    .constructor<int>()

    // add operators/comparators (cpp function not recognized)
    // .method("==", &Integer::operator==)
    // .method("!=", &Integer::operator!=)
    // .method("<", &Integer::operator<)
    // .method("<=", &Integer::operator<=)
    // .method(">", &Integer::operator>)
    // .method(">=", &Integer::operator>=)

    // .method("+", &Integer::operator+)
    // .method("+=", &Integer::operator+=)
    // .method("-", &Integer::operator-)
    // .method("-=", &Integer::operator-=)
    // .method("*", &Integer::operator*)
    // .method("*=", &Integer::operator*=)
    // .method("/", &Integer::operator/)
    // .method("/=", &Integer::operator/=)

    // add regular methods
    .method("is_defined", &Integer::isDefined)
    .method("is_zero", &Integer::isZero)
    .method("is_positive", &Integer::isPositive)
    .method("is_negative", &Integer::isNegative)
    .method("is_strictly_positive", &Integer::isStrictlyPositive)
    .method("is_strictly_negative", &Integer::isStrictlyNegative)
    .method("is_infinity", &Integer::isInfinity)
    .method("is_positive_infinity", &Integer::isPositiveInfinity)
    .method("is_negative_infinity", &Integer::isNegativeInfinity)
    .method("is_finite", &Integer::isFinite)
    .method("is_even", &Integer::isEven)
    .method("is_odd", &Integer::isOdd)
    .method("get_sign", &Integer::getSign)
    .method("to_string", &Integer::toString) ;

    // add static methods

  // Real
  Core.add_type<Real>("Real")

    .method("is_defined", &Real::isDefined)
    .method("is_zero", &Real::isZero)
    .method("is_positive", &Real::isPositive)
    .method("is_negative", &Real::isNegative)
    .method("is_strictly_positive", &Real::isStrictlyPositive)
    .method("is_strictly_negative", &Real::isStrictlyNegative)
    .method("is_infinity", &Real::isInfinity)
    .method("is_positive_infinity", &Real::isPositiveInfinity)
    .method("is_negative_infinity", &Real::isNegativeInfinity)
    .method("is_integer", &Real::isInteger)
    .method("is_finite", &Real::isFinite)
    .method("is_near", &Real::isNear)

    .method("get_sign", &Real::getSign)
    .method("to_integer", &Real::toInteger)
    .method("abs", &Real::abs)
    .method("floor", &Real::floor)
    .method("sqrt", &Real::sqrt) ;

  // Adding submodules to main module core [TBR]

  // OpenSpaceToolkitCoreJl_Types(Core) ;
  // OpenSpaceToolkitCoreJl_Containers(Core) ;
  // OpenSpaceToolkitCoreJl_FileSystem(Core) ;

}

// BOOST_PYTHON_MODULE (OpenSpaceToolkitCorePy)
// {

//     boost::python::object package = boost::python::scope() ;

//     package.attr("__path__") = "ostk" ;

//     OpenSpaceToolkitCorePy_Types() ;
//     OpenSpaceToolkitCorePy_Containers() ;
//     OpenSpaceToolkitCorePy_FileSystem() ;

// }

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
