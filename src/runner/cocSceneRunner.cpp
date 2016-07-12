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

#include "cocSceneRunner.h"
#include "cocSceneObject.h"
#include "cocSceneSolver.h"
#include "cocSceneRendererCI.h"
#include "cocSceneRendererOF.h"

namespace coc {
namespace scene {

//--------------------------------------------------------------
SceneRunner::SceneRunner() {
    object = NULL;
    solver = NULL;
    renderer = NULL;
}

SceneRunner::~SceneRunner() {
    //
}

//--------------------------------------------------------------
void SceneRunner::setup(Object * obj) {
    object = obj;

    initSolver();
    initRenderer();
}

//--------------------------------------------------------------
void SceneRunner::initSolver() {
    killSolver();
    
    solver = new coc::scene::Solver();
    solver->setup();
}

void SceneRunner::killSolver() {
    if(solver == NULL) {
        return;
    }
    
    delete solver;
    solver = NULL;
}

//--------------------------------------------------------------
void SceneRunner::initRenderer() {
    killRenderer();

#if defined( COC_OF )
    renderer = new coc::scene::RendererOF();
#elif defined( COC_CI )
    renderer = new coc::scene::RendererCI();
#endif

    renderer->setup();
}

void SceneRunner::killRenderer() {
    if(renderer == NULL) {
        return;
    }
    
#if defined( COC_OF )
    delete (coc::scene::RendererOF *)renderer;
#elif defined( COC_CI )
    delete (coc::scene::RendererCI *)renderer;
#endif
    renderer = NULL;
}

//--------------------------------------------------------------
void SceneRunner::update() {
    solver->update(*object);
}

//--------------------------------------------------------------
void SceneRunner::draw() const {
    renderer->draw(*object);
}

};
};