#include "self_balancing_binary_search_tree.h"

bool SelfBalancingBinarySearchTree::Set(const Key& key, const Value& value) {
  if (FindNode(std::move(root_), key).has_value()) return false;
  InsertHelper(root_, key, value);
  return true;
}

std::optional<Value> SelfBalancingBinarySearchTree::Get(const Key& key) const {
  auto result = FindNode(std::move(root_), key);
  if (result.has_value()) return result.value();
  return std::nullopt;
}

bool SelfBalancingBinarySearchTree::Exists(const Key& key) const {
  return FindNode(root_, key).has_value();
}

bool SelfBalancingBinarySearchTree::Del(const Key& key) {
  if (!FindNode(std::move(root_), key).has_value()) return false;
  
  return true;
}

std::optional<Value> SelfBalancingBinarySearchTree::FindNode(
    const std::unique_ptr<AVLNode>& node, const Key& key) const {
  if (node == nullptr) return std::nullopt;
  if (node->key == key) return node->value;
  if (node->key > key) {
    return FindNode(node->left, key);
  } else {
    return FindNode(node->right, key);
  }
}

void SelfBalancingBinarySearchTree::InsertHelper(std::unique_ptr<AVLNode>& node,
                                                 const Key& key,
                                                 const Value& value) {
  if (node == nullptr) {
    node = std::make_unique<AVLNode>(key, value);
    return;
  }
  if (key < node->key) {
    InsertHelper(node->left, key, value);
  } else {
    InsertHelper(node->right, key, value);
  }
}

void SelfBalancingBinarySearchTree::InOrderTraversal(
    const std::unique_ptr<AVLNode>& node, std::vector<Key>& vec_keys) const {
  if (node == nullptr) return;
  InOrderTraversal(node->left, vec_keys);
  vec_keys.push_back(node->key);
  InOrderTraversal(node->right, vec_keys);
}

const std::unique_ptr<AVLNode>& SelfBalancingBinarySearchTree::GetRoot() const {
  return root_;
}

std::vector<AbstractStore::Key> SelfBalancingBinarySearchTree::Keys() const {
  std::vector<AbstractStore::Key> vec_keys;
  InOrderTraversal(root_, vec_keys);
  return vec_keys;
}

// bool SelfBalancingBinarySearchTree::Update(const Key& key,
//                                            const std::string& value) {}

// bool SelfBalancingBinarySearchTree::Rename(const Key& old_key,
//                                            const Key& new_key) {}

// std::optional<std::size_t> SelfBalancingBinarySearchTree::TTL(
//     const Key& key) const {}

// std::vector<AbstractStore::Key> SelfBalancingBinarySearchTree::Find(
//     const std::string& value) const {}

// std::vector<Value> SelfBalancingBinarySearchTree::ShowAll() const {}

// std::size_t SelfBalancingBinarySearchTree::Upload(
//     const std::string& file_name) {}

// std::size_t SelfBalancingBinarySearchTree::Export(
//     const std::string& file_name) const {}
