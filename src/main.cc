#include <iostream>

#include "self_balancing_binary_search_tree.h"
int main() {
  SelfBalancingBinarySearchTree avl_tre;
  Value value("Vasya", "Pupkin", "1992", "Moskow", "23");
  std::cout << avl_tre.Set("key1", value) << std::endl;
  std::cout << avl_tre.Set("key2", value) << std::endl;
  std::cout << avl_tre.Exists("key1") << std::endl;
  std::cout << avl_tre.Exists("key3") << std::endl;
  return 0;
}