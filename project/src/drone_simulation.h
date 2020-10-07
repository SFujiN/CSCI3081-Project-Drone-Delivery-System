#ifndef DRONE_SIMULATION_H_
#define DRONE_SIMULATION_H_

/*! \mainpage CSCI 3081 - Support Code
 * [TOC]
 * \section intro_sec Introduction
 *
 * This is the support code documentation for the CSCI 3081 - Drone Delivery Project for Fall 2020, sections 10 and 20.
 * Please review the <a href="https://pages.github.umn.edu/umn-csci-3081-f20/project-portal/Iteration1Requirements.pdf">specification</a>
 * for more details about Iteration 1 of Project ANVIL.  Developers should review the <a href="annotated.html">class documentation</a> as well as
 * the <a href="files.html">header file interfaces</a> for this system.
 * \subsection link_sec Quick Links
 * <ul>
 *  <li><a href="https://pages.github.umn.edu/umn-csci-3081-f20/project-portal/Iteration1Requirements.pdf">Iteration 1</a> - Specification for Project ANVIL</li>
 * 	<li><a href="annotated.html">Classes</a> - Support code classes.</li>
 * 	<li><a href="files.html">Files</a> - Structure of project header files.</li>
 * </ul>
 *
 * \section getting_started_sec Getting Started
 *
 * The project centers around implementing the facade entity_project::DroneDeliverySystem.  It is recommended that new developers start by understanding this
 * class and its functions.  The functions themselves need to be implemented inside of the csci3081::DroneSimulation class.  All drones, customers, and packages
 * extend the entity_project::Entity class, which has basic information about position, direction, and size.  This is used inside the visualization.
 *
 * For this project it is important to learn how to cast to your types using the entity_project::TypedObject::AddType<T>() and entity_project::TypedObject::AsType<T>()
 * methods so that you can change entities into your types efficiently in C++ when implementing the facade.  Below is example code to illustrate the usage of AsType() and AddType():
 * \code{.cpp}
 * class MyDrone : entity_project::Entity {
 * public:
 *   MyDrone() { AddType<MyDrone>(); }
 * };
 *
 * //...
 *
 * Entity* entity = CreateEntity();
 * MyDrone* drone = entity->AsType<MyDrone>();
 * if (drone) {
 *   // Is a MyDrone type
 * }
 * else {
 *   // Is not a MyDrone type
 * }
 * \endcode
 *
 * \subsection building_sec Build and Run
 *
 * Start by building the environment:
 * \code{.sh}
 * ./bin/build-env.sh
 * \endcode
 *
 * Then navigate to the project directory to build and run:
 * \code{.sh}
 * cd project
 * make
 * ./bin/run-env.sh
 * \endcode
 *
 * \subsection uml_sec UML Diagram
 * <a href="https://z.umn.edu/uml_iteration1">Lucidchart Template</a>
 * <img src="https://pages.github.umn.edu/umn-csci-3081-f20/project-portal/images/UML.png">
 */

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
