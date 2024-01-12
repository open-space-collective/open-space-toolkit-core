/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Table.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_Containers_Table, Constructor)
{
    using ostk::core::types::String;
    using ostk::core::containers::Array;
    using ostk::core::containers::Object;
    using ostk::core::containers::Table;
    using ostk::core::containers::table::Row;

    {
        const Array<String> header = {"Column A", "Column B"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        EXPECT_NO_THROW(Table table(header, rows););
    }

    {
        const Array<String> header = {"Column A", "Column B"};

        EXPECT_NO_THROW(Table table(header););
    }

    {
        const Array<String> header = {"Column A"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        EXPECT_ANY_THROW(Table table(header, rows););
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Table, CopyConstructor)
{
    using ostk::core::types::String;
    using ostk::core::containers::Array;
    using ostk::core::containers::Object;
    using ostk::core::containers::Table;
    using ostk::core::containers::table::Row;

    {
        const Array<String> header = {"Column A", "Column B"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table = {header, rows};

        const Table copyTable(table);

        EXPECT_NE(&table, &copyTable);
        EXPECT_EQ(table, copyTable);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Table, CopyAssignmentOperator)
{
    using ostk::core::types::String;
    using ostk::core::containers::Array;
    using ostk::core::containers::Object;
    using ostk::core::containers::Table;
    using ostk::core::containers::table::Row;

    {
        const Array<String> header = {"Column A", "Column B"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table = {header, rows};

        const Table copyTable = table;

        EXPECT_NE(&table, &copyTable);
        EXPECT_EQ(table, copyTable);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Table, EqualToOperator)
{
    using ostk::core::types::String;
    using ostk::core::containers::Array;
    using ostk::core::containers::Object;
    using ostk::core::containers::Table;
    using ostk::core::containers::table::Row;

    {
        const Array<String> header = {"Column A", "Column B"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table = {header, rows};

        EXPECT_TRUE(table == table);
    }

    {
        const Array<String> header = {"Column A", "Column B"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table_A = {header, rows};
        const Table table_B = {header, rows};

        EXPECT_TRUE(table_A == table_B);
    }

    {
        const Array<String> header_A = {"Column A", "Column B"};
        const Array<Row> rows_A = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table_A = {header_A, rows_A};

        const Array<String> header_B = {"Column A", "Column B"};
        const Array<Row> rows_B = {
            {Object::Integer(123), Object::Real(123.456)}, {Object::String("Hello"), Object::Undefined()}
        };

        const Table table_B = {header_B, rows_B};

        EXPECT_FALSE(table_A == table_B);
    }

    {
        const Array<String> header_A = {"Column A", "Column B"};
        const Array<Row> rows_A = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table_A = {header_A, rows_A};

        const Array<String> header_B = {"Column A", "Column B", "Column C"};
        const Array<Row> rows_B = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table_B = {header_B, rows_B};

        EXPECT_FALSE(table_A == table_B);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Table, NotEqualToOperator)
{
    using ostk::core::types::String;
    using ostk::core::containers::Array;
    using ostk::core::containers::Object;
    using ostk::core::containers::Table;
    using ostk::core::containers::table::Row;

    {
        const Array<String> header = {"Column A", "Column B"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table = {header, rows};

        EXPECT_FALSE(table != table);
    }

    {
        const Array<String> header = {"Column A", "Column B"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table_A = {header, rows};
        const Table table_B = {header, rows};

        EXPECT_FALSE(table_A != table_B);
    }

    {
        const Array<String> header_A = {"Column A", "Column B"};
        const Array<Row> rows_A = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table_A = {header_A, rows_A};

        const Array<String> header_B = {"Column A", "Column B"};
        const Array<Row> rows_B = {
            {Object::Integer(123), Object::Real(123.456)}, {Object::String("Hello"), Object::Undefined()}
        };

        const Table table_B = {header_B, rows_B};

        EXPECT_TRUE(table_A != table_B);
    }

    {
        const Array<String> header_A = {"Column A", "Column B"};
        const Array<Row> rows_A = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table_A = {header_A, rows_A};

        const Array<String> header_B = {"Column A", "Column B", "Column C"};
        const Array<Row> rows_B = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table_B = {header_B, rows_B};

        EXPECT_TRUE(table_A != table_B);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Table, SubscriptOperator)
{
    using ostk::core::types::String;
    using ostk::core::containers::Array;
    using ostk::core::containers::Object;
    using ostk::core::containers::Table;
    using ostk::core::containers::table::Row;

    {
        const Array<String> header = {"Column A", "Column B"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table = {header, rows};

        EXPECT_NO_THROW(table[0]);

        const Row& firstRow = table[0];

        EXPECT_EQ(Object::Integer(123), firstRow[0]);
        EXPECT_EQ(Object::Real(123.456), firstRow[1]);
        EXPECT_ANY_THROW(firstRow[2]);

        EXPECT_EQ(Object::Integer(123), firstRow["Column A"]);
        EXPECT_EQ(Object::Real(123.456), firstRow["Column B"]);
        EXPECT_ANY_THROW(firstRow["Column C"]);

        EXPECT_NO_THROW(table[1]);

        const Row& secondRow = table[1];

        EXPECT_EQ(Object::String("Hello"), secondRow[0]);
        EXPECT_FALSE(secondRow[1].isDefined());
        EXPECT_ANY_THROW(secondRow[2]);

        EXPECT_EQ(Object::String("Hello"), secondRow["Column A"]);
        EXPECT_FALSE(secondRow["Column B"].isDefined());
        EXPECT_ANY_THROW(secondRow["Column C"]);

        const Row& thirdRow = table[2];

        EXPECT_EQ(Object::String("World!"), thirdRow[0]);
        EXPECT_ANY_THROW(thirdRow[1]);

        EXPECT_EQ(Object::String("World!"), thirdRow["Column A"]);
        EXPECT_ANY_THROW(thirdRow["Column B"]);

        EXPECT_ANY_THROW(table[3]);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Table, FunctionCallOperator)
{
    using ostk::core::types::String;
    using ostk::core::containers::Array;
    using ostk::core::containers::Object;
    using ostk::core::containers::Table;
    using ostk::core::containers::table::Row;

    {
        const Array<String> header = {"Column A", "Column B"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table = {header, rows};

        EXPECT_EQ(Object::Integer(123), table(0, 0));
        EXPECT_EQ(Object::Real(123.456), table(0, 1));
        EXPECT_ANY_THROW(table(0, 2));

        EXPECT_EQ(Object::String("Hello"), table(1, 0));
        EXPECT_FALSE(table(1, 1).isDefined());
        EXPECT_ANY_THROW(table(1, 2));

        EXPECT_EQ(Object::String("World!"), table(2, 0));
        EXPECT_ANY_THROW(table(2, 1));

        EXPECT_ANY_THROW(table(3, 0));
    }

    {
        const Array<String> header = {"Column A", "Column B"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table = {header, rows};

        EXPECT_EQ(Object::Integer(123), table(0, "Column A"));
        EXPECT_EQ(Object::Real(123.456), table(0, "Column B"));
        EXPECT_ANY_THROW(table(0, "Column C"));

        EXPECT_EQ(Object::String("Hello"), table(1, "Column A"));
        EXPECT_FALSE(table(1, "Column B").isDefined());
        EXPECT_ANY_THROW(table(1, "Column C"));

        EXPECT_EQ(Object::String("World!"), table(2, "Column A"));
        EXPECT_ANY_THROW(table(2, "Column B"));

        EXPECT_ANY_THROW(table(3, "Column A"));
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Table, StreamOperator)
{
    using ostk::core::types::String;
    using ostk::core::containers::Array;
    using ostk::core::containers::Object;
    using ostk::core::containers::Table;
    using ostk::core::containers::table::Row;

    {
        const Array<String> header = {"Column A", "Column B"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table = {header, rows};

        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << table << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Table, Iterator)
{
    using ostk::core::types::Index;
    using ostk::core::types::String;
    using ostk::core::containers::Array;
    using ostk::core::containers::Object;
    using ostk::core::containers::Table;
    using ostk::core::containers::table::Row;

    {
        const Array<String> header = {"Column A", "Column B"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table = {header, rows};

        Index index = 0;

        for (const auto& row : table)
        {
            if (index == 0)
            {
                EXPECT_EQ(Object::Integer(123), row[0]);
                EXPECT_EQ(Object::Real(123.456), row[1]);
            }
            else if (index == 1)
            {
                EXPECT_EQ(Object::String("Hello"), row[0]);
                EXPECT_FALSE(row[1].isDefined());
            }
            else if (index == 2)
            {
                EXPECT_EQ(Object::String("World!"), row[0]);
            }
            else
            {
                FAIL();
            }

            index++;
        }

        EXPECT_EQ(3, index);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Table, IsEmpty)
{
    using ostk::core::types::String;
    using ostk::core::containers::Array;
    using ostk::core::containers::Object;
    using ostk::core::containers::Table;
    using ostk::core::containers::table::Row;

    {
        const Array<String> header = {"Column A", "Column B"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table = {header, rows};

        EXPECT_FALSE(table.isEmpty());
    }

    {
        const Array<String> header = {"Column A", "Column B"};

        const Table table = {header};

        EXPECT_TRUE(table.isEmpty());
    }

    {
        EXPECT_TRUE(Table::Empty().isEmpty());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Table, HasColumnWithName)
{
    using ostk::core::types::String;
    using ostk::core::containers::Array;
    using ostk::core::containers::Object;
    using ostk::core::containers::Table;
    using ostk::core::containers::table::Row;

    {
        const Array<String> header = {"Column A", "Column B"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table = {header, rows};

        EXPECT_TRUE(table.hasColumnWithName("Column A"));
        EXPECT_TRUE(table.hasColumnWithName("Column B"));

        EXPECT_FALSE(table.hasColumnWithName("Column C"));
    }

    {
        const Array<String> header = {"Column A", "Column B"};

        const Table table = {header};

        EXPECT_TRUE(table.hasColumnWithName("Column A"));
        EXPECT_TRUE(table.hasColumnWithName("Column B"));

        EXPECT_FALSE(table.hasColumnWithName("Column C"));
    }

    {
        EXPECT_FALSE(Table::Empty().hasColumnWithName("Column A"));
    }

    {
        EXPECT_ANY_THROW(Table::Empty().hasColumnWithName(""));
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Table, GetRowCount)
{
    using ostk::core::types::String;
    using ostk::core::containers::Array;
    using ostk::core::containers::Object;
    using ostk::core::containers::Table;
    using ostk::core::containers::table::Row;

    {
        const Array<String> header = {"Column A", "Column B"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table = {header, rows};

        EXPECT_EQ(3, table.getRowCount());
    }

    {
        EXPECT_EQ(0, Table::Empty().getRowCount());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Table, GetColumnCount)
{
    using ostk::core::types::String;
    using ostk::core::containers::Array;
    using ostk::core::containers::Object;
    using ostk::core::containers::Table;
    using ostk::core::containers::table::Row;

    {
        const Array<String> header = {"Column A", "Column B"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table = {header, rows};

        EXPECT_EQ(2, table.getColumnCount());
    }

    {
        EXPECT_EQ(0, Table::Empty().getColumnCount());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Table, GetIndexOfColumnWithName)
{
    using ostk::core::types::String;
    using ostk::core::containers::Array;
    using ostk::core::containers::Object;
    using ostk::core::containers::Table;
    using ostk::core::containers::table::Row;

    {
        const Array<String> header = {"Column A", "Column B"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        const Table table = {header, rows};

        EXPECT_EQ(0, table.getIndexOfColumnWithName("Column A"));
        EXPECT_EQ(1, table.getIndexOfColumnWithName("Column B"));

        EXPECT_ANY_THROW(table.getIndexOfColumnWithName("Column C"));
    }

    {
        EXPECT_ANY_THROW(Table::Empty().getIndexOfColumnWithName(""));
        EXPECT_ANY_THROW(Table::Empty().getIndexOfColumnWithName("Column A"));
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Table, AddRow)
{
    using ostk::core::types::String;
    using ostk::core::containers::Array;
    using ostk::core::containers::Object;
    using ostk::core::containers::Table;
    using ostk::core::containers::table::Row;

    {
        const Array<String> header = {"Column A", "Column B"};

        Table table = {header};

        EXPECT_TRUE(table.isEmpty());
        EXPECT_EQ(2, table.getColumnCount());

        table.addRow({Object::Integer(123), Object::Real(123.456)});
        table.addRow({Object::String("Hello"), Object::Undefined()});
        table.addRow({Object::String("World!")});

        EXPECT_FALSE(table.isEmpty());
        EXPECT_EQ(2, table.getColumnCount());
    }

    {
        const Array<String> header = {"Column A"};

        Table table = {header};

        EXPECT_TRUE(table.isEmpty());
        EXPECT_EQ(1, table.getColumnCount());

        EXPECT_NO_THROW(table.addRow({Object::Integer(123), Object::Real(123.456)}));

        EXPECT_EQ(2, table.getColumnCount());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Table, Clear)
{
    using ostk::core::types::String;
    using ostk::core::containers::Array;
    using ostk::core::containers::Object;
    using ostk::core::containers::Table;
    using ostk::core::containers::table::Row;

    {
        const Array<String> header = {"Column A", "Column B"};
        const Array<Row> rows = {
            {Object::Integer(123), Object::Real(123.456)},
            {Object::String("Hello"), Object::Undefined()},
            {Object::String("World!")}
        };

        Table table = {header, rows};

        EXPECT_FALSE(table.isEmpty());

        table.clear();

        EXPECT_TRUE(table.isEmpty());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Table, Empty)
{
    using ostk::core::containers::Table;

    {
        EXPECT_NO_THROW(Table::Empty());
        EXPECT_TRUE(Table::Empty().isEmpty());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Table, Load)
{
    using ostk::core::types::String;
    using ostk::core::containers::Array;
    using ostk::core::containers::Object;
    using ostk::core::containers::Table;
    using ostk::core::containers::table::Row;
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::File;

    {
        const Array<String> header = {"A", "B", "C", "D", "E", "F"};
        const Array<Row> rows = {
            {Object::Integer(123),
             Object::Integer(-123),
             Object::Integer(123),
             Object::Real(123.456),
             Object::Real(-123.456),
             Object::Real(123.456)},
            {Object::String("Hello"),
             Object::String("World"),
             Object::String("!"),
             Object::String("Hello,"),
             Object::String("Wo\"\"rld")},
            {Object::Integer(1), Object::Undefined(), Object::Integer(3), Object::Undefined(), Object::Integer(5)}
        };

        const Table referenceTable = {header, rows};

        const File file = File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Core/Containers/Table/A.csv"));

        const Table table = Table::Load(file);

        EXPECT_EQ(referenceTable, table);
    }

    {
        const Array<String> header = {
            "Start Time (UTCG)",
            "Stop Time (UTCG)",
            "Duration (sec)",
            "Obstruction",
            "Current Condition",
            "Worst Condition",
            "Total Duration (sec)"
        };
        const Array<Row> rows = {
            {Object::String("1 Jan 2018 00:00:00.000"),
             Object::String("1 Jan 2018 04:15:48.956"),
             Object::Real(15348.956),
             Object::String("Earth"),
             Object::String("Umbra"),
             Object::String("Umbra"),
             Object::Real(15492.990)}
        };

        const Table referenceTable = {header, rows};

        const File file = File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Core/Containers/Table/B.csv"));

        const Table table = Table::Load(file);

        EXPECT_EQ(referenceTable, table);
    }
}
