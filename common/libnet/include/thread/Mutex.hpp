#ifndef		_MUTEX_
#define		_MUTEX_

#include "NetDef.hpp"

NET_BEGIN_NAMESPACE

# if defined (_WIN32)
#define _WINSOCKAPI_
#include <windows.h>

#define MUTEX CRITICAL_SECTION 

# else
#  include	<pthread.h>
#  include	<time.h>
#  include	<stdlib.h>

#define MUTEX pthread_mutex_t

# endif

class NET_DLLREQ Mutex
{
  public:
	Mutex();
	virtual ~Mutex();
	bool	lock();
	bool	unlock();
	bool	tryLock();
	bool	timedLock(int sec, int nano);

  protected:
	MUTEX    _mutex;
};

class NET_DLLREQ ScopedLock
{
  public:
	ScopedLock(Mutex &mutex);
	~ScopedLock();

  private:
	Mutex	&_mutex;
};

NET_END_NAMESPACE

#endif		/* _MUTEX_ */
