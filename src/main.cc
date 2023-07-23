#include <iostream>

#include "self_balancing_binary_search_tree.h"
int main() {
  SelfBalancingBinarySearchTree avl_tre;
  Value value("Vasya", "Pupkin", "1992", "Moskow", "23");
  Value value1("Petya", "Popov", "1998", "NSK", "11");
  std::cout << avl_tre.Set("key3", value1) << std::endl;
  std::cout << avl_tre.Set("key2", value) << std::endl;
  std::cout << avl_tre.Set("key1", value) << std::endl;
  std::cout << avl_tre.Set("key5", value) << std::endl;
  std::cout << avl_tre.Set("key0", value) << std::endl;
  std::cout << avl_tre.Exists("key1") << std::endl;
  std::cout << avl_tre.Exists("key3") << std::endl;
  std::vector<AbstractStore::Key> nodes = avl_tre.Keys();
  for (const auto& node : nodes) {
    std::cout << node << " ";
  }
  std::cout << std::endl;
  auto res = avl_tre.Get("key");
  auto value_vec = avl_tre.ShowAll();
  for (const auto& el : value_vec) {
    std::cout << el.ToString() << std::endl;
  }
  avl_tre.Rename("key1", "abc");
  std::vector<AbstractStore::Key> nodes1 = avl_tre.Keys();
  std::cout << "\n\n";
  for (const auto& node : nodes1) {
    std::cout << node << " ";
  }
  std::cout << "\n\n####################\n\n";
  auto value_vec1 = avl_tre.ShowAll();
  for (const auto& el : value_vec1) {
    std::cout << el.ToString() << std::endl;
  }

  std::cout << "\n\n####################\n\n";

  avl_tre.Update("abc", "SAVA - 2000 - EKV -");

  // value_vec1 = avl_tre.ShowAll();
  // for (const auto& el : value_vec1) {
  //   std::cout << el.ToString() << std::endl;
  // }
  return 0;
}