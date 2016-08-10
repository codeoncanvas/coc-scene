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
#include "cocAssetsCI.h" // coc-assets >> https://github.com/codeoncanvas/coc-assets
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

RendererCiRef RendererCI::create() {
    return RendererCiRef(new RendererCI());
}

void RendererCI::setup() {
    
    //
}

void RendererCI::pushModelMatrix(const glm::mat4 & matrix) const {
    ci::gl::pushModelMatrix();
    ci::gl::multModelMatrix(matrix);
}

void RendererCI::popModelMatrix() const {
    ci::gl::popModelMatrix();
}

void RendererCI::drawShape(const coc::scene::ShapeRef & shape) const {

    drawShapeRect(shape);
}

void RendererCI::drawShapeRect(const coc::scene::ShapeRef & shape) const {
    
    ci::Rectf rect(0.0, 0.0, shape->width, shape->height);
    
    if(shape->colorFill.a > 0.0) {
        ci::gl::ScopedColor color(shape->colorFill);
        ci::gl::drawSolidRect(rect);
    }
    
    if(shape->colorStroke.a > 0.0) {
        ci::gl::ScopedColor color(shape->colorStroke);
        ci::gl::drawStrokedRect(rect);
    }
}

void RendererCI::drawShapeCircle(const coc::scene::ShapeRef & shape) const {
    //
}

void RendererCI::drawTexture(const coc::scene::TextureRef & texture) const {
    
    AssetsCI * assets = (AssetsCI *)getAssets();
    ci::gl::TextureRef textureRef = assets->getTextureRef(texture->assetID);
    if(textureRef == NULL) {
        return;
    }
    ci::gl::draw(textureRef, ci::Rectf(0, 0, texture->width, texture->height));
}

};
};

#endif