#include <iostream>

#include "Options.hh"
#include "utils.hh"
#include "Graph.hh"
#include "PatternGenerator.hh"
#include "PatternMatching.hh"
#include "Peregrine.hh"
#include <string>

using namespace Peregrine;

template <typename T>
void printResults(T results)
{
  std::cout << "Printing results: " << std::endl;
  for (const auto &[pattern, val] : results)
  {
    std::cout << pattern << " " << val << std::endl;
  }
  std::cout << "End of results" << std::endl;
}