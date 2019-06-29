#pragma once
#include "Event.h"

namespace King {

  class KING_API KeyEvent : public Event {

  public:
    inline int getKeyCode() { return m_keyCode; };
    std::string toString() const override
    {
      std::stringstream ss;
      ss << "KeyEvent";
      return ss.str();
    }
  protected:
    KeyEvent(int keyCode) : m_keyCode(keyCode) {};
    int m_keyCode;

  };

  class KING_API KeyPressedEvent : public KeyEvent {
  public:
    KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_repeatCount(repeatCount) {}
    static EventType getStaticType() { return EventType::KeyPressed; };
    virtual EventType getEventType() const override { return getStaticType(); };
    virtual const char* getName() const override { return "KeyPressed"; };
    virtual int getEventCategoryFlags() const override { return EventCategoryInput | EventCategoryKeyboard; };

    inline int getRepeatCount() { return m_repeatCount; };

    std::string toString() const override
    {
      std::stringstream ss;
      ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
      return ss.str();
    }

  protected:
    int m_repeatCount;
  };

  class KING_API KeyReleasedEvent : public KeyEvent {
  public:
    KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}
    static EventType getStaticType() { return EventType::KeyReleased; };
    virtual EventType getEventType() const override { return getStaticType(); };
    virtual const char* getName() const override { return "KeyReleased"; };
    virtual int getEventCategoryFlags() const override { return EventCategoryInput | EventCategoryKeyboard; };

    std::string toString() const override
    {
      std::stringstream ss;
      ss << "KeyRealeasdEvent: " << m_keyCode;
      return ss.str();
    }
  };

}