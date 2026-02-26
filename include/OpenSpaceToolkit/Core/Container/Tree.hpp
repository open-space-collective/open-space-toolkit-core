/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Container_Tree__
#define __OpenSpaceToolkit_Core_Container_Tree__

namespace ostk
{
namespace core
{
namespace container
{

/// @brief Undirected graph in which any two vertices are connected by exactly one path [TBI]
///
/// A tree data structure can be defined recursively (locally) as a collection of nodes
/// (starting at a root node), where each node is a data structure consisting of a value,
/// together with a list of references to nodes (the "children"), with the constraints that
/// no reference is duplicated, and none points to the root.
///
/// @ref https://en.wikipedia.org/wiki/Tree_(graph_theory)
/// @ref https://en.wikipedia.org/wiki/Tree_(data_structure)
class Tree
{
   public:
    /// @brief Default constructor (disabled)
    Tree() = delete;

    /// @brief Copy constructor
    ///
    /// @param [in] aTree A tree
    Tree(const Tree& aTree);

    /// @brief Destructor
    ~Tree();

    /// @brief Copy assignment operator
    ///
    /// @param [in] aTree A tree
    /// @return Reference to tree
    Tree& operator=(const Tree& aTree) const;

    /// @brief Output stream operator
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aTree A tree
    /// @return Reference to output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Tree& aTree);

    /// @brief Check if tree is defined
    ///
    /// @return True if defined
    bool isDefined() const;

    /// @brief Construct an empty tree
    ///
    /// @return Empty tree
    static Tree Empty();

    /// @brief Construct a tree from an object
    ///
    /// @param [in] anObject An object
    /// @return Tree
    static Tree Object(const Object& anObject);

   private:
    // [TBI]
};

}  // namespace container
}  // namespace core
}  // namespace ostk

#endif
