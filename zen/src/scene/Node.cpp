#include "Node.h"
#include "scene/Component.h"
#include "scene/Context.h"
#include "scene/Entity.h"
#include <string_view>



namespace zen {

    Node::Node(Entity e):mEntity(e) {
    }

    Node::~Node() {

    }


    Component * Node::addComponent(std::string_view name) {
        ContextScope scope;
        auto *mgr= scope.getComponentManager();
        return mgr->allocate(name, this->mEntity);
    }
}