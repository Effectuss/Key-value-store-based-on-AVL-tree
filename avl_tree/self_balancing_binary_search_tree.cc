#include "self_balancing_binary_search_tree.h"

bool SelfBalancingBinarySearchTree::Set(const Key& key, const Value& value) {
  if (FindNode(root_, key).has_value()) return false;
  InsertHelper(root_, key, value);
  return true;
}

std::optional<Value> SelfBalancingBinarySearchTree::Get(const Key& key) const {
  auto result = FindNode(root_, key);
  if (result.has_value()) {
    return result.value()->value;
  }
  return std::nullopt;
}

bool SelfBalancingBinarySearchTree::Exists(const Key& key) const {
  return FindNode(root_, key).has_value();
}

bool SelfBalancingBinarySearchTree::Del(const Key& key) {
  if (!FindNode(root_, key).has_value()) return false;
  root_ = DeletHelper(std::move(root_), key);
  return true;
}

const SelfBalancingBinarySearchTree::AVLNode*
SelfBalancingBinarySearchTree::FindMin(const AVLNode* node) const {
  while (node->left) {
    node = node->left.get();
  }
  return node;
}

std::unique_ptr<SelfBalancingBinarySearchTree::AVLNode>
SelfBalancingBinarySearchTree::DeletHelper(std::unique_ptr<AVLNode> node,
                                           const Key& key) {
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
      const AVLNode* min_right = FindMin(node->right.get());
      node->key = min_right->key;
      node->value = min_right->value;
      node->right = DeletHelper(std::move(node->right), min_right->key);
    }
  }
  if (node != nullptr) {
    UpdateHeight(node);
    BalanceNode(node);
  }
  return node;
}

std::optional<SelfBalancingBinarySearchTree::AVLNode*>
SelfBalancingBinarySearchTree::FindNode(const std::unique_ptr<AVLNode>& node,
                                        const Key& key) const {
  if (node == nullptr) return std::nullopt;
  if (node->key == key) return node.get();
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
  UpdateHeight(node);
  BalanceNode(node);
}

void SelfBalancingBinarySearchTree::InOrderTraversal(
    const std::unique_ptr<AVLNode>& node, std::vector<AbstractStore::Key>& keys,
    std::vector<Value>& values) const {
  if (node == nullptr) return;
  InOrderTraversal(node->left, keys, values);
  keys.push_back(node->key);
  values.push_back(node->value);
  InOrderTraversal(node->right, keys, values);
}

std::vector<AbstractStore::Key> SelfBalancingBinarySearchTree::Keys() const {
  std::vector<AbstractStore::Key> vec_keys;
  std::vector<Value> vec_values;
  InOrderTraversal(root_, vec_keys, vec_values);
  return vec_keys;
}

std::vector<Value> SelfBalancingBinarySearchTree::ShowAll() const {
  std::vector<Value> vec_values;
  std::vector<AbstractStore::Key> vec_keys;
  InOrderTraversal(root_, vec_keys, vec_values);
  return vec_values;
}

bool SelfBalancingBinarySearchTree::Update(const Key& key,
                                           const std::string& new_value) {
  auto node = FindNode(root_, key);
  if (!node.has_value()) return false;
  node.value()->value.Update(new_value);
  return true;
}

bool SelfBalancingBinarySearchTree::Rename(const Key& old_key,
                                           const Key& new_key) {
  auto node = FindNode(root_, old_key);
  if (!node.has_value()) return false;
  Value tmp_val = node.value()->value;
  Del(old_key);
  return Set(new_key, tmp_val);
}

std::size_t SelfBalancingBinarySearchTree::Upload(
    const std::string& file_name) {
  std::ifstream file(file_name);
  if (!file.is_open()) throw std::invalid_argument("File can't be opened");
  Key read_key;
  std::string read_value;
  std::size_t count_keys = 0;
  while (file >> read_key) {
    std::getline(file >> std::ws, read_value);
    Set(read_key, Value::FromString(read_value));
    ++count_keys;
  }
  file.close();
  return count_keys;
}

std::size_t SelfBalancingBinarySearchTree::Export(
    const std::string& file_name) const {
  std::ofstream file(file_name);
  if (!file.is_open()) throw std::invalid_argument("File can't be opened");

  std::size_t count_keys = 0;
  auto keys = Keys();
  auto values = ShowAll();
  for (auto i = 0u; i < keys.size(); ++i) {
    file << keys[i] << " " << values[i].ToQuotedString() << "\n";
    ++count_keys;
  }
  file.close();
  return count_keys;
}

std::optional<std::size_t> SelfBalancingBinarySearchTree::TTL(
    const Key& key) const {
  auto node = FindNode(root_, key);
  if (!node.has_value()) return std::nullopt;
  return node.value()->value.TTL();
}

std::vector<AbstractStore::Key> SelfBalancingBinarySearchTree::Find(
    const std::string& value) const {
  std::vector<Key> result_match;
  std::vector<Key> keys = Keys();
  std::vector<Value> value_storage = ShowAll();
  for (auto i = 0u; i < keys.size(); ++i) {
    if (value_storage[i].Match(value)) {
      result_match.push_back(keys[i]);
    }
  }
  return result_match;
}

int SelfBalancingBinarySearchTree::GetHeight(
    const std::unique_ptr<AVLNode>& node) const {
  return (node == nullptr) ? -1 : node->height;
}

void SelfBalancingBinarySearchTree::UpdateHeight(
    std::unique_ptr<AVLNode>& node) {
  node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
}

int SelfBalancingBinarySearchTree::GetBalance(
    const std::unique_ptr<AVLNode>& node) const {
  return (node == nullptr) ? 0 : GetHeight(node->right) - GetHeight(node->left);
}

void SelfBalancingBinarySearchTree::RotateLeft(std::unique_ptr<AVLNode>& node) {
  std::unique_ptr<AVLNode> buffer = std::move(node->right);
  node->right = std::move(buffer->left);
  buffer->left = std::move(node);
  node = std::move(buffer);
  UpdateHeight(node->left);
  UpdateHeight(node);
}

void SelfBalancingBinarySearchTree::RotateRight(
    std::unique_ptr<AVLNode>& node) {
  std::unique_ptr<AVLNode> buffer = std::move(node->left);
  node->left = std::move(buffer->right);
  buffer->right = std::move(node);
  node = std::move(buffer);
  UpdateHeight(node->right);
  UpdateHeight(node);
}

void SelfBalancingBinarySearchTree::BalanceNode(
    std::unique_ptr<AVLNode>& node) {
  if (GetBalance(node) == -2) {
    if (GetBalance(node->left) > 0) {
      RotateLeft(node->left);
    }
    RotateRight(node);
  } else if (GetBalance(node) == 2) {
    if (GetBalance(node->right) < 0) {
      RotateRight(node->right);
    }
    RotateLeft(node);
  }
}

void SelfBalancingBinarySearchTree::MakeDotFile(
    const std::string& file_name) const {
  std::ofstream file;
  file.open(file_name + ".dot", std::ios::trunc);
  if (!file.is_open()) throw std::invalid_argument("File can't be opened");
  file << "digraph BST {\n";
  file << "    node [shape=circle, style=filled, fillcolor=green];\n";
  std::function<void(const std::unique_ptr<AVLNode>& node)> writeNodes =
      [&](const std::unique_ptr<AVLNode>& node) {
        if (node == nullptr) {
          return;
        }
        file << "    " << node->key << ";\n";
        if (node->left != nullptr) {
          file << "    " << node->key << " -> " << node->left->key << ";\n";
          writeNodes(node->left);
        }
        if (node->right != nullptr) {
          file << "    " << node->key << " -> " << node->right->key << ";\n";
          writeNodes(node->right);
        }
      };
  writeNodes(root_);
  file << "}";
  file.close();
}

int SelfBalancingBinarySearchTree::GetBalance(const Key& key) const {
  auto node = FindNode(root_, key);
  return (node.value() == nullptr)
             ? 0
             : GetHeight(node.value()->right) - GetHeight(node.value()->left);
}

int SelfBalancingBinarySearchTree::GetHeight(const AVLNode* node) const {
  return (node == nullptr) ? -1 : node->height;
}

const AbstractStore::Key SelfBalancingBinarySearchTree::GetRootKey() const {
  if (root_ == nullptr) return "";
  return root_->key;
}

void SelfBalancingBinarySearchTree::DeleteExpiredElements() {
  root_ = std::move(DeleteExpiredElementsHelper(root_));
}

std::unique_ptr<SelfBalancingBinarySearchTree::AVLNode>&
SelfBalancingBinarySearchTree::DeleteExpiredElementsHelper(
    std::unique_ptr<AVLNode>& node) {
  if (node == nullptr) {
    return node;
  } else if (node->value.TTL() == std::nullopt) {
    return node;
  } else if (node->value.TTL() == 0u) {
    node = DeletHelper(std::move(node), node->key);
    return node;
  }
  DeleteExpiredElementsHelper(node->left);
  DeleteExpiredElementsHelper(node->right);
  return node;
}
