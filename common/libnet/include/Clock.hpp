
#ifndef _CLOCK_
#define _CLOCK_

#include <stdint.h>
#include <string>
#include <time.h>
#include "NetDef.hpp"

NET_BEGIN_NAMESPACE

#if defined (_WIN32)
#define _WINSOCKAPI_
#define EPOCHFILETIME (116444736000000000LL)

#include <windows.h>

#define TIME DWORD

#else

#include <sys/time.h>

#define TIME struct timeval

#endif

class Clock
{
public:
	Clock();
	~Clock();

	void	play();
	void	pause();
	void	update();
	void	reset();
	bool	isPaused() const;

	double	getElapsedTime() const;
	static uint64_t getMsSinceEpoch();
	static std::string getTimeInStr();
	static void			sleep(int ms);

private:
	bool						_paused;
	TIME						_time;
};

NET_END_NAMESPACE

#endif /* _CLOCK_ */
