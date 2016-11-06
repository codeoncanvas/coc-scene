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
#include "cocAssetsCI.h"
#include "cocAssetsOF.h"

namespace coc {
namespace scene {

//--------------------------------------------------------------
Texture::Texture(std::string objID) :
coc::scene::Object(objID),
assetID("") {

    objectType = coc::scene::ObjectTypeTexture;
}

Texture::~Texture() {
    //
}

//--------------------------------------------------------------
TextureRef Texture::create(std::string objID) {
    return TextureRef(new Texture(objID));
}

//--------------------------------------------------------------
void Texture::copyTo(TextureRef object) const {
    *object = *this;
    Object::copyTo(object);
}

void Texture::copyFrom(const TextureRef & object) {
    *this = *object;
    Object::copyFrom(object);
}

//--------------------------------------------------------------
void Texture::drawSelf() {

    coc::Assets * assets = coc::scene::getAssets();

#if defined( COC_CI )
    ci::gl::TextureRef textureRef = ((coc::AssetsCI *)assets)->getTextureRef(assetID);
    if(textureRef == NULL) {
        return;
    }
    ci::gl::draw(textureRef, ci::Rectf(0, 0, width, height));
#endif
}

};
};
