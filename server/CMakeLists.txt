cmake_minimum_required (VERSION 2.8)

project(R-Type_Server)

set(EXECUTABLE_OUTPUT_PATH ../)

set(COMMON_INCLUDE_DIR "../common/")

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
	${NET_MUTEX_SRCS_DIR}Thread.cpp
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

IF(!WIN32)
set_source_files_properties (
  ${SRCS_NET}
  PROPERTIES
  COMPILE_FLAGS
  "-std=c++0x"
)
ENDIF(!WIN32)

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
	${CORE_DIR}GUIManager.hpp
	${CORE_DIR}GUILayout.hpp
	${CORE_DIR}GUIElement.hpp	
	${CORE_DIR}GSManager.hpp
	${CORE_DIR}HitBox.hpp
	${CORE_DIR}Input.hpp
	${CORE_DIR}InputManager.hpp
	${CORE_DIR}IPhysicsSubscriber.hpp
	${CORE_DIR}md5.h
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
	${CORE_DIR}ResourceManager.ipp
	${CORE_DIR}SharedLoader.hpp
	${CORE_DIR}Sprite.hpp
	${CORE_DIR}SpriteProvider.hpp
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
	${CORE_DIR}Callback.cpp
	${CORE_DIR}CircleHitBox.cpp
	${CORE_DIR}CommandDispatcher.cpp
	${CORE_DIR}CommandHandler.cpp
	${CORE_DIR}GameObject.cpp
	${CORE_DIR}GameObjectManager.cpp
	${CORE_DIR}GameState.cpp
	${CORE_DIR}GameStateObserver.cpp
	${CORE_DIR}GUIManager.cpp
	${CORE_DIR}GUILayout.cpp
	${CORE_DIR}GUIElement.cpp	
	${CORE_DIR}GSManager.cpp
	${CORE_DIR}HitBox.cpp
	${CORE_DIR}InputManager.cpp
	${CORE_DIR}md5.cpp
	${CORE_DIR}Module.cpp
	${CORE_DIR}ModuleManager.cpp
	${CORE_DIR}PhysicManager.cpp
	${CORE_DIR}PhysicObject.cpp
	${CORE_DIR}PolyHitBox.cpp
	${CORE_DIR}RectHitBox.cpp
	${CORE_DIR}ResourceManager.cpp
	${CORE_DIR}TimeEffectManager.cpp
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

add_library(
	core
	STATIC
	${SRCS_CORE}
)

set(SRCS
	${INCLUDES_CORE}
	main.cpp
	File.cpp
	File.hpp
	Game.cpp
	Game.hpp
	GameLogic.cpp
	GameLogic.hpp
	GameManager.cpp
	GameManager.hpp
	GameTask.cpp
	GameTask.hpp
	NetworkModule.cpp
	NetworkModule.hpp
	PacketCommand.cpp
	PacketCommand.hpp
	Player.cpp
	Player.hpp
	Server.cpp
	Server.hpp
	ServerResourceManager.cpp
	ServerResourceManager.hpp
	Task.hpp
	ThreadPool.cpp
	ThreadPool.hpp
	UdpHandler.cpp
	UdpHandler.hpp
	main.cpp
)

IF(!WIN32)
set_source_files_properties (
  ${SRCS}
  PROPERTIES
  COMPILE_FLAGS
  "-std=c++0x"
)
ENDIF(!WIN32)

set (COMMON_FILES
	${COMMON_INCLUDE_DIR}PacketType.hpp
)

SOURCE_GROUP (common FILES(${COMMON_FILES}))

##### Setting the output directory for the solution
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${EXECUTABLE_OUTPUT_PATH} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${EXECUTABLE_OUTPUT_PATH} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${EXECUTABLE_OUTPUT_PATH} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
#####


add_executable(
	RType_server
	${SRCS}
)

include_directories (
	${NET_INCLUDE_DIR}
	${NET_MUTEX_INCLUDE_DIR}
	${CORE_DIR}
	${CORE_CALLBACK_DIR}
	${CORE_QUADTREE_INCLUDE_DIR}
	${CORE_BULLETML_DIR}
	${CORE_TINYXML_DIR}
	${COMMON_INCLUDE_DIR}
)

###### linking net to core
target_link_libraries(
	core
	net
)

###link_directories(/chemin/vers/boost_x_xx_x/stage/lib)

target_link_libraries(
	RType_server
	core
	net
)