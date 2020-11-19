#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include <EntityProject/entity_observer.h>
#include <EntityProject/entity_console_logger.h>
#include <vector>

namespace csci3081 {

/// Class used in a composition relationship with Entity objects.
/**
 * @brief Observable class
 */
class Observable {
 public:
 /**
  * Attaches an EntityObserver* to the observer list of a subject
  * 
  * @param observer is an EntityObserver* that wants to observe this subject
  */
  void Attach(entity_project::EntityObserver* observer) { observers.push_back(observer); }

  /**
  * Detaches an EntityObserver* from the observer list of a subject
  * 
  * @param observer is an EntityObserver* that wants to be detached from this subject
  */
  void Detach(entity_project::EntityObserver* observer) {
      observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end()); }

  /**
  * Notifies all EntityObservers* of observers of an event
  * 
  * @param event is an picojson::value& that contains details for updating observers
  */
  void Notify(const picojson::value& event);

  /**
  * Sets the Entity* (Subject) of this Observable instance. The Entity* is the
  * actual subject.
  * 
  * @param e is an Entity*
  */
  void SetEntity(entity_project::Entity* e) { entity = e; }

 private:
  const entity_project::Entity* entity = nullptr;  ///< Entity* that's using the Observable functionality
  std::vector<entity_project::EntityObserver*> observers;  ///< List of observers of the subject
};

}  // namespace csci3081

#endif
