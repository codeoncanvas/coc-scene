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
    bModelMatrixConcatenatedChanged = false;
}

Solver::~Solver() {
    //
}

void Solver::update(coc::scene::Object & object) {

    bModelMatrixConcatenatedChanged = false;
    
    updateObject(object);
}

void Solver::updateObject(coc::scene::Object & object) {

    object.update();

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
    
        glm::vec3 position(object.x, object.y, 0.0);
        glm::vec3 transformationPoint(object.transformationPointX, object.transformationPointY, 0.0);
        glm::vec3 rotationAxis(0, 0, 1);
        glm::vec3 scale(object.scale, object.scale, 1.0);
    
        object.modelMatrix = glm::translate(position);
        object.modelMatrix = object.modelMatrix * glm::rotate((float)object.rotation, rotationAxis);
        object.modelMatrix = object.modelMatrix * glm::scale(scale);
        object.modelMatrix = object.modelMatrix * glm::translate(-transformationPoint);
    }
    
    bModelMatrixConcatenatedChanged = bModelMatrixConcatenatedChanged || bModelMatrixChanged;
    if(bModelMatrixConcatenatedChanged) {
    
        if(object.parent == NULL) {
            object.modelMatrixConcatenated = object.modelMatrix;
        } else {
            object.modelMatrixConcatenated = object.parent->modelMatrixConcatenated * object.modelMatrix;
        }
    }
    
    for(int i=0; i<object.children.size(); i++) {
        updateObject(*object.children[i]);
    }
}

};
};