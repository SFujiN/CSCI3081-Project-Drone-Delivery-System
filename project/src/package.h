#ifndef PACKAGE_H_
#define PACKAGE_H_

#include <EntityProject/ANVIL2/package.h>
#include <EntityProject/entity_console_logger.h>
#include <vector>

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
  void NotifyScheduled() { HasBeenScheduled = true; Notify(); } //Notify();
  void NotifyDelivered() { HasBeenDelivered = true; Notify(); } //Notify(); 
  void Attach(entity_project::EntityObserver* observer) { observers.push_back(observer); }//observers.push_back(observer); }
  void Detach(entity_project::EntityObserver* observer) { observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end()); }
  void Notify();


  bool ShouldDelete() { return HasBeenDelivered; }
  bool IsDynamic() const override { return HasBeenScheduled; }

 private:
  bool HasBeenScheduled = false;
  bool HasBeenDelivered = false;
  std::vector<entity_project::EntityObserver*> observers;
};

}  // namespace csci3081
#endif
