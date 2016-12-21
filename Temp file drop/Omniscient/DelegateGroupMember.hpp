#pragma once
#include "Delegate.hpp"


namespace OEvent
{
  class DelegateGroupMember
  {
  public:
    // Constructors and Destructor
    DelegateGroupMember(Delegate *d, O_ID DelegateID, bool handleCleanup_ = true);
    DelegateGroupMember(DelegateGroupMember &rhs);
    ~DelegateGroupMember();

    // Member Functions
    DelegateGroupMember &operator =(DelegateGroupMember &rhs);

    // Public Variables
    Delegate *DelegateObject;
    O_ID DelegateID;
    bool Active;

  private:
    // Private Variables
    bool handleCleanup_;
  };
}
