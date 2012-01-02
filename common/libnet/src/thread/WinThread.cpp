#if defined (_WIN32)
#include "Thread.hpp"

NET_USE_NAMESPACE

static DWORD WINAPI		starter(void *arg)
{
  Thread	**tmp = static_cast<Thread**>(arg);
  (*tmp)->run();
  delete tmp;
  return (0);
}

bool	Thread::start()
 {
   if (this->_state == false)
   {
     Thread	**tmp = new (Thread*);
     *tmp = thread;
     _tid = CreateThread(0, 0, starter, tmp, 0, 0);
     bool ret = (_tid) ? true : false;
     if (ret)
	this->_state = true;
     return (ret);
  }
  else
    return (false);
}

bool	Thread::cancel()
{
  bool	ret;

  if (_state == true)
  {
    ret = TerminateThread(_tid, 0);
    if (ret)
      _state = false;
    return (ret);
  }
  else
    return (false);
}

bool		Thread::join(void **exit_value)
{
   DWORD	ret;

   if (_state != false)
    {
      ret = WaitForSingleObject(_tid, INFINITE);
      if (ret == WAIT_OBJECT_0)
      	_state = false;
      return (ret == WAIT_OBJECT_0);
    }
   else
      return false;
}

bool		Thread::tryjoin(void **exit_value)
{
   DWORD	ret;

    if (_state != false)
     {
       ret = WaitForSingleObject(_tid, 0);
       if (ret == WAIT_OBJECT_0)
	 _state = false;
       return (ret == WAIT_OBJECT_0);
     }
   else
     return false;
}
#endif
