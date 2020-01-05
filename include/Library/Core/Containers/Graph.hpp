////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           Library/Core/Containers/Graph.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Core_Containers_Graph__
#define __OpenSpaceToolkit_Core_Containers_Graph__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace core
{
namespace ctnr
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Structure consisting of a finite set of vertices, together with a set of pairs of these vertices (edges).
///
/// @ref                        https://en.wikipedia.org/wiki/Graph_(abstract_data_type)

class Graph
{

    public:

                                Graph                                       ( ) = delete ;

                                Graph                                       (   const   Graph&                      aGraph                                      ) ;

                                ~Graph                                      ( ) ;

        Graph&                  operator =                                  (   const   Graph&                      aGraph                                      ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Graph&                      aGraph                                      ) ;

        bool                    isDefined                                   ( ) const ;

        static Graph            Empty                                       ( ) ;

        static Graph            Object                                      (   const   Object&                     anObject                                    ) ;

    private:

        // [TBI]

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
