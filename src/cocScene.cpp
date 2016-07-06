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
#include "cocSceneRendererCI.h"
#include "cocSceneRendererOF.h"

namespace coc {
namespace scene {

//--------------------------------------------------------------
Scene::Scene() {
    renderer = NULL;
}

Scene::~Scene() {
    //
}

//--------------------------------------------------------------
void Scene::setup() {
    coc::scene::Object::setup();

    initRenderer();
    renderer->setup();
}

void Scene::initRenderer() {
    killRenderer();

#if defined( COC_OF )
    renderer = new coc::scene::RendererOF();
#elif defined( COC_CI )
    renderer = new coc::scene::RendererCI();
#endif
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
}

//--------------------------------------------------------------
void Scene::update() {
    coc::scene::Object::update();
}

//--------------------------------------------------------------
void Scene::draw() {
    renderer->draw(*this);
}

};
};