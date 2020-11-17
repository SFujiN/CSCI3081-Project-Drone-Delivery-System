//
// Created by alli on 11/12/20.
//

#include "route_utils.h"

namespace csci3081 {

entity_project::IGraphNode* RouteManager::GetRoutePointFor(entity_project::Entity*) {
  // TODO
  // we can't instantiate IGraphNodes...I think I will repurpose this to find the closest graph node to the entity
  return nullptr;
}

float
RouteManager::GetRouteDistanceBetween(const entity_project::IGraphNode* start, const entity_project::IGraphNode* end) {
  std::vector<float> startPos = start->GetPosition();
  std::vector<float> endPos = end->GetPosition();
  return Vector3d(startPos[0],startPos[1],startPos[2]).distanceTo(Vector3d(endPos[0],endPos[1],endPos[2]));
}

std::vector<entity_project::IGraphNode*>
RouteManager::GetRoute(const entity_project::IGraphNode* start, const entity_project::IGraphNode* end) {

  return std::vector<entity_project::IGraphNode*>();
}

Vector3d RouteManager::AsVec(const entity_project::IGraphNode* node) {
  auto pos = node->GetPosition();
  return {pos[0], pos[1], pos[2]};
}

}  // namespace csci3081
