#pragma once

#include <vector>
#include "./Entity.h"
#include "./Component.h"

namespace zen {

    class Component;


    class Node final {
    public:
        Node();
        ~Node();
        void addChild(Node *node);
        void removeChild(Node *node);
        void removeAllChildren();

        template<typename C>
        C * addComponent() {
            auto *c =  C::Storage::allocate(mEntity); 
            mComponents.emplace_back(c);
            return c;
        }

        template<typename C>
        void removeComponent(){
            C::Storage::free(mEntity);
            for(auto itr = mComponents.begin(); itr != mComponents.end(); itr++) {
                if((*itr)->name == C::name) {
                    mComponents.erase(itr);
                    break;
                }
            }
        }

        Component *addComponent(const std::string& name);
        void removeComponent(Component *comp);
        void removeComponent(const std::string &name);

        template<typename T>
        std::vector<Component*> getComponents() {
            
        }

    private:
        Entity mEntity;
        Node *mParent{nullptr};
        std::vector<std::unique_ptr<Node>> mChildren;
        std::vector<Component*> mComponents;
    };
}