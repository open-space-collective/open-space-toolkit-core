/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Containers_Table_Row__
#define __OpenSpaceToolkit_Core_Containers_Table_Row__

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table/Cell.hpp>
#include <OpenSpaceToolkit/Core/Types/Index.hpp>
#include <OpenSpaceToolkit/Core/Types/Size.hpp>

namespace ostk
{
namespace core
{
namespace ctnr
{

class Table;

namespace table
{

using ostk::core::types::Index;
using ostk::core::types::Size;
using ostk::core::types::String;
using ostk::core::ctnr::Array;
using ostk::core::ctnr::table::Cell;

/// @brief                      Row of table container

class Row
{
   public:
    typedef Array<Cell>::ConstIterator ConstIterator;

    Row(const Array<Cell>& aCellArray);

    Row(std::initializer_list<Cell> aCellList);

    Row(const Table* aTablePtr);

    Row(const Table* aTablePtr, const Array<Cell>& aCellArray);

    Row(const Row& aRow);

    Row& operator=(const Row& aRow);

    bool operator==(const Row& aRow) const;

    bool operator!=(const Row& aRow) const;

    const Cell& operator[](const Index& aColumnIndex) const;

    const Cell& operator[](const String& aColumnName) const;

    bool isEmpty() const;

    Size getSize() const;

    Row::ConstIterator begin() const;

    Row::ConstIterator end() const;

    void associateTable(const Table* aTablePtr);

   private:
    const Table* tablePtr_;
    Array<Cell> cells_;
};

}  // namespace table
}  // namespace ctnr
}  // namespace core
}  // namespace ostk

#endif
