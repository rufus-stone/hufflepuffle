#include "huffle.hpp"

#include <queue>
#include <spdlog/spdlog.h>

#include <hamarr/format.hpp>

namespace hfl
{

// Constructs a Huffman tree
tree_t::tree_t(std::string_view input) : m_data(input)
{
  // Iterate through the input and count the occurances of each char
  for (char const &ch : input)
  {
    this->m_freqs[ch]++;
  }

  // Priority queue of nodes sorted by char counts
  auto pq = std::priority_queue<
    std::shared_ptr<node_t>,
    std::vector<std::shared_ptr<node_t>>,
    freq_ascending>{};

  // Populate the queue
  for (auto const &[ch, count] : this->m_freqs)
  {
    pq.push(std::make_shared<node_t>(ch, count));
  }

  // Now pop pairs of nodes off the queue until only one remains (this will be our root node)
  while (pq.size() != 1)
  {
    std::shared_ptr<node_t> const lhs = pq.top();
    pq.pop();

    std::shared_ptr<node_t> const rhs = pq.top();
    pq.pop();

    // Sum the counts of these two nodes
    std::size_t const sum = lhs->count() + rhs->count();

    // Create a new non-leaf node and add to the queue
    pq.push(std::make_shared<node_t>('\x00', sum, lhs, rhs));
  }

  // Pop the final node off the queue and use it as the root node
  std::shared_ptr<node_t> const root = pq.top();
  pq.pop();
}


void tree_t::freqs()
{
  static auto tmp = std::array<std::pair<char, std::size_t>, 256>{};

  for (auto const &[ch, count] : this->m_freqs)
  {
    tmp.at(ch).first = ch;
    tmp.at(ch).second = count;
  }

  std::sort(std::begin(tmp), std::end(tmp), [](auto const &lhs, auto const &rhs) { return lhs.second < rhs.second; });

  for (auto const &[ch, count] : tmp)
  {
    if (count > 0)
    {
      spdlog::info("{}: {}", hmr::fmt::escape(std::string(1, ch)), count);
    }
  }
}


auto tree_t::encode() -> std::string
{
  spdlog::info(this->m_data);
  return {};
}

auto tree_t::decode() -> std::string
{
  spdlog::info(this->m_data);
  return {};
}

} // namespace hfl
