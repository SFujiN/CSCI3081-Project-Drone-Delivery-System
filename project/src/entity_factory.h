//
// Created by alli on 11/12/20.
//

#ifndef PROJECT_ENTITY_FACTORY_H
#define PROJECT_ENTITY_FACTORY_H

#include <EntityProject/entity.h>
#include <picojson.h>

namespace csci3081 {

class EntityFactory {
 public:
  /**
   * @brief Create an entity that corresponds to the passed in JSON encoding
   * @return A new reference to a new entity. The caller is responsible for managing this memory.
   * This should probably just return the entity itself and allow move semantics to optimize the returning process, but no.
   */
  static entity_project::Entity* CreateEntity(const picojson::object&);
};

}  // namespace csci3081;

#endif //PROJECT_ENTITY_FACTORY_H
