#ifndef TEST_OBSERVER_H_
#define TEST_OBSERVER_H_

#include <EntityProject/entity_observer.h>
#include <string>
#include "src/json_helper.h"

namespace csci3081 {

/// Class used to test Observable class
class TestObserver : public entity_project::EntityObserver {
 public:
  /// called when an event occurs
  void OnEvent(const picojson::value& event, const entity_project::Entity& entity) {
    picojson::object eventobj;
    if (event.is<picojson::object>()) {
      eventobj = event.get<picojson::object>();
    } else { return; }

    std::string type = JsonHelper::GetNoFail<std::string>(eventobj, "type", "no type");
    std::string value = JsonHelper::GetNoFail<std::string>(eventobj, "value", "no value");
    name = entity.GetName();

    if (type == "notify") {
      if (value == "scheduled") {
        notifiedScheduled = true;
      }
      if (value == "en route") {
        notifiedPickedUp = true;
      }
      if (value == "delivered") {
        notifiedDelivered = true;
      }
    }
  }

  bool notifiedScheduled = false;
  bool notifiedPickedUp = false;
  bool notifiedDelivered = false;

  std::string name;
};

}  // namespace csci3081

#endif
