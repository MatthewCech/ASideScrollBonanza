#pragma once
#include "Delegate.hpp"
#include "OEvent.hpp"



namespace OEvent
{
  // A derived delegate for specifically handling class member functions.
  template <typename Caller, typename EventType>
  class DelegateMemberFunction : public Delegate
  {
  public:
    // Public typedefs fore ease of use
    typedef void(Caller::*CallerFunction)(EventType *e);

    // Constructor
    DelegateMemberFunction(CallerFunction func, Caller *caller);

    // Member functions
    void Call(OEvent *e);

  private:
    // Variables
    CallerFunction function_;
    Caller *caller_;
  };
}

#include "DelegateMemberFunction.tpp"
