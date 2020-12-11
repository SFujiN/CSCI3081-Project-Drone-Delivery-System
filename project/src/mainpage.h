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
 * Iteration 3 - Drone Statistics Feature Description
 * 
 * The feature our team implemented was the Drone Statistics feature. This was 
 * achieved by using a mix of the Singleton Pattern and the Drone Observer Pattern
 * (from Iteration 2). By having our statistics.h (Singleton class) inherit from 
 * EntityObserver, the Statistics instance could be added to a drone’s observer list
 * and receive information about a drone’s state during runtime. This information was
 * easily utilized to update statistics about a drone’s time spent moving, idling, or 
 * delivering, etc, based on a picojson::value event. After the simulation is 
 * run, in the destructor of DroneSimulation a call to Statistics::WriteStats()
 * is made that takes all of the statistics data stored in an unordered map and writes it
 * to a CSV file for analysis.
 *
 * \image html "Iteration 2 3081W Project UML.png" "UML diagram of the drone delivery simulation" width=120%
 */
