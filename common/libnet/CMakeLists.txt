cmake_minimum_required (VERSION 2.8)

project(LibNet)
include (CheckFunctionExists)
check_function_exists (epoll_create HAVE_EPOLL)
check_function_exists (kqueue HAVE_KQUEUE)
check_function_exists (WaitForMultipleObjects HAVE_WFMO)

set(EXECUTABLE_OUTPUT_PATH ./)

##### Linking libnet
set(NET_SRCS_DIR "src/")
set(NET_INCLUDE_DIR "include/")
set(NET_MUTEX_INCLUDE_DIR "include/thread/")
set(NET_MUTEX_SRCS_DIR "src/thread/")

set(SRCS_NET
	${NET_SRCS_DIR}InetAddr.cpp
	${NET_SRCS_DIR}Error.cpp
	${NET_SRCS_DIR}Socket.cpp
	${NET_SRCS_DIR}SocketIO.cpp
	${NET_SRCS_DIR}SocketAcceptor.cpp
	${NET_SRCS_DIR}SocketConnector.cpp
	${NET_SRCS_DIR}SocketStream.cpp
	${NET_SRCS_DIR}SocketDatagram.cpp
	${NET_SRCS_DIR}SetupNetwork.cpp
	${NET_SRCS_DIR}NetHandler.cpp
	${NET_SRCS_DIR}Reactor.cpp
	${NET_SRCS_DIR}PollPolicy.cpp
	${NET_SRCS_DIR}EpollPolicy.cpp
	${NET_SRCS_DIR}KqueuePolicy.cpp
	${NET_SRCS_DIR}WFMOPolicy.cpp
	${NET_SRCS_DIR}Packet.cpp
	${NET_SRCS_DIR}DataBlock.cpp
	${NET_SRCS_DIR}UdpPacketHandler.cpp
	${NET_SRCS_DIR}IOVec.cpp
	${NET_SRCS_DIR}Clock.cpp
	${NET_MUTEX_SRCS_DIR}PosixMutex.cpp
	${NET_MUTEX_SRCS_DIR}PosixThread.cpp
	${NET_MUTEX_SRCS_DIR}PosixConditionVar.cpp
	${NET_MUTEX_SRCS_DIR}Thread.cpp
	${NET_MUTEX_SRCS_DIR}WinMutex.cpp
	${NET_MUTEX_SRCS_DIR}WinThread.cpp
	${NET_MUTEX_SRCS_DIR}WinConditionVar.cpp
	${NET_MUTEX_SRCS_DIR}ScopedLock.cpp
)

include_directories (
	${NET_INCLUDE_DIR}
	${NET_MUTEX_INCLUDE_DIR}
)

add_library(
	net
	STATIC
	${SRCS_NET}
)

IF(HAVE_EPOLL)
set_source_files_properties (
  ${SRCS_NET}
  PROPERTIES
  COMPILE_FLAGS
  "-DHAVE_EPOLL"
)
ENDIF(HAVE_EPOLL)

IF(HAVE_KQUEUE)
set_source_files_properties (
  ${SRCS_NET}
  PROPERTIES
  COMPILE_FLAGS
  "-DHAVE_KQUEUE"
)
ENDIF(HAVE_KQUEUE)
