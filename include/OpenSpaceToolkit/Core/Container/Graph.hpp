/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Container_Graph__
#define __OpenSpaceToolkit_Core_Container_Graph__

#include <ostream>

#include <OpenSpaceToolkit/Core/Container/Object.hpp>

namespace ostk
{
namespace core
{
namespace container
{

using ostk::core::container::Object;

/// @brief Structure consisting of a finite set of vertices, together with a set of pairs of these
/// vertices (edges). [TBI]
///
/// @ref https://en.wikipedia.org/wiki/Graph_(abstract_data_type)
class Graph
{
   public:
    /// @brief Default constructor (disabled)
    Graph() = delete;

    /// @brief Copy constructor
    ///
    /// @param [in] aGraph A graph
    Graph(const Graph& aGraph);

    /// @brief Destructor
    ~Graph();

    /// @brief Copy assignment operator
    ///
    /// @param [in] aGraph A graph
    /// @return Reference to graph
    Graph& operator=(const Graph& aGraph);

    /// @brief Output stream operator
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aGraph A graph
    /// @return Reference to output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Graph& aGraph);

    /// @brief Check if graph is defined
    ///
    /// @return True if defined
    bool isDefined() const;

    /// @brief Construct an empty graph
    ///
    /// @return Empty graph
    static Graph Empty();

    /// @brief Construct a graph from an object
    ///
    /// @param [in] anObject An object
    /// @return Graph
    static Graph Object(const Object& anObject);

   private:
    // [TBI]
};

}  // namespace container
}  // namespace core
}  // namespace ostk

#endif
