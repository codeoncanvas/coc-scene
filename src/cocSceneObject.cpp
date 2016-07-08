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

static Object emptyObject;

Object::Object(std::string objID) :
    objectID(objID),
    objectType(coc::scene::ObjectTypeBase),
    x(0.0f),
    y(0.0f),
    width(0.0f),
    height(0.0f),
    scale(1.0f),
    rotation(0.0f),
    transformationPointX(0.0f),
    transformationPointY(0.0f),
    alpha(1.0f),
    visible(true),
    color(1.0f, 1.0f, 1.0f, 1.0f),
    parent(NULL) {
    
    //
}

Object::~Object() {
    //
}

void Object::addChild(Object & child) {
    if(child.parent != NULL) {
        child.parent->removeChild(child);
    }
    children.push_back(&child);
	child.parent = this;
}

void Object::addChildAt(Object & child, int index) {
	if(index < 0 || index > children.size() - 1) {
		return;
    }
    if(child.parent != NULL) {
        child.parent->removeChild(child);
    }
	children.insert(children.begin() + index, &child);
	child.parent = this;
}

bool Object::removeChild(Object & child) {
	for(int i=0; i<children.size(); i++) {
		if(children[i] == &child) {
			child.parent = NULL;
			children.erase(children.begin() + i);
			return true;
		}
	}
	return false;
}

bool Object::removeChildAt(int index) {
	if(index < 0 || index > children.size() - 1) {
		return false;
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

bool Object::contains(const Object & child) const {
	for(int i=0; i<children.size(); i++) {
		if(children[i] == &child) {
			return true;
		}
	}
	return false;
}

Object & Object::getChildAt(int index) const {
	if(index < 0 || index > children.size() - 1) {
		return emptyObject;
    }
	return *children[index];
}

Object & Object::getChildByID(std::string objectID) const {
	for(int i=0; i<children.size(); i++) {
		if(children[i]->objectID == objectID) {
			return *children[i];
		}
	}
	return emptyObject;
}

void Object::setChildIndex(Object & child, int index) {
	if(index < 0 || index > children.size() - 1) {
		return;
    }

	for(int i=0; i<children.size(); i++) {
		if(children[i] == &child) {
			children.erase(children.begin() + i);
			children.insert(children.begin() + index, &child);
			return;
		}
	}
}

int Object::getChildIndex(const Object & child) const {
	for(int i=0; i<children.size(); i++) {
		if(children[i] == &child) {
			return i;
		}
	}
	return -1;
}

int Object::numChildren() const {
	return children.size();
}

};
};