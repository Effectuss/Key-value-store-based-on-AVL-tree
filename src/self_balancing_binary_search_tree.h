#ifndef __SELF_BALANCING_BINARY_SEARCH_TREE_H__
#define __SELF_BALANCING_BINARY_SEARCH_TREE_H__

#include <memory>

#include "abstract_store.h"

class SelfBalancingBinarySearchTree : public AbstractStore {
 public:
  bool Set(const Key& key, const Value& value) override;
  std::optional<Value> Get(const Key& key) const override;
  bool Exists(const Key& key) const override;
  bool Del(const Key& key) override;
  bool Update(const Key& key, const std::string& value) override;
  std::vector<Key> Keys() const override;
  bool Rename(const Key& old_key, const Key& new_key) override;
  std::optional<std::size_t> TTL(const Key& key) const override;
  std::vector<Key> Find(const std::string& value) const override;
  std::vector<Value> ShowAll() const override;
  std::size_t Upload(const std::string& file_name) override;
  std::size_t Export(const std::string& file_name) const override;

 private:
  struct AVLNode {
    AbstractStore::Key key;
    Value value;
    std::unique_ptr<AVLNode> left;
    std::unique_ptr<AVLNode> right;
    int height = 0;
  };
  std::unique_ptr<AVLNode> root_;
};

#endif  // __SELF_BALANCING_BINARY_SEARCH_TREE_H__