/**
 *
 *      ┌─┐╔═╗┌┬┐┌─┐
 *      │  ║ ║ ││├┤
 *      └─┘╚═╝─┴┘└─┘
 *   ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
 *   │  ├─┤║║║└┐┌┘├─┤└─┐
 *   └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
 *
 * Copyright (c) 2016 Code on Canvas Pty Ltd, http://CodeOnCanvas.cc
 *
 **/

#include "cocScene.h"

namespace coc {
namespace scene {

ObjectRef deepCopy(const ObjectRef & object) {
    
    ObjectRef objectClone = nullptr;
    coc::scene::ObjectType objectType = (coc::scene::ObjectType)object->getObjectType();
    
    if((objectType == coc::scene::ObjectTypeBase) ||
       (objectType == coc::scene::ObjectTypeCustom)) {
        
        objectClone = object->clone();
        
    } else if(objectType == coc::scene::ObjectTypeShape) {
    
        objectClone = ((coc::scene::Shape *)object.get())->clone();
    
    } else if(objectType == coc::scene::ObjectTypeTexture) {
    
        objectClone = ((coc::scene::Texture *)object.get())->clone();
    }

    int numOfChildren = objectClone->numChildren();
    for(int i=0; i<numOfChildren; i++) {
        ObjectRef child = objectClone->getChildAt(0);
        deepCopy(child);
    }

    return objectClone;
}

}
}
