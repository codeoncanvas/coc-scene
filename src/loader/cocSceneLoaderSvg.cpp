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

#include "cocSceneLoaderSvg.h"
#include "cocSceneObject.h"

namespace coc {
namespace scene {

LoaderSvg::LoaderSvg() {
    //
}

LoaderSvg::~LoaderSvg() {
    //
}

void LoaderSvg::load(Object & object, std::string svgPath) {
    // override.
}

};
};