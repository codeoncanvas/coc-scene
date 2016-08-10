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
#include "cocSceneObject.h"
#include "cocSceneShape.h"
#include "cocSceneTexture.h"

namespace coc {
namespace scene {

class Object;
class Shape;
class Texture;

class Renderer;
typedef std::shared_ptr<Renderer> RendererRef;

class Renderer {

public:

    Renderer();
    ~Renderer();
    
    virtual void setup();
    
    virtual void pushModelMatrix(const glm::mat4 & matrix) const;
    virtual void popModelMatrix() const;
    
    virtual void draw(const coc::scene::ObjectRef & object) const;
    
protected:
    
    virtual void drawShape(const coc::scene::ShapeRef & shape) const {};
    virtual void drawShapeRect(const coc::scene::ShapeRef & shape) const {};
    virtual void drawShapeCircle(const coc::scene::ShapeRef & shape) const {};
    virtual void drawTexture(const coc::scene::TextureRef & texture) const {};
    
};
};
};