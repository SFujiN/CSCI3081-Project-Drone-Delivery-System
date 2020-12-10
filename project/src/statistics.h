#ifndef STATISTICS_H_
#define STATISTICS_H_

#include <EntityProject/entity_observer.h>
#include <string>
#include <unordered_map>
#include "src/json_helper.h"

namespace csci3081 {

/**
 * @brief Statistics class
 *
 * This class
 */
class Statistics : public entity_project::EntityObserver {
private:
  /// private constructor because this is Singleton
  Statistics();
  /// single instance of this class
  static Statistics* instance;
public:
  /// returns the same instance each time
  static Statistics* GetInstance() {
    if (!instance) {
      instance = new Statistics;
    }
    return instance;
  }
  /// Destructor
  ~Statistics();
  /// called when an event occurs
  void OnEvent(const picojson::value& event, const entity_project::Entity& entity);
  /// called when a drone movement event is received
  void OnEventDroneMoving(const picojson::value& event, const entity_project::Entity& entity);
  /// called every update, used to keep track of in-simulation runtime
  void Update(float dt);
protected:
  float time_elapsed = 0;
  bool is_idled = false;
  bool is_moving = false;

  struct PackData {
    float time_scheduled;
    float time_enroute;
    float time_delivered;
  };
  struct DroneData {
    float deliveries_made;
    float time_moving;
    float time_delivering;
    float time_idle;
    float distance_traveled;
  };
  /// maps from the Entity id to their associated data
  std::unordered_map<int,PackData> package_data;
  std::unordered_map<int,DroneData> drone_data;
};

Statistics* Statistics::instance = 0;

}  // namespace csci3081

#endif
