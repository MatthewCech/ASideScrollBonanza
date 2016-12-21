#pragma once
#include "Events\ODefines.hpp"


namespace Events
{
  // Base class Event, used for grouping all derived event objects.
  class Event
  {
  public:
    // Constructor and Destructor
    Event();
    virtual ~Event();
  };
}

