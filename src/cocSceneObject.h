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

enum ObjectType {
    ObjectTypeBase = 0,
    ObjectTypeShape = 1,
    ObjectTypeTexture = 2
};

//class Solver;

class Object {

friend class Solver;
friend class Renderer;
friend class RendererCI;
friend class RendererOF;

public:

    Object();
    ~Object();
    
    virtual void setup() {};
    virtual void update() {};
    virtual void draw() {};

	virtual void pointMoved(int x, int y, int mouseID) {};
	virtual void pointDragged(int x, int y, int mouseID) {};
	virtual void pointPressed(int x, int y, int mouseID) {};
	virtual void pointReleased(int x, int y, int mouseID) {};
    
    Object * addChild(Object * child);
    Object * addChildAt(Object * child, int index);
    bool contains(Object * child);
    Object * getChildAt(int index);
    Object * getChildByID(std::string objectID);
    int getChildIndex(Object * child);
    Object * removeChild(Object * child);
    Object * removeChildAt(int index);
    void removeAllChildren();
    void setChildIndex(Object * child, int index);
    int numChildren();

    coc::Value<float> x;
    coc::Value<float> y;
    coc::Value<float> width;
    coc::Value<float> height;
    coc::Value<float> scale;
    coc::Value<float> rotation;
    coc::Value<float> alpha;
    coc::Value<bool> visible;
    
protected:

    std::string objectID;
    unsigned int objectType;
    
    glm::mat4 modelMatrix;
    glm::vec4 color;
    
    coc::scene::Object * parent;
    std::vector<coc::scene::Object *> children;
    
};
};
};