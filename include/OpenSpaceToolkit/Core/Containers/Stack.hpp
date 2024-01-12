/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Containers_Stack__
#define __OpenSpaceToolkit_Core_Containers_Stack__

namespace ostk
{
namespace core
{
namespace containers
{

/// @brief                      First-in, last-out (FILO) container

class Stack
{
   public:
    Stack() = delete;

    Stack(const Stack& aStack);

    ~Stack();

    Stack& operator=(const Stack& aStack) const;

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Stack& aStack);

    bool isDefined() const;

    static Stack Empty();

    static Stack Object(const Object& anObject);

   private:
    // [TBI]
};

}  // namespace containers
}  // namespace core
}  // namespace ostk

#endif
