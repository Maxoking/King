#pragma once
#include "../Core.h"

namespace King {

  enum class EventType {
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppTick, Appupdate, AppRender,
    KeyPressed, KeyReleased,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MoseScrolled
  };

  enum EventCategory
  {
    None = 0,
    EventCategoryApplication = BIT(0),
    EventCategoryInput = BIT(1),
    EventCategoryKeyboard = BIT(2),
    EventCategoryMouse = BIT(3),
    EventCategoryMouseButton = BIT(4)
  };

  class KING_API Event {
  friend class EventDispatcher;

  public:
    virtual EventType getEventType() const = 0;
    virtual const char* getName() const = 0;
    virtual int getEventCategoryFlags() const = 0;
    virtual std::string toString() const { return getName(); };
    inline bool isInCategory(EventCategory category) { return getEventCategoryFlags() & category; };

  protected:
    bool m_handled = false;

  };

  class KING_API EventDispatcher {
    template<typename T> using EventFn = std::function<bool(T&)>;

  public:
    EventDispatcher(Event& event) : m_event(event) {};

    template<typename T> bool dispatch(EventFn<T> function) {
      if (m_event.getEventType() == T::GetStaticType()) {
        m_event.m_handled = function(*(T*)&m_event);
      }
    };

  private:
    Event& m_event;
  };

  inline std::ostream& operator<<(std::ostream& os, const Event& e)
  {
    return os << e.toString();
  }
}