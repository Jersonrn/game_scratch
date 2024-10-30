#include "Entity.hpp"




class Player: public Entity {
    public:
        Player(
            std::shared_ptr<std::unordered_map<
                ComponentBitset,
                std::vector<std::shared_ptr<Entity>>,
                BitsetHash
            >> ptrArchetypes
        );

        int initialize();
        virtual ~Player();

        void handleInputEvents(const SDL_KeyboardEvent& keyEvent) override;
};
