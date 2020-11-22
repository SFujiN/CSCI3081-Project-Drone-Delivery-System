//
// Created by alli on 11/12/20.
//

#include "src/entity_factory.h"
#include "src/drone.h"
#include "src/package.h"
#include "src/customer.h"
#include <string>

entity_project::Entity* csci3081::EntityFactory::CreateEntity(const picojson::object& val) {
  auto type = JsonHelper::GetNoFail<std::string>(val, "type", "No Type");
  if (type == "drone") {
    return new Drone(val);
  } else if (type == "package") {
    return new Package(val);
  } else if (type == "customer") {
    return new Customer(val);
  } else {
    std::cerr << "Incorrect attempt to create entity with unknown type\""
              << type
              << "\"" << std::endl;
    return nullptr;
  }
}
