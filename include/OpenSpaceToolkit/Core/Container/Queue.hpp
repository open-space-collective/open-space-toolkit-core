/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Container_Graph__
#define __OpenSpaceToolkit_Core_Container_Graph__

namespace ostk
{
namespace core
{
namespace container
{

/// @brief                      First-in, first-out (FIFO) container

class Queue
{
   public:
    Queue() = delete;

    Queue(const Queue& aQueue);

    ~Queue();

    Queue& operator=(const Queue& aQueue) const;

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Queue& aQueue);

    bool isDefined() const;

    static Queue Empty();

    static Queue Object(const Object& anObject);

   private:
    // [TBI]
};

}  // namespace container
}  // namespace core
}  // namespace ostk

#endif
