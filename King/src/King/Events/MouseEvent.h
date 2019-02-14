#pragma once

#include "Event.h"

namespace King {

  class KING_API MouseMoved : public Event {
  public:
    MouseMoved(float x, float y) : m_MouseX(x), m_MouseY(y) {};
    float getMouseX() { return m_MouseX; };
    float getMouseY() { return m_MouseY; };
    static EventType getStaticType() { return EventType::MouseMoved; };
    virtual EventType getEventType() const override { return getStaticType(); };
    virtual int getEventCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse; };
    virtual const char* getName() const override { return "MouseMoved"; };

    std::string toString() const override
    {
      std::stringstream ss;
      ss << "MouseMoved: " << "X: " << m_MouseX << "Y: " << m_MouseY;
      return ss.str();
    }

  protected:
    float m_MouseX, m_MouseY;
  };

  class KING_API MouseButtonPressed : public Event {
  public:
    MouseButtonPressed(int keyCode) : m_keyCode(keyCode) {};
    int getKeyCode() { return m_keyCode; };
    static EventType getStaticType() { return EventType::MouseButtonPressed; };
    virtual EventType getEventType() const override { return getStaticType(); };
    virtual int getEventCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse; };
    virtual const char* getName() const override { return "MouseButtonPressed"; };

    std::string toString() const override
    {
      std::stringstream ss;
      ss << "MouseButtonPressed: " << m_keyCode;
      return ss.str();
    }

  protected:
    int m_keyCode;
  };

  class KING_API MouseButtonReleased : public Event {
  public:
    MouseButtonReleased(int keyCode) : m_keyCode(keyCode) {};
    int getKeyCode() { return m_keyCode; };
    static EventType getStaticType() { return EventType::MouseButtonReleased; };
    virtual EventType getEventType() const override { return getStaticType(); };
    virtual int getEventCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse; };
    virtual const char* getName() const override { return "MouseButtonReleased"; };

    std::string toString() const override
    {
      std::stringstream ss;
      ss << "MouseButtonReleased: " << m_keyCode;
      return ss.str();
    }

  protected:
    int m_keyCode;
  };



}