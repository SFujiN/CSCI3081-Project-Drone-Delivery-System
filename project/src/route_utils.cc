//
// Created by alli on 11/12/20.
//

#include "src/route_utils.h"
#include <string>

namespace csci3081 {

entity_project::IGraphNode* RouteManager::GetRoutePointFor(entity_project::Entity* entity) {
  std::vector<float> entityPosVec = entity->GetPosition();
  Vector3d entityPos(entityPosVec[0], entityPosVec[1], entityPosVec[2]);
  std::vector<float> nodePosVec;
  entity_project::IGraphNode* bestNode = nullptr;
  float bestDist = 9e10;
  for (auto* node : graph->GetNodes()) {
    nodePosVec = node->GetPosition();
    float dist = entityPos.distanceTo(Vector3d(nodePosVec[0], nodePosVec[1], nodePosVec[2]));
    if (dist < bestDist) {
      bestNode = node;
      bestDist = dist;
    }
  }
  nodePosVec = bestNode->GetPosition();
  return bestNode;
}

float
RouteManager::GetRouteDistanceBetween(
    const entity_project::IGraphNode* start,
    const entity_project::IGraphNode* end) {
  std::vector<float> startPos = start->GetPosition();
  std::vector<float> endPos = end->GetPosition();
  return Vector3d(startPos[0], startPos[1], startPos[2])
           .distanceTo(Vector3d(endPos[0], endPos[1], endPos[2]));
}

std::vector<entity_project::IGraphNode*> RouteManager::GetRoute(
    const entity_project::IGraphNode* start,
    const entity_project::IGraphNode* end) {
  struct DijkNode {
    DijkNode() {}
    explicit DijkNode(entity_project::IGraphNode* node) : thisNode(node) {}
    entity_project::IGraphNode* thisNode = nullptr;
    entity_project::IGraphNode* prevNode = nullptr;
    float pathLength = 9999999999999;
    bool operator<(const DijkNode& other) const {
      return pathLength < other.pathLength;
    }
  };

  // Dijkstra's algorithm, copied from Wikipedia
  // it searches for the shortest route from the end to the start
  std::unordered_map<std::string, DijkNode> Q;
  std::unordered_map<std::string, DijkNode> explored;
  DijkNode u;
  for (auto i = graph->GetNodes().begin(); i != graph->GetNodes().end(); ++i) {
    Q[(*i)->GetName()] = DijkNode(*i);
  }
  Q[start->GetName()].pathLength = 0;

  while (!Q.empty()) {
    u = Q.begin()->second;
    for (auto i = Q.begin(); i != Q.end(); ++i) {
      u = (u < i->second) ? u : i->second;
    }
    if (u.thisNode->GetName() == end->GetName()) {
      std::vector<entity_project::IGraphNode*> rev_solution = {u.thisNode};
      std::vector<entity_project::IGraphNode*> solution;
      while (u.prevNode) {
        u = explored.at(u.prevNode->GetName());
        rev_solution.push_back(u.thisNode);
      }
      for (auto i = rev_solution.rbegin(); i != rev_solution.rend(); ++i) {
        solution.push_back(*i);
      }
      if ((*--solution.end())->GetName() != end->GetName()) {
        std::cout << "WARNING: Dijkstra solution does not end at desired end node"
                  << std::endl;
        std::cout << "Desired: " << end->GetName() << std::endl;
        std::cout << "Actual: " << (*--solution.end())->GetName() << std::endl;
        solution.push_back(explored.at(end->GetName()).thisNode);
      }
      return solution;
    }
    explored[u.thisNode->GetName()] = Q.at(u.thisNode->GetName());
    Q.erase(u.thisNode->GetName());
    for (const auto* node : u.thisNode->GetNeighbors()) {
      if (Q.count(node->GetName()) == 0) { continue; }
      DijkNode& v = Q.at(node->GetName());
      float altPathLength = u.pathLength + GetRouteDistanceBetween(u.thisNode, v.thisNode);
      if (altPathLength < v.pathLength) {
        v.pathLength = altPathLength;
        v.prevNode = u.thisNode;
      }
    }
  }

  std::cout << "Dijkstra didn't find a valid route" << std::endl;

  return std::vector<entity_project::IGraphNode*>();
}

Vector3d RouteManager::AsVec(const entity_project::IGraphNode* node) {
  auto pos = node->GetPosition();
  return {pos[0], pos[1], pos[2]};
}

}  // namespace csci3081
