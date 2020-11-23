/*! \mainpage Drone Delivery Simulation Documentation
 *
 * \section intro_sec Introduction
 *
 * This program simulates a drone package delivery system and displays the
 * realtime simulation in a webpage. The simulation is set on the
 * University of Minnesota campus and involves packages being delivered to
 * different locations on campus to fulfill delivery requests made by customers.
 *
 * The program can be built by running
 *
 * $ make
 *
 * from within the project folder.
 * The simulation can be run using
 *
 * $ ./bin/run.sh
 *
 * from within the project folder. With the simulation running, navigate to
 * http://127.0.0.1:8081/ from within a web browser to see the visualization.
 *
 * The simulation consists of three base Entity types, Drone, Customer, and
 * Package. Drones deliver Packages to Customers. All interaction with the
 * simulation should be done through the DroneSimulation facade.
 *
 * Deliveries are passed to the RoutingScheduler, which finds a drone to assign
 * the delivery to. Once a drone has been assigned the delivery, it uses functions
 * from RouteManager to calculate the route it should take.
 *
 * Drones can have different properties, specified by their model number. These
 * properties are contained in droneSpecs and are assigned by the factory.
 *
 * Drones and Packages can now be observed. This functionality is handled by the
 * Observable object.
 *
 * \image html "Iteration 2 3081W Project UML.png" "UML diagram of the drone delivery simulation" width=120%
 */
