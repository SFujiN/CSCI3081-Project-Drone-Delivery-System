#include "src/statistics.h"

namespace csci3081 {

Statistics::Statistics() {
  // nothing yet
}

Statistics::~Statistics() {
  // nothing yet
}

void Statistics::OnEvent(const picojson::value& event, const entity_project::Entity& entity) {
  picojson::object eventobj;
  if (event.is<picojson::object>()) {
    eventobj = event.get<picojson::object>();
  } else { return; }

  std::string type = JsonHelper::GetNoFail<std::string>(eventobj, "type", "no type");
  std::string value = JsonHelper::GetNoFail<std::string>(eventobj, "value", "no value");
  // std::string name = entity.GetName();
  id = entity.GetId();
  is_idled = false;
  is_moving = false;

  if (type == "notify") {
    if (value == "scheduled") {
      // package was scheduled
    }
    if (value == "en route") {
      // package is enroute
    }
    if (value == "delivered") {
      // package was delivered
    }
    if (value == "idle") {
      // drone is idle
      // set a boolean value here to be used in Update()
      is_idled = true;
    }
    if (value == "moving") {
      // drone is moving
      is_moving = true;
      OnEventDroneMoving(event, entity);
    }
  }
}

void Statistics::OnEventDroneMoving(const picojson::value& event, const entity_project::Entity& entity) {
  // do things
}

void Statistics::Update(float dt) {
  time_elapsed += dt;

  if (is_idled) {
    drone_data[id].time_idle += dt;
  } 
  if (is_moving) {
    drone_data[id].time_moving += dt;
  }
}

}  // namespace csci3081
