#include "gtest/gtest.h"
#include "src/route_utils.h"
#include "src/test_graph.h"
#include <EntityProject/project_settings.h>

#include <iostream>

namespace csci3081 {

class RouteManagerTest : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}

};



/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(RouteManagerTest, RouteDistanceBetween) {
  RouteManager rm;
  TestNode a("A", 0,0,0);
  TestNode b("B", 0,0,0);

  ASSERT_FLOAT_EQ(rm.GetRouteDistanceBetween(&a,&b),0);

  a.SetPosition(1,4,8);
  b.SetPosition(0,0,0);
  ASSERT_FLOAT_EQ(rm.GetRouteDistanceBetween(&a,&b),9);

  a.SetPosition(0,0,0);
  b.SetPosition(-1,4,8);
  ASSERT_FLOAT_EQ(rm.GetRouteDistanceBetween(&a,&b),9);

  a.SetPosition(2,-1,-5);
  b.SetPosition(2-14,-1+3,-5-18);
  ASSERT_FLOAT_EQ(rm.GetRouteDistanceBetween(&a,&b),23);

  a.SetPosition(-49.32,32.515,-60.005);
  b.SetPosition(-49.32+30,32.515-240,-60.005+160);
  ASSERT_FLOAT_EQ(rm.GetRouteDistanceBetween(&a,&b),290);
}

TEST_F(RouteManagerTest, BasicRoute) {
  RouteManager rm;
  TestNode n0("0", 0,0,0);
  TestNode n1("1", 1,0,0);
  TestNode n2("2", 2,0,0);
  TestNode n3("3", 0,1,0);
  TestNode n4("4", 1,1,0);
  TestNode n5("5", 2,1,0);
  TestNode n6("6", 0,2,0);
  TestNode n7("7", 1,2,0);
  TestNode n8("8", 2,2,0);
  TestGraph g;

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

  rm.SetGraph(&g);
  std::vector<entity_project::IGraphNode*> route = rm.GetRoute(&n0,&n8);

  for(auto i = route.begin(); i != route.end(); ++i) {
    std::cout << (*i)->GetName() << std::endl;
  }
  ASSERT_EQ(route.size(),5);
  ASSERT_EQ(route.at(0)->GetName(),"0");
  ASSERT_EQ(route.at(4)->GetName(),"8");
}

TEST_F(RouteManagerTest, SpecificRoute) {
  RouteManager rm;
  TestNode n0("0", 0,0,0);
  TestNode n1("1", 1,0,0);
  TestNode n2("2", 2,0,0);
  TestNode n3("3", 0,1,0);
  TestNode n4("4", 1,1,0);
  TestNode n5("5", 2,1,0);
  TestNode n6("6", 0,2,0);
  TestNode n7("7", 1,2,0);
  TestNode n8("8", 1.5,5,0);
  TestGraph g;

  n0.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n3,&n4});
  n2.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n5});
  n6.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n3,&n7});
  n8.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n7,&n5});
  n1.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n0,&n4,&n2});
  n3.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n0,&n4,&n6});
  n5.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n8,&n4,&n2});
  n7.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n6,&n4,&n8});
  n4.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n3,&n5,&n7,&n0});

  g.AddNodes(std::vector<entity_project::IGraphNode*>{&n0,&n1,&n2,&n3,&n4,&n5,&n6,&n7,&n8});

  rm.SetGraph(&g);
  std::vector<entity_project::IGraphNode*> route = rm.GetRoute(&n0,&n8);

  std::string routeNames = "";
  for(auto i = route.begin(); i != route.end(); ++i) {
    std::cout << (*i)->GetName() << std::endl;
    routeNames += (*i)->GetName();
  }
  ASSERT_EQ(routeNames,"0478");
}

TEST_F(RouteManagerTest, NoRoute) {
  RouteManager rm;
  TestNode n0("0", 0,0,0);
  TestNode n1("1", 1,0,0);
  TestNode n2("2", 2,0,0);
  TestNode n3("3", 0,1,0);
  TestNode n4("4", 1,1,0);
  TestNode n5("5", 2,1,0);
  TestNode n6("6", 0,2,0);
  TestNode n7("7", 1,2,0);
  TestNode n8("8", 1.5,5,0);
  TestGraph g;

  n0.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n3,&n4});
  n2.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n5});
  n6.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n3,&n7});
  n8.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n8});
  n1.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n0,&n4,&n2});
  n3.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n0,&n4,&n6});
  n5.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n4,&n2});
  n7.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n6,&n4});
  n4.SetNeighbors(std::vector<entity_project::IGraphNode*>{&n1,&n3,&n5,&n7,&n0});

  g.AddNodes(std::vector<entity_project::IGraphNode*>{&n0,&n1,&n2,&n3,&n4,&n5,&n6,&n7,&n8});

  rm.SetGraph(&g);
  std::vector<entity_project::IGraphNode*> route = rm.GetRoute(&n0,&n8);

  std::string routeNames = "";
  for(auto i = route.begin(); i != route.end(); ++i) {
    std::cout << (*i)->GetName() << std::endl;
    routeNames += (*i)->GetName();
  }
  ASSERT_EQ(routeNames,"8");
}

}  // namespace csci3081
