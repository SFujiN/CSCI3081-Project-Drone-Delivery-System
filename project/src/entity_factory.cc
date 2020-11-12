//
// Created by alli on 11/12/20.
//

#include "entity_factory.h"
#include "src/drone.h"
#include "src/package.h"
#include "src/customer.h"

entity_project::Entity* csci3081::EntityFactory::CreateEntity(const picojson::object& val) {
  if (val.find("type") == val.end()) return nullptr;
  auto type = val.at("type").get<std::string>();
  if (type == "drone") {
    return new Drone(val);
  } else if (type == "package") {
    return new Package(val);
  } else if (type == "customer") {
    return new Customer(val);
  } else {
    std::cerr << "Incorrect attempt to create entity with unknown type\""
              << val.at("type").get<std::string>()
              << "\"" << std::endl;
    return nullptr;
  }
}
