#include <iostream>

#include "core/Options.hh"
#include "core/utils.hh"
#include "core/Graph.hh"
#include "core/PatternGenerator.hh"
#include "core/PatternMatching.hh"
#include "Peregrine.hh"
#include <string>

using namespace Peregrine;

SmallGraph generateCyclic(uint32_t size)
{
  std::vector<std::pair<uint32_t, uint32_t>> edge_list;
  uint32_t init = 1;
  for (uint32_t prev = init, curr = init + 1; curr <= size; prev = curr, ++curr)
  {
    edge_list.emplace_back(prev, curr);
  }
  edge_list.emplace_back(size, init);
  for (auto &[i, j] : edge_list)
  {
    std::cout << i << j << std::endl;
  }
  return SmallGraph(edge_list);
}

int main(int argc, char **argv)
{
  if (argc < 3)
  {
    std::cout << argv[0] << " topo.txt pattern_size\n";
    exit(0);
  }

  else
  {
    std::string fileName = argv[1];
    int patternSize = atoi(argv[2]);
    std::vector<Peregrine::SmallGraph> patternsToMine; // App graph

    patternsToMine.emplace_back(generateCyclic(patternSize)); // 4 -> 1 -> 2 -> 3 -> 4

    size_t nthreads = 1;
    const auto callback = [](auto &&handle, auto &&match) { handle.map(match.pattern, 1); };
    auto results = match<Pattern, uint64_t, AT_THE_END, UNSTOPPABLE>(SmallGraph("topoGraph.txt"), patternsToMine, nthreads, callback);

    for (const auto &[pattern, tmp] : results)
    {
      std::cout << pattern << std::endl;
    }
  }

  return 0;
}