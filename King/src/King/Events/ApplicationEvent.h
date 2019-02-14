#pragma once

#include "Event.h"

namespace King {

  class KING_API WindowCloseEvent : public Event {
  public:
    WindowCloseEvent() {};
    static EventType getStaticType() { return EventType::WindowClose; };
    virtual EventType getEventType() const override { return getStaticType(); };
    virtual const char* getName() const override { return "WindowClose"; };
    virtual int getEventCategoryFlags() const override { return EventCategoryApplication;  };
  };

  class KING_API WindowResizeEvent : public Event
  {
  public:
    WindowResizeEvent(unsigned int width, unsigned int height)
      : m_width(width), m_height(height) {}

    inline unsigned int getWidth() const { return m_width; }
    inline unsigned int getHeight() const { return m_height; }

    std::string toString() const override
    {
      std::stringstream ss;
      ss << "WindowResizeEvent: " << m_width << ", " << m_height;
      return ss.str();
    }

    static EventType getStaticType() { return EventType::WindowResize; };
    virtual EventType getEventType() const override { return getStaticType(); };
    virtual const char* getName() const override { return "WindowResize"; };
    virtual int getEventCategoryFlags() const override { return EventCategoryApplication; };

  private:
    unsigned int m_width, m_height;
  };

 

}