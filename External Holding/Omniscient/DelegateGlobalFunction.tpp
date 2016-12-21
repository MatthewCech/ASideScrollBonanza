namespace OEvent
{
  // Constructor, takes the member function and 'this' such that it can be called later.
  template <typename EventType>
  DelegateGlobalFunction<typename EventType>::DelegateGlobalFunction(Function func)
    : Delegate()
    , function_(func)
  {  }


  // Calls the function specified in the constructor on the object from the constructor, with event e.
  // E is cast to a pointer of the type of the event being passed.
  template <typename EventType>
  void DelegateGlobalFunction<typename EventType>::Call(OEvent *e)
  {
    function_(dynamic_cast<EventType *>(e));
  }
}
