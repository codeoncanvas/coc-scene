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

#include "cocSceneAssetsCI.h"

#if defined( COC_CI )

namespace coc {
namespace scene {

AssetsCI::AssetsCI() : coc::scene::Assets() {
    //
}

AssetsCI::~AssetsCI() {
    //
}

//--------------------------------------------------------------
void AssetsCI::load(std::string assetID) {
    AssetTextureCI * asset = (AssetTextureCI *)getAssetPtr(assetID);
    if(asset == NULL) {
        return;
    }

    asset->textureRef = ci::gl::Texture::create(ci::loadImage(asset->assetPath));
    asset->bLoaded = (asset->textureRef.get() != NULL);
}

void AssetsCI::unload(std::string assetID) {
    AssetTextureCI * asset = (AssetTextureCI *)getAssetPtr(assetID);
    if(asset == NULL) {
        return;
    }
    
    asset->textureRef = NULL;
    asset->bLoaded = false;
}

//--------------------------------------------------------------
void AssetsCI::update(float timeDelta) {
    Assets::update(timeDelta);

    //
}

//--------------------------------------------------------------
const ci::gl::Texture * AssetsCI::getTexture(std::string assetID) {
    AssetTextureCI * asset = (AssetTextureCI *)getAssetPtr(assetID);
    if(asset == NULL) {
        return NULL;
    }

    if(asset->bLoaded == false) {
        return NULL;
    }
    
    return asset->textureRef.get();
}

//--------------------------------------------------------------
Asset * AssetsCI::initAsset() {
    return new AssetTextureCI();
}

void AssetsCI::killAsset(Asset * asset) {
    delete (AssetTextureCI *)asset;
}

};
};

#endif