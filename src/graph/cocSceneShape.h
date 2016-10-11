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

class Shape;
typedef std::shared_ptr<Shape> ShapeRef;

class Shape : public coc::scene::Object {

public:

    Shape(std::string objID="");
    ~Shape();
    
    static ShapeRef create(std::string objID="");
    
    virtual void copyTo(ShapeRef & object) const;
    virtual void copyTo(Shape * object) const;
    virtual void copyFrom(const ShapeRef & object);
    virtual void copyFrom(const Shape * object);
    ShapeRef clone() const;
    
    glm::vec4 colorFill;
    glm::vec4 colorStroke;
    
protected:
    
    virtual void drawSelf() override;
};

};
};
