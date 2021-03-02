#include <string>
#include <string_view>

#include <spdlog/spdlog.h>

#include "huffle.hpp"

using namespace std::string_view_literals;

static constexpr auto text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."sv;

int main()
{
  auto coder = hfl::tree_t{text};

  coder.freqs();

  coder.encode();

  return EXIT_SUCCESS;
}
