#include <spdlog/spdlog.h>

#include "blah.hpp"

int main()
{
  spdlog::info("Hello!");

  example::do_thing();

  return EXIT_SUCCESS;
}
