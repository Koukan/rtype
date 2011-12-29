NAME		=  ../rtype

DIR		=  .

SRCS		= $(DIR)/main.cpp								\
		  $(DIR)/Game.cpp									\
		  $(DIR)/Loading.cpp								\
		  $(DIR)/Wall.cpp

OBJS		= $(SRCS:.cpp=.o)

CXX		= g++

RM		= rm -f

CXXFLAGS	= -g3 -std=c++0x -pipe -I ../common/core -I../common/core/Callback_Impl -I../common/core/QuadTree -I../common/core/bulletml -I../common/core/tinyxml

LDFLAGS		= -lpthread -ldl -lsfml-graphics -lsfml-window -lsfml-system -L../common/core -lcore -L ../common/core/bulletml -lbulletml

$(NAME)		: $(OBJS)
		$(CXX) -o $(NAME) $(OBJS) $(LDFLAGS)

all		: $(NAME)

clean		:
		$(RM) $(OBJS)

fclean		: clean
		$(RM) $(NAME)

re		: fclean all
