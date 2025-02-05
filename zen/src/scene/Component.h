#pragma once

#include "Entity.h"
#include <string>
#include <unordered_map>
#include <valarray>

namespace zen {


    template<typename C>
    class ComponetStorage {
    public:
        static C * allocate(Entity ent);
        static void free(Entity ent);
    };

    class Component {
    public:
        constexpr static int Bits = 0;
        constexpr static std::string name = "_Component";
        using Storage = ComponetStorage<Component>;

    };

    struct ComponentAllocator {
        Component *(*allocate)(Entity);
        void (*free)(Entity);
    };

    class ComponentManager {
    public:
        template<typename C>
        void addAllocator(const std::string &name) {
            mAllocators.emplace(name, ComponentAllocator{.allocate = &C::Storage::allocate, .free = &C::Storage::free});
        }

        const ComponentAllocator * getAllocator(const std::string & name) const {
            auto itr = mAllocators.find(name);
            return itr == mAllocators.end() ? nullptr : &itr->second;
        }

        Component * allocate(const std::string& name, Entity ent) {
            auto *ac = getAllocator(name);
            return ac ? ac->allocate(ent) : nullptr;
        }

        void free(const std::string &name, Entity ent) {
            auto *ac = getAllocator(name);
            if(ac) {
                ac->free(ent);
            }
        }

    private: 
        std::unordered_map<std::string, ComponentAllocator> mAllocators;
    };
}