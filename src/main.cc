#include <iostream>

#include "self_balancing_binary_search_tree.h"
int main() {
  SelfBalancingBinarySearchTree avl_tre;
  Value value("Vasya", "Pupkin", "1992", "Moskow", "23");
  Value value1("Petya", "Popov", "1998", "Novosibirsk", "11");
  Value value3("Sidorov", "Sergei", "1980", "Novosibirsk", "50");
  // avl_tre.Set("key0", value3);
  // avl_tre.Set("key3", value1);
  // avl_tre.Set("key2", value);
  // avl_tre.Set("key1", value);
  // avl_tre.Set("key5", value);
  // avl_tre.Set("key0", value);
  // std::vector<AbstractStore::Key> nodes = avl_tre.Keys();
  // for (const auto& node : nodes) {
  //   std::cout << node << " ";
  // }
  // // std::cout << std::endl;
  // auto value_vec = avl_tre.ShowAll();
  // for (const auto& el : value_vec) {
  //   std::cout << el.ToString() << std::endl;
  // }

  // avl_tre.Rename("key0", "key15");

  // std::cout << "\n\n####################\n\n";
  // auto value_vec1 = avl_tre.ShowAll();
  // for (const auto& el : value_vec1) {
  //   std::cout << el.ToString() << std::endl;
  // }

  // std::cout << "\n\n####################\n\n";

  // avl_tre.Update("key15", "SAVA - 2000 EKV -");

  // auto value_vec1 = avl_tre.ShowAll();
  // for (const auto& el : value_vec1) {
  //   std::cout << el.ToString() << std::endl;
  // }

  avl_tre.Upload("test.dat");

  // auto value_vec1 = avl_tre.ShowAll();
  // for (const auto& el : value_vec1) {
  //   std::cout << el.ToString() << std::endl;
  // }
  // std::cout << "\n\n";
  std::vector<AbstractStore::Key> nodes1 = avl_tre.Keys();
  std::cout << "\n\n";
  for (const auto& node : nodes1) {
    std::cout << node << " ";
  }
  avl_tre.Export("omg.dat");
  auto res = avl_tre.Find("- - - Novosibirsk -");
  // for (const auto& el : res) {
  //   std::cout << el << std::endl;
  // }
  avl_tre.MakeDotFile("test");
  return 0;
}