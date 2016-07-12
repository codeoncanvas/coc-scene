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

#if defined( COC_CI )

#include "cocSceneLoaderSvgCI.h"
#include "cocSceneShape.h"
#include "cocSceneTexture.h"

#include <glm/gtx/matrix_decompose.hpp>

namespace coc {
namespace scene {

using namespace ci;
using namespace ci::app;
using namespace ci::svg;

LoaderSvgCI::LoaderSvgCI() {
    //
}

LoaderSvgCI::~LoaderSvgCI() {
    //
}

void LoaderSvgCI::load(Object * object, std::string svgPath) {

    docRef = Doc::create(getAssetPath(svgPath));
    load(object, docRef.get());
}

void LoaderSvgCI::load(Object * parent, Group * group) {

    std::list<Node *> & children = group->getChildren();
    for(Node * node : children) {

        // TODO: lots of uncertainty around the conversion between mat3 to mat4.
        // glm doesn't provide a way to convert between mat3 to matm4 :(
        // wondering if i should maybe use mat3 inside the scene graph,
        // but then glm doesn't support decomposition for mat3.
        
        glm::mat3 m3 = node->getTransform();
        glm::mat4 m4(m3[0][0], m3[0][1], 0, 0,
                     m3[1][0], m3[1][1], 0, 0,
                     0,        0,        1, 0,
                     m3[2][0], m3[2][1], 0, 1);
        
        glm::vec3 scale;
        glm::quat orientation;
        glm::vec3 translation;
        glm::vec3 skew;
        glm::vec4 perspective;
        glm::decompose(m4, scale, orientation, translation, skew, perspective);
        
        Object * child = NULL;
        std::string objID = node->getId();
        
        auto * svgGroup = dynamic_cast<Group *>(node);
        auto * svgPath = dynamic_cast<ci::svg::Path *>(node);
        auto * svgPolygon = dynamic_cast<ci::svg::Polygon *>(node);
        auto * svgPolyline = dynamic_cast<ci::svg::Polyline *>(node);
        auto * svgLine = dynamic_cast<ci::svg::Line *>(node);
        auto * svgRect = dynamic_cast<ci::svg::Rect *>(node);
        auto * svgCircle = dynamic_cast<ci::svg::Circle *>(node);
        auto * svgEllipse = dynamic_cast<ci::svg::Ellipse *>(node);
        auto * svgUse = dynamic_cast<ci::svg::Use *>(node);
        auto * svgImage = dynamic_cast<ci::svg::Image *>(node);
        auto * svgLinearGradient = dynamic_cast<ci::svg::LinearGradient *>(node);
        auto * svgRadialGradient = dynamic_cast<ci::svg::RadialGradient *>(node);
        auto * svgText = dynamic_cast<ci::svg::Text *>(node);
        
        bool bGroup = (svgGroup != NULL);
        bool bImage = (svgImage != NULL);
        bool bShape = false;
        bShape = bShape || (svgPath != NULL);
        bShape = bShape || (svgPolygon != NULL);
        bShape = bShape || (svgPolyline != NULL);
        bShape = bShape || (svgLine != NULL);
        bShape = bShape || (svgRect != NULL);
        bShape = bShape || (svgCircle != NULL);
        bShape = bShape || (svgEllipse != NULL);
        bShape = bShape || (svgUse != NULL);
        bShape = bShape || (svgLinearGradient != NULL);
        bShape = bShape || (svgRadialGradient != NULL);
        bShape = bShape || (svgText != NULL);
        
        if(bShape) {

            ci::Shape2d shape2d = node->getShape();
            ci::Rectf boundingBox = shape2d.calcPreciseBoundingBox();

            child = new Shape(objID);
            child->x = boundingBox.getX1();
            child->y = boundingBox.getY1();
            child->width = boundingBox.getWidth();
            child->height = boundingBox.getHeight();
        }
    
        if(child == NULL) {
            child = new Object(objID);
        }
        
        child->x = child->x + translation.x;
        child->y = child->y + translation.y;
        child->bDeleteOnExit = true;
        child->svgNode = node;
        child->setup();
        
        parent->addChild(child);
    
        if(bGroup) {
            load(child, svgGroup);
        }
    }
}

};
};

#endif