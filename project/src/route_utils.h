//
// Created by alli on 11/12/20.
//

#ifndef PROJECT_ROUTE_UTILS_H
#define PROJECT_ROUTE_UTILS_H

#include <EntityProject/graph.h>
#include <EntityProject/entity.h>
#include "src/vector_3d.h"
#include <unordered_map>
#include <iostream>
#include <vector>

namespace csci3081 {

/**
 * @brief A collection of functions that encapsulate routing
 *
 * This is where the implementation of dijkstra's lives, as well as allowing conversions
 * to and from graph nodes
 */
class RouteManager {
 public:
  /**
   * @brief Convert the position of an Entity into a RoutePoint.
   * @return The point corresponding to the position of the entity
   */
  entity_project::IGraphNode* GetRoutePointFor(entity_project::Entity*);

  /**
   * @brief Find the distance from one route point to another, following only known routes
   */
  float GetRouteDistanceBetween(
      const entity_project::IGraphNode* start,
      const entity_project::IGraphNode* end);

  /**
   * @brief Get the actual route between two points.
   */
  std::vector<entity_project::IGraphNode*> GetRoute(
      const entity_project::IGraphNode* start,
      const entity_project::IGraphNode* end);

  /**
   * @brief Convert a RoutePoint to a Vector3d
   */
  static Vector3d AsVec(const entity_project::IGraphNode*);
  /**
   * @brief Sets the graph that the routes are calculated on
   */
  void SetGraph(const entity_project::IGraph* g) { graph = g; }

 private:
  const entity_project::IGraph* graph;
};

}  // namespace csci3081

#endif  // PROJECT_ROUTE_UTILS_H
