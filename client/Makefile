NAME		=  ../rtype

DIR		=  .

SRCS		= $(DIR)/main.cpp								\
		  $(DIR)/Game.cpp									\
		  $(DIR)/Module.cpp									\
		  $(DIR)/ModuleManager.cpp                          \
		  $(DIR)/GameStateManager.cpp						\
		  $(DIR)/Callback.cpp								\
		  $(DIR)/InputModule.cpp							\
		  $(DIR)/InputManager.cpp							\
		  $(DIR)/Loading.cpp								\
		  $(DIR)/Event.cpp									\
		  $(DIR)/EventDispatcher.cpp						\
		  $(DIR)/GameObject.cpp								\
		  $(DIR)/GameObjectManager.cpp						\
		  $(DIR)/PhysicObject.cpp							\
		  $(DIR)/PhysicManager.cpp							\
		  $(DIR)/ManagerManager.cpp							\
		  $(DIR)/AudioManager.cpp							\
		  $(DIR)/RendererManager.cpp						\
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
		  $(DIR)/Sound.cpp									\
		  $(DIR)/Wall.cpp									\
		  $(DIR)/CommandDispatcher.cpp						\
		  $(DIR)/GameStateObserver.cpp						\
		  $(DIR)/QuadTree/QuadTree.cpp						\
		  $(DIR)/QuadTree/Node.cpp							\
		  $(DIR)/QuadTree/TreeElement.cpp					\
		  $(DIR)/../common/PosixMutex.cpp					\
		  $(DIR)/ResourceManager.cpp						\
		  $(DIR)/SFMLSprite.cpp

OBJS		= $(SRCS:.cpp=.o)

CC		= g++

RM		= rm -f

CXXFLAGS	= -g3 -std=c++0x -pipe `pkg-config --cflags clanCore-2.3 clanNetwork-2.3 clanDisplay-2.3 clanGL-2.3 clanGL1-2.3 clanApp-2.3 clanMikMod-2.3 clanSound-2.3 clanVorbis-2.3` -I Callback_Impl -I bulletml -I QuadTree -I ../common -I bulletml/tinyxml

LDFLAGS		= `pkg-config --libs clanCore-2.3 clanGUI-2.3 clanNetwork-2.3 clanDisplay-2.3 clanGL-2.3 clanGL1-2.3 clanApp-2.3 clanMikMod-2.3 clanSound-2.3 clanVorbis-2.3` \
		  -lpthread -Lbulletml -lbulletml -ldl -lsfml-graphics -lsfml-window -lsfml-system

$(NAME)		: $(OBJS)
		make -C bulletml
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

all		: $(NAME)

clean		:
		$(RM) $(OBJS)

fclean		: clean
		$(RM) $(NAME)

re		: fclean all

libclean:
	make clean -C bulletml

libfclean:
	make fclean -C bulletml

libre:
	make re -C bulletml
