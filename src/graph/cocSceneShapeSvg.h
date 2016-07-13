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

#pragma once

#include "cocSceneObject.h"

namespace coc {
namespace scene {

enum ShapeSvgType {
    ShapeSvgTypeUndefined = 0,
    ShapeSvgTypePath,
    ShapeSvgTypePolygon,
    ShapeSvgTypePolyline,
    ShapeSvgTypeLine,
    ShapeSvgTypeRect,
    ShapeSvgTypeCircle,
    ShapeSvgTypeEllipse,
    ShapeSvgTypeText
};

class ShapeSvg : public coc::scene::Object {

public:

    ShapeSvg(ShapeSvgType type, const void * node, std::string objID="");
    ~ShapeSvg();
    
    ShapeSvgType svgType;
    const void * svgNode;
};

};
};