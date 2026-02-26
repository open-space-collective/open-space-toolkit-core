/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Container_Table_Row__
#define __OpenSpaceToolkit_Core_Container_Table_Row__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Table/Cell.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>

namespace ostk
{
namespace core
{
namespace container
{

class Table;

namespace table
{

using ostk::core::container::Array;
using ostk::core::container::table::Cell;
using ostk::core::type::Index;
using ostk::core::type::Size;
using ostk::core::type::String;

/// @brief Row of table container
class Row
{
   public:
    typedef Array<Cell>::ConstIterator ConstIterator;

    /// @brief Constructor from cell array
    ///
    /// @param [in] aCellArray An array of cells
    Row(const Array<Cell>& aCellArray);

    /// @brief Constructor from initializer list
    ///
    /// @param [in] aCellList An initializer list of cells
    Row(std::initializer_list<Cell> aCellList);

    /// @brief Constructor from table pointer
    ///
    /// @param [in] aTablePtr A pointer to the parent table
    Row(const Table* aTablePtr);

    /// @brief Constructor from table pointer and cell array
    ///
    /// @param [in] aTablePtr A pointer to the parent table
    /// @param [in] aCellArray An array of cells
    Row(const Table* aTablePtr, const Array<Cell>& aCellArray);

    /// @brief Copy constructor
    ///
    /// @param [in] aRow A row
    Row(const Row& aRow);

    /// @brief Copy assignment operator
    ///
    /// @param [in] aRow A row
    /// @return Reference to row
    Row& operator=(const Row& aRow);

    /// @brief Equal to operator
    ///
    /// @param [in] aRow A row
    /// @return True if rows are equal
    bool operator==(const Row& aRow) const;

    /// @brief Not equal to operator
    ///
    /// @param [in] aRow A row
    /// @return True if rows are not equal
    bool operator!=(const Row& aRow) const;

    /// @brief Index subscript operator
    ///
    /// @param [in] aColumnIndex A column index
    /// @return Const reference to cell
    const Cell& operator[](const Index& aColumnIndex) const;

    /// @brief Name subscript operator
    ///
    /// @param [in] aColumnName A column name
    /// @return Const reference to cell
    const Cell& operator[](const String& aColumnName) const;

    /// @brief Check if row is empty
    ///
    /// @return True if empty
    bool isEmpty() const;

    /// @brief Get number of cells in row
    ///
    /// @return Number of cells
    Size getSize() const;

    /// @brief Returns a const iterator pointing to the first cell
    ///
    /// @return Const iterator to first cell
    Row::ConstIterator begin() const;

    /// @brief Returns a const iterator pointing past the last cell
    ///
    /// @return Const iterator past last cell
    Row::ConstIterator end() const;

    /// @brief Associate row with a table
    ///
    /// @param [in] aTablePtr A pointer to the parent table
    void associateTable(const Table* aTablePtr);

   private:
    const Table* tablePtr_;
    Array<Cell> cells_;
};

}  // namespace table
}  // namespace container
}  // namespace core
}  // namespace ostk

#endif
