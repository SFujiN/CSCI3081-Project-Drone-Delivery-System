#include "src/observable.h"
#include <vector>
#include <algorithm>

namespace csci3081 {

void Observable::Notify(const picojson::value& event) {
  for (auto& o : observers) {
    if (entity != nullptr) {
      o->OnEvent(event, *entity);
    }
  }
}

}  // namespace csci3081
