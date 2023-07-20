#include "self_balancing_binary_search_tree.h"

bool SelfBalancingBinarySearchTree::Set(const Key& key, const Value& value) {}

std::optional<Value> SelfBalancingBinarySearchTree::Get(const Key& key) const {}

bool SelfBalancingBinarySearchTree::Exists(const Key& key) const {}

bool SelfBalancingBinarySearchTree::Del(const Key& key) {}

bool SelfBalancingBinarySearchTree::Update(const Key& key,
                                           const std::string& value) {}

std::vector<AbstractStore::Key> SelfBalancingBinarySearchTree::Keys() const {}

bool SelfBalancingBinarySearchTree::Rename(const Key& old_key,
                                           const Key& new_key) {}

std::optional<std::size_t> SelfBalancingBinarySearchTree::TTL(
    const Key& key) const {}

std::vector<AbstractStore::Key> SelfBalancingBinarySearchTree::Find(
    const std::string& value) const {}

std::vector<Value> SelfBalancingBinarySearchTree::ShowAll() const {}

std::size_t SelfBalancingBinarySearchTree::Upload(
    const std::string& file_name) {}

std::size_t SelfBalancingBinarySearchTree::Export(
    const std::string& file_name) const {}
