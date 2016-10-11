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

#include "cocSceneShape.h"

namespace coc {
namespace scene {

//--------------------------------------------------------------
Shape::Shape(std::string objID) :
coc::scene::Object(objID),
colorFill(1.0f, 1.0f, 1.0f, 1.0f),
colorStroke(1.0f, 1.0f, 1.0f, 0.0f) {

    objectType = coc::scene::ObjectTypeShape;
}

Shape::~Shape() {
    //
}

//--------------------------------------------------------------
ShapeRef Shape::create(std::string objID) {
    return ShapeRef(new Shape(objID));
}

void Shape::drawSelf() {

#if defined( COC_CI )
    ci::Rectf rect(0.0, 0.0, width, height);
    
    if(colorFill.a > 0.0) {
        pushColor(colorFill * colorWithAlphaAbsolute);
        ci::gl::drawSolidRect(rect);
        popColor();
    }
    
    if(colorStroke.a > 0.0) {
        pushColor(colorStroke * colorWithAlphaAbsolute);
        ci::gl::drawStrokedRect(rect);
        popColor();
    }
#endif
    
}

};
};
