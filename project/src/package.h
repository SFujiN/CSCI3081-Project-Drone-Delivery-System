#ifndef PACKAGE_H_
#define PACKAGE_H_

#include <EntityProject/ANVIL2/package.h>
#include "src/customer.h"

namespace csci3081 {

/// TODO: Add documentation. You may edit this class including adding members or methods.
/**
 * TODO: Add detailed documentation.
 */
class Package : public entity_project::Package {
 public:
  /// TODO: Add documentation.
  Package() { AddType<Package>(); }
  /**
   * @brief Create a Package from the JSON encoding.
   */
  explicit Package(const picojson::object&);
  /// Provides the package weight
  float GetWeight() const override;

  /// Tell the drone that it has been picked up so it becomes dynamic
  void NotifyScheduled() { HasBeenScheduled = true; }
  void NotifyDelivered() { HasBeenDelivered = true; }

  bool ShouldDelete() { return HasBeenDelivered; }
  bool IsDynamic() const override { return HasBeenScheduled; }

  /// Sets a destination Customer
  void SetDestination(Customer* customer) {
    dest = customer;
  }
  /// Gets the Customer to be delivered to
  Customer* GetDestination() {
    return dest;
  }

 private:
  bool HasBeenScheduled = false;
  bool HasBeenDelivered = false;
  Customer* dest;
};

}  // namespace csci3081
#endif
