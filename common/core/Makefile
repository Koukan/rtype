NAMESTATIC		=  libcore.a
NAMEDYNAMIC		=  libcore.so

DIR			=  .

SRCS		= $(DIR)/Module.cpp								\
		  $(DIR)/ModuleManager.cpp                          \
		  $(DIR)/GSManager.cpp								\
		  $(DIR)/Callback.cpp								\
		  $(DIR)/GameObject.cpp								\
		  $(DIR)/GameObjectManager.cpp						\
		  $(DIR)/PhysicObject.cpp							\
		  $(DIR)/PhysicManager.cpp							\
		  $(DIR)/Callback_Impl/Callback_Impl_Function.cpp	\
		  $(DIR)/GameState.cpp								\
		  $(DIR)/BulletCommand.cpp							\
		  $(DIR)/Bullet.cpp									\
		  $(DIR)/BulletResourceManager.cpp					\
		  $(DIR)/TimeEffectManager.cpp						\
		  $(DIR)/PolyHitBox.cpp								\
		  $(DIR)/CircleHitBox.cpp							\
		  $(DIR)/HitBox.cpp									\
		  $(DIR)/RectHitBox.cpp								\
		  $(DIR)/CommandHandler.cpp							\
		  $(DIR)/CommandDispatcher.cpp						\
		  $(DIR)/GameStateObserver.cpp						\
		  $(DIR)/QuadTree/QuadTree.cpp						\
		  $(DIR)/QuadTree/Node.cpp							\
		  $(DIR)/QuadTree/TreeElement.cpp					\
		  $(DIR)/ResourceManager.cpp						\
		  $(DIR)/tinyxml/tinyxml.cpp						\
		  $(DIR)/tinyxml/tinyxmlerror.cpp					\
		  $(DIR)/tinyxml/tinyxmlparser.cpp					\
		  $(DIR)/../libnet/src/thread/PosixMutex.cpp

OBJS		= $(SRCS:.cpp=.o)

CXX			= g++

RM			= rm -f

AR			= ar r

RANLIB		= ranlib

CXXFLAGS	= -W -Wall -Wextra -g3 -pipe -fPIC -I Callback_Impl -I QuadTree -I bulletml -I tinyxml -I ../libnet/include -I ../libnet/include/thread

LDFLAGS		= -lnet -L bulletml -lbulletml


$(NAMESTATIC)		: $(OBJS)
					$(AR) $(NAMESTATIC) $(OBJS)
					$(RANLIB) $(NAMESTATIC)

$(NAMEDYNAMIC)		: $(OBJS)
					$(CXX) $(OBJS) -shared -o $(NAMEDYNAMIC)

all		: $(NAMESTATIC) $(NAMEDYNAMIC)

clean		:
		$(RM) $(OBJS)

fclean		: clean
		$(RM) $(NAMESTATIC)
		$(RM) $(NAMEDYNAMIC)

re		: fclean all

