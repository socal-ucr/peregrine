#include <iostream>
#include <vector>
#include <unordered_map>
#include <sys/types.h>
#include <set>

#include "utils.hh"

namespace utils
{
std::vector<std::vector<uint32_t>> foundPatterns; //populate this with match.mapping.

std::mutex logging_mutex;

timestamp_t get_timestamp() {
  struct timeval now;
  gettimeofday (&now, NULL);
  return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

void store_pattern(std::vector<uint32_t> v)
{
    foundPatterns.emplace_back(v);
}

void print_patterns()
{
    std::cout << "Printing found patterns" << std::endl;
    for (auto pattern : foundPatterns)
    {
        for (auto vertex_id : pattern)
        {
            std::cout << vertex_id << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<uint32_t>> get_patterns()
{
  return foundPatterns;
}

void clear_patterns()
{
    foundPatterns.clear();
}

} // namespace utils
