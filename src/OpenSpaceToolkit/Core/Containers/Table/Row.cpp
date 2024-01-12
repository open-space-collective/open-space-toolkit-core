/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table/Row.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

namespace ostk
{
namespace core
{
namespace containers
{
namespace table
{

Row::Row(const Array<Cell>& aCellArray)
    : tablePtr_(nullptr),
      cells_(aCellArray)
{
}

Row::Row(std::initializer_list<Cell> aCellList)
    : tablePtr_(nullptr),
      cells_(aCellList)
{
}

Row::Row(const Table* aTablePtr)
    : tablePtr_(aTablePtr),
      cells_(Array<Cell>::Empty())
{
}

Row::Row(const Table* aTablePtr, const Array<Cell>& aCellArray)
    : tablePtr_(aTablePtr),
      cells_(aCellArray)
{
}

Row::Row(const Row& aRow)
    : tablePtr_(nullptr),
      cells_(aRow.cells_)
{
}

Row& Row::operator=(const Row& aRow)
{
    if (this != &aRow)
    {
        tablePtr_ = nullptr;

        cells_ = aRow.cells_;
    }

    return *this;
}

bool Row::operator==(const Row& aRow) const
{
    return std::equal(
        cells_.begin(),
        cells_.end(),
        aRow.cells_.begin(),
        aRow.cells_.end(),
        [](const Cell& aFirstCell, const Cell& aSecondCell) -> bool
        {
            return ((!aFirstCell.isDefined()) && (!aSecondCell.isDefined())) || (aFirstCell == aSecondCell);
        }
    );
}

bool Row::operator!=(const Row& aRow) const
{
    return cells_ != aRow.cells_;
}

const Cell& Row::operator[](const Index& aColumnIndex) const
{
    if (aColumnIndex >= cells_.getSize())
    {
        throw ostk::core::error::RuntimeError(
            "Column index [{}] out of range [0 - {}].", aColumnIndex, cells_.getSize()
        );
    }

    return cells_[aColumnIndex];
}

const Cell& Row::operator[](const String& aColumnName) const
{
    if (tablePtr_ == nullptr)
    {
        throw ostk::core::error::RuntimeError("No associated table.");
    }

    return (*this)[tablePtr_->getIndexOfColumnWithName(aColumnName)];
}

bool Row::isEmpty() const
{
    return cells_.isEmpty();
}

Size Row::getSize() const
{
    return cells_.getSize();
}

Row::ConstIterator Row::begin() const
{
    return cells_.begin();
}

Row::ConstIterator Row::end() const
{
    return cells_.end();
}

void Row::associateTable(const Table* aTablePtr)
{
    tablePtr_ = aTablePtr;
}

}  // namespace table
}  // namespace containers
}  // namespace core
}  // namespace ostk
