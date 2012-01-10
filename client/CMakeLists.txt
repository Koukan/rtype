cmake_minimum_required (VERSION 2.8)

project(R-Type_Client)

set(EXECUTABLE_OUTPUT_PATH ../)

##### Linking the sfml libraries
IF(WIN32)
set(TYPE "Windows")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
set(SFML_INCLUDE_DIR "C:/Development/Environment/SFML-1.6/include")
set(SFMLDIR "C:/Development/Environment/SFML-1.6")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 1.6 REQUIRED SYSTEM GRAPHICS WINDOW)
set(SFML_LIBRARIES
	${SFML_GRAPHICS_LIBRARY}
	${SFML_WINDOW_LIBRARY}
	${SFML_SYSTEM_LIBRARY}
)
ELSE(WIN32)
set(TYPE "Unix")
set(SFML_INCLUDE_DIR "/usr/include/SFML")
set(SFML_LIBRARIES
	sfml-graphics
	sfml-window
	sfml-system
	dl
)
ENDIF(WIN32)
#####

##### Linking libnet
set(NET_SRCS_DIR "../common/libnet/src/")
set(NET_INCLUDE_DIR "../common/libnet/include")
set(NET_MUTEX_INCLUDE_DIR "../common/libnet/include/thread/")
set(NET_MUTEX_SRCS_DIR "../common/libnet/src/thread/")

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
	${NET_SRCS_DIR}Packet.cpp			
	${NET_SRCS_DIR}DataBlock.cpp		
	${NET_SRCS_DIR}UdpPacketHandler.cpp	
	${NET_SRCS_DIR}IOVec.cpp			
	${NET_SRCS_DIR}Clock.cpp			
	${NET_MUTEX_SRCS_DIR}PosixMutex.cpp
	${NET_MUTEX_SRCS_DIR}PosixThread.cpp
	${NET_MUTEX_SRCS_DIR}PosixConditionVar.cpp
	${NET_MUTEX_SRCS_DIR}WinMutex.cpp
	${NET_MUTEX_SRCS_DIR}WinThread.cpp
	${NET_MUTEX_SRCS_DIR}WinConditionVar.cpp
	${NET_MUTEX_SRCS_DIR}ScopedLock.cpp
)
	
add_library(
	net
	STATIC
	${SRCS_NET}
)

IF(WIN32)
ELSE(WIN32)
set_source_files_properties (
  ${SRCS_NET}
  PROPERTIES
  COMPILE_FLAGS
  "-std=c++0x -W -Wall"
)
ENDIF(WIN32)

##### Linking core
set(CORE_DIR
	"../common/core/"
)
set(CORE_CALLBACK_DIR
	"../common/core/Callback_Impl/"
)
set(CORE_QUADTREE_INCLUDE_DIR
	"../common/core/QuadTree/"
)
set(CORE_BULLETML_DIR
	"../common/core/bulletml/"
)
set(CORE_TINYXML_DIR
	"../common/core/tinyxml/"
)

##### Add core headers
set(INCLUDES_CORE
	${CORE_DIR}Bullet.hpp
	${CORE_DIR}BulletCommand.hpp
	${CORE_DIR}BulletResourceManager.hpp
	${CORE_DIR}ButtonSprite.hpp
	${CORE_DIR}Callback.hpp
	${CORE_DIR}Callback.ipp
	${CORE_DIR}CircleHitBox.hpp
	${CORE_DIR}Command.hpp
	${CORE_DIR}CommandDispatcher.hpp
	${CORE_DIR}CommandHandler.hpp
	${CORE_DIR}Converter.hpp
	${CORE_DIR}DrawableObject.hpp
	${CORE_DIR}GameObject.hpp
	${CORE_DIR}GameObjectManager.hpp
	${CORE_DIR}GameObjectManager.ipp
	${CORE_DIR}GameState.hpp
	${CORE_DIR}GameStateManager.hpp
	${CORE_DIR}GameStateObserver.hpp
	${CORE_DIR}GSManager.hpp
	${CORE_DIR}GUIElement.hpp
	${CORE_DIR}GUIManager.hpp
	${CORE_DIR}GUILayout.hpp
	${CORE_DIR}HitBox.hpp
	${CORE_DIR}Input.hpp
	${CORE_DIR}InputManager.hpp
	${CORE_DIR}IPhysicsSubscriber.hpp
	${CORE_DIR}Module.hpp
	${CORE_DIR}ModuleManager.hpp
	${CORE_DIR}NonCopyable.hpp
	${CORE_DIR}Observable.hpp
	${CORE_DIR}PhysicManager.hpp
	${CORE_DIR}PhysicObject.hpp
	${CORE_DIR}PhysicsSubscriber.hpp
	${CORE_DIR}PhysicsSubscriber2.hpp
	${CORE_DIR}PolyHitBox.hpp
	${CORE_DIR}RectHitBox.hpp
	${CORE_DIR}ResourceManager.hpp
	${CORE_DIR}SharedLoader.hpp
	${CORE_DIR}Sprite.hpp
	${CORE_DIR}SpriteProvider.hpp
	${CORE_DIR}SpriteProvider.ipp
	${CORE_DIR}XMLProvider.hpp
	${CORE_DIR}TimeEffectManager.hpp
	${CORE_DIR}Singleton.hpp
	${CORE_CALLBACK_DIR}Callback_Impl.hpp
	${CORE_QUADTREE_INCLUDE_DIR}QuadTree.hpp
	${CORE_BULLETML_DIR}bulletmlparser.h
	${CORE_TINYXML_DIR}tinyxml.h
)

set(SRCS_CORE
	${INCLUDES_CORE}
	${CORE_DIR}Bullet.cpp
	${CORE_DIR}BulletCommand.cpp
	${CORE_DIR}BulletResourceManager.cpp
	${CORE_DIR}ButtonSprite.cpp
	${CORE_DIR}Callback.cpp
	${CORE_DIR}CircleHitBox.cpp
	${CORE_DIR}CommandDispatcher.cpp
	${CORE_DIR}CommandHandler.cpp
	${CORE_DIR}GameObject.cpp
	${CORE_DIR}GameObjectManager.cpp
	${CORE_DIR}GameState.cpp
	${CORE_DIR}GameStateObserver.cpp
	${CORE_DIR}GSManager.cpp
	${CORE_DIR}GUIElement.cpp
	${CORE_DIR}GUIManager.cpp
	${CORE_DIR}GUILayout.cpp
	${CORE_DIR}HitBox.cpp
	${CORE_DIR}InputManager.cpp
	${CORE_DIR}Module.cpp
	${CORE_DIR}ModuleManager.cpp
	${CORE_DIR}PhysicManager.cpp
	${CORE_DIR}PhysicObject.cpp
	${CORE_DIR}PolyHitBox.cpp
	${CORE_DIR}RectHitBox.cpp
	${CORE_DIR}ResourceManager.cpp
	${CORE_DIR}SpriteProvider.cpp
	${CORE_DIR}TimeEffectManager.cpp
	${CORE_DIR}XMLProvider.cpp
	${CORE_QUADTREE_INCLUDE_DIR}QuadTree.cpp
	${CORE_QUADTREE_INCLUDE_DIR}Node.cpp
	${CORE_QUADTREE_INCLUDE_DIR}TreeElement.cpp
	${CORE_BULLETML_DIR}bulletmlparser.cc
	${CORE_BULLETML_DIR}bulletmlparser-tinyxml.cc
	${CORE_BULLETML_DIR}bulletmltree.cc
	${CORE_BULLETML_DIR}calc.cc
	${CORE_BULLETML_DIR}formula-variables.cc
	${CORE_BULLETML_DIR}bulletmlrunner.cc
	${CORE_BULLETML_DIR}bulletmlrunnerimpl.cc
	${CORE_TINYXML_DIR}tinyxml.cpp
	${CORE_TINYXML_DIR}tinyxmlerror.cpp
	${CORE_TINYXML_DIR}tinyxmlparser.cpp
	${CORE_CALLBACK_DIR}/Callback_Impl_Function.cpp
)
SOURCE_GROUP (core_headers FILES(${INCLUDES_CORE}))

IF(WIN32)
ELSE(WIN32)
set_source_files_properties (
  ${SRCS_CORE}
  PROPERTIES
  COMPILE_FLAGS
  "-W -Wall"
)
ENDIF(WIN32)

add_library(
	core
	STATIC
	${SRCS_CORE}
)

set(TARGET_NAME rtype_client)

##	Font.cpp
##	Font.hpp
##	AudioManager.cpp
##	AudioManager.hpp
set(GUI_INCLUDE_DIR "gui")

set(GUI_SRC_DIR "gui")
set(INCLUDES_COMMON_DIR "../common/")

set(SRCS
	${INCLUDES_CORE}
	main.cpp
	Game.cpp
	Game.hpp
	GameCommand.hpp
	GSInGame.cpp
	GSInGame.hpp
	GSLoading.cpp
	GSLoading.hpp
	InputModule.cpp
	InputModule.hpp
	main.cpp
	Monster.cpp
	Monster.hpp
	NetworkModule.cpp
	NetworkModule.hpp
	PacketCommand.cpp
	PacketCommand.hpp
	${INCLUDES_COMMON_DIR}PacketType.hpp
	RendererManager.cpp
	RendererManager.hpp
	Server.cpp
	Server.hpp
	SFMLSprite.cpp
	SFMLSprite.hpp
	SFMLSpriteProvider.cpp
	SFMLSpriteProvider.hpp
	UdpHandler.cpp
	UdpHandler.hpp
	Wall.cpp
	Wall.hpp
	${GUI_SRC_DIR}/GUIList.hpp
	${GUI_SRC_DIR}/GUIVLayout.cpp
	${GUI_SRC_DIR}/GUIHLayout.cpp
	ScrollingSprite.hpp
	ScrollingSprite.cpp
)

IF(WIN32)
ELSE(WIN32)
set_source_files_properties (
  ${SRCS}
  PROPERTIES
  COMPILE_FLAGS
  "-std=c++0x -W -Wall"
)
ENDIF(WIN32)

##### Setting the output directory for the solution
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${EXECUTABLE_OUTPUT_PATH} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${EXECUTABLE_OUTPUT_PATH} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${EXECUTABLE_OUTPUT_PATH} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
#####


add_executable(
	${TARGET_NAME}
	${SRCS}
)

include_directories (
	${INCLUDES_COMMON_DIR}
	${SFML_INCLUDE_DIR}
	${NET_INCLUDE_DIR}
	${NET_MUTEX_INCLUDE_DIR}
	${CORE_DIR}
	${CORE_CALLBACK_DIR}
	${CORE_QUADTREE_INCLUDE_DIR}
	${CORE_BULLETML_DIR}
	${CORE_TINYXML_DIR}
	${GUI_INCLUDE_DIR}
)

###### linking net to core
target_link_libraries(
	core
	net
)

target_link_libraries(
	${TARGET_NAME}
	${SFML_LIBRARIES}
	core
	net
)