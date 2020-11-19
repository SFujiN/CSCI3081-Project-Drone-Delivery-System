//
// Created by alli on 11/12/20.
//

#include "route_utils.h"

namespace csci3081 {

entity_project::IGraphNode* RouteManager::GetRoutePointFor(entity_project::Entity* entity) {
  std::vector<float> entityPosVec = entity->GetPosition();
  Vector3d entityPos(entityPosVec[0],entityPosVec[1],entityPosVec[2]);
  std::vector<float> nodePosVec;
  entity_project::IGraphNode* bestNode = nullptr;
  float bestDist = 9e10;
  for (auto* node : graph->GetNodes()) {
    nodePosVec = node->GetPosition();
    float dist = entityPos.distanceTo(Vector3d(nodePosVec[0],nodePosVec[1],nodePosVec[2]));
    if (dist < bestDist) {
      bestNode = node;
      bestDist = dist;
    }
  }
  std::cout << "Requested: " << entityPosVec[0] << ' ' << entityPosVec[1] << ' ' << entityPosVec[2] << std::endl;
  nodePosVec = bestNode->GetPosition();
  std::cout << "Found: " << nodePosVec[0] << ' ' << nodePosVec[1] << ' ' << nodePosVec[2] << std::endl;
  return bestNode;
}

float
RouteManager::GetRouteDistanceBetween(const entity_project::IGraphNode* start, const entity_project::IGraphNode* end) {
  std::vector<float> startPos = start->GetPosition();
  std::vector<float> endPos = end->GetPosition();
  return Vector3d(startPos[0],startPos[1],startPos[2]).distanceTo(Vector3d(endPos[0],endPos[1],endPos[2]));
}

std::vector<entity_project::IGraphNode*>
RouteManager::GetRoute(const entity_project::IGraphNode* start, const entity_project::IGraphNode* end) {
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
  std::unordered_map<std::string,DijkNode> Q;
  std::unordered_map<std::string,DijkNode> explored;
  DijkNode u;
  for( auto i = graph->GetNodes().begin(); i != graph->GetNodes().end(); ++i ) {
    Q[(*i)->GetName()] = DijkNode(*i);
  }
  Q[end->GetName()].pathLength = 0;

  while(!Q.empty()) {
    u = Q.begin()->second;
    for( auto i = Q.begin(); i != Q.end(); ++i ) {
      u = (u < i->second) ? u : i->second;
    }
    if( u.thisNode->GetName() == start->GetName() ) {
      std::vector<entity_project::IGraphNode*> solution = {u.thisNode};
      while(u.prevNode) {
        u = explored.at(u.prevNode->GetName());
        solution.push_back(u.thisNode);
      }
      if( (*--solution.end())->GetName() != end->GetName() ) {
        std::cout << "WARNING: Dijkstra solution does not end at desired end node" << std::endl;
        solution.push_back(explored.at(end->GetName()).thisNode);
      }
      return solution;
    }
    explored[u.thisNode->GetName()] = Q.at(u.thisNode->GetName());
    Q.erase(u.thisNode->GetName());
    for( auto v_iter = u.thisNode->GetNeighbors().begin(); v_iter != u.thisNode->GetNeighbors().end(); ++v_iter) {
      if( Q.count((*v_iter)->GetName()) == 0 ) {continue;}
      DijkNode& v = Q.at((*v_iter)->GetName());
      float altPathLength = u.pathLength + GetRouteDistanceBetween(u.thisNode, v.thisNode);
      if( altPathLength < v.pathLength ) {
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
