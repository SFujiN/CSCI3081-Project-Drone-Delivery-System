#include "src/observable.h"
#include <vector>
#include <algorithm>

namespace csci3081 {

void Observable::Notify(const picojson::value& event) {
    for (std::vector<entity_project::EntityObserver*>::const_iterator iter = observers.begin(); iter != observers.end(); ++iter) {
        (*iter)->OnEvent(event, *entity);
    }
}

}  // namespace csci3081
