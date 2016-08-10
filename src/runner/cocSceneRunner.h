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
#include "cocSceneSolver.h"
#include "cocSceneRenderer.h"

namespace coc {
namespace scene {

class Renderer;
class Solver;

class Runner {

public:

    Runner();
    ~Runner();
    
    void setup(const ObjectRef & object);
    void update();
    void draw() const;
    
private:

    coc::scene::ObjectRef object;
    coc::scene::SolverRef solver;
    coc::scene::RendererRef renderer;
};

};
};