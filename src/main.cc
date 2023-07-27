#include <iostream>

#include "self_balancing_binary_search_tree.h"
int main() {
  // SelfBalancingBinarySearchTree avl_tre;
  // Value value("Vasya", "Pupkin", "1992", "Moskow", "23");
  // Value value1("Petya", "Popov", "1998", "Novosibirsk", "11");
  // Value value3("Sidorov", "Sergei", "1980", "Novosibirsk", "50");
  // avl_tre.Set("1", value3);
  // avl_tre.Set("2", value1);
  // avl_tre.Set("3", value);
  // avl_tre.Set("4", value1);
  // avl_tre.Set("0", value1);
  // avl_tre.Set("6", value1);
  // avl_tre.Set("5", value);
  // SelfBalancingBinarySearchTree avl_tree;
  // Value val("Pupkin", "Vasya", "1992", "Moskow", "23");
  // avl_tree.Set("10", val);
  // avl_tree.Set("5", val);
  // avl_tree.Set("15", val);
  // avl_tree.Set("3", val);
  // avl_tree.MakeDotFile("test");
  // avl_tre.Del("2");
  // avl_tre.Del("3");
  // avl_tre.Del("6");
  // avl_tre.Del("5");
  // avl_tre.Del("0");
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

  // avl_tre.Upload("test.dat");

  // auto value_vec1 = avl_tre.ShowAll();
  // for (const auto& el : value_vec1) {
  //   std::cout << el.ToString() << std::endl;
  // }
  // std::cout << "\n\n";
  // std::vector<AbstractStore::Key> nodes1 = avl_tree.Keys();
  // std::cout << "\n\n";
  // for (const auto& node : nodes1) {
  //   std::cout << node << " ";
  // }
  // for (const auto& el : res) {
  //   std::cout << el << std::endl;
  // }
  // avl_tree.MakeDotFile("test");
  SelfBalancingBinarySearchTree avl_tree;
  Value value1("Ivanov", "Ivan", "2000", "Moscow", "55");
  Value value2("Petrov", "Petr", "1990", "St. Petersburg", "100");
  Value value3("Sidorov", "Sergei", "1980", "Novosibirsk", "50");

  avl_tree.Set("key1", value1);
  avl_tree.Set("key2", value2);
  avl_tree.Set("key3", value3);

  avl_tree.Rename("key2", "key99");
  avl_tree.Get("key99").value() == value1;

  avl_tree.Rename("key3", "asdads");
  avl_tree.Get("asdads").value() == value3;

  avl_tree.Rename("unknown_key", "unknown_key");

  avl_tree.Export("asd.dat");
  avl_tree.MakeDotFile("test");
  return 0;
}