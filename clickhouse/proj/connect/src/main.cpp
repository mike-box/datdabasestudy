#include <clickhouse/client.h>
#include <iostream>

using namespace clickhouse;

#include <clickhouse/client.h>

using namespace clickhouse;

int main() {
    /// Initialize client connection.
    Client client(ClientOptions().SetHost("207.148.96.181"));
    
    // Create a database
    client.Execute("CREATE DATABASE IF NOT EXISTS test");

    /// Create a table.
    client.Execute("CREATE TABLE IF NOT EXISTS test.numbers (id UInt64, name String) ENGINE = Memory");
    // insert a row
    client.Execute("INSERT INTO test.numbers VALUES (100, 'mengmingliang')");
    client.Execute("INSERT INTO test.numbers VALUES (200, 'guoxiaohui')");

    /// Insert some values.
    {
        Block block;

        auto id = std::make_shared<ColumnUInt64>();
        id->Append(1);
        id->Append(7);

        auto name = std::make_shared<ColumnString>();
        name->Append("one");
        name->Append("seven");

        block.AppendColumn("id"  , id);
        block.AppendColumn("name", name);

        client.Insert("test.numbers", block);
    }

    /// Select values inserted in the previous step.
    client.Select("SELECT id, name FROM test.numbers", [] (const Block& block)
        {
            for (size_t i = 0; i < block.GetRowCount(); ++i) {
                std::cout << block[0]->As<ColumnUInt64>()->At(i) << " "
                        << block[1]->As<ColumnString>()->At(i) << "\n";
            }
        }
    );

    /// Delete table.
    // client.Execute("DROP TABLE test.numbers");
    return 0;
}