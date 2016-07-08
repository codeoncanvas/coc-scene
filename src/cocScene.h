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
#include "cocSceneShape.h"
#include "cocSceneTexture.h"

namespace coc {
namespace scene {

class Renderer;
class Solver;

class Scene : public coc::scene::Object {

public:

    Scene();
    ~Scene();
    
    void setup();
    void update();
    void draw();
    
private:

    void initSolver();
    void killSolver();

    void initRenderer();
    void killRenderer();
    
    coc::scene::Solver * solver;
    coc::scene::Renderer * renderer;
};

};
};