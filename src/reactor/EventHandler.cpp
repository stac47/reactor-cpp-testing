#include "EventHandler.h"

namespace reactor {

void EventHandler::operator()(int iFd, EventType iEventType) {
    handle(iFd, iEventType);
}

} // namespace reactor
