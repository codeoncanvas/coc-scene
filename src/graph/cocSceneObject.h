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

class ObjectDelegate {
public:
    virtual void setup(Object & object) {};
    virtual void update(Object & object) {};
    virtual void draw(const Object & object) const {};
};

//--------------------------------------------------------------
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
    
    virtual void setup();
    virtual void update();
    virtual void draw() const;

	virtual void pointMoved(int x, int y, int mouseID) {};
	virtual void pointDragged(int x, int y, int mouseID) {};
	virtual void pointPressed(int x, int y, int mouseID) {};
	virtual void pointReleased(int x, int y, int mouseID) {};
    
    virtual void copyTo(Object * object) const;
    virtual void copyFrom(const Object * object);
    
    void addChild(Object * child);
    void addChildAt(Object * child, int index);
    bool removeChild(Object * child);
    bool removeChildAt(int index);
    bool removeSelf();
    void removeAllChildren();
    bool replaceChild(Object * childOld, Object * childNew);
    bool replaceChild(std::string childID, Object * childNew);
    bool replaceChildAt(int index, Object * childNew);
    bool contains(const Object * child) const;
    Object * getChildAt(int index) const;
    Object * getChildByID(std::string objectID) const;
    Object * getParent();
    void setChildIndex(Object * child, int index);
    int getChildIndex(const Object * child) const;
    int numChildren() const;
    
    std::string getObjectID() const { return objectID; }
    unsigned int getObjectType() const { return objectType; }
    bool isMananged() const { return bManaged; }

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
    
    ObjectDelegate * delegate;
    
protected:

    std::string objectID;
    unsigned int objectType;
    bool bManaged;
    
    glm::mat4 modelMatrix;
    glm::mat4 modelMatrixConcatenated;
    
    coc::scene::Object * parent;
    std::vector<coc::scene::Object *> children;
    
};
};
};