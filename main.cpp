#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <functional>
#include <algorithm>

struct edge
{
  int from;
  int to;
  int cost;
};


constexpr int Infintiy = std::numeric_limits<int>::max();

void BellmanFord(std::vector<edge>& edges, int vertexCount, int start, std::vector<int>& distances, std::vector<int>& way);

void AddEdge(std::vector<edge>& edges, int start, int end, int distance);

void AddEdges(std::vector<edge>& edges, int start, std::initializer_list<std::pair<int, int>> ends);

std::vector<int> getWayToVertex(std::vector<int> way, int start, int end);

int main()
{
  std::vector<edge> edges;
  AddEdges(edges, 0, { {1, 6}, {2, 7} });
  AddEdges(edges, 1, { {2, 8}, {3, 5}, {4, -4} });
  AddEdges(edges, 2, { {3, -3}, {4, 9} });
  AddEdges(edges, 3, { {1, -2} });
  AddEdges(edges, 4, { {3, 7}, {0, 2} });
  std::vector<int> lenght;
  std::vector<int> way;
  BellmanFord(edges, 5, 0, lenght, way);
  for (int i = 0; i < lenght.size(); i++)
  {
    std::cout << lenght[i] << " ";
  }
  std::cout << '\n';
  for (int i = 0; i < way.size(); i++)
  {
    std::cout << way[i] << " ";
  }
  std::cout << '\n';
  for (int i = 0; i < 5; i++)
  {
    for (const auto& e : getWayToVertex(way, 0, i))
    {
      std::cout << e << " ";
    }
    std::cout << '\n';
  }
}

void BellmanFord(std::vector<edge>& edges, int vertexCount, int start, std::vector<int>& distances, std::vector<int>& way) {
  distances.resize(vertexCount, Infintiy);
  way.resize(vertexCount, -1);
  distances[start] = 0;
  bool wasChanges;
  for (int i = 0; i < vertexCount - 1; ++i) {
    wasChanges = false;
    for (const auto& e : edges) {
      if (distances[e.from] != Infintiy && distances[e.from] + e.cost < distances[e.to]) {
        distances[e.to] = distances[e.from] + e.cost;
        way[e.to] = e.from;
        wasChanges = true;
      }
    }
    if (!wasChanges)
    {
      break;
    }
  }
}

void AddEdge(std::vector<edge>& edges, int start, int end, int distance) {
  edges.push_back({ start,end, distance });
}

void AddEdges(std::vector<edge>& edges, int start, std::initializer_list<std::pair<int, int>> ends) {
  for (auto i = ends.begin(); i < ends.end(); i++)
  {
    AddEdge(edges, start, i->first, i->second);
  }
}

std::vector<int> getWayToVertex(std::vector<int> way, int start, int end) {
  std::vector<int> ans;
  ans.push_back(end);
  while (start != end && end != -1)
  {
    ans.push_back(way[end]);
    end = way[end];
  }
  std::reverse(ans.begin(), ans.end());
  if (start != end) {
    return std::vector<int>();
  }
  else {
    return ans;
  }
}