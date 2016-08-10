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

void Renderer::setup() {

}

void Renderer::pushModelMatrix(const glm::mat4 & matrix) const {
    // override.
}

void Renderer::popModelMatrix() const {
    // override.
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
    
    for(int i=0; i<object->children.size(); i++) {
        draw(object->children[i]);
    }
}

};
};