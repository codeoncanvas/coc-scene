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
#include "cocSceneShapeSvg.h"
#include "cocSceneTexture.h"

#include "cinder/svg/Svg.h"
#include <glm/gtx/matrix_decompose.hpp>

namespace coc {
namespace scene {

using namespace ci;
using namespace ci::app;
using namespace ci::svg;

LoaderSvgCI::LoaderSvgCI() {
    doc = NULL;
}

LoaderSvgCI::~LoaderSvgCI() {
    if(doc != NULL) {
        delete doc;
        doc = NULL;
    }
}

void LoaderSvgCI::load(Object * object, std::string svgPath) {

    doc = new Doc(getAssetPath(svgPath));
    load(object, doc);
}

void LoaderSvgCI::load(Object * parent, Group * group) {

    const std::list<Node *> & children = group->getChildren();
    for(const Node * node : children) {

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
        
        if(dynamic_cast<const ci::svg::Use *>(node)) {
        
            node = ((ci::svg::Use *)node)->getReferenced();
        }
        
        if(dynamic_cast<const Group *>(node)) {
        
            child = new Object(objID);
            
        } else if(dynamic_cast<const ci::svg::Path *>(node)) {
        
            child = new ShapeSvg(ShapeSvgTypePath, node, objID);
            
        } else if(dynamic_cast<const ci::svg::Polygon *>(node)) {
        
            child = new ShapeSvg(ShapeSvgTypePolygon, node, objID);
            
        } else if(dynamic_cast<const ci::svg::Polyline *>(node)) {
        
            child = new ShapeSvg(ShapeSvgTypePolyline, node, objID);
            
        } else if(dynamic_cast<const ci::svg::Line *>(node)) {
        
            child = new ShapeSvg(ShapeSvgTypeLine, node, objID);
            
        } else if(dynamic_cast<const ci::svg::Rect *>(node)) {
        
            child = new ShapeSvg(ShapeSvgTypeRect, node, objID);
            
        } else if(dynamic_cast<const ci::svg::Circle *>(node)) {
        
            child = new ShapeSvg(ShapeSvgTypeCircle, node, objID);
            
        } else if(dynamic_cast<const ci::svg::Ellipse *>(node)) {
        
            child = new ShapeSvg(ShapeSvgTypeEllipse, node, objID);
            
        } else if(dynamic_cast<const ci::svg::Image *>(node)) {
        
            //
            
        } else if(dynamic_cast<const ci::svg::LinearGradient *>(node)) {
        
            //
            
        } else if(dynamic_cast<const ci::svg::RadialGradient *>(node)) {
        
            //
            
        } else if(dynamic_cast<const ci::svg::Text *>(node)) {
        
            //
        }
        
        if(child == NULL) {
            continue;
        }
        
        if(child->objectType == ObjectTypeShapeSvg) {

            ci::Shape2d shape2d = node->getShape();
            ci::Rectf boundingBox = shape2d.calcPreciseBoundingBox();

            child->x = boundingBox.getX1();
            child->y = boundingBox.getY1();
            child->width = boundingBox.getWidth();
            child->height = boundingBox.getHeight();
        }
    
        child->x = child->x + translation.x;
        child->y = child->y + translation.y;
        child->bDeleteOnExit = true;
        child->setup();
        
        parent->addChild(child);
    
        if(child->objectType == ObjectTypeBase) {
            
            // since its not a shape,
            // it must be a group.
            // drill down further!
            
            load(child, (Group * )node);
        }
    }
}

};
};

#endif