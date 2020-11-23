#include "gtest/gtest.h"
#include "EntityProject/ANVIL/drone_delivery_system.h"
#include "src/drone.h"
#include "src/package.h"
#include "src/customer.h"
#include <EntityProject/project_settings.h>
#include "src/json_helper.h"
#include <EntityProject/osm_graph_parser.h>
#include "src/test_observer.h"

#include <iostream>

namespace csci3081 {

using entity_project::DroneDeliverySystem;
using entity_project::Entity;

class ObservableObserverIntegration : public ::testing::Test {
 protected:
  virtual void SetUp() {
    system = GetDroneDeliverySystem("default");
    // Create and set the graph
    entity_project::OSMGraphParser parser;
    const entity_project::IGraph* graph = parser.CreateGraph("data/umn.osm", "data/umn-height.csv");
    system->SetGraph(graph);

    obj["type"] = picojson::value("package");
    obj["name"] = picojson::value("TEST PACKAGE 1");
    obj["position"] = picojson::value(picojson::array(
        {picojson::value(1.0),
         picojson::value(2.0),
         picojson::value(3.0)}));
    package = system->CreateEntity(obj)->AsType<Package>();
    system->AddEntity(package);

    obs = new TestObserver();
  }
  virtual void TearDown() {
    delete obs;
    delete system;
  }

  DroneDeliverySystem* system;
  picojson::object obj;
  Package* package;
  TestObserver* obs;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/



TEST_F(ObservableObserverIntegration, PackageObservation) {
  system->AddObserver(package, obs);

  package->NotifyScheduled();
  EXPECT_TRUE(obs->notifiedScheduled);
  EXPECT_FALSE(obs->notifiedPickedUp);
  EXPECT_FALSE(obs->notifiedDelivered);
  EXPECT_EQ(obs->name, "TEST PACKAGE 1");

  package->DronePickUp();
  EXPECT_TRUE(obs->notifiedScheduled);
  EXPECT_TRUE(obs->notifiedPickedUp);
  EXPECT_FALSE(obs->notifiedDelivered);
  EXPECT_EQ(obs->name, "TEST PACKAGE 1");

  package->NotifyDelivered();
  EXPECT_TRUE(obs->notifiedScheduled);
  EXPECT_TRUE(obs->notifiedPickedUp);
  EXPECT_TRUE(obs->notifiedDelivered);
  EXPECT_EQ(obs->name, "TEST PACKAGE 1");
}

}  // namespace csci3081
