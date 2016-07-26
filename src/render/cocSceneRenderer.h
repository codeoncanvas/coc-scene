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

#include "cocSceneGlobals.h"

namespace coc {
namespace scene {

class Object;
class Shape;
class Texture;

class Renderer {

public:

    Renderer();
    ~Renderer();
    
    virtual void setup();
    
    virtual void pushModelMatrix(const glm::mat4 & matrix) const;
    virtual void popModelMatrix() const;
    
    virtual void draw(const coc::scene::Object & object) const;
    
protected:
    
    virtual void drawShape(const coc::scene::Shape & shape) const {};
    virtual void drawShapeRect(const coc::scene::Shape & shape) const {};
    virtual void drawShapeCircle(const coc::scene::Shape & shape) const {};
    virtual void drawTexture(const coc::scene::Texture & texture) const {};
    
};
};
};