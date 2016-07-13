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

#include "cocSceneShapeSvg.h"

namespace coc {
namespace scene {

ShapeSvg::ShapeSvg(ShapeSvgType type, const void * node, std::string objID) : coc::scene::Object(objID) {
    objectType = coc::scene::ObjectTypeShapeSvg;
    svgType = type;
    svgNode = node;
}

ShapeSvg::~ShapeSvg() {
    //
}

};
};