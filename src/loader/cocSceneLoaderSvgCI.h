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

#if defined( COC_CI )

#include "cocSceneLoaderSvg.h"

namespace cinder {
    class XmlTree;
}

namespace coc {
namespace scene {

class Texture;

//--------------------------------------------------------------
class LoaderSvgCI : public LoaderSvg {

public:

    LoaderSvgCI();
    ~LoaderSvgCI();
    
    void load(coc::scene::Object * object, std::string svgPath) override;

    void parseGroup(coc::scene::Object * object, const ci::XmlTree & xml);
    void parseGroupItem(coc::scene::Object * object, const ci::XmlTree & xml);
    void parseNode(coc::scene::Object * object, const ci::XmlTree & xml);
    void parseDefs(coc::scene::Object * object, const ci::XmlTree & xml);
    void parseUse(coc::scene::Object * object, const ci::XmlTree & xml);
    void parseRect(coc::scene::Object * object, const ci::XmlTree & xml);
    void parsePath(coc::scene::Object * object, const ci::XmlTree & xml);
    void parsePolygon(coc::scene::Object * object, const ci::XmlTree & xml);
    void parsePolyline(coc::scene::Object * object, const ci::XmlTree & xml);
    void parseLine(coc::scene::Object * object, const ci::XmlTree & xml);
    void parseCircle(coc::scene::Object * object, const ci::XmlTree & xml);
    void parseEllipse(coc::scene::Object * object, const ci::XmlTree & xml);
    void parseImage(coc::scene::Texture * object, const ci::XmlTree & xml);
    void parseLinearGradient(coc::scene::Object * object, const ci::XmlTree & xml);
    void parseRadialGradient(coc::scene::Object * object, const ci::XmlTree & xml);
    void parseText(coc::scene::Object * object, const ci::XmlTree & xml);
    
    void parseStyleAttribute(const std::string & stylePropertyString, LoaderSvgStyle & style);
    void parseProperty(const std::string & key, const std::string & value, LoaderSvgStyle & style);
    glm::vec4 * parseColor(const char * value);
    
    glm::mat3 parseTransform(const std::string & value);
    bool parseTransformComponent(const char **c, glm::mat3 * result);
    
    void pushStyle();
    void popStyle();
    
//    void load(Object * parent, const ci::XmlTree & xml);
  
    bool bDefs;
    std::map<std::string, const ci::XmlTree &> defs;
    std::vector<LoaderSvgStyle *> styleStack;
};

};
};

#endif