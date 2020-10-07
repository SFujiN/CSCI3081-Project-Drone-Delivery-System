#ifndef DRONE_SIMULATION_H_
#define DRONE_SIMULATION_H_


#include <EntityProject/ANVIL/drone_delivery_system.h>
#include <vector>
#include <string>
namespace csci3081 {


/// TODO: Add documentation. You may edit this class including adding members or methods.
/**
 * TODO: Add detailed documentation.
 */
class DroneSimulation : public entity_project::DroneDeliverySystem {
 public:
  /// TODO: Add documentation.
  const std::string& GetTeamName() const { return teamName_; }

  /// TODO: Add documentation.
  entity_project::Entity* CreateEntity(const picojson::object& val) { return NULL; }

  /// TODO: Add documentation.
  void AddEntity(entity_project::Entity* entity) {}

  /// TODO: Add documentation.
  void ScheduleDelivery(entity_project::Package* package,
    entity_project::Customer* dest, const picojson::object& details) {}

  /// TODO: Add documentation.
  void AddObserver(entity_project::Entity* entity, entity_project::EntityObserver* observer) {}

  /// TODO: Add documentation.
  void RemoveObserver(entity_project::Entity* entity, entity_project::EntityObserver* observer) {}

  /// TODO: Add documentation.
  const std::vector<entity_project::Entity*>& GetEntities() const { return entities_; }

  /// TODO: Add documentation.
  void Update(float dt) {}

 private:
  std::string teamName_;
  std::vector<entity_project::Entity*> entities_;
};

}  // namespace csci3081


#endif  // DRONE_SIMULATION_H_
