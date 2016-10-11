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

ObjectRef Clone(const ObjectRef & object) {
    
    ObjectRef objectClone = nullptr;
    coc::scene::ObjectType objectType = (coc::scene::ObjectType)object->getObjectType();
    
    if((objectType == coc::scene::ObjectTypeBase) ||
       (objectType == coc::scene::ObjectTypeCustom)) {
        
        objectClone = coc::scene::Object::create();
        coc::scene::Object * objectClonePtr = (coc::scene::Object *)objectClone.get();
        coc::scene::Object * objectPtr = (coc::scene::Object *)object.get();
        *objectClonePtr = *objectPtr;
        
    } else if(objectType == coc::scene::ObjectTypeShape) {

        objectClone = coc::scene::Shape::create();
        coc::scene::Shape * objectClonePtr = (coc::scene::Shape *)objectClone.get();
        coc::scene::Shape * objectPtr = (coc::scene::Shape *)object.get();
        *objectClonePtr = *objectPtr;
    
    } else if(objectType == coc::scene::ObjectTypeTexture) {
    
        objectClone = coc::scene::Texture::create();
        coc::scene::Texture * objectClonePtr = (coc::scene::Texture *)objectClone.get();
        coc::scene::Texture * objectPtr = (coc::scene::Texture *)object.get();
        *objectClonePtr = *objectPtr;
    }
    
    objectClone->getChildren().clear();
    
    std::vector<ObjectRef> & children = object->getChildren();
    for(int i=0; i<children.size(); i++) {
        ObjectRef childClone = Clone(children[i]);
        objectClone->addChild(childClone);
    }

    return objectClone;
}

}
}
