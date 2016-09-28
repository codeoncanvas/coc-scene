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

Solver::Solver():
bUpdateOnEveryFrame(true),
bModelMatrixAbsoluteChanged(false),
bColorConcatenatedChanged(false) {
    //
}

Solver::~Solver() {
    //
}

SolverRef Solver::create() {
    return SolverRef(new Solver());
}

void Solver::update(const coc::scene::ObjectRef & object) {

    bModelMatrixAbsoluteChanged = false;
    bColorConcatenatedChanged = false;
    
    updateObject(object);
}

void Solver::updateObject(const coc::scene::ObjectRef & object) {

    object->update();

    object->x.update();
    object->y.update();
    object->width.update();
    object->height.update();
    object->scale.update();
    object->rotation.update();
    object->alpha.update();
    object->visible.update();
    
    bool bModelMatrixRelativeChanged = false;
    if(bUpdateOnEveryFrame) {
        bModelMatrixRelativeChanged = true;
    } else {
        bModelMatrixRelativeChanged = bModelMatrixRelativeChanged || object->x.hasChanged();
        bModelMatrixRelativeChanged = bModelMatrixRelativeChanged || object->y.hasChanged();
        bModelMatrixRelativeChanged = bModelMatrixRelativeChanged || object->scale.hasChanged();
        bModelMatrixRelativeChanged = bModelMatrixRelativeChanged || object->rotation.hasChanged();
    }
    if(bModelMatrixRelativeChanged == true) {
    
        glm::vec3 position(object->x, object->y, 0.0);
        glm::vec3 transformationPoint(object->transformationPointX, object->transformationPointY, 0.0);
        glm::vec3 rotationAxis(0, 0, 1);
        glm::vec3 scale(object->scale, object->scale, 1.0);
    
        object->modelMatrixRelative = glm::translate(position);
        object->modelMatrixRelative = object->modelMatrixRelative * glm::rotate((float)object->rotation, rotationAxis);
        object->modelMatrixRelative = object->modelMatrixRelative * glm::scale(scale);
        object->modelMatrixRelative = object->modelMatrixRelative * glm::translate(-transformationPoint);
    }
    
    bModelMatrixAbsoluteChanged = bModelMatrixAbsoluteChanged || bModelMatrixRelativeChanged;
    if(bModelMatrixAbsoluteChanged) {
    
        if(object->parent == NULL) {
            object->modelMatrixAbsolute = object->modelMatrixRelative;
        } else {
            object->modelMatrixAbsolute = object->parent->modelMatrixAbsolute * object->modelMatrixRelative;
        }
    }
    
    bool bColorChanged = false;
    if(bUpdateOnEveryFrame) {
        bColorChanged = true;
    } else {
        bColorChanged = bColorChanged || (object->colorWithAlpha.r != object->color.r);
        bColorChanged = bColorChanged || (object->colorWithAlpha.g != object->color.g);
        bColorChanged = bColorChanged || (object->colorWithAlpha.b != object->color.b);
        bColorChanged = bColorChanged || (object->colorWithAlpha.a != object->alpha);
    }
    if(bColorChanged) {
    
        object->colorWithAlpha = glm::vec4(object->color, object->alpha);
    }
    
    bColorConcatenatedChanged = bColorConcatenatedChanged || bColorChanged;
    if(bColorConcatenatedChanged) {
    
        if(object->parent == NULL) {
            object->colorWithAlphaConcatenated = object->colorWithAlpha;
        } else {
            object->colorWithAlphaConcatenated = object->parent->colorWithAlphaConcatenated * object->colorWithAlpha;
        }
    }
    
    for(int i=0; i<object->children.size(); i++) {
        updateObject(object->children[i]);
    }
}

};
};