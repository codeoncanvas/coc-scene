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
#include "cocScene.h"

namespace coc {
namespace scene {

LoaderSvg::LoaderSvg() {
    //
}

LoaderSvg::~LoaderSvg() {
    //
}

void LoaderSvg::load(Scene & scene, std::string svgPath) {

#if defined( COC_CI )
    loadCI(scene, svgPath);
#endif

#if defined( COC_OF )
    loadOF(scene, svgPath);
#endif
}

void LoaderSvg::loadCI(Scene & scene, std::string svgPath) {
#if defined( COC_CI )

    //

#endif
}

void LoaderSvg::loadOF(Scene & scene, std::string svgPath) {
#if defined( COC_OF )
    
    //

#endif
}

};
};