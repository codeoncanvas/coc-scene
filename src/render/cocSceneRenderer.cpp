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

    object.draw();

    if(object.objectType == coc::scene::ObjectTypeBase) {
    
        //
    
    } else if(object.objectType == coc::scene::ObjectTypeShape) {
    
        drawShape((const coc::scene::Shape &)object);
    
    } else if(object.objectType == coc::scene::ObjectTypeTexture) {
    
        drawTexture((const coc::scene::Texture &)object);
    }
    
    for(int i=0; i<object.children.size(); i++) {
        draw(*object.children[i]);
    }
}

};
};