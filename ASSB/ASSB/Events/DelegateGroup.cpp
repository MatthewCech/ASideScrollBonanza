#include "DelegateGroup.hpp"



namespace OEvent
{
  // Running Unique ID Static initialization
  O_ID DelegateGroup::runningUID_ = 0;
  
  
  // Constructor, sets reasonable defaults.
  DelegateGroup::DelegateGroup() 
    : delegates_()
    , dirty_(false)
  {  }


  // Adds a DelegateGroupMember to the data structure, and returns the
  // unique ID given to it.
  O_ID DelegateGroup::Add(Delegate *d)
  {
    delegates_.push_back(DelegateGroupMember(d, ++runningUID_));
    return runningUID_;
  }


  // Handle removing an ID. If more efficiency is needed than this, a second data 
  // structure sorted by O_ID and the corresponding index in deleagates_
  void DelegateGroup::Remove(O_ID id)
  {
    for (unsigned int i{ 0 }; i < delegates_.size(); ++i)
      if (delegates_[i].DelegateID == id)
      {
        delegates_[i].Active = false;
        dirty_ = true;
        break;
      }
  }


  // Dispatch the event e to all active delegates in the group.
  // Returns the number of delegates the event was dispatchedo to.
  int DelegateGroup::Dispatch(OEvent *e)
  {
    int numDispatched{ 0 };
    for (unsigned int i{ 0 }; i < delegates_.size(); ++i)
      if (delegates_[i].Active)
      {
        delegates_[i].DelegateObject->Call(e);
        ++numDispatched;
      }

    return numDispatched;
  }


  // Cleans up the structure if there was anything to remove. Tracks changes,
  // costs O(n) if something was flagged for removal, O(1) if nothing was marked.
  void DelegateGroup::CleanRemoved()
  {
    if (!dirty_)
      return;

    for (unsigned int i{ 0 }; i < delegates_.size();)
      if (!delegates_[i].Active)
        delegates_.erase(delegates_.begin() + i);
      else
        ++i;

    dirty_ = false;
  }
}
