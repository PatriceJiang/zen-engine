#include "Node.h"
#include "scene/Component.h"
#include "scene/Context.h"
#include "scene/Entity.h"
#include <string_view>



namespace zen {

    Node::Node() {
        ContextScope scope;
        mEntity = scope.getEntityManager()->get();
    }

    Node::~Node() {
        ContextScope scope;
        scope.getEntityManager()->put(mEntity);
    }


    Component * Node::addComponent(const std::string& name) {
        ContextScope scope;
        auto *mgr= scope.getComponentManager();
        return mgr->allocate(name, this->mEntity);
    }

    void Node::removeComponent(Component *comp) {
        ContextScope scope;
        auto *mgr= scope.getComponentManager();
        return mgr->free(comp->name, this->mEntity);
    }
}