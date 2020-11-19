#ifndef PACKAGE_H_
#define PACKAGE_H_

#include <EntityProject/ANVIL2/package.h>
#include <EntityProject/entity_console_logger.h>
#include "src/observable.h"
#include <vector>

namespace csci3081 {

/// Represents a package in the drone system.
/**
 * @brief Package class
 */
class Package : public entity_project::Package {
 public:
  /// @brief Default package constructor
  Package() { AddType<Package>(); }
  /**
   * @brief Create a Package from the JSON encoding.
   */
  explicit Package(const picojson::object&);
  /// Provides the package weight
  float GetWeight() const override;

  /**
  * Tell the drone that it has been picked up so it becomes dynamic.
  * Call's Notify from Observable& to notify observers that package is
  * scheduled.
  */
  void NotifyScheduled();
  /**
  * Called when package has been delivered, and sets HasBeenDelivered
  * to true. Call's Notify from Observable& to notify observers that package is
  * delivered.
  */
  void NotifyDelivered();
  /**
  * Called when package has been picked up. Call's Notify from Observable&
  * to notify observers that package is picked up and en route.
  */
  void NotifyPickedUp();
  /**
  * Retrieves a Package's Observable reference to call functions
  * related to the subject of an observer pattern. 
  * 
  * @return Observable object reference. Returns packageObservable
  */
  Observable& GetObservable() { return packageObservable; }

  bool ShouldDelete() { return HasBeenDelivered; }
  bool IsDynamic() const override { return HasBeenScheduled; }

 private:
  bool HasBeenScheduled = false;  ///< boolean to track scheduled state
  bool HasBeenDelivered = false;  ///< boolean to track delivered state
  Observable packageObservable;  ///< Calls subject functionality
};

}  // namespace csci3081
#endif
