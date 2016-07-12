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

class Object;
class Renderer;
class Solver;

class SceneRunner {

public:

    SceneRunner();
    ~SceneRunner();
    
    void setup(Object * obj);
    void update();
    void draw() const;
    
private:

    void initSolver();
    void killSolver();

    void initRenderer();
    void killRenderer();
    
    coc::scene::Object * object;
    coc::scene::Solver * solver;
    coc::scene::Renderer * renderer;
};

};
};