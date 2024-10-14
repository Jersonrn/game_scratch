#pragma once
#include <cstddef>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <utils.hpp>
#include <Component.hpp>



class Entity: public std::enable_shared_from_this<Entity> {
    private:
        bool active = true;
        std::size_t ID;
        static std::size_t counter;

        ComponentBitset componentBitset;
        std::shared_ptr<std::unordered_map<
            ComponentBitset,
            std::vector<std::shared_ptr<Entity>>,
            BitsetHash
        >> ptrArchetypes;

    public:
        std::vector<std::unique_ptr<Component>> components;

        Entity(
            std::shared_ptr<std::unordered_map<
                ComponentBitset,
                std::vector<std::shared_ptr<Entity>>,
                BitsetHash
            >> ptrArchetypes
        );
        virtual ~Entity();

        std::size_t getID();
        bool isActive();
        void destroy();


        //TEMPLATES

        template<class T, class... TArgs>
        typename std::enable_if<std::is_base_of<Component, T>::value, void>::type
        addComponent(TArgs&&... Args) {
            if (!this->hasComponent<T>()) {
                int ID = getComponentID<T>();

                this->components[ID] = std::make_unique<T>(std::forward<TArgs>(Args)...);
                this->componentBitset[ID] = true;

            }
            if (!this->inArchetype<T>()) {
                std::shared_ptr<Entity> self = shared_from_this();
                (*this->ptrArchetypes)[getComponentBitset<T>()].push_back(self);
            }
            ComponentBitset bitset = getComponentBitset<T>() | this->componentBitset;
            if (!this->inArchetype(bitset)) {
                std::shared_ptr<Entity> self = shared_from_this();
                (*this->ptrArchetypes)[bitset].push_back(self);
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
