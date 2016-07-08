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

#include "cocSceneLoaderSvg.h"

#if defined( COC_CI )

namespace coc {
namespace scene {

class Scene;

class LoaderSvgCI : public LoaderSvg {

public:

    LoaderSvgCI();
    ~LoaderSvgCI();
    
    void load(Scene & scene, std::string svgPath) override;
    
};
};
};

#endif