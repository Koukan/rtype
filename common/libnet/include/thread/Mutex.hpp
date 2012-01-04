#ifndef		_MUTEX_
#define		_MUTEX_

#include "NetDef.hpp"

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

NET_BEGIN_NAMESPACE

class		Mutex
{
  public:
	Mutex();
	~Mutex();
	bool	lock(void);
	bool	unlock(void);
	bool	tryLock(void);
	bool	timedLock(int sec, int nano);

  private:
	MUTEX    _mutex;
};

class		ScopedLock
{
  public:
	ScopedLock(Mutex &mutex);
	~ScopedLock();

  private:
	Mutex	&_mutex;
};

NET_END_NAMESPACE

#endif		/* _MUTEX_ */
