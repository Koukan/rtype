NAMESTATIC		=  ../libcore.a
NAMEDYNAMIC		=  ../libcore.so

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
		  $(DIR)/InputManager.cpp							\
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

CXXFLAGS	= -W -Wall -Wextra -g3 -pipe -I Callback_Impl -I QuadTree -I bulletml -I tinyxml -I ../libnet/include -I ../libnet/include/thread

LDFLAGS		= -L bulletml -lbulletml -lstdc++

$(NAMESTATIC)		: $(OBJS)
					make -C tinyxml
					make -C bulletml
					$(AR) $(NAMESTATIC) $(OBJS)
					$(RANLIB) $(NAMESTATIC)

$(NAMEDYNAMIC)		: $(OBJS)
					$(CXX) $(OBJS) -shared -o $(NAMEDYNAMIC)

all		: $(NAMESTATIC) $(NAMEDYNAMIC)
		make -C tinyxml
		make -C bulletml

clean		:
		make clean -C tinyxml
		make clean -C bulletml
		$(RM) $(OBJS)

fclean		: clean
		make fclean -C tinyxml
		make fclean -C bulletml
		$(RM) $(NAMESTATIC)
		$(RM) $(NAMEDYNAMIC)

re		: fclean all
