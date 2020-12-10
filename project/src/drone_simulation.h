#ifndef DRONE_SIMULATION_H_
#define DRONE_SIMULATION_H_

#include <EntityProject/ANVIL/drone_delivery_system.h>
#include <vector>
#include <string>
#include "src/json_helper.h"
#include "src/entity_factory.h"
#include "src/routing_scheduler.h"
#include "src/drone_pool.h"
#include <EntityProject/entity_console_logger.h>

namespace csci3081 {


/// The abstract facade of a drone delivery subsystem.
class DroneSimulation : public entity_project::DroneDeliverySystem {
 public:
  ~DroneSimulation() override;
  /// Returns the team name for the drone system.
  const std::string& GetTeamName() const { return teamName_; }

  /// Creates an entity based on a JSON object passed in.
  entity_project::Entity* CreateEntity(const picojson::object& val) {
    // Investigate json object that is passed in
    JsonHelper::PrintKeyValues(val);
    // csci3081::updateDroneModelList(models_, "data/planet-x.csv");
    return EntityFactory::CreateEntity(val);
  }

  /// Register the entity with the system.
  void AddEntity(entity_project::Entity* entity) {
    // Console Observer
    static entity_project::EntityConsoleLogger logger;
    AddObserver(entity, &logger);
    AddObserver(entity, Statistics::GetInstance());
    entities_.push_back(entity);
  }

#ifdef ANVIL2
  /// Adds the graph used for dynamic routing in the delivery system.
  void SetGraph(const entity_project::IGraph* graph) { scheduler.SetGraph(graph); }
#endif

  /**
   * @brief Schedule a drone delivery for a package to be delivered to a customer.
   * Details allows extra specifications for package delivery based on the business needs.
   */
  void ScheduleDelivery(entity_project::Package* package,
                        entity_project::Customer* dest, const picojson::object& details) {
    scheduler.ScheduleDelivery(
        package->AsType<Package>(),
        dest->AsType<Customer>(),
        entities_,
        details);
  }

  /// Add an observer to a specific entity.
  void AddObserver(entity_project::Entity* entity, entity_project::EntityObserver* observer) {
    csci3081::Package* p = entity->AsType<Package>();
    csci3081::Drone* d = entity->AsType<Drone>();
    if (p != nullptr) {
      p->GetObservable().Attach(observer);
    }
    if (d != nullptr) {
      d->GetObservable().Attach(observer);
    }
  }

  /// Remove an observer from a specific entity.
  void RemoveObserver(entity_project::Entity* entity, entity_project::EntityObserver* observer) {
    csci3081::Package* p = entity->AsType<Package>();
    csci3081::Drone* d = entity->AsType<Drone>();
    if (p != nullptr) {
      p->GetObservable().Detach(observer);
    }
    if (d != nullptr) {
      d->GetObservable().Detach(observer);
    }
  }

  /// Returns all the entities that are added to the drone system.
  const std::vector<entity_project::Entity*>& GetEntities() const { return entities_; }

  /// Updates the drone system time by dt.
  void Update(float dt);

 private:
  std::string teamName_;
  std::vector<entity_project::Entity*> entities_;
  /**
   * @brief The simulation's routing manager.
   * This is called whenever a new delivery is scheduled and must be routed.
   */
  csci3081::RoutingScheduler scheduler;
};

}  // namespace csci3081


#endif  // DRONE_SIMULATION_H_
