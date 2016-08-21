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

#include "cocSceneTexture.h"

namespace coc {
namespace scene {

//--------------------------------------------------------------
Texture::Texture(std::string objID) : coc::scene::Object(objID), assetID("") {
    objectType = coc::scene::ObjectTypeTexture;
}

Texture::~Texture() {
    //
}

//--------------------------------------------------------------
TextureRef Texture::create(std::string objID) {
    return TextureRef(new Texture(objID));
}

void Texture::drawSelf() {

#ifdef COC_CI
    if(textureRef == NULL) {
        return;
    }
    ci::gl::draw(textureRef, ci::Rectf(0, 0, width, height));
#endif
}

};
};