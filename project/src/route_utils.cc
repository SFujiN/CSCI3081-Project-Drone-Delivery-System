//
// Created by alli on 11/12/20.
//

#include "route_utils.h"

namespace csci3081 {

entity_project::IGraphNode* RouteManager::GetRoutePointFor(entity_project::Entity*) {
  // TODO
  return nullptr;
}

float
RouteManager::GetRouteDistanceBetween(const entity_project::IGraphNode* start, const entity_project::IGraphNode* end) {
  // TODO
  return 0;
}

std::vector<entity_project::IGraphNode*>
RouteManager::GetRoute(const entity_project::IGraphNode* start, const entity_project::IGraphNode* end) {
  // TODO
  return std::vector<entity_project::IGraphNode*>();
}

Vector3d RouteManager::AsVec(const entity_project::IGraphNode* node) {
  auto pos = node->GetPosition();
  return {pos[0], pos[1], pos[2]};
}

}  // namespace csci3081
