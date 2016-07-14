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

#include "cocSceneAssets.h"

namespace coc {
namespace scene {

//--------------------------------------------------------------
Assets::Assets() {
    //
}

Assets::~Assets() {
    //
}

//--------------------------------------------------------------
const Asset & Assets::addAsset(std::string assetPath, std::string assetID) {
    assets.push_back(initAsset());
    Asset & asset = *assets.back();
    asset.assetPath = assetPath;
    asset.assetID = assetID;
    if(asset.assetID.length() == 0) {
        asset.assetID = asset.assetPath;
    }
    return asset;
}

void Assets::removeAsset(std::string assetID) {
    for(int i=0; i<assets.size(); i++) {
        if(assets[i]->assetID != assetID) {
            continue;
        }
        killAsset(assets[i]);
        assets.erase(assets.begin() + i);
        break;
    }
}

//--------------------------------------------------------------
void Assets::load(std::string assetID) {
    // override
}

void Assets::unload(std::string assetID) {
    // override
}

//--------------------------------------------------------------
void Assets::update(float timeDelta) {

    for(int i=0; i<assets.size(); i++) {
        Asset & asset = *assets[i];
        
        if(asset.bLoaded == false) {
            continue;
        }
        
        //
    }
}

//--------------------------------------------------------------
const Asset * Assets::getAsset(std::string assetID) const {
    return getAssetPtr(assetID);
}

//--------------------------------------------------------------
Asset * Assets::initAsset() {
    return new Asset();
}

void Assets::killAsset(Asset * asset) {
    delete asset;
}

//--------------------------------------------------------------
Asset * Assets::getAssetPtr(std::string assetID) const {
    for(int i=0; i<assets.size(); i++) {
        if(assets[i]->assetID == assetID) {
            return assets[i];
        }
    }
    return NULL;
}

};
};