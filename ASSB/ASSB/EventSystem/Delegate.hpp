#pragma once
#include "ODefines.hpp"
#include "Event.hpp"



namespace EventSystem
{
  // An abstract class designed to act as a template for different types of delegates,
  // allowing them all to be manipulated together.
  class Delegate
  {
  public:
    // Constructor and Destructor
    Delegate();
    virtual ~Delegate();

    // Abstract Functions
    virtual void Call(Event *e) MU_ABSTRACT;
  };
}
