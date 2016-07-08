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

#include "cocSceneSolver.h"
#include "cocSceneObject.h"

namespace coc {
namespace scene {

Solver::Solver() {
    //
}

Solver::~Solver() {
    //
}

void Solver::setup() {

}

void Solver::update(coc::scene::Object & object) {

    object.x.update();
    object.y.update();
    object.width.update();
    object.height.update();
    object.scale.update();
    object.rotation.update();
    object.alpha.update();
    object.visible.update();
    
    bool bModelMatrixChanged = false;
    bModelMatrixChanged = bModelMatrixChanged || object.x.hasChanged();
    bModelMatrixChanged = bModelMatrixChanged || object.y.hasChanged();
    bModelMatrixChanged = bModelMatrixChanged || object.scale.hasChanged();
    bModelMatrixChanged = bModelMatrixChanged || object.rotation.hasChanged();
    if(bModelMatrixChanged == true) {
    
        object.modelMatrix = glm::translate(glm::vec3(object.x, object.y, 0.0));
        object.modelMatrix *= glm::rotate((float)object.rotation, glm::vec3(0, 0, 1));
        object.modelMatrix *= glm::scale(glm::vec3(object.scale, object.scale, 1.0));
    }
    
    for(int i=0; i<object.children.size(); i++) {
        update(*object.children[i]);
    }
}

};
};