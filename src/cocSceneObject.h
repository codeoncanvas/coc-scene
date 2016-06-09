//
//	    ┌─┐╔═╗┌┬┐┌─┐
//      │  ║ ║ ││├┤
//      └─┘╚═╝─┴┘└─┘
//	 ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
//	 │  ├─┤║║║└┐┌┘├─┤└─┐
//	 └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
//	http://codeoncanvas.cc
//
// Copyright (c) 2016, Code on Canvas Pty Ltd
//

#pragma once

#include "cocSceneGlobals.h"

namespace coc {
namespace scene {

class Object {

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

    std::string objectID;
    unsigned int objectType;
    
    coc::Rect rect;
    glm::mat4 modelMatrix;
    glm::vec4 color;
    
    coc::scene::Object * parent;
    std::vector<coc::scene::Object *> children;
    
};
};
};