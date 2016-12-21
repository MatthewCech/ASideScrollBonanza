#include "DelegateGroupMember.hpp"



namespace OEvent
{
  // Non-default constructor. Takes an allocated delegate object, d, and associates it with 
  // a unique ID that is provided.
  DelegateGroupMember::DelegateGroupMember(Delegate *d, O_ID delID, bool handleCleanup)
    : DelegateObject(d)
    , DelegateID(delID)
    , Active(true)
    , handleCleanup_(handleCleanup)
  {  }


  // Copy Constructor
  DelegateGroupMember::DelegateGroupMember(DelegateGroupMember &rhs)
    : DelegateObject(rhs.DelegateObject)
    , DelegateID(rhs.DelegateID)
    , Active(rhs.Active)
    , handleCleanup_(rhs.handleCleanup_)
  {
    if (this != &rhs)
      if (rhs.handleCleanup_)
        rhs.handleCleanup_ = false;
  }


  // Assignment operator. Hands off the task of delegate deletion.
  DelegateGroupMember &DelegateGroupMember::operator =(DelegateGroupMember &rhs)
  {
    if (this != &rhs)
    {
      DelegateObject = rhs.DelegateObject;
      DelegateID = rhs.DelegateID;
      Active = rhs.Active;
      handleCleanup_ = rhs.handleCleanup_;

      if (rhs.handleCleanup_)
        rhs.handleCleanup_ = false;
    }

    return *this;
  }


  // Destructor - Handles object cleanup if it's the last one of the chain.
  DelegateGroupMember::~DelegateGroupMember()
  {
    if (handleCleanup_)
      delete DelegateObject;
  }
}
