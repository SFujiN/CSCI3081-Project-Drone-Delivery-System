//
// Created by alli on 11/12/20.
//

#ifndef PROJECT_ENTITY_FACTORY_H
#define PROJECT_ENTITY_FACTORY_H

#include <EntityProject/entity.h>
#include <picojson.h>
#include "src/json_helper.h"

namespace csci3081 {

/**
 * @brief a class that contains a single static function that constructs and entity from a JSON.
 * A simple concrete factory
 */
class EntityFactory {
 public:
  /**
   * @brief Create an entity that corresponds to the passed in JSON encoding
   * @return A new reference to a new entity. The caller is responsible for managing this memory.
   */
  static entity_project::Entity* CreateEntity(const picojson::object&);
};

}  // namespace csci3081

#endif  // PROJECT_ENTITY_FACTORY_H
