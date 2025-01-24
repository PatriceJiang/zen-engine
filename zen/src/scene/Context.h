#pragma  once


#include "scene/Component.h"
#include "scene/Entity.h"
namespace zen {
    
    class ContextScope {
    public:
        ContextScope() = default;

        EntityManager *getEntityManager();
        ComponentManager * getComponentManager();

    };
}