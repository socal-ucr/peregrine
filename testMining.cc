#include <iostream>

// #include "core/Options.hh"
// #include "core/utils.hh"
// #include "core/Graph.hh"
// #include "core/PatternGenerator.hh"
// #include "core/PatternMatching.hh"
#include "Peregrine.hh"

using namespace Peregrine;

SmallGraph generateCyclic(uint32_t size)
{
  std::vector<std::pair<uint32_t, uint32_t>> edge_list;
  for (uint32_t i = 1, u = 2; u <= size; i = u, ++u)
  {
    edge_list.emplace_back(i, u);
  }
  return SmallGraph(edge_list);
}

template <Graph::Labelling L = Graph::UNLABELLED, typename F>
void matchPattern(DataGraph &dg,
          const SmallGraph &p,
          F &process)
{
  std::vector<std::vector<uint32_t>> cands(p.num_vertices()+2, std::vector<uint32_t>{});
  for (auto &cand : cands) cand.reserve(10000);

  dg.set_rbi(p);
  bool has_anti_edges = dg.rbi.has_anti_edges();
  bool has_anti_vertices = !dg.rbi.anti_vertices.empty();

  uint32_t num_vertices = dg.get_vertex_count();
  uint32_t vgs_count = dg.get_vgs_count();

  if (has_anti_edges)
  {
    if (has_anti_vertices)
    {
      for (uint32_t vgsi = 0; vgsi < vgs_count; ++vgsi)
      {
        Peregrine::Matcher<true, UNSTOPPABLE, decltype(process)> m(dg.rbi, &dg, vgsi, cands, process);
        for (uint32_t v = 1; v <= num_vertices; ++v)
        {
          m.template map_into<L, true>(v);
        }
      }
    }
    else
    {
      for (uint32_t vgsi = 0; vgsi < vgs_count; ++vgsi)
      {
        Peregrine::Matcher<false, UNSTOPPABLE, decltype(process)> m(dg.rbi, &dg, vgsi, cands, process);
        for (uint32_t v = 1; v <= num_vertices; ++v)
        {
          m.template map_into<L, true>(v);
        }
      }
    }
  }
  else
  {
    if (has_anti_vertices)
    {
      for (uint32_t vgsi = 0; vgsi < vgs_count; ++vgsi)
      {
        Peregrine::Matcher<true, UNSTOPPABLE, decltype(process)> m(dg.rbi, &dg, vgsi, cands, process);
        for (uint32_t v = 1; v <= num_vertices; ++v)
        {
          m.template map_into<L, false>(v);
        }
      }
    }
    else
    {
      for (uint32_t vgsi = 0; vgsi < vgs_count; ++vgsi)
      {
        Peregrine::Matcher<false, UNSTOPPABLE, decltype(process)> m(dg.rbi, &dg, vgsi, cands, process);
        for (uint32_t v = 1; v <= num_vertices; ++v)
        {
          m.template map_into<L, false>(v);
        }
      }
    }
  }

}

int main() {
  SmallGraph topoGraph("topoGraph.txt");
  // DataGraph topoGraph(SmallGraph("topoGraph.txt"));
  std::vector<Peregrine::SmallGraph> patternToMine;
  patternToMine.emplace_back(generateCyclic(4));
  // patternToMine.emplace_back(Peregrine::PatternGenerator::star(4));

  size_t nthreads = 1;

  auto results = count(topoGraph, patternToMine, nthreads);
  
  // uint64_t num = 0;
  // const auto process = [&num](auto &&) { num += 1; };
  // matchPattern(topoGraph, patternToMine, process);

  // for (const auto &[pattern, count] : results)
  // {
  //   std::cout << pattern << ": " << count << std::endl;
  // }
  return 0;

}