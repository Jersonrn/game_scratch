#include "Entity.hpp"
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
