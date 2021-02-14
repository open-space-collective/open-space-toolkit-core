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

#include <OpenSpaceToolkit/Core/Types/Integer.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Integer ;

// C++ code defining classes
struct World
{
  World(const std::string& message = "default hello") : msg(message){}
  void set(const std::string& msge) { this->msg = msge; }
  std::string greet() { return msg; }
  std::string msg;
  ~World() { std::cout << "Destroying World with message " << msg << std::endl; }
};

// Seems to be needed to mirror types directly without exposing the Integer type
// template<> struct IsMirroredType<Integer> : std::false_type { };

// C++ code to expose classes and their members to Julia in a Module
JLCXX_MODULE OpenSpaceToolkitCore(jlcxx::Module& Core)
{

  // Dummy Example to add type in the main module directly

  Core.add_type<World>("World")
    .constructor<const std::string&>()
    .method("set", &World::set)
    .method("greet", &World::greet);

  // Adding Integer types to Julia

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

    // .method("+", &Integer::operator==)
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
