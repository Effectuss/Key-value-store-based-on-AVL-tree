#include "self_balancing_binary_search_tree.h"

bool SelfBalancingBinarySearchTree::Set(const Key& key, const Value& value) {
  if (FindNode(std::move(root_), key)) return false;
  InsertHelper(root_, key, value);
  return true;
}

// std::optional<Value> SelfBalancingBinarySearchTree::Get(const Key& key) const
// {}

bool SelfBalancingBinarySearchTree::Exists(const Key& key) const {
  return FindNode(root_, key);
}

bool SelfBalancingBinarySearchTree::Del(const Key& key) {
  if (!FindNode(std::move(root_), key)) return false;
  return true;
}

// bool SelfBalancingBinarySearchTree::Update(const Key& key,
//                                            const std::string& value) {}

// std::vector<AbstractStore::Key> SelfBalancingBinarySearchTree::Keys() const
// {}

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

bool SelfBalancingBinarySearchTree::FindNode(
    const std::unique_ptr<AVLNode>& node, const Key& key) const {
  if (node == nullptr) return false;
  if (node->key == key) return true;
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