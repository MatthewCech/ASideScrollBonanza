#pragma once
#include "ODefines.hpp"
#include "OEvent.hpp"


namespace OEvent
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
    virtual void Call(OEvent *e) MU_ABSTRACT;
  };
}
