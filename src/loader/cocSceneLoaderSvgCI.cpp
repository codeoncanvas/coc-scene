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
#include "cocSceneObject.h"

namespace coc {
namespace scene {

LoaderSvgCI::LoaderSvgCI() {
    //
}

LoaderSvgCI::~LoaderSvgCI() {
    //
}

void LoaderSvgCI::load(Object & object, std::string svgPath) {

    ci::svg::DocRef doc = ci::svg::Doc::create(ci::app::loadAsset(svgPath));
    load(object, doc.get());
}

void LoaderSvgCI::load(Object & object, ci::svg::Group * group) {

    std::list<ci::svg::Node *> & children = group->getChildren();
    for(ci::svg::Node * node : children) {
        ci::svg::Group * g = dynamic_cast<ci::svg::Group *>(node);
        if(g != NULL) {
            load(object, g);
        }
    }
}


};
};

#endif