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
    ObjectTypeShape,
    ObjectTypeTexture,
    ObjectTypeCustom
};

//--------------------------------------------------------------
class Object;
typedef std::shared_ptr<Object> ObjectRef;

class Object {

friend class LoaderSvg;
friend class LoaderSvgCI;
friend class LoaderSvgOF;

public:

    Object(std::string objID="");
    ~Object();
    
    static ObjectRef create(std::string objID="");
    
    virtual void setup();
    virtual void update();
    virtual void draw();

	virtual void pointMoved(int pointX, int pointY, int pointID=0);
    virtual void pointPressed(int pointX, int pointY, int pointID=0);
	virtual void pointDragged(int pointX, int pointY, int pointID=0);
	virtual void pointReleased(int pointX, int pointY, int pointID=0);
    
    virtual void copyTo(ObjectRef object) const;
    virtual void copyFrom(const ObjectRef & object);
    
    virtual void addChild(const ObjectRef & child);
    virtual void addChildAt(const ObjectRef & child, int index);
    virtual void addChildAbove(const ObjectRef & child, const ObjectRef & childRef);
    virtual void addChildBelow(const ObjectRef & child, const ObjectRef & childRef);
    virtual void setChildIndex(const ObjectRef & child, int index);
    virtual bool removeChild(const ObjectRef & child);
    virtual bool removeChildAt(int index);
    virtual void removeAllChildren();
    virtual bool replaceChild(const ObjectRef & childOld, const ObjectRef & childNew);
    virtual bool replaceChild(std::string childID, const ObjectRef & childNew);
    virtual bool replaceChildAt(int index, const ObjectRef & childNew);

    std::vector<ObjectRef> & getChildren();
    ObjectRef getChildAt(int index) const;
    ObjectRef getChildByID(std::string objectID) const;
    ObjectRef findObjectByID(std::string objectID, Object * object=NULL);
    Object * getParent() const;
    bool contains(const ObjectRef & child) const;
    int getChildIndex(const ObjectRef & child) const;
    int numChildren() const;
    
    std::string getObjectID() const { return objectID; }
    unsigned int getObjectType() const { return objectType; }
    
	coc::Rect getBounds();
	void setBounds( coc::Rect & bounds );

    const glm::mat4 & getModelMatrixRelative() const { return modelMatrixRelative; }
	const glm::mat4 & getModelMatrixAbsolute() const { return modelMatrixAbsolute; }
    
    glm::vec2 localToScreen(const glm::vec2 & point) const;
    glm::vec2 screenToLocal(const glm::vec2 & point) const;

    coc::Value<float> x;
    coc::Value<float> y;
    coc::Value<float> width;
    coc::Value<float> height;
    coc::Value<float> scale;
    coc::Value<float> rotation;
    coc::Value<float> transformationPointX;
    coc::Value<float> transformationPointY;
    coc::Value<float> alpha;
    coc::Value<bool> visible;
    bool userInteractionEnabled;
    
    glm::vec3 color;
    
protected:

    virtual void updateSelf();
    virtual void updateChildren();
    virtual void updateChild(const ObjectRef & child);

    virtual void drawSelf();
    virtual void drawChildren();
    virtual void drawChild(const ObjectRef & child);
    
    virtual void pushModelMatrix(const glm::mat4 & matrix) const;
    virtual void popModelMatrix() const;
    
    virtual void pushColor(const glm::vec4 & color) const;
    virtual void popColor() const;

    std::string objectID;
    unsigned int objectType;
    
    glm::mat4 modelMatrixRelative;
    glm::mat4 modelMatrixAbsolute;
    bool bModelMatrixChanged;
    bool bModelMatrixAbsoluteChanged;
    
    glm::vec4 colorWithAlpha;
    glm::vec4 colorWithAlphaAbsolute;
    bool bColorChanged;
    bool bColorAbsoluteChanged;
    
    Object * parent;
    Object * mask; // TODO: still needs work. 
    std::vector<ObjectRef> children;
    
};
};
};
