#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <algorithm>

namespace zen {

class EntityManager;

    class VersionSlot final {
    public:
        VersionSlot() = default;
        ~VersionSlot() = default;

        void drop() {
            version = (version > 0) ? ~version : version;
        }

        void incr() {
            version = (version > 0)? version + 1 : (~version) + 1;
        }

        bool isAlive() const {
            return version > 0;
        }

        bool operator==(const VersionSlot& other) const {
            return version == other.version;
        }

        VersionSlot &operator=(const VersionSlot&) = default;
    private:
        VersionSlot(int32_t v):version(v){}
         int32_t version{0};
         friend class EntityManager;
    };


    class Entity final {
    public:
        Entity() = default;
        Entity(VersionSlot v, uint32_t idx):version(v), index(idx) {}
        bool operator == (Entity e) const {
            return version == e.version && index == e.index;
        }
        bool operator != (Entity e) const {
            return !this->operator == (e); 
        }
        Entity(const Entity &) = default;
        Entity &operator = (const Entity&) = default;
    private:
        VersionSlot version;
        uint32_t index;

        friend class EntityManager;
    }; 

    class EntityManager final {
    public:
        EntityManager() {
            preAllocate();
        }  

        Entity get() {
            if(mFreeList.empty()) {
                preAllocate();
            }
            uint32_t index = mFreeList.back();
            mFreeList.pop_back();
            VersionSlot& entity = mEntities[index];
            entity.incr();
            return Entity{entity, index};
        }

        void put(Entity ent) {
            mFreeList.push_back(ent.index);
            mEntities[ent.index].drop();
        }

    private:
        void preAllocate() {
            if(mFreeList.size() > 16) {
                return; 
            }
            size_t size = std::min(16ULL, mEntities.size() * 2ULL);
            size_t start = mEntities.size();
            size_t end = start + size;
            mEntities.resize(size);
            for(uint32_t i = end - 1; i >= start; i--) {
                mFreeList.push_back(i);
            }
        }
        std::vector<VersionSlot> mEntities;
        std::vector<uint32_t> mFreeList;
    };
}