NAME		=  ../rtype-server

DIR			=  .

SRCS		= $(DIR)/main.cpp				\
			  $(DIR)/Server.cpp				\
			  $(DIR)/NetworkModule.cpp		\
			  $(DIR)/Player.cpp				\
			  $(DIR)/GameManager.cpp		\
			  $(DIR)/Game.cpp				\
			  $(DIR)/ThreadPool.cpp			\
			  $(DIR)/GameTask.cpp			\
			  $(DIR)/GameLogic.cpp

OBJS		= $(SRCS:.cpp=.o)

CXX			= g++

RM			= rm -f

CXXFLAGS	= -g3 -std=c++0x -pipe -I ../common/core -I../common/core/Callback_Impl -I../common/core/QuadTree -I../common/core/bulletml -I../common/core/tinyxml \
			  -I../common/libnet/include -I../common/libnet/include/thread

LDFLAGS		= -lpthread -ldl -lsfml-graphics -lsfml-window -lsfml-system -L ../common -lcore -lbulletml -lnet

$(NAME)		: $(OBJS)
		$(CXX) -o $(NAME) $(OBJS) $(LDFLAGS)

all		: $(NAME)

clean		:
		$(RM) $(OBJS)

fclean		: clean
		$(RM) $(NAME)

re		: fclean all
