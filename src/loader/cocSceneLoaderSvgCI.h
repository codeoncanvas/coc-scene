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

#if defined( COC_CI )

#include "cocSceneLoaderSvg.h"
#include "cinder/svg/Svg.h"

namespace coc {
namespace scene {

class LoaderSvgCI : public LoaderSvg {

public:

    LoaderSvgCI();
    ~LoaderSvgCI();
    
    void load(Object & object, std::string svgPath) override;
    void load(Object & object, ci::svg::Group * group);
    
};
};
};

#endif