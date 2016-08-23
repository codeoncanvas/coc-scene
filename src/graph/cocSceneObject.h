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
friend class Solver;
friend class Renderer;
friend class RendererCI;
friend class RendererOF;

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
    
    void addChild(const ObjectRef & child);
    void addChildAt(const ObjectRef & child, int index);
    void addChildAbove(const ObjectRef & child, const ObjectRef & childRef);
    void addChildBelow(const ObjectRef & child, const ObjectRef & childRef);
    void setChildIndex(const ObjectRef & child, int index);
    bool removeChild(const ObjectRef & child);
    bool removeChildAt(int index);
    void removeAllChildren();
    bool replaceChild(const ObjectRef & childOld, const ObjectRef & childNew);
    bool replaceChild(std::string childID, const ObjectRef & childNew);
    bool replaceChildAt(int index, const ObjectRef & childNew);
    
    ObjectRef getChildAt(int index);
    ObjectRef getChildByID(std::string objectID);
    ObjectRef findObjectByID(std::string objectID, Object * object=NULL);
    Object * getParent();
    bool contains(const ObjectRef & child) const;
    int getChildIndex(const ObjectRef & child) const;
    int numChildren() const;
    
    std::string getObjectID() const { return objectID; }
    unsigned int getObjectType() const { return objectType; }

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
    
    glm::vec4 color;

	coc::Rect getBounds();
	void setBounds( coc::Rect & bounds );

	glm::mat4 & getMatrix() { return modelMatrixConcatenated; }
    
protected:

    virtual void drawSelf();
    virtual void drawChildren();
    virtual void drawChild(const ObjectRef & child);
    
    virtual void pushModelMatrix(const glm::mat4 & matrix) const;
    virtual void popModelMatrix() const;

    std::string objectID;
    unsigned int objectType;
    
    glm::mat4 modelMatrix;
    glm::mat4 modelMatrixConcatenated;
    
    Object * parent;
    Object * mask; // TODO: still needs work. 
    std::vector<ObjectRef> children;
    
};
};
};