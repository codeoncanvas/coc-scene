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
Runner::Runner() {
    object = NULL;
    solver = NULL;
    renderer = NULL;
}

Runner::~Runner() {
    //
}

//--------------------------------------------------------------
void Runner::setup(const ObjectRef & objectRef) {
    object = objectRef;
    solver = getSolver();
    renderer = getRenderer();
}

//--------------------------------------------------------------
void Runner::update() {
    solver->update(*object);
}

//--------------------------------------------------------------
void Runner::draw() const {
    renderer->draw(*object);
}

};
};