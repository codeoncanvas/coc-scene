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

#if defined( COC_OF )

namespace coc {
namespace scene {

class Scene;

class LoaderSvgOF : public LoaderSvg {

public:

    LoaderSvgOF();
    ~LoaderSvgOF();
    
    void load(Object * object, std::string svgPath) override;
    
};
};
};

#endif