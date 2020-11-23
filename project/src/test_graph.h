#ifndef TEST_GRAPH_H_
#define TEST_GRAPH_H_

#include <EntityProject/graph.h>
#include "src/route_utils.h"
#include <vector>
#include <string>
#include <unordered_map>

namespace csci3081 {
/// A class used to test RouteManager
class TestGraph : public entity_project::IGraph {
 public:
   /// Creates a node from a name
  const entity_project::IGraphNode* GetNode(const std::string& name) const override {
    return nodesmap.at(name);
  }
  /// Gets a list of nodes in the graph
  const std::vector<entity_project::IGraphNode*>& GetNodes() const override {
    return nodesvec;
  }
  /// Adds a single node
  void AddNode(entity_project::IGraphNode* node) {
    nodesvec.push_back(node);
    nodesmap[node->GetName()] = node;
  }
  /// Adds all nodes in the vector
  void AddNodes(std::vector<entity_project::IGraphNode*> nodes) {
    for (auto i = nodes.begin(); i != nodes.end(); ++i) {
      AddNode(*i);
    }
  }
 private:
  std::unordered_map<std::string, entity_project::IGraphNode*> nodesmap;
  std::vector<entity_project::IGraphNode*> nodesvec;
};

/// A testing class used by TestGraph to test RouteManager
class TestNode : public entity_project::IGraphNode {
 public:
  /// Constructs a node from a name and coordinates
  TestNode(std::string newName, float x, float y, float z) {
    name = newName;
    position = {x, y, z};
  }
  /// returns the node name
  const std::string& GetName() const override { return name; }
  /// returns the node's neighbors
  const std::vector<entity_project::IGraphNode*>& GetNeighbors() const override {return neighbors;}
  /// Gets the node position as a vector
  const std::vector<float> GetPosition() const override { return position; }
  /// Sets the coordinates of the node
  void SetPosition(float x, float y, float z) { position = {x, y, z}; }
  /// Adds a node as a neighbor
  void AddNeighbor(entity_project::IGraphNode* node) { neighbors.push_back(node); }
  /// Sets the list of neighbors to this node
  void SetNeighbors(std::vector<entity_project::IGraphNode*> nodes) { neighbors = nodes; }
 private:
  std::string name;
  std::vector<float> position;
  std::vector<entity_project::IGraphNode*> neighbors;
};

}  // namespace csci3081
#endif
