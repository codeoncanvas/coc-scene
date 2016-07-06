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

#include "cocSceneRendererCI.h"
#include "cocSceneShape.h"
#include "cocSceneTexture.h"
#include "cinder/gl/gl.h"

#if defined( COC_CI )

namespace coc {
namespace scene {

RendererCI::RendererCI() : coc::scene::Renderer() {
    //
}

RendererCI::~RendererCI() {
    //
}

void RendererCI::setup() {
    //
}

void RendererCI::drawShape(const coc::scene::Shape & shape) const {
    drawShapeRect(shape);
}

void RendererCI::drawShapeRect(const coc::scene::Shape & shape) const {
    
    ci::Rectf rect(shape.x, shape.y, shape.x + shape.width, shape.y + shape.height);
    
    if(shape.color.a > 0.0) {
        ci::gl::drawSolidRect(rect);
    }
    
    if(shape.colorStroke.a > 0.0) {
        ci::gl::drawStrokedRect(rect);
    }
}

void RendererCI::drawShapeCircle(const coc::scene::Shape & shape) const {
    //
}

void RendererCI::drawTexture(const coc::scene::Texture & texture) const {
    //
}

};
};

#endif