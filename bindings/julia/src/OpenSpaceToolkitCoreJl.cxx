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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// C++ code defining classes
struct World
{
  World(const std::string& message = "default hello") : msg(message){}
  void set(const std::string& msge) { this->msg = msge; }
  std::string greet() { return msg; }
  std::string msg;
  ~World() { std::cout << "Destroying World with message " << msg << std::endl; }
};

// C++ code to expose classes and their members to Julia in a Module
JLCXX_MODULE define_julia_module(jlcxx::Module& CppTypes)
{
  CppTypes.add_type<World>("World")
    .constructor<const std::string&>()
    .method("set", &World::set)
    .method("greet", &World::greet);
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
