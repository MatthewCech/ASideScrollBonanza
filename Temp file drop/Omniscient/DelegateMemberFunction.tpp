namespace OEvent
{
  // Constructor, takes the member function and 'this' such that it can be called later.
  template <typename Caller, typename EventType>
  DelegateMemberFunction<typename Caller, typename EventType>::DelegateMemberFunction(CallerFunction func, Caller *caller)
    : Delegate()
    , function_(func)
    , caller_(caller)
  {  }


  // Calls the function specified in the constructor on the object from the constructor, with event e.
  // E is cast to a pointer of the type of the event being passed.
  template <typename Caller, typename EventType>
  void DelegateMemberFunction<typename Caller, typename EventType>::Call(OEvent *e)
  {
    (caller_->*function_)(dynamic_cast<EventType *>(e));
  }
}
