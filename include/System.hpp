#include <Entity.hpp>



class System {
    private:

    protected:
        std::shared_ptr<std::unordered_map<
            ComponentBitset,
            std::vector<std::shared_ptr<Entity>>,
            BitsetHash
        >> ptrArchetypes;

    public:
        System(
            std::shared_ptr<std::unordered_map<
                ComponentBitset,
                std::vector<std::shared_ptr<Entity>>,
                BitsetHash
            >> ptrArchetypes
        );
        virtual ~System();

        virtual void update();
        virtual void update(float deltaTime);
};


class MovementSystem: public System {
    private:

    public:
        MovementSystem(
            std::shared_ptr<std::unordered_map<
                ComponentBitset,
                std::vector<std::shared_ptr<Entity>>,
                BitsetHash
            >> ptrArchetypes
        );
        ~MovementSystem();

        void update() override;
        void update(float deltaTime) override;
};

