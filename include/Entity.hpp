#pragma once
#include "Texture.hpp"
#include <SDL2/SDL_events.h>
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <Utils.hpp>
#include <Component.hpp>



class Entity: public std::enable_shared_from_this<Entity> {
    private:
        bool active = true;
        std::size_t ID;
        static std::size_t counter;

        std::shared_ptr<std::unordered_map<
            ComponentBitset,
            std::vector<std::shared_ptr<Entity>>,
            BitsetHash
        >> ptrArchetypes;

    public:
        ComponentBitset componentBitset;
        std::vector<std::unique_ptr<Component>> components;
        std::unique_ptr<Texture> texture;

        Entity(
            std::shared_ptr<std::unordered_map<
                ComponentBitset,
                std::vector<std::shared_ptr<Entity>>,
                BitsetHash
            >> ptrArchetypes
        );
        virtual ~Entity();

        void virtual handleInputEvents(const SDL_Event& keyEvent);

        std::size_t getID();
        bool isActive();
        void destroy();
        void render();

        void updatePosition(float deltaTime);



        //TEMPLATES

        template<class T, class... TArgs>
        typename std::enable_if<std::is_base_of<Component, T>::value, void>::type
        addComponent(TArgs&&... Args) {
            std::shared_ptr<Entity> self = shared_from_this();

            if (!this->hasComponent<T>()) {
                int ID = getComponentID<T>();

                this->components[ID] = std::make_unique<T>(self, std::forward<TArgs>(Args)...);
                this->componentBitset[ID] = true;

            }

            //adding the entity to their respective archetypes
            if (!this->inArchetype<T>()) {
                (*this->ptrArchetypes)[getComponentBitset<T>()].push_back(self);
            }

            //adding the entity to PositionVelocity Archetype
            if (this->hasComponent<Velocity>() && this->hasComponent<Position>()) {
                ComponentBitset bitset = getComponentBitset<Velocity>() | getComponentBitset<Position>();
                if (!this->inArchetype(bitset)) {
                    (*this->ptrArchetypes)[bitset].push_back(self);
                }
            }
        };

        template<class T>
        typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type
        hasComponent() {
            return this->componentBitset[getComponentID<T>()];
        };

        template<typename T>
        T* getComponent() {
            /* return static_cast<T*>(this->components[getComponentID<T>()].get()); */
            return dynamic_cast<T*>(this->components[getComponentID<T>()].get());
        }

        bool inArchetype(ComponentBitset bitset){
            //search ComponentBitset in Archetype
            auto it = (*this->ptrArchetypes).find(bitset);

            //if ComponentBitset was found
            if (it != (*this->ptrArchetypes).end()) {
                for (auto &i: it->second) {
                    if (i->getID() == this->getID()) {
                        return true;
                    }
                }
            }
            return false;
        };

        template<typename  T>
        bool inArchetype() {
            return this->inArchetype(getComponentBitset<T>());
        };



};
