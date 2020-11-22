#ifndef TEST_GRAPH_H_
#define TEST_GRAPH_H_

#include <EntityProject/graph.h>
#include "src/route_utils.h"
#include <vector>
#include <string>
#include <unordered_map>

namespace csci3081 {

class TestGraph : public entity_project::IGraph {
 public:
  const entity_project::IGraphNode* GetNode(const std::string& name) const override {
    return nodesmap.at(name);
  }
  const std::vector<entity_project::IGraphNode*>& GetNodes() const override {
    return nodesvec;
  }
  void AddNode(entity_project::IGraphNode* node) {
    nodesvec.push_back(node);
    nodesmap[node->GetName()] = node;
  }
  void AddNodes(std::vector<entity_project::IGraphNode*> nodes) {
    for (auto i = nodes.begin(); i != nodes.end(); ++i) {
      AddNode(*i);
    }
  }
 private:
  std::unordered_map<std::string, entity_project::IGraphNode*> nodesmap;
  std::vector<entity_project::IGraphNode*> nodesvec;
};

class TestNode : public entity_project::IGraphNode {
 public:
  TestNode(std::string newName, float x, float y, float z) {
    name = newName;
    position = {x, y, z};
  }
  const std::string& GetName() const override { return name; }
  const std::vector<entity_project::IGraphNode*>& GetNeighbors() const override {return neighbors;}
  const std::vector<float> GetPosition() const override { return position; }
  void SetPosition(float x, float y, float z) { position = {x, y, z}; }
  void AddNeighbor(entity_project::IGraphNode* node) { neighbors.push_back(node); }
  void SetNeighbors(std::vector<entity_project::IGraphNode*> nodes) { neighbors = nodes; }
 private:
  std::string name;
  std::vector<float> position;
  std::vector<entity_project::IGraphNode*> neighbors;
};

}  // namespace csci3081
#endif
