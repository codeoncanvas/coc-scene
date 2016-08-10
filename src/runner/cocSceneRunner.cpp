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
#include "cocSceneRendererCI.h"
#include "cocSceneRendererOF.h"

namespace coc {
namespace scene {

//--------------------------------------------------------------
Runner::Runner() {
    renderer = NULL;
}

Runner::~Runner() {
    //
}

//--------------------------------------------------------------
void Runner::setup(const ObjectRef & objectRef) {
    object = objectRef;

    solver = Solver::create();

#if defined( COC_OF )
    renderer = RendererOF::create();
#elif defined( COC_CI )
    renderer = RendererCI::create();
#endif
    
}

//--------------------------------------------------------------
void Runner::update() {
    solver->update(object);
}

//--------------------------------------------------------------
void Runner::draw() const {
    renderer->draw(object);
}

};
};