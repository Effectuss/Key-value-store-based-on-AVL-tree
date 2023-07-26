#include <gtest/gtest.h>

#include <cmath>

#include "self_balancing_binary_search_tree.h"

TEST(AVLTree, SetEmptyTree) {
  SelfBalancingBinarySearchTree avl_tree;
  Value val("Pupkin", "Vasya", "1992", "Moskow", "23");
  EXPECT_TRUE(avl_tree.Set("10", val));
}

TEST(AVLTree, SetTwoElements) {
  SelfBalancingBinarySearchTree avl_tree;
  Value val("Pupkin", "Vasya", "1992", "Moskow", "23");
  EXPECT_TRUE(avl_tree.Set("10", val));
  EXPECT_TRUE(avl_tree.Set("5", val));
}

TEST(AVLTree, SetFourElements) {
  SelfBalancingBinarySearchTree avl_tree;
  Value val("Pupkin", "Vasya", "1992", "Moskow", "23");
  EXPECT_TRUE(avl_tree.Set("v", val));
  EXPECT_TRUE(avl_tree.Set("d", val));
  EXPECT_TRUE(avl_tree.Set("z", val));
  EXPECT_TRUE(avl_tree.Set("a", val));
}

TEST(AVLTree, CheckBalance) {
  SelfBalancingBinarySearchTree avl_tree;
  Value val("Pupkin", "Vasya", "1992", "Moskow", "23");
  EXPECT_TRUE(avl_tree.Set("v", val));
  EXPECT_TRUE(avl_tree.Set("d", val));
  EXPECT_TRUE(avl_tree.Set("z", val));
  EXPECT_TRUE(avl_tree.Set("a", val));
  EXPECT_TRUE(std::abs(avl_tree.GetBalance("v")) <= 1);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}