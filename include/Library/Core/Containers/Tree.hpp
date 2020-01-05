////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           Library/Core/Containers/Tree.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Core_Containers_Tree__
#define __OpenSpaceToolkit_Core_Containers_Tree__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace core
{
namespace ctnr
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Undirected graph in which any two vertices are connected by exactly one path
///
///                             A tree data structure can be defined recursively (locally) as a collection of nodes (starting at a root node),
///                             where each node is a data structure consisting of a value, together with a list of references to nodes (the "children"),
///                             with the constraints that no reference is duplicated, and none points to the root.
///
/// @ref                        https://en.wikipedia.org/wiki/Tree_(graph_theory)
/// @ref                        https://en.wikipedia.org/wiki/Tree_(data_structure)

class Tree
{

    public:

                                Tree                                        ( ) = delete ;

                                Tree                                        (   const   Tree&                       aTree                                       ) ;

                                ~Tree                                       ( ) ;

        Tree&                   operator =                                  (   const   Tree&                       aTree                                       ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Tree&                       aTree                                       ) ;

        bool                    isDefined                                   ( ) const ;

        static Tree             Empty                                       ( ) ;

        static Tree             Object                                      (   const   Object&                     anObject                                    ) ;

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
