#pragma once
#include "ODefines.hpp"


namespace EventSystem
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

