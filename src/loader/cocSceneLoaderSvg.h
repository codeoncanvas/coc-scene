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

namespace coc {
namespace scene {

class Scene;

class LoaderSvg {

public:

    LoaderSvg();
    ~LoaderSvg();
    
    virtual void load(Scene & scene, std::string svgPath);
    
protected:
    
    void loadCI(Scene & scene, std::string svgPath);
    void loadOF(Scene & scene, std::string svgPath);
    
};
};
};