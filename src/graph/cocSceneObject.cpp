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
parent(NULL),
mask(NULL) {
    
    //
}

Object::~Object() {
    parent = NULL;
    children.clear();
}

//--------------------------------------------------------------
ObjectRef Object::create(std::string objID) {
    return ObjectRef(new Object(objID));
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

void Object::draw() {
    if(delegate != NULL) {
        delegate->draw(*this);
    }
}

//--------------------------------------------------------------
void Object::pointMoved(int pointX, int pointY, int pointID) {
    for(int i=0; i<children.size(); i++) {
        children[i]->pointMoved(pointX, pointY, pointID);
    }
}

void Object::pointPressed(int pointX, int pointY, int pointID) {
    for(int i=0; i<children.size(); i++) {
        children[i]->pointPressed(pointX, pointY, pointID);
    }
}

void Object::pointDragged(int pointX, int pointY, int pointID) {
    for(int i=0; i<children.size(); i++) {
        children[i]->pointDragged(pointX, pointY, pointID);
    }
}

void Object::pointReleased(int pointX, int pointY, int pointID) {
    for(int i=0; i<children.size(); i++) {
        children[i]->pointReleased(pointX, pointY, pointID);
    }
}

//--------------------------------------------------------------
void Object::copyTo(ObjectRef object) const {
    *object = *this;

    // object properties have been copied over,
    // but the object children are still pointing to the old parent.
    // need to update to point to new parent.
    
    for(int i=0; i<object->children.size(); i++) {
        object->children[i]->parent = object.get();
    }
}

void Object::copyFrom(const ObjectRef & object) {
    *this = *object;
    
    // object properties have been copied over,
    // but the object children are still pointing to the old parent.
    // need to update to point to new parent.
    
    for(int i=0; i<children.size(); i++) {
        children[i]->parent = this;
    }
}

//--------------------------------------------------------------
void Object::addChild(const ObjectRef & child) {
    if(child->parent) {
        child->parent->removeChild(child);
    }
    children.push_back(child);
	child->parent = this;
}

void Object::addChildAt(const ObjectRef & child, int index) {
	if(index < 0 || index > children.size() - 1) {
		return;
    }
    if(child->parent) {
        child->parent->removeChild(child);
    }
	children.insert(children.begin() + index, child);
	child->parent = this;
}

void Object::addChildAbove(const ObjectRef & child, const ObjectRef & childRef) {
    for(int i=0; i<children.size(); i++) {
        if(children[i] == childRef) {
            children.insert(children.begin()+i+1, child);
        }
    }
}

void Object::addChildBelow(const ObjectRef & child, const ObjectRef & childRef) {
    for(int i=0; i<children.size(); i++) {
        if(children[i] == childRef) {
            children.insert(children.begin()+i, child);
        }
    }
}

void Object::setChildIndex(const ObjectRef & child, int index) {
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

bool Object::removeChild(const ObjectRef & child) {
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

void Object::removeAllChildren() {
    for(int i=0; i<children.size(); i++) {
        ObjectRef child= children[i];
        child->parent = NULL;
        children.erase(children.begin() + i--);
    }
}

bool Object::replaceChild(const ObjectRef & childOld, const ObjectRef & childNew) {
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

bool Object::replaceChild(std::string childID, const ObjectRef & childNew) {
    const ObjectRef & childOld = getChildByID(childID);
    return replaceChild(childOld, childNew);
}

bool Object::replaceChildAt(int index, const ObjectRef & childNew) {
    const ObjectRef & childOld = getChildAt(index);
    return replaceChild(childOld, childNew);
}

//--------------------------------------------------------------
ObjectRef Object::getChildAt(int index) {
	return children[index];
}

ObjectRef Object::getChildByID(std::string objectID) {
	for(int i=0; i<children.size(); i++) {
		if(children[i]->objectID == objectID) {
			return children[i];
		}
	}
    return ObjectRef();
}

ObjectRef Object::findObjectByID(std::string objectID, Object * object) {
    if(object == NULL) {
        object = this;
    }
    for(int i=0; i<object->children.size(); i++) {
        ObjectRef child = object->children[i];
        if(child == nullptr) {
            continue;
        }
        if(child->getObjectID() == objectID) {
            return child;
        }
        child = findObjectByID(objectID, child.get());
        if(child) {
            return child;
        }
    }
    return ObjectRef();
}

Object * Object::getParent() {
    return parent;
}

bool Object::contains(const ObjectRef & child) const {
	for(int i=0; i<children.size(); i++) {
		if(children[i] == child) {
			return true;
		}
	}
	return false;
}

int Object::getChildIndex(const ObjectRef & child) const {
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