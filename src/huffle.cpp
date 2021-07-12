#include "huffle.hpp"

#include <queue>
#include <spdlog/spdlog.h>

#include <hamarr/format.hpp>
#include <hamarr/binary.hpp>

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
  // This is a convenient way to order chars by their frequency
  auto pq = std::priority_queue<
    std::shared_ptr<node_t>,
    std::vector<std::shared_ptr<node_t>>,
    freq_ascending>{};

  // Populate the queue - this will keep the least frequent chars at the top of the queue
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

    // Sum the char counts of these two nodes
    std::size_t const sum = lhs->count() + rhs->count();

    // Create a new non-leaf node with this sum and add to the queue
    // The char value is irrelevant but we'll just set it to \x00 here
    pq.push(std::make_shared<node_t>('\x00', sum, lhs, rhs));
  }

  // Pop the final node off the queue...
  std::shared_ptr<node_t> const root = pq.top();
  pq.pop();

  // ...and set it as the root node
  this->m_root = root;

  // Now, starting at the root node, walk the tree and work out the Huffman codes for each char
  tree_t::traverse(this->m_root, std::string{}, this->m_longest_code, this->m_huff_codes);
}

// Print out the frequencies of the chars, sorted ascending
void tree_t::freqs()
{
  static auto tmp = std::array<std::pair<char, std::size_t>, 256>{};

  for (auto const &[ch, count] : this->m_freqs)
  {
    tmp.at(ch).first = ch;
    tmp.at(ch).second = count;
  }

  std::sort(std::begin(tmp), std::end(tmp), [](auto const &lhs, auto const &rhs) {
    return lhs.second < rhs.second;
  });

  for (auto const &[ch, count] : tmp)
  {
    if (count > 0)
    {
      spdlog::info("{}: {}", hmr::fmt::escape(std::string(1, ch)), count);
    }
  }
}


// Print out all the chars and their correpsonding Huffman codes
void tree_t::codes()
{
  for (const auto &[ch, code] : this->m_huff_codes)
  {
    spdlog::info("{} == {}", ch, code);
  }
}

// Generated the encoded string
auto tree_t::encode() -> std::string
{
  auto output = std::string{};

  output.reserve(this->m_longest_code * this->m_data.size()); // This will be too much memory, but can't hurt to overshoot

  // Step through the input data and append the Huffman code for the given char
  for (auto const &ch : this->m_data)
  {
    output += this->m_huff_codes[ch];
  }

  return output;
}

// TODO: Generated the decoded string
auto tree_t::decode() -> std::string
{
  auto output = std::string{};

  return output;
}

} // namespace hfl
