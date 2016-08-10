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
    colorFill(1.0, 1.0, 1.0, 1.0),
    colorStroke(1.0, 1.0, 1.0, 0.0) {
    
    objectType = coc::scene::ObjectTypeShape;
}

Shape::~Shape() {
    //
}

//--------------------------------------------------------------
ShapeRef Shape::create(std::string objID) {
    return ShapeRef(new Shape(objID));
}

};
};