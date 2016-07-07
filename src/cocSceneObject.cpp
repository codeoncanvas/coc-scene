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

#include "cocSceneObject.h"

namespace coc {

namespace scene {

Object::Object() :
    objectID(""),
    objectType(coc::scene::ObjectTypeBase),
    x(0.0f),
    y(0.0f),
    width(0.0f),
    height(0.0f),
    scale(1.0f),
    rotation(0.0f),
    alpha(1.0f),
    visible(true),
    color(1.0f, 1.0f, 1.0f, 1.0f),
    parent(NULL) {
    
    //
}

Object::~Object() {
    //
}

Object * Object::addChild(Object * child) {
    if(child->parent != NULL) {
        child->parent->removeChild(child);
    }
    
    children.push_back(child);
	child->parent = this;
    return child;
}

Object * Object::addChildAt(Object * child, int index) {
	if(index < 0 || index > children.size() - 1) {
		return NULL;
    }
    
    if(child->parent != NULL) {
        child->parent->removeChild(child);
    }
	
	children.insert(children.begin() + index, child);
	child->parent = this;
    return child;
}

bool Object::contains(Object * child) {
	for(int i=0; i<children.size(); i++) {
		if(children[i] == child) {
			return true;
		}
	}
	return false;
}

Object * Object::getChildAt(int index) {
	if(index < 0 || index > children.size() - 1) {
		return NULL;
    }
	return children[index];
}

Object * Object::getChildByID(std::string objectID) {
	for(int i=0; i<children.size(); i++) {
		if(children[i]->objectID == objectID) {
			return children[i];
		}
	}
	return NULL;
}

int Object::getChildIndex(Object * child) {
	for(int i=0; i<children.size(); i++) {
		if(children[i] == child) {
			return i;
		}
	}
	return -1;
}

Object * Object::removeChild(Object * child) {
	for(int i=0; i<children.size(); i++) {
		if(children[i] == child) {
			child->parent = NULL;
			children.erase(children.begin() + i);
			return child;
		}
	}
	return child;
}

Object * Object::removeChildAt(int index) {
	if(index < 0 || index > children.size() - 1) {
		return NULL;
    }
	
	Object * child = children[index];
	child->parent = NULL;
	children.erase(children.begin() + index);
	return child;
}

void Object::removeAllChildren() {
    for(int i=0; i<children.size(); i++) {
        Object * child= children[ i ];
        child->parent = NULL;
        children.erase(children.begin() + i--);
    }
}

void Object::setChildIndex(Object * child, int index) {
	if(index < 0 || index > children.size() - 1) {
		return;
    }

	for(int i=0; i<children.size(); i++) {
		if(children[i] == child) {
			children.erase(children.begin() + i);
			children.insert(children.begin() + index, child);
			return;
		}
	}
}

int Object::numChildren() {
	return children.size();
}

};
};