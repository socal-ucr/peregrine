#include <iostream>
#include <string>

#include "MinePattern.hh"

SmallGraph cubemesh()
{
  std::vector<std::pair<uint32_t, uint32_t>> edge_list;
  edge_list.emplace_back(1, 2);
  edge_list.emplace_back(1, 3);
  edge_list.emplace_back(1, 4);
  edge_list.emplace_back(1, 5);
  edge_list.emplace_back(2, 3);
  edge_list.emplace_back(3, 4);
  edge_list.emplace_back(4, 8);
  edge_list.emplace_back(5, 6);
  edge_list.emplace_back(5, 7);
  edge_list.emplace_back(5, 8);
  edge_list.emplace_back(6, 7);
  edge_list.emplace_back(7, 8);
  return SmallGraph(edge_list);
}

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    std::cout << argv[0] << " pattern_size\n";
    exit(0);
  }

  else
  {
    int patternSize = atoi(argv[1]);
    std::vector<Peregrine::SmallGraph> patternsToMine; // App graph

    // patternsToMine.emplace_back(PatternGenerator::ring(patternSize)); // 4 -> 1 -> 2 -> 3 -> 4
    patternsToMine.emplace_back(PatternGenerator::star(patternSize));
    

    std::cout << "\nRunning Match test\n" << std::endl;

    size_t nthreads = 1;
    // const auto callback = [](auto &&handle, auto &&match) { handle.map(match.pattern, 1); };
    const auto callback = [](auto &&handle, auto &&match) {
      handle.map(match.pattern, 1);
      utils::store_pattern(match.mapping);
    };
    auto results = match<Pattern, uint64_t, AT_THE_END, UNSTOPPABLE>(cubemesh(), patternsToMine, nthreads, callback);
    utils::print_patterns();
    auto patterns = utils::get_patterns();
    std::cout << "Psst..." << std::endl;
    for (auto pattern : patterns)
    {
      for (auto vertex_id : pattern)
      {
        std::cout << vertex_id << " ";
      }
      std::cout << std::endl;
    }
    // printResults(results);

    std::cout << "\nRunning Counts test\n" << std::endl;

    auto counts = count(cubemesh(), patternsToMine, nthreads);
    printResults(counts);
  }

  return 0;
}
