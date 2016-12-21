#pragma once
#include "Delegate.hpp"
#include "Event.hpp"



namespace EventSystem
{
  // A derived delegate for specifically handling class member functions.
  template <typename EventType>
  class DelegateGlobalFunction : public Delegate
  {
  public:
    // Public typedefs fore ease of use
    typedef void(*Function)(EventType *e);

    // Constructor
    DelegateGlobalFunction(Function func);

    // Member functions
    void Call(Event *e);

  private:
    // Variables
    Function function_;
  };
}

#include "DelegateGlobalFunction.tpp"
