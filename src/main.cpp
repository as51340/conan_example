#include "hello.h"
#include <vector>
#include <string>
#include <iostream>
#include <rocksdb/db.h>

int main() {
  hello();

  std::vector<std::string> vec;
  vec.push_back("test_package");

  hello_print_vector(vec);

  // RocksDB example

  // Path to RocksDB database
  const std::string db_path = "testdb";

  // Open the database
  rocksdb::DB* db;
  rocksdb::Options options;
  options.create_if_missing = true;  // Create the database if it doesn't exist

  rocksdb::Status status = rocksdb::DB::Open(options, db_path, &db);
  if (!status.ok()) {
    std::cerr << "Unable to open/create RocksDB database: " << status.ToString() << std::endl;
    return 1;
  }

  std::cout << "Database opened successfully!" << std::endl;

  // Key-value pair to write and read
  std::string key = "key1";
  std::string value = "value1";

  // Write a key-value pair
  status = db->Put(rocksdb::WriteOptions(), key, value);
  if (!status.ok()) {
    std::cerr << "Failed to write to RocksDB: " << status.ToString() << std::endl;
    delete db;
    return 1;
  }

  std::cout << "Successfully wrote key-value pair (" << key << ", " << value << ") to RocksDB." << std::endl;

  // Read the value back
  std::string read_value;
  status = db->Get(rocksdb::ReadOptions(), key, &read_value);
  if (!status.ok()) {
    std::cerr << "Failed to read from RocksDB: " << status.ToString() << std::endl;
    delete db;
    return 1;
  }

  std::cout << "Successfully read value for key \"" << key << "\": " << read_value << std::endl;

  // Clean up
  delete db;



}
