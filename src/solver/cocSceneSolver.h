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

namespace coc {
namespace scene {

class Solver;
typedef std::shared_ptr<Solver> SolverRef;

class Solver {

public:

    Solver();
    ~Solver();
    
    static SolverRef create();
    
    virtual void update(const coc::scene::ObjectRef & object);
    
protected:
    
    void updateObject(const coc::scene::ObjectRef & object);
    
    bool bModelMatrixConcatenatedChanged;
    
};
};
};