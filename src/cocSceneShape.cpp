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

Shape::Shape() : coc::scene::Object() {
    objectType = coc::scene::ObjectTypeShape;
    colorStroke.r = colorStroke.g = colorStroke.b = 1.0;
    colorStroke.a = 0.0; // stroke is turned off by default.
    
    //
}

Shape::~Shape() {
    //
}

};

};