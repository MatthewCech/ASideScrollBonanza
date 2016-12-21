#pragma once
#include <vector>
#include <utility>
#include "DelegateGroupMember.hpp"
#include "ODefines.hpp"
#include "OEvent.hpp"



namespace OEvent
{
  class DelegateGroup
  {
  public:
	  // Constructor
    DelegateGroup();

	  // Member Functions
    O_ID Add(Delegate *d);
    void Remove(O_ID);
    int Dispatch(OEvent *e);
    void CleanRemoved();

  private:
    // Member Variables
  	std::vector< DelegateGroupMember > delegates_;
    bool dirty_;

	  // Static variables
	  static O_ID runningUID_;
  };
}
