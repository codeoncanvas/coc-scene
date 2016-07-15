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

void Renderer::draw(const coc::scene::Object & object) const {

    ci::gl::ScopedModelMatrix modelMatrix;
    ci::gl::multModelMatrix(object.modelMatrix);

    if(object.objectType == coc::scene::ObjectTypeBase) {
    
        // base object has nothing to draw.
    
    } else if(object.objectType == coc::scene::ObjectTypeShape) {
    
        drawShape((const coc::scene::Shape &)object);
    
    } else if(object.objectType == coc::scene::ObjectTypeTexture) {
    
        drawTexture((const coc::scene::Texture &)object);
    }
    
    object.draw(); // custom drawing by either a custom subclass or object delegate.
    
    for(int i=0; i<object.children.size(); i++) {
        draw(*object.children[i]);
    }
}

};
};