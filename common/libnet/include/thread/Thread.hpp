# ifndef	_OOPTHREAD_H
#  define	_OOPTHREAD_H

# if defined (_WIN32)

#define _WINSOCKAPI_
#include <windows.h>

#define THREAD HANDLE

# else

#include	<pthread.h>
#include	<stdlib.h>

#define THREAD pthread_t

# endif

#include "NetDef.hpp"
#include "ThreadSubscriber.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ	Thread
{
 public:
 Thread(IThreadSubscriber &func);

 template <typename Functor>
 Thread(Functor &functor) : _func(new ThreadFunctor<Functor>(functor))
 {}

 template <typename Functor, typename Arg>
 Thread(Functor &functor, Arg arg) : _func(new ThreadFunctorArg<Functor, Arg>(functor, arg))
 {}

 template <typename Object>
 Thread(Object *obj, void (Object::*func)()) : _func(new ThreadMemberFunc<Object>(obj, func))
 {}

 ~Thread();

 bool           start();
 bool			cancel(void);
 bool			join(void **exit_value = 0);
 bool			tryjoin(void **exit_value = 0);
 void			run();

 private:
 IThreadSubscriber 	*_func;
 bool				_state;
 THREAD				_tid;
};

NET_END_NAMESPACE

#endif
