/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Container_Queue__
#define __OpenSpaceToolkit_Core_Container_Queue__

#include <ostream>

#include <OpenSpaceToolkit/Core/Container/Object.hpp>

namespace ostk
{
namespace core
{
namespace container
{

using ostk::core::container::Object;

/// @brief First-in, first-out (FIFO) container [TBI]
class Queue
{
   public:
    /// @brief Default constructor (disabled)
    Queue() = delete;

    /// @brief Copy constructor
    ///
    /// @param [in] aQueue A queue
    Queue(const Queue& aQueue);

    /// @brief Destructor
    ~Queue();

    /// @brief Copy assignment operator
    ///
    /// @param [in] aQueue A queue
    /// @return Reference to queue
    Queue& operator=(const Queue& aQueue);

    /// @brief Output stream operator
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aQueue A queue
    /// @return Reference to output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Queue& aQueue);

    /// @brief Check if queue is defined
    ///
    /// @return True if defined
    bool isDefined() const;

    /// @brief Construct an empty queue
    ///
    /// @return Empty queue
    static Queue Empty();

    /// @brief Construct a queue from an object
    ///
    /// @param [in] anObject An object
    /// @return Queue
    static Queue Object(const Object& anObject);

   private:
    // [TBI]
};

}  // namespace container
}  // namespace core
}  // namespace ostk

#endif
