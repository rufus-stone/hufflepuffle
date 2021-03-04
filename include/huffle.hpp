#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <array>
#include <vector>
#include <queue>
#include <unordered_map>

#include <spdlog/spdlog.h>

namespace hfl
{

class node_t
{
private:
  char m_value{};
  std::size_t m_count{};

  std::shared_ptr<node_t> m_lhs = nullptr;
  std::shared_ptr<node_t> m_rhs = nullptr;

public:
  node_t(char value, std::size_t count) : m_value(value), m_count(count) {}

  node_t(char value,
    std::size_t count,
    std::shared_ptr<node_t> const &lhs,
    std::shared_ptr<node_t> const &rhs) : m_value(value), m_count(count), m_lhs(lhs), m_rhs(rhs) {}

  [[nodiscard]] auto value() const -> char
  {
    return this->m_value;
  }

  [[nodiscard]] auto count() const -> std::size_t
  {
    return this->m_count;
  }

  [[nodiscard]] auto lhs() const -> std::shared_ptr<node_t>
  {
    return this->m_lhs;
  }

  [[nodiscard]] auto rhs() const -> std::shared_ptr<node_t>
  {
    return this->m_rhs;
  }

  [[nodiscard]] auto is_leaf() const -> bool
  {
    return (this->m_lhs == nullptr && this->m_rhs == nullptr);
  }
};


struct freq_ascending
{
  bool operator()(std::shared_ptr<node_t> const &lhs, std::shared_ptr<node_t> const &rhs) const
  {
    return lhs->count() > rhs->count();
  }
};

struct freq_descending
{
  bool operator()(node_t const &lhs, node_t const &rhs) const
  {
    return lhs.count() < rhs.count();
  }
};


class tree_t
{
private:
  std::string_view m_data; // The original input string

  std::unordered_map<char, std::size_t> m_freqs{}; // How frequently does each char occur?

  std::shared_ptr<node_t> m_root; // Pointer to the root node of the tree

  std::unordered_map<char, std::string> m_huff_codes{}; // Mapping of Huffman codes for each char

  std::size_t m_longest_code = 0; // Keep track of the longest Huffman code - we can use this to guestimate the max size of the output string

public:
  explicit tree_t(std::string_view input);

  void freqs(); // Print the char frequencies
  void codes(); // Print the Huffman codes

  auto encode(bool as_binary = true) -> std::string;
  auto decode() -> std::string;

  static auto traverse(std::shared_ptr<node_t> const &node, std::string const &str, std::size_t &longest_code, std::unordered_map<char, std::string> &huff_codes)
  {
    // Do nothing if node is null
    // This will happen if we reached a leaf node previously, as this has no lhs or rhs node
    if (!node)
    {
      return;
    }

    // Is this a leaf node? Add to the huff_code map if so
    if (node->is_leaf())
    {
      // If the leaf node is the only node in the branch, set it to 1 ...
      // ...otherwise set it to whatever string we've built so far
      huff_codes[node->value()] = str.empty() ? "1" : str;

      spdlog::debug("Leaf: {} == {}", node->value(), str);

      // Update the longest code if this one is bigger
      longest_code = str.size() > longest_code ? str.size() : longest_code;
    }

    // Recursively check the left and right side nodes
    // Each time we move left we add a 0 to the string, or a 1 if moving right
    traverse(node->lhs(), str + "0", longest_code, huff_codes);
    traverse(node->rhs(), str + "1", longest_code, huff_codes);
  }
};

} // namespace hfl
