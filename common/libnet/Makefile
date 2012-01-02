NAMESTATIC		=  ../libnet.a
NAMEDYNAMIC		=  ../libnet.so

DIR		=  ./src

SRCS		= $(DIR)/InetAddr.cpp				\
				$(DIR)/Error.cpp				\
				$(DIR)/Socket.cpp				\
				$(DIR)/SocketIO.cpp				\
				$(DIR)/SocketAcceptor.cpp		\
				$(DIR)/SocketConnector.cpp		\
				$(DIR)/SocketStream.cpp			\
				$(DIR)/SocketDatagram.cpp		\
				$(DIR)/SetupNetwork.cpp			\
				$(DIR)/NetHandler.cpp			\
				$(DIR)/Reactor.cpp				\
				$(DIR)/PollPolicy.cpp			\
				$(DIR)/EpollPolicy.cpp			\
				$(DIR)/KqueuePolicy.cpp			\
				$(DIR)/Packet.cpp				\
				$(DIR)/DataBlock.cpp			\
				$(DIR)/UdpPacketHandler.cpp		\
				$(DIR)/IOVec.cpp				\
				$(DIR)/Clock.cpp				\
				$(DIR)/thread/Thread.cpp		\
				$(DIR)/thread/PosixMutex.cpp	\
				$(DIR)/thread/PosixThread.cpp	\
				$(DIR)/thread/ScopedLock.cpp


OBJS		= $(SRCS:.cpp=.o)

CXX			= g++ 

RM			= rm -f

AR			= ar r

RANLIB		= ranlib

CXXFLAGS	= -W -Wall -Wextra -O2 -pipe -I include/ -I include/thread

LDFLAGS		= 


$(NAMESTATIC)		: $(OBJS)
					$(AR) $(NAMESTATIC) $(OBJS)
					$(RANLIB) $(NAMESTATIC)

$(NAMEDYNAMIC)		: $(OBJS)
					$(CXX) $(OBJS) -shared -o $(NAMEDYNAMIC)

all		: $(NAMESTATIC) 

clean		:
		$(RM) $(OBJS)

fclean		: clean
		$(RM) $(NAMESTATIC)
		$(RM) $(NAMEDYNAMIC)

re		: fclean all

