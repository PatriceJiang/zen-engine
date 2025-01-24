#pragma once

#include <bitset>
#include <vector>
#include <string_view>
#include "./Entity.h"

namespace zen {

    class Component;


    class Node final {
    public:
        Node(Entity e);
        ~Node();
        void addChild(Node *node);
        void removeChild(Node *node);
        void removeAllChildren();

        template<typename C>
        C * addComponent() {
            return C::Storage::allocate(mEntity); 
        }

        template<typename C>
        void removeComponent(){
            C::Storage::free(mEntity);
        }

        Component *addComponent(std::string_view name);
        void removeComponent(Component *comp);
    private:
        Entity mEntity;
        Node *mParent{nullptr};
        std::vector<std::unique_ptr<Node>> mChildren;
        std::vector<Component*> mComponents;
    };
}