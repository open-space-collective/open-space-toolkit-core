/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Container_Stack__
#define __OpenSpaceToolkit_Core_Container_Stack__

#include <ostream>

#include <OpenSpaceToolkit/Core/Container/Object.hpp>

namespace ostk
{
namespace core
{
namespace container
{

using ostk::core::container::Object;

/// @brief First-in, last-out (FILO) container [TBI]
class Stack
{
   public:
    /// @brief Default constructor (disabled)
    Stack() = delete;

    /// @brief Copy constructor
    ///
    /// @param [in] aStack A stack
    Stack(const Stack& aStack);

    /// @brief Destructor
    ~Stack();

    /// @brief Copy assignment operator
    ///
    /// @param [in] aStack A stack
    /// @return Reference to stack
    Stack& operator=(const Stack& aStack);

    /// @brief Output stream operator
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aStack A stack
    /// @return Reference to output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Stack& aStack);

    /// @brief Check if stack is defined
    ///
    /// @return True if defined
    bool isDefined() const;

    /// @brief Construct an empty stack
    ///
    /// @return Empty stack
    static Stack Empty();

    /// @brief Construct a stack from an object
    ///
    /// @param [in] anObject An object
    /// @return Stack
    static Stack Object(const Object& anObject);

   private:
    // [TBI]
};

}  // namespace container
}  // namespace core
}  // namespace ostk

#endif
