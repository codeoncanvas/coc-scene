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

#include "cocSceneRenderer.h"
#include "cocSceneShape.h"
#include "cocSceneTexture.h"

namespace coc {
namespace scene {

Renderer::Renderer() {
    //
}

Renderer::~Renderer() {
    //
}

void Renderer::draw(const coc::scene::ObjectRef & object) const {

    bool bDraw = true;
    bDraw = bDraw && (object->visible);
    bDraw = bDraw && (object->alpha > 0.0);
    if(!bDraw) {
        return;
    }

    pushModelMatrix(object->modelMatrixConcatenated);

    if(object->objectType == coc::scene::ObjectTypeBase) {
    
        // base object has nothing to draw.
    
    } else if(object->objectType == coc::scene::ObjectTypeShape) {
    
        drawShape(std::static_pointer_cast<Shape>(object));
    
    } else if(object->objectType == coc::scene::ObjectTypeTexture) {
    
        drawTexture(std::static_pointer_cast<Texture>(object));
    }
    
    object->draw(); // custom drawing by either a custom subclass or object delegate.
    
    popModelMatrix();
    
    int numOfChildren = object->children.size();
    for(int i=0; i<numOfChildren; i++) {
        const coc::scene::ObjectRef & child = object->children[i];
        
        bool bMask = true;
        bMask = bMask && (child->mask != NULL); // has mask
        bMask = bMask && (i < numOfChildren-1); // there is a child above it, which could be the mask.
        if(bMask) {
            const coc::scene::ObjectRef & mask = object->children[i+1];
            bMask = bMask && (child->mask == mask.get());
            if(bMask) {
            
                // TODO: make masks work.
                
                i++; // skip ahead mask object.
                continue;
            }
        }
        
        draw(child);
    }
}

};
};