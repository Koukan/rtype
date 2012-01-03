cmake_minimum_required (VERSION 2.8)

project(R-Type_Client)

set(EXECUTABLE_OUTPUT_PATH ../)

##### Linking the sfml libraries
IF(WIN32)
set(TYPE "Windows")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
set(SFML_INCLUDE_DIR "C:/Development/Environment/SFML2.0/include")
set(SFMLDIR "C:/Development/Environment/SFML2.0")
set(SFML_STATIC_LIBRARIES TRUE)
##find_package(SFML 2.0 REQUIRED SYSTEM GRAPHICS WINDOW)
set(SFML_LIBRARIES
	${SFML_GRAPHICS_LIBRARY}
	${SFML_WINDOW_LIBRARY}
	${SFML_SYSTEM_LIBRARY}
)
ELSE(WIN32)
set(TYPE "Unix")
set(SFML_INCLUDE_DIR /usr/include/SFML)
set(SFML_LIBRARIES
	sfml-graphics
	sfml-window
	sfml-system
	dl
)
ENDIF(WIN32)
#####

##### Linking core
set(CORE_INCLUDE_DIR
	"../common/core/"
)
set(CORE_CALLBACK_INCLUDE_DIR
	"../common/core/Callback_Impl/"
)
set(CORE_QUADTREE_INCLUDE_DIR
	"../common/core/QuadTree/"
)
set(CORE_BULLETML_INCLUDE_DIR
	"../common/core/bulletml/"
)
set(CORE_TINYXML_INCLUDE_DIR
	"../common/core/tinyxml/"
)
set(CORE_LIBRARY
	core
)

##### Linking libnet
set(NET_INCLUDE_DIR "../common/libnet/include")
set(NET_MUTEX_INCLUDE_DIR "../common/libnet/include/thread/")
set(NET_LIBRARY
	net
)


##### Setting the output directory for the solution
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${EXECUTABLE_OUTPUT_PATH} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${EXECUTABLE_OUTPUT_PATH} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${EXECUTABLE_OUTPUT_PATH} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
#####

set(TARGET_NAME rtype_client)

##### Add core headers
set(SRCS_CORE
	${CORE_INCLUDE_DIR}Bullet.hpp
	${CORE_INCLUDE_DIR}BulletCommand.hpp
	${CORE_INCLUDE_DIR}BulletResourceManager.hpp
	${CORE_INCLUDE_DIR}Callback.hpp
	${CORE_INCLUDE_DIR}Callback.ipp
	${CORE_INCLUDE_DIR}CircleHitBox.hpp
	${CORE_INCLUDE_DIR}Command.hpp
	${CORE_INCLUDE_DIR}CommandDispatcher.hpp
	${CORE_INCLUDE_DIR}CommandHandler.hpp
	${CORE_INCLUDE_DIR}Converter.hpp
	${CORE_INCLUDE_DIR}DrawableObject.hpp
	${CORE_INCLUDE_DIR}GameObject.hpp
	${CORE_INCLUDE_DIR}GameObjectManager.hpp
	${CORE_INCLUDE_DIR}GameObjectManager.ipp
	${CORE_INCLUDE_DIR}GameState.hpp
	${CORE_INCLUDE_DIR}GameStateManager.hpp
	${CORE_INCLUDE_DIR}GameStateObserver.hpp
	${CORE_INCLUDE_DIR}GSManager.hpp
	${CORE_INCLUDE_DIR}HitBox.hpp
	${CORE_INCLUDE_DIR}InputManager.hpp
	${CORE_INCLUDE_DIR}IPhysicsSubscriber.hpp
	${CORE_INCLUDE_DIR}Module.hpp
	${CORE_INCLUDE_DIR}ModuleManager.hpp
	${CORE_INCLUDE_DIR}NonCopyable.hpp
	${CORE_INCLUDE_DIR}Observable.hpp
	${CORE_INCLUDE_DIR}PhysicManager.hpp
	${CORE_INCLUDE_DIR}PhysicObject.hpp
	${CORE_INCLUDE_DIR}PhysicsSubscriber.hpp
	${CORE_INCLUDE_DIR}PhysicsSubscriber2.hpp
	${CORE_INCLUDE_DIR}PolyHitBox.hpp
	${CORE_INCLUDE_DIR}RectHitBox.hpp
	${CORE_INCLUDE_DIR}ResourceManager.hpp
	${CORE_INCLUDE_DIR}ResourceManager.ipp
	${CORE_INCLUDE_DIR}SharedLoader.hpp
	${CORE_INCLUDE_DIR}Sprite.hpp
	${CORE_INCLUDE_DIR}SpriteProvider.hpp
	${CORE_INCLUDE_DIR}TimeEffectManager.hpp
	${CORE_INCLUDE_DIR}Singleton.hpp
	${CORE_CALLBACK_INCLUDE_DIR}Callback_Impl.hpp
	${CORE_QUADTREE_INCLUDE_DIR}QuadTree.hpp
	${CORE_BULLETML_INCLUDE_DIR}bulletmlparser.h
	${CORE_TINYXML_INCLUDE_DIR}tinyxml.h
)

SOURCE_GROUP (core_headers FILES(${SRCS_CORE}))

##### Add libnet headers
set(SRCS_NET
	${NET_MUTEX_INCLUDE_DIR}Mutex.hpp
)
SOURCE_GROUP (net_headers FILES(${SRCS_NET}))

##	Font.cpp
##	Font.hpp
##	AudioManager.cpp
##	AudioManager.hpp

set(SRCS
	${SRCS_CORE}
	${SRCS_NET}
	main.cpp
	Game.cpp
	Game.hpp
	InputManager.cpp
	InputManager.hpp
	InputModule.cpp
	InputModule.hpp
	Loading.cpp
	Loading.hpp
	main.cpp
	RendererManager.cpp
	RendererManager.hpp
	SFMLSprite.cpp
	SFMLSprite.hpp
	SFMLSpriteProvider.cpp
	SFMLSpriteProvider.hpp
	Wall.cpp
	Wall.hpp
)

add_executable(
	${TARGET_NAME}
	${SRCS}
)

include_directories (
	${SFML_INCLUDE_DIR}
	${CORE_INCLUDE_DIR}
	${NET_INCLUDE_DIR}
	${NET_MUTEX_INCLUDE_DIR}
	${CORE_CALLBACK_INCLUDE_DIR}
	${CORE_QUADTREE_INCLUDE_DIR}
	${CORE_BULLETML_INCLUDE_DIR}
	${CORE_TINYXML_INCLUDE_DIR}
)

target_link_libraries(
	${TARGET_NAME}
	${SFML_LIBRARIES}
	${CORE_LIBRARY}
	${NET_LIBRARY}
)
