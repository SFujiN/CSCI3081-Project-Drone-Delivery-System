#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include <EntityProject/entity_observer.h>
#include <EntityProject/entity_console_logger.h>
#include <vector>

namespace csci3081 {

/// TODO: Add documentation. You may edit this class including adding members or methods.
/**
 * TODO: Add detailed documentation.
 */
class Observable {
 public:
  void Attach(entity_project::EntityObserver* observer) { observers.push_back(observer); }
  void Detach(entity_project::EntityObserver* observer) {
      observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end()); }
  void Notify(const picojson::value& event);
  void SetEntity(entity_project::Entity* e) { entity = e; }
 private:
  
  const entity_project::Entity* entity = nullptr;
  std::vector<entity_project::EntityObserver*> observers;
};

}  // namespace csci3081

#endif
