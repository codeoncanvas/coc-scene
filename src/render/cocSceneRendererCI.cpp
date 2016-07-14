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
#include "cocSceneAssetsCI.h"
#include "cocSceneShape.h"
#include "cocSceneShapeSvg.h"
#include "cocSceneTexture.h"
#include "cinder/gl/gl.h"
#include "cinder/svg/SvgGl.h"

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
    
    svgGL = new ci::SvgRendererGl();
}

void RendererCI::drawShape(const coc::scene::Shape & shape) const {

    drawShapeRect(shape);
}

void RendererCI::drawShapeSvg(const coc::scene::ShapeSvg & shape) const {

    if(shape.svgNode == NULL) {
        return;
    }

    ci::svg::Node * node = (ci::svg::Node *)shape.svgNode;

    ci::svg::Style style = node->calcInheritedStyle();
    style.startRender(*svgGL, true);
    
    if(shape.svgType == ShapeSvgTypePath) {
    
        svgGL->drawPath((ci::svg::Path &)*node);
    
    } else if(shape.svgType == ShapeSvgTypePolygon) {

        svgGL->drawPolygon((ci::svg::Polygon &)*node);
    
    } else if(shape.svgType == ShapeSvgTypePolyline) {

        svgGL->drawPolyline((ci::svg::Polyline &)*node);
    
    } else if(shape.svgType == ShapeSvgTypeLine) {

        svgGL->drawLine((ci::svg::Line &)*node);
    
    } else if(shape.svgType == ShapeSvgTypeRect) {

        svgGL->drawRect((ci::svg::Rect &)*node);
    
    } else if(shape.svgType == ShapeSvgTypeCircle) {

        svgGL->drawCircle((ci::svg::Circle &)*node);
    
    } else if(shape.svgType == ShapeSvgTypeEllipse) {

        svgGL->drawEllipse((ci::svg::Ellipse &)*node);
    }
    
    style.finishRender(*svgGL, true);
}

void RendererCI::drawShapeRect(const coc::scene::Shape & shape) const {
    
    ci::Rectf rect(0.0, 0.0, shape.width, shape.height);
    
    if(shape.colorFill.a > 0.0) {
        ci::gl::ScopedColor color(shape.colorFill);
        ci::gl::drawSolidRect(rect);
    }
    
    if(shape.colorStroke.a > 0.0) {
        ci::gl::ScopedColor color(shape.colorStroke);
        ci::gl::drawStrokedRect(rect);
    }
}

void RendererCI::drawShapeCircle(const coc::scene::Shape & shape) const {
    //
}

void RendererCI::drawTexture(const coc::scene::Texture & texture) const {
    
    AssetsCI * assets = (AssetsCI *)getAssets();
    ci::gl::TextureRef textureRef = assets->getTexture(texture.assetID);
    if(textureRef == NULL) {
        return;
    }
    ci::gl::draw(textureRef, ci::Rectf(0, 0, texture.width, texture.height));
}

};
};

#endif