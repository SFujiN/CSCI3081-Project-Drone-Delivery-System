#include "gtest/gtest.h"
#include "src/route_utils.h"
#include "src/test_graph.h"
#include "entity_factory.h"
#include "routing_scheduler.h"
#include "src/json_helper.h"
#include <EntityProject/project_settings.h>

#include <iostream>

namespace csci3081 {


class RoutingIntegrationTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    obj["type"] = picojson::value("drone");
    obj["position"] = picojson::value(picojson::array(
     {picojson::value(0.0),
     picojson::value(0.0),
     picojson::value(0.0)} ));
    drone = EntityFactory::CreateEntity(obj)->AsType<Drone>();

    obj["type"] = picojson::value("package");
    obj["position"] = picojson::value(picojson::array(
     {picojson::value(2.0),
     picojson::value(2.0),
     picojson::value(0.0)} ));
    package = EntityFactory::CreateEntity(obj)->AsType<Package>();

    obj["type"] = picojson::value("customer");
    obj["position"] = picojson::value(picojson::array(
     {picojson::value(1.0),
     picojson::value(1.0),
     picojson::value(5.0)} ));
    customer = EntityFactory::CreateEntity(obj)->AsType<Customer>();

    entities.push_back(drone);
    entities.push_back(package);
    entities.push_back(customer);

    n0.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n3});
    n2.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n5});
    n6.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n3,&n7});
    n8.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n7,&n5});
    n1.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n0,&n4,&n2});
    n3.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n0,&n4,&n6});
    n5.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n8,&n4,&n2});
    n7.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n6,&n4,&n8});
    n4.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n3,&n5,&n7});
    g.AddNodes(std::vector<entity_project::IGraphNode*>{&n0,&n1,&n2,&n3,&n4,&n5,&n6,&n7,&n8});

    scheduler.SetGraph(&g);
  }
  virtual void TearDown() {}

  picojson::object obj;
  Drone* drone;
  Customer* customer;
  Package* package;
  std::vector<entity_project::Entity*> entities;
  RoutingScheduler scheduler;

  TestNode n0 = TestNode("0", 0,0,0);
  TestNode n1 = TestNode("1", 1,0,0);
  TestNode n2 = TestNode("2", 2,0,0);
  TestNode n3 = TestNode("3", 0,1,0);
  TestNode n4 = TestNode("4", 1,1,0);
  TestNode n5 = TestNode("5", 2,1,0);
  TestNode n6 = TestNode("6", 0,2,0);
  TestNode n7 = TestNode("7", 1,2,0);
  TestNode n8 = TestNode("8", 2,2,0);
  TestGraph g;
};



/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(RoutingIntegrationTest, BasicRouteInt) {
  scheduler.ScheduleDelivery(package, customer, entities);

  std::vector<std::string> route_node_names = drone->GetCurrentRoute();

  for(auto name : route_node_names) {
    std::cout << name << std::endl;
  }
  ASSERT_EQ(route_node_names.size(),5);
  ASSERT_EQ(route_node_names.at(0),"0");
  ASSERT_EQ(route_node_names.at(4),"8");
}

TEST_F(RoutingIntegrationTest, SpecificRouteInt) {
  n5.SetPosition(2.5,1,0);

  n0.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n3,&n4});
  n4.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n3,&n5,&n7,&n0});

  scheduler.ScheduleDelivery(package, customer, entities);

  std::vector<std::string> route_node_names = drone->GetCurrentRoute();
  std::string routeNames = "";
  for(auto name : route_node_names) {
    std::cout << name << std::endl;
    routeNames += name;
  }
  ASSERT_EQ(routeNames,"0478");
}

TEST_F(RoutingIntegrationTest, NoRouteInt) {
  n5.SetPosition(2.5,1,0);

  n0.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n3,&n4});
  n8.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n8});
  n5.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n4,&n2});
  n7.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n6,&n4});
  n4.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n3,&n5,&n7,&n0});

  scheduler.ScheduleDelivery(package, customer, entities);

  std::vector<std::string> route_node_names = drone->GetCurrentRoute();
  std::string routeNames = "";
  for(auto name : route_node_names) {
    std::cout << name << std::endl;
    routeNames += name;
  }
  ASSERT_EQ(routeNames,"8");
}

}  // namespace csci3081
