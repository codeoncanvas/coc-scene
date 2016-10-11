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

//--------------------------------------------------------------
void Shape::copyTo(ShapeRef & object) const {
    copyTo(object);
}

void Shape::copyTo(Shape * object) const {
    *object = *this;
    Object::copyTo(object);
}

void Shape::copyFrom(const ShapeRef & object) {
    copyFrom(object.get());
}

void Shape::copyFrom(const Shape * object) {
    *this = *object;
    Object::copyFrom(object);
}

ShapeRef Shape::clone() const {
    ShapeRef object = Shape::create();
    object->copyFrom(this);
    return object;
}

//--------------------------------------------------------------
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
