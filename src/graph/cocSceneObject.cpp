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

//--------------------------------------------------------------
Object::Object(std::string objID) :
    objectID(objID),
    objectType(coc::scene::ObjectTypeBase),
    bManaged(false),
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
    delegate(NULL),
    parent(NULL) {
    
    //
}

Object::~Object() {
    
    parent = NULL;
    for(int i=0; i<children.size(); i++) {
        if(children[i]->bManaged == true) {
            
            // only delete objects which the scenegraph is responsible for creating.
            // objects created manually outside of the screngraph will not be deleted.
            
            delete children[i];
        }
    }
    children.clear();
}

//--------------------------------------------------------------
void Object::setup() {
    if(delegate != NULL) {
        delegate->setup(*this);
    }
}

void Object::update() {
    if(delegate != NULL) {
        delegate->update(*this);
    }
}

void Object::draw() const {
    if(delegate != NULL) {
        delegate->draw(*this);
    }
}

//--------------------------------------------------------------
void Object::copyTo(Object * object) const {
    *object = *this;
}

void Object::copyFrom(const Object * object) {
    *this = *object;
}

//--------------------------------------------------------------
void Object::addChild(Object * child) {
    if(child->parent != NULL) {
        child->parent->removeChild(child);
    }
    children.push_back(child);
	child->parent = this;
}

void Object::addChildAt(Object * child, int index) {
	if(index < 0 || index > children.size() - 1) {
		return;
    }
    if(child->parent != NULL) {
        child->parent->removeChild(child);
    }
	children.insert(children.begin() + index, child);
	child->parent = this;
}

bool Object::removeChild(Object * child) {
	for(int i=0; i<children.size(); i++) {
		if(children[i] == child) {
			child->parent = NULL;
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
	
	children[index]->parent = NULL;
	children.erase(children.begin() + index);
	return true;
}

bool Object::removeSelf() {
    if(parent == NULL) {
        return false;
    }
    return parent->removeChild(this);
}

void Object::removeAllChildren() {
    for(int i=0; i<children.size(); i++) {
        Object * child= children[ i ];
        child->parent = NULL;
        children.erase(children.begin() + i--);
    }
}

bool Object::replaceChild(Object * childOld, Object * childNew) {
    if(childOld == NULL || childNew == NULL) {
        return false;
    }
    for(int i=0; i<children.size(); i++) {
        if(children[i] == childOld) {
            children[i] = childNew;
            return true;
        }
    }
    return false;
}

bool Object::replaceChild(std::string childID, Object * childNew) {
    Object * childOld = getChildByID(childID);
    return replaceChild(childOld, childNew);
}

bool Object::replaceChildAt(int index, Object * childNew) {
    Object * childOld = getChildAt(index);
    return replaceChild(childOld, childNew);
}

bool Object::contains(const Object * child) const {
	for(int i=0; i<children.size(); i++) {
		if(children[i] == child) {
			return true;
		}
	}
	return false;
}

Object * Object::getChildAt(int index) const {
	if(index < 0 || index > children.size() - 1) {
		return NULL;
    }
	return children[index];
}

Object * Object::getChildByID(std::string objectID) const {
	for(int i=0; i<children.size(); i++) {
		if(children[i]->objectID == objectID) {
			return children[i];
		}
	}
	return NULL;
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

int Object::getChildIndex(const Object * child) const {
	for(int i=0; i<children.size(); i++) {
		if(children[i] == child) {
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