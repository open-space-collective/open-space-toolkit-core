/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Container_Table__
#define __OpenSpaceToolkit_Core_Container_Table__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Table/Cell.hpp>
#include <OpenSpaceToolkit/Core/Container/Table/Row.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace core
{
namespace container
{

using ostk::core::type::Index;
using ostk::core::type::Size;
using ostk::core::type::String;
using ostk::core::container::Array;
using ostk::core::container::table::Row;
using ostk::core::container::table::Cell;
using ostk::core::filesystem::File;

/// @brief                      Table container

class Table
{
   public:
    /// @brief              Table format

    enum class Format
    {

        Undefined,  ///< Undefined format
        CSV         ///< Comma-Separated Values format

    };

    /// @brief              Table constant iterator

    typedef Array<Row>::ConstIterator ConstIterator;

    /// @brief              Constructor
    ///
    /// @code
    ///                     Table table = { { "Column A", "Column B" }, { { Cell::Integer(123), Cell::Real(123.456) } }
    ///                     } ;
    /// @endcode
    ///
    /// @param              [in] aHeader A column name array
    /// @param              [in] aRowArray A table row array

    Table(const Array<String>& aHeader, const Array<Row>& aRowArray);

    /// @brief              Constructor
    ///
    /// @code
    ///                     Table table = { { "Column A", "Column B" } } ;
    /// @endcode
    ///
    /// @param              [in] aHeader A column name array

    Table(const Array<String>& aHeader);

    /// @brief              Copy constructor
    ///
    /// @param              [in] aTable A table

    Table(const Table& aTable);

    /// @brief              Copy assignment operator
    ///
    /// @param              [in] aTable A table
    /// @return             Reference to table

    Table& operator=(const Table& aTable);

    /// @brief              Equal to operator
    ///
    /// @code
    ///                     Table(...) == Table(...) ; // True
    /// @endcode
    ///
    /// @param              [in] aTable A table
    /// @return             True if tables are equal

    bool operator==(const Table& aTable) const;

    /// @brief              Not equal to operator
    ///
    /// @code
    ///                     Table(...) != Table(1.0, 0.0, 0.0, 0.0) ; // True
    /// @endcode
    ///
    /// @param              [in] aTable A table
    /// @return             True if tables are not equal

    bool operator!=(const Table& aTable) const;

    /// @brief              Subscript operator (row accessor)
    ///
    /// @code
    ///                     Table table = { { "Column A", "Column B" }, { { Cell::Integer(123), Cell::Real(123.456) } }
    ///                     } ; const Row& row = table[0] ; // { Cell::Integer(123), Cell::Real(123.456) }
    /// @endcode
    ///
    /// @param              [in] aRowIndex A row index
    /// @return             Reference to row

    const Row& operator[](const Index& aRowIndex) const;

    /// @brief              Function call operator (cell accessor)
    ///
    /// @code
    ///                     Table table = { { "Column A", "Column B" }, { { Cell::Integer(123), Cell::Real(123.456) } }
    ///                     } ; const Cell& cell = table(0, 0) ; // Cell::Integer(123)
    /// @endcode
    ///
    /// @param              [in] aRowIndex A row index
    /// @param              [in] aColumnIndex A column index
    /// @return             Reference to cell

    const Cell& operator()(const Index& aRowIndex, const Index& aColumnIndex) const;

    /// @brief              Function call operator (cell accessor)
    ///
    /// @code
    ///                     Table table = { { "Column A", "Column B" }, { { Cell::Integer(123), Cell::Real(123.456) } }
    ///                     } ; const Cell& cell = table(0, "Column A") ; // Cell::Integer(123)
    /// @endcode
    ///
    /// @param              [in] aRowIndex A row index
    /// @param              [in] aColumnName A column name
    /// @return             Reference to cell

    const Cell& operator()(const Index& aRowIndex, const String& aColumnName) const;

    /// @brief              Output stream operator
    ///
    /// @code
    ///                     std::cout << Table(...) ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] aTable A table
    /// @return             A reference to output stream

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Table& aTable);

    /// @brief              Check if table is empty
    ///
    /// @code
    ///                     Table::Empty().isEmpty() ; // True
    /// @endcode
    ///
    /// @return             True if table is empty

    bool isEmpty() const;

    /// @brief              Returns true is table has column with a given name
    ///
    /// @param              [in] aColumnName A column name
    /// @return             True is table has column with a given name

    bool hasColumnWithName(const String& aColumnName) const;

    /// @brief              Get number of rows
    ///
    /// @code
    ///                     Table table = { { "Column A", "Column B" }, { { Cell::Integer(123), Cell::Real(123.456) } }
    ///                     } ; table.getRowCount() ; // 1
    /// @endcode
    ///
    /// @return             Number of rows

    Size getRowCount() const;

    /// @brief              Get number of columns
    ///
    /// @code
    ///                     Table table = { { "Column A", "Column B" }, { { Cell::Integer(123), Cell::Real(123.456) } }
    ///                     } ; table.getColumnCount() ; // 2
    /// @endcode
    ///
    /// @return             Number of columns

    Size getColumnCount() const;

    /// @brief              Returns the index of column with a given name
    ///
    /// @param              [in] aColumnName A column name
    /// @return             Index of column with a given name

    Index getIndexOfColumnWithName(const String& aColumnName) const;

    /// @brief              Add row
    ///
    /// @code
    ///                     Table table = { { "Column A", "Column B" }, { { Cell::Integer(123), Cell::Real(123.456) } }
    ///                     } ; table.addRow({ Cell::Integer(456), Cell::Real(456.789) }) ;
    /// @endcode
    ///
    /// @param              [in] aRow A row to add

    void addRow(const Row& aRow);

    /// @brief              Clear table
    ///
    /// @code
    ///                     Table table = { { "Column A", "Column B" }, { { Cell::Integer(123), Cell::Real(123.456) } }
    ///                     } ; table.clear() ;
    /// @endcode

    void clear();

    /// @brief              Get begin constant interator
    ///
    /// @return             Begin constant interator

    Table::ConstIterator begin() const;

    /// @brief              Get end constant interator
    ///
    /// @return             End constant interator

    Table::ConstIterator end() const;

    /// @brief              Constructs an empty table
    ///
    /// @code
    ///                     Table table = Table::Empty() ;
    /// @endcode
    ///
    /// @return             Empty table

    static Table Empty();

    /// @brief              Constructs a table from a file
    ///
    /// @code
    ///                     Table table = Table::Load(File::Path(Path::Parse("/path/to/file.csv")), Table::Format::CSV,
    ///                     true) ;
    /// @endcode
    ///
    /// @param              [in] aFile A table file
    /// @param              [in] (optional) aFormat A table format
    /// @param              [in] (optional) hasHeader True if file has a header
    /// @return             Table

    static Table Load(
        const File& aFile, const Table::Format& aFormat = Table::Format::Undefined, bool hasHeader = true
    );

   private:
    Array<String> header_;
    Array<Row> rows_;

    static Table LoadCsv(const File& aFile, bool hasHeader = true);
};

}  // namespace container
}  // namespace core
}  // namespace ostk

#endif
