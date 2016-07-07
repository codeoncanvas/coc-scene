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

#include "cocScene.h"
#include "cocSceneSolver.h"
#include "cocSceneRendererCI.h"
#include "cocSceneRendererOF.h"

namespace coc {
namespace scene {

//--------------------------------------------------------------
Scene::Scene() : coc::scene::Object() {
    solver = NULL;
    renderer = NULL;
}

Scene::~Scene() {
    //
}

//--------------------------------------------------------------
void Scene::setup() {
    coc::scene::Object::setup();

    initSolver();
    initRenderer();
}

//--------------------------------------------------------------
void Scene::initSolver() {
    killSolver();
    
    solver = new coc::scene::Solver();
    solver->setup();
}

void Scene::killSolver() {
    if(solver == NULL) {
        return;
    }
    
    delete solver;
    solver = NULL;
}

//--------------------------------------------------------------
void Scene::initRenderer() {
    killRenderer();

#if defined( COC_OF )
    renderer = new coc::scene::RendererOF();
#elif defined( COC_CI )
    renderer = new coc::scene::RendererCI();
#endif

    renderer->setup();
}

void Scene::killRenderer() {
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
void Scene::update() {
    solver->update(*this);
}

//--------------------------------------------------------------
void Scene::draw() {
    renderer->draw(*this);
}

};
};