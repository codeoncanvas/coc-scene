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
userInteractionEnabled(true),
bModelMatrixChanged(false),
bModelMatrixAbsoluteChanged(false),
color(1.0f, 1.0f, 1.0f),
colorWithAlpha(1.0f, 1.0f, 1.0f, 1.0f),
colorWithAlphaAbsolute(1.0f, 1.0f, 1.0f, 1.0f),
bColorChanged(false),
bColorAbsoluteChanged(false),
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
    //
}

//--------------------------------------------------------------
void Object::update() {
    updateSelf();
    updateChildren();
}

void Object::updateSelf() {

    //----------------------------------------------------------
    x.update();
    y.update();
    width.update();
    height.update();
    scale.update();
    rotation.update();
    alpha.update();
    visible.update();
    
    bool bUpdateOnEveryFrame = true;
    
    //----------------------------------------------------------
    bool bModelMatrixChanged = false;
    if(bUpdateOnEveryFrame) {
        bModelMatrixChanged = true;
    } else {
        bModelMatrixChanged = bModelMatrixChanged || x.hasChanged();
        bModelMatrixChanged = bModelMatrixChanged || y.hasChanged();
        bModelMatrixChanged = bModelMatrixChanged || scale.hasChanged();
        bModelMatrixChanged = bModelMatrixChanged || rotation.hasChanged();
    }
    if(bModelMatrixChanged == true) {
    
        glm::vec3 position(x, y, 0);
        glm::vec3 transformationPoint(transformationPointX, transformationPointY, 0);
        glm::vec3 rotationAxis(0, 0, 1);
        glm::vec3 scaleVec(scale, scale, 1);
    
        modelMatrixRelative = glm::translate(position);
        modelMatrixRelative = modelMatrixRelative * glm::rotate((float)rotation, rotationAxis);
        modelMatrixRelative = modelMatrixRelative * glm::scale(scaleVec);
        modelMatrixRelative = modelMatrixRelative * glm::translate(-transformationPoint);
    }
    
    bModelMatrixAbsoluteChanged = bModelMatrixChanged;
    if(parent) {
        bModelMatrixAbsoluteChanged = bModelMatrixAbsoluteChanged || parent->bModelMatrixAbsoluteChanged;
    }
    if(bModelMatrixAbsoluteChanged) {
        if(parent) {
            modelMatrixAbsolute = parent->modelMatrixAbsolute * modelMatrixRelative;
        } else {
            modelMatrixAbsolute = modelMatrixRelative;
        }
    }

    //----------------------------------------------------------
    bool bColorChanged = false;
    if(bUpdateOnEveryFrame) {
        bColorChanged = true;
    } else {
        bColorChanged = bColorChanged || (colorWithAlpha.r != color.r);
        bColorChanged = bColorChanged || (colorWithAlpha.g != color.g);
        bColorChanged = bColorChanged || (colorWithAlpha.b != color.b);
        bColorChanged = bColorChanged || (colorWithAlpha.a != alpha);
    }
    if(bColorChanged) {
    
        colorWithAlpha = glm::vec4(color, alpha);
    }
    
    bColorAbsoluteChanged = bColorChanged;
    if(parent) {
        bColorAbsoluteChanged = bColorAbsoluteChanged || parent->bColorAbsoluteChanged;
    }
    if(bColorAbsoluteChanged) {
        if(parent) {
            colorWithAlphaAbsolute = parent->colorWithAlphaAbsolute * colorWithAlpha;
        } else {
            colorWithAlphaAbsolute = colorWithAlpha;
        }
    }
}

void Object::updateChildren() {
    for(int i=0; i<children.size(); i++) {
        updateChild(children[i]);
    }
}

void Object::updateChild(const ObjectRef & child) {
    child->update();
}

//--------------------------------------------------------------
void Object::draw() {
    pushModelMatrix(modelMatrixRelative);
    pushColor(colorWithAlphaAbsolute);
    
    drawSelf();
    drawChildren();
    
    popModelMatrix();
    popColor();
}

void Object::drawSelf() {
    // override.
}

void Object::drawChildren() {
    for(int i=0; i<children.size(); i++) {
        drawChild(children[i]);
    }
}

void Object::drawChild(const ObjectRef & child) {
    bool bDraw = true;
    bDraw = bDraw && (child->visible);
    bDraw = bDraw && (child->alpha > 0.0);
    if(!bDraw) {
        return;
    }
    child->draw();
}

void Object::pushModelMatrix(const glm::mat4 & matrix) const {
#if defined( COC_CI )
    ci::gl::pushModelMatrix();
    ci::gl::multModelMatrix(matrix);
#endif
}

void Object::popModelMatrix() const {
#if defined( COC_CI )
    ci::gl::popModelMatrix();
#endif
}

void Object::pushColor(const glm::vec4 & color) const {
#if defined( COC_CI )
    ci::gl::color(ci::ColorA(color));
#endif
}

void Object::popColor() const {
#if defined( COC_CI )
    ci::gl::color(1.0, 1.0, 1.0, 1.0);
#endif
}

//--------------------------------------------------------------
void Object::pointMoved(int pointX, int pointY, int pointID) {
    for(int i=0; i<children.size(); i++) {
        if(children[i]->userInteractionEnabled == false) {
            continue;
        }
        children[i]->pointMoved(pointX, pointY, pointID);
    }
}

void Object::pointPressed(int pointX, int pointY, int pointID) {
    for(int i=0; i<children.size(); i++) {
        if(children[i]->userInteractionEnabled == false) {
            continue;
        }
        children[i]->pointPressed(pointX, pointY, pointID);
    }
}

void Object::pointDragged(int pointX, int pointY, int pointID) {
    for(int i=0; i<children.size(); i++) {
        if(children[i]->userInteractionEnabled == false) {
            continue;
        }
        children[i]->pointDragged(pointX, pointY, pointID);
    }
}

void Object::pointReleased(int pointX, int pointY, int pointID) {
    for(int i=0; i<children.size(); i++) {
        if(children[i]->userInteractionEnabled == false) {
            continue;
        }
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
std::vector<ObjectRef> & Object::getChildren() {
    return children;
}

ObjectRef Object::getChildAt(int index) const {
	return children[index];
}

ObjectRef Object::getChildByID(std::string objectID) const {
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

Object * Object::getParent() const {
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

//--------------------------------------------------------------
coc::Rect Object::getBounds()
{
	coc::Rect bounds;
	bounds.setX(x);
	bounds.setY(y);
	bounds.setW(width);
	bounds.setH(height);
	return bounds;

}

void Object::setBounds( coc::Rect &bounds )
{
	x = bounds.getX();
	y = bounds.getY();
	width = bounds.getW();
	height = bounds.getH();
}

};
};
