#pragma once

#include "Event.h"

namespace King {

  class KING_API WindowCloseEvent : public Event {
  public:
    static EventType getStaticType() { return EventType::WindowClose; };
    virtual EventType getEventType() const override { return getStaticType(); };
    virtual const char* getName() const override { return "WindowClose"; };
  };

 

}