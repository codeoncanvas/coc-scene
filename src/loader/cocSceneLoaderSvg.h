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

namespace coc {
namespace scene {

class Object;

//--------------------------------------------------------------
class LoaderSvg {

public:

    LoaderSvg();
    ~LoaderSvg();
    
    virtual void load(Object * object, std::string svgPath);
    
};

//--------------------------------------------------------------
class LoaderSvgStyle {
public:

    LoaderSvgStyle() {
        opacity = NULL;
        fillOpacity = NULL;
        strokeOpacity = NULL;
        fill = NULL;
        stroke = NULL;
        strokeWidth = NULL;
        fillRule = NULL;
        lineCap = NULL;
        lineJoin = NULL;
        displayNone = NULL;
        visible = NULL;
    }
    
    ~LoaderSvgStyle() {
        if(opacity != NULL) {
            delete opacity;
        }
        if(fillOpacity != NULL) {
            delete fillOpacity;
        }
        if(strokeOpacity != NULL) {
            delete strokeOpacity;
        }
        if(fill != NULL) {
            delete fill;
        }
        if(stroke != NULL) {
            delete stroke;
        }
        if(strokeWidth != NULL) {
            delete strokeWidth;
        }
        if(fillRule != NULL) {
            delete fillRule;
        }
        if(lineCap != NULL) {
            delete lineCap;
        }
        if(lineJoin != NULL) {
            delete lineJoin;
        }
        if(displayNone != NULL) {
            delete displayNone;
        }
        if(visible != NULL) {
            delete visible;
        }
    }

    float * opacity;
    float * fillOpacity;
    float * strokeOpacity;
    glm::vec4 * fill;
    glm::vec4 * stroke;
    float * strokeWidth;
    unsigned int * fillRule;
    unsigned int * lineCap;
    unsigned int * lineJoin;
    bool * displayNone;
    bool * visible;
};

};
};