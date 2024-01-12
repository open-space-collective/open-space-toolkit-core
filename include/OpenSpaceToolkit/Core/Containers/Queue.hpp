/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Containers_Graph__
#define __OpenSpaceToolkit_Core_Containers_Graph__

namespace ostk
{
namespace core
{
namespace containers
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

}  // namespace containers
}  // namespace core
}  // namespace ostk

#endif
