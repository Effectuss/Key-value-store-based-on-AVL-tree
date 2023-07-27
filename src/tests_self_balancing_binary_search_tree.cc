#include <gtest/gtest.h>

#include <cmath>

#include "self_balancing_binary_search_tree.h"

Value val("Pupkin", "Vasya", "1992", "Moskow", "23");

TEST(AVLTree, Set1) {
  SelfBalancingBinarySearchTree avl_tree;
  EXPECT_TRUE(avl_tree.Set("10", val));
}

TEST(AVLTree, Set2) {
  SelfBalancingBinarySearchTree avl_tree;
  EXPECT_TRUE(avl_tree.Set("10", val));
  EXPECT_TRUE(avl_tree.Set("5", val));
  EXPECT_TRUE(std::abs(avl_tree.GetBalance(avl_tree.GetRootKey())) <= 1);
}

TEST(AVLTree, SetFourElements) {
  SelfBalancingBinarySearchTree avl_tree;
  EXPECT_TRUE(avl_tree.Set("g", val));
  EXPECT_TRUE(avl_tree.Set("d", val));
  EXPECT_TRUE(avl_tree.Set("x", val));
  EXPECT_TRUE(avl_tree.Set("a", val));
  EXPECT_TRUE(std::abs(avl_tree.GetBalance(avl_tree.GetRootKey())) <= 1);
}

TEST(AVLTree, CheckBalanceAfterSet1) {
  SelfBalancingBinarySearchTree avl_tree;
  EXPECT_TRUE(avl_tree.Set("g", val));
  EXPECT_TRUE(avl_tree.Set("d", val));
  EXPECT_TRUE(avl_tree.Set("x", val));
  EXPECT_TRUE(avl_tree.Set("b", val));
  EXPECT_TRUE(avl_tree.Set("y", val));
  EXPECT_TRUE(avl_tree.Set("z", val));
  EXPECT_TRUE(std::abs(avl_tree.GetBalance(avl_tree.GetRootKey())) <= 1);
  EXPECT_FALSE(avl_tree.Exists("a"));
  EXPECT_TRUE(avl_tree.Exists("x"));
  EXPECT_TRUE(avl_tree.Exists("g"));
}

TEST(AVLTree, CheckBalanceAfterSet2) {
  SelfBalancingBinarySearchTree avl_tree;
  EXPECT_TRUE(avl_tree.Set("g", val));
  EXPECT_FALSE(avl_tree.Set("g", val));
  EXPECT_TRUE(avl_tree.Set("d", val));
  EXPECT_TRUE(avl_tree.Set("x", val));
  EXPECT_TRUE(avl_tree.Set("b", val));
  EXPECT_TRUE(avl_tree.Set("y", val));
  EXPECT_TRUE(avl_tree.Set("z", val));
  EXPECT_TRUE(avl_tree.Set("l", val));
  EXPECT_TRUE(avl_tree.Set("a", val));
  EXPECT_TRUE(avl_tree.Set("99", val));
  EXPECT_TRUE(std::abs(avl_tree.GetBalance(avl_tree.GetRootKey())) <= 1);
  EXPECT_TRUE(avl_tree.Exists("a"));
  EXPECT_TRUE(avl_tree.Exists("x"));
  EXPECT_TRUE(avl_tree.Exists("g"));
  EXPECT_FALSE(avl_tree.Exists("k"));
}

TEST(AVLTree, LoopSet) {
  SelfBalancingBinarySearchTree avl_tree;
  for (int i = 0; i < 100; ++i) {
    EXPECT_TRUE(avl_tree.Set(std::to_string(i), val));
    EXPECT_TRUE(std::abs(avl_tree.GetBalance(avl_tree.GetRootKey())) <= 1);
  }
  avl_tree.MakeDotFile("tree_100_values");
}

void InsertNodes(SelfBalancingBinarySearchTree& avl_tree) {
  avl_tree.Set("F", val);
  avl_tree.Set("B", val);
  avl_tree.Set("G", val);
  avl_tree.Set("A", val);
  avl_tree.Set("D", val);
  avl_tree.Set("I", val);
  avl_tree.Set("C", val);
  avl_tree.Set("E", val);
  avl_tree.Set("H", val);
}

TEST(AVLTree, DeleteLeafNode) {
  SelfBalancingBinarySearchTree avl_tree;
  InsertNodes(avl_tree);

  // Deleting a node without children (leaf node)
  EXPECT_TRUE(avl_tree.Del("A"));
  EXPECT_FALSE(avl_tree.Exists("A"));
  EXPECT_TRUE(std::abs(avl_tree.GetBalance(avl_tree.GetRootKey())) <= 1);
}

TEST(AVLTree, DeleteNodeWithOneChild) {
  SelfBalancingBinarySearchTree avl_tree;
  InsertNodes(avl_tree);

  // Deleting a node with one child
  EXPECT_TRUE(avl_tree.Del("D"));
  EXPECT_FALSE(avl_tree.Exists("D"));
  EXPECT_TRUE(avl_tree.Exists("C"));
  EXPECT_TRUE(avl_tree.Exists("E"));
  EXPECT_TRUE(std::abs(avl_tree.GetBalance(avl_tree.GetRootKey())) <= 1);
}

TEST(AVLTree, DeleteNodeWithTwoChildren) {
  SelfBalancingBinarySearchTree avl_tree;
  InsertNodes(avl_tree);

  // Deleting a node with two children
  EXPECT_TRUE(avl_tree.Del("B"));
  EXPECT_FALSE(avl_tree.Exists("B"));
  EXPECT_TRUE(avl_tree.Exists("A"));
  EXPECT_TRUE(avl_tree.Exists("C"));
  EXPECT_TRUE(avl_tree.Exists("D"));
  EXPECT_TRUE(avl_tree.Exists("E"));
  EXPECT_TRUE(std::abs(avl_tree.GetBalance(avl_tree.GetRootKey())) <= 1);
}

TEST(AVLTree, DeleteRootWithOneChild) {
  SelfBalancingBinarySearchTree avl_tree;
  EXPECT_TRUE(avl_tree.Set("A", val));
  EXPECT_TRUE(avl_tree.Set("Z", val));
  // Deleting root with one child
  EXPECT_TRUE(avl_tree.Del("A"));
  EXPECT_FALSE(avl_tree.Exists("A"));
}

TEST(AVLTree, DeleteRootWithTwoChildren) {
  SelfBalancingBinarySearchTree avl_tree;
  InsertNodes(avl_tree);

  // Deleting root with two children
  EXPECT_TRUE(avl_tree.Del("F"));
  EXPECT_FALSE(avl_tree.Exists("F"));
  EXPECT_TRUE(avl_tree.Exists("G"));
  EXPECT_TRUE(avl_tree.Exists("B"));
  EXPECT_TRUE(avl_tree.Exists("A"));
  EXPECT_TRUE(avl_tree.Exists("D"));
  EXPECT_TRUE(avl_tree.Exists("I"));
  EXPECT_TRUE(avl_tree.Exists("C"));
  EXPECT_TRUE(avl_tree.Exists("E"));
  EXPECT_TRUE(avl_tree.Exists("H"));
  EXPECT_TRUE(std::abs(avl_tree.GetBalance(avl_tree.GetRootKey())) <= 1);
}

TEST(AVLTree, DeleteNonexistentNode) {
  SelfBalancingBinarySearchTree avl_tree;
  InsertNodes(avl_tree);

  // Try deleting a non-existent node
  EXPECT_FALSE(avl_tree.Del("Z"));
  EXPECT_FALSE(avl_tree.Exists("Z"));
  EXPECT_TRUE(std::abs(avl_tree.GetBalance(avl_tree.GetRootKey())) <= 1);
}

TEST(AVLTree, DeleteLoop) {
  SelfBalancingBinarySearchTree avl_tree;
  for (int i = 0; i < 100; ++i) {
    EXPECT_TRUE(avl_tree.Set(std::to_string(i), val));
    EXPECT_TRUE(std::abs(avl_tree.GetBalance(avl_tree.GetRootKey())) <= 1);
  }
  for (int i = 0; i < 100; i += 2) {
    EXPECT_TRUE(avl_tree.Del(std::to_string(i)));
    EXPECT_TRUE(std::abs(avl_tree.GetBalance(avl_tree.GetRootKey())) <= 1);
  }
  avl_tree.MakeDotFile("tree_with_delet_node");
  // Try deleting a non-existent node
  EXPECT_FALSE(avl_tree.Del("Z"));
  EXPECT_FALSE(avl_tree.Exists("Z"));
  EXPECT_TRUE(std::abs(avl_tree.GetBalance(avl_tree.GetRootKey())) <= 1);
}

TEST(AVLTree, GetValue) {
  SelfBalancingBinarySearchTree avl_tree;
  InsertNodes(avl_tree);
  EXPECT_TRUE(avl_tree.Get("A").value() ==
              Value("Pupkin", "Vasya", "1992", "Moskow", "23"));
  EXPECT_FALSE(avl_tree.Get("A").value() ==
               Value("Pupkin", "Petr", "2000", "Nsk", "23"));
}

TEST(AVLTree, TestKeys) {
  SelfBalancingBinarySearchTree avl_tree;
  auto check_size = avl_tree.Upload("test.dat");
  EXPECT_EQ(check_size, 9);
  auto vec_key = avl_tree.Keys();
  EXPECT_EQ(vec_key.size(), 9);
  for (int i = 1; i <= vec_key.size(); ++i) {
    EXPECT_EQ(std::to_string(i), vec_key[i - 1]);
  }
}

TEST(AVLTree, TestShowAll) {
  SelfBalancingBinarySearchTree avl_tree;

  Value value1("Ivanov", "Ivan", "2000", "Moscow", "55");
  Value value2("Petrov", "Petr", "1990", "St.Petersburg", "100");
  Value value3("Sidorov", "Sergei", "1980", "Novosibirsk", "50");
  Value value4("Vasilev", "Vasiliy", "2002", "Moscow", "150");

  EXPECT_TRUE(avl_tree.Set("key1", value1));
  EXPECT_TRUE(avl_tree.Set("key2", value2));
  EXPECT_TRUE(avl_tree.Set("key3", value3));
  EXPECT_TRUE(avl_tree.Set("key4", value4));
  EXPECT_EQ(avl_tree.ShowAll(),
            std::vector<Value>({value1, value2, value3, value4}));
}

TEST(AVLTree, UpdateTest) {
  SelfBalancingBinarySearchTree avl_tree;
  Value value1("Ivanov", "Ivan", "2000", "Moscow", "55");
  Value value2("Petrov", "Petr", "1990", "St.Petersburg", "100");
  Value value3("Sidorov", "Sergei", "1980", "Novosibirsk", "50");
  Value value4("Vasilev", "Vasiliy", "2002", "Moscow", "150");

  EXPECT_TRUE(avl_tree.Set("key1", value1));
  EXPECT_TRUE(avl_tree.Set("key2", value2));
  EXPECT_TRUE(avl_tree.Set("key3", value3));
  EXPECT_TRUE(avl_tree.Set("key4", value4));

  EXPECT_TRUE(avl_tree.Update("key1", "Pupkin Vasya 1992 Moskow 23"));

  EXPECT_TRUE(avl_tree.Update("key2", "Panov Sava - Nsk -"));

  EXPECT_TRUE(avl_tree.Get("key1").value() ==
              Value("Pupkin", "Vasya", "1992", "Moskow", "23"));

  EXPECT_TRUE(avl_tree.Get("key2").value() ==
              Value("Panov", "Sava", "1990", "Nsk", "100"));
}

TEST(AVLTree, UpdateTest2) {
  SelfBalancingBinarySearchTree avl_tree;

  Value value1("Ivanov", "Ivan", "2000", "Moscow", "55");
  Value value2("Petrov", "Petr", "1990", "St. Petersburg", "100");
  Value value3("Sidorov", "Sergei", "1980", "Novosibirsk", "50");

  EXPECT_TRUE(avl_tree.Set("key1", value1));
  EXPECT_TRUE(avl_tree.Set("key2", value2));
  EXPECT_TRUE(avl_tree.Set("key3", value3));
  EXPECT_TRUE(avl_tree.Update("key1", "- - 1999 Msk 90"));
  EXPECT_TRUE(avl_tree.Update("key2", "- - - Msk -"));
  EXPECT_TRUE(avl_tree.Update("key3", "Ivanov Ivan 2000 Moscow 55"));
  EXPECT_TRUE(avl_tree.Get("key1").value().Match("Ivanov Ivan 1999 Msk 90"));
  EXPECT_TRUE(avl_tree.Get("key2").value().Match("Petrov Petr 1990 Msk 100"));
  EXPECT_TRUE(avl_tree.Get("key3").value().Match("Ivanov Ivan 2000 Moscow 55"));
  EXPECT_FALSE(avl_tree.Update("unknown_key", "- - - - -"));
}

TEST(AVLTree, RenameTest) {
  SelfBalancingBinarySearchTree avl_tree;
  Value value1("Ivanov", "Ivan", "2000", "Moscow", "55");
  Value value2("Petrov", "Petr", "1990", "St. Petersburg", "100");
  Value value3("Sidorov", "Sergei", "1980", "Novosibirsk", "50");

  EXPECT_TRUE(avl_tree.Set("key1", value1));
  EXPECT_TRUE(avl_tree.Set("key2", value2));
  EXPECT_TRUE(avl_tree.Set("key3", value3));

  EXPECT_TRUE(avl_tree.Rename("key1", "key99"));
  EXPECT_TRUE(avl_tree.Get("key99").value() == value1);

  EXPECT_TRUE(avl_tree.Rename("key3", "asdads"));
  EXPECT_TRUE(avl_tree.Get("asdads").value() == value3);

  EXPECT_FALSE(avl_tree.Rename("unknown_key", "unknown_key"));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}