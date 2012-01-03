#ifndef _CONDITIONVAR_
#define _CONDITIONVAR_

#include "NetDef.hpp"


#if defined  (_WIN32)
#define _WINSOCKAPI_
#include <windows.h>

#define CONDVAR CONDITION_VARIABLE

#else

#include <pthread.h>

#define	CONDVAR	pthread_cond_t

#endif

#include "Mutex.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ ConditionVar : public Mutex
{
public:
	ConditionVar();
	~ConditionVar();
	bool	signal();
	bool	broadcast();
	bool	uniqueWait();
	bool	uniqueTimedWait(int ms);
	bool	wait();
	bool	timedWait(int ms);

private:
	CONDVAR 	_cond;
};

NET_END_NAMESPACE

#endif /* _CONDITIONVAR_ */
