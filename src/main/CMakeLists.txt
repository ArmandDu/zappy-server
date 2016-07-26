set(SOURCE_SERVER
        tcp/Request.cpp tcp/Request.h
        tcp/Server.cpp tcp/Server.h
        tcp/Socket.cpp tcp/Socket.h
        tcp/Client.cpp tcp/Client.h
        tcp/Select.cpp tcp/Select.h tcp/Response.cpp tcp/Response.h)

set(SOURCE_ZAPPY_FILES
        parser/Parser.cpp parser/Parser.h
        world/Rect.cpp                                      world/Rect.h
        world/endpoint/AbstractRequestHandler.cpp world/endpoint/AbstractRequestHandler.h
        world/endpoint/SpectatorRequestHandler.cpp world/endpoint/SpectatorRequestHandler.h
        world/World.cpp                                     world/World.h
        world/actors/player/Team.cpp world/actors/player/Team.h
        world/actors/player/Inventory.cpp world/actors/player/Inventory.h
        world/Timeout.cpp                                   world/Timeout.h
        world/actors/player/Player.cpp world/actors/player/Player.h
        world/actors/spectator/Spectator.cpp world/actors/spectator/Spectator.h
        world/Point.cpp                                     world/Point.h
        world/Square.cpp                                    world/Square.h
        world/Resource.cpp                                  world/Resource.h
        Game.cpp                                            Game.h
        world/endpoint/PlayerRequestHandler.cpp world/endpoint/PlayerRequestHandler.h
        world/actors/Actor.cpp world/actors/Actor.h
        world/actors/ActionInterface.h
        world/actors/player/actions/MoveAction.cpp world/actors/player/actions/MoveAction.h
        world/actors/player/actions/TurnAction.cpp world/actors/player/actions/TurnAction.h
        world/actors/player/actions/ManipulateResourceAction.cpp world/actors/player/actions/ManipulateResourceAction.h
        world/actors/player/actions/ConnectNbrAction.cpp world/actors/player/actions/ConnectNbrAction.h
        world/actors/player/actions/SeeAction.cpp world/actors/player/actions/SeeAction.h
        world/actors/player/actions/BroadcastAction.cpp world/actors/player/actions/BroadcastAction.h
        world/actors/player/actions/InventoryAction.cpp world/actors/player/actions/InventoryAction.h
        world/actors/player/actions/ExpelAction.cpp world/actors/player/actions/ExpelAction.h
        world/actors/player/actions/IncantationAction.cpp world/actors/player/actions/IncantationAction.h
        world/actors/player/actions/ForkAction.cpp world/actors/player/actions/ForkAction.h
        world/actors/spectator/actions/MapSizeAction.cpp world/actors/spectator/actions/MapSizeAction.h
        world/actors/spectator/actions/TeamListingAction.cpp world/actors/spectator/actions/TeamListingAction.h
        world/actors/spectator/actions/ServerTimeAction.cpp world/actors/spectator/actions/ServerTimeAction.h
        world/actors/spectator/actions/MapContentAction.cpp world/actors/spectator/actions/MapContentAction.h
        world/actors/spectator/actions/PlayerSpawnAction.cpp world/actors/spectator/actions/PlayerSpawnAction.h
        world/actors/spectator/actions/PlayerInventoryAction.cpp world/actors/spectator/actions/PlayerInventoryAction.h
        world/actors/spectator/actions/PlayerPositionOrientationAction.cpp world/actors/spectator/actions/PlayerPositionOrientationAction.h
        world/actors/spectator/actions/PlayerLevelAction.cpp world/actors/spectator/actions/PlayerLevelAction.h)

add_library(tcp_server ${SOURCE_SERVER})
add_library(zappy_game ${SOURCE_ZAPPY_FILES})

add_executable(zappy main.cpp)
target_link_libraries(zappy zappy_game tcp_server)

