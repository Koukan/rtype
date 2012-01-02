#if defined (WIN32)

# include "Mutex.hpp"

NET_USE_NAMESPACE

bool	Mutex::lock(void)
{
  EnterCriticalSection(&_mutex);
}

bool	Mutex::unlock(void)
{
  LeaveCriticalSectioni(&_mutex);
}

bool	Mutex::tryLock(void)
{
}

bool	Mutex::timedLock(int sec, int nano)
{
}

Mutex::Mutex()
{
  InitializeCriticalSection(&_mutex);
}

Mutex::~Mutex()
{
  DeleteCriticalSection(&_mutex);
}
#endif
