#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <array>
#include <vector>
#include <queue>
#include <unordered_map>

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
  std::string_view m_data;

  std::unordered_map<char, std::size_t> m_freqs{};

public:
  explicit tree_t(std::string_view input);

  void freqs();

  auto encode() -> std::string;
  auto decode() -> std::string;
};

} // namespace hfl
