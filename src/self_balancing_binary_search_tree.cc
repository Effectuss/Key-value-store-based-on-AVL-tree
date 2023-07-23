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
  root_ = DeletHelper(std::move(root_), key);
  return root_ != nullptr;
}

std::unique_ptr<AVLNode> SelfBalancingBinarySearchTree::FindMin(
    std::unique_ptr<AVLNode> node) {
  while (node->left != nullptr) node = std::move(node->left);
  return node;
}

std::unique_ptr<AVLNode> SelfBalancingBinarySearchTree::FindMax(
    std::unique_ptr<AVLNode> node) {
  while (node->right != nullptr) node = std::move(node->right);
  return node;
}
std::unique_ptr<AVLNode> SelfBalancingBinarySearchTree::DeletHelper(
    std::unique_ptr<AVLNode> node, const Key& key) {
  if (node == nullptr) return nullptr;
  if (key < node->key) {
    node->left = DeletHelper(std::move(node->left), key);
  } else if (key > node->key) {
    node->right = DeletHelper(std::move(node->right), key);
  } else {
    if (node->left == nullptr || node->right == nullptr) {
      node = (node->left == nullptr) ? std::move(node->right)
                                     : std::move(node->left);
    } else {
      std::unique_ptr<AVLNode> max_node = FindMax(std::move(node->left));
      node->key = max_node->key;
      node->value = max_node->value;
      node->right = DeletHelper(std::move(node->right), max_node->key);
    }
  }
  return node;
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

void SelfBalancingBinarySearchTree::InOrderTraversalKeys(
    const std::unique_ptr<AVLNode>& node, std::vector<Key>& vec_keys) const {
  if (node == nullptr) return;
  InOrderTraversalKeys(node->left, vec_keys);
  vec_keys.push_back(node->key);
  InOrderTraversalKeys(node->right, vec_keys);
}

void SelfBalancingBinarySearchTree::InOrderTraversalValues(
    const std::unique_ptr<AVLNode>& node,
    std::vector<Value>& vec_values) const {
  if (node == nullptr) return;
  InOrderTraversalValues(node->left, vec_values);
  vec_values.push_back(node->value);
  InOrderTraversalValues(node->right, vec_values);
}

const std::unique_ptr<AVLNode>& SelfBalancingBinarySearchTree::GetRoot() const {
  return root_;
}

std::vector<AbstractStore::Key> SelfBalancingBinarySearchTree::Keys() const {
  std::vector<AbstractStore::Key> vec_keys;
  InOrderTraversalKeys(root_, vec_keys);
  return vec_keys;
}

std::vector<Value> SelfBalancingBinarySearchTree::ShowAll() const {
  std::vector<Value> vec_values;
  InOrderTraversalValues(root_, vec_values);
  return vec_values;
}

bool SelfBalancingBinarySearchTree::Update(const Key& key,
                                           const std::string& value) {}

bool SelfBalancingBinarySearchTree::Rename(const Key& old_key,
                                           const Key& new_key) {}

// std::optional<std::size_t> SelfBalancingBinarySearchTree::TTL(
//     const Key& key) const {}

// std::vector<AbstractStore::Key> SelfBalancingBinarySearchTree::Find(
//     const std::string& value) const {}

// std::size_t SelfBalancingBinarySearchTree::Upload(
//     const std::string& file_name) {}

// std::size_t SelfBalancingBinarySearchTree::Export(
//     const std::string& file_name) const {}
