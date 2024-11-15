#include "Entity.hpp"
#include <SDL2/SDL_events.h>
#include <utility>


class Enemy: public Entity {
    public:
        Enemy(
            std::shared_ptr<std::unordered_map<
                ComponentBitset,
                std::vector<std::shared_ptr<Entity>>,
                BitsetHash
            >> ptrArchetypes
        );
        int initialize();
        virtual ~Enemy();
};
