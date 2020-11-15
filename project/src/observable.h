#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include <EntityProject/ANVIL2/entity_observer.h>
#include <vector>

namespace csci3081 {

/// TODO: Add documentation. You may edit this class including adding members or methods.
/**
 * TODO: Add detailed documentation.
 */
class Observable {
 public:
  void Attach(const entity_project::EntityObserver* observer) { observers.push_back(observer); }
  void Detach(const entity_project::EntityObserver* observer) {
      observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end()); }
  void Notify(const picojson::value& event);
 private:
  std::vector<const entity_project::EntityObserver*> observers;
};

}  // namespace csci3081

#endif
