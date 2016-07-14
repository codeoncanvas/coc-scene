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

#include "cocSceneAssets.h"

#if defined( COC_CI )

namespace coc {
namespace scene {

//--------------------------------------------------------------
class AssetTextureCI : public AssetTexture {
public:
    AssetTextureCI() : AssetTexture() {
        //
    }
    
    ci::gl::TextureRef textureRef;
};

//--------------------------------------------------------------
class AssetsCI : public coc::scene::Assets {

public:

    AssetsCI();
    ~AssetsCI();
    
    void load(std::string assetID) override;
    void unload(std::string assetID) override;
    
    void update(float timeDelta=0) override;
    
    ci::gl::TextureRef getTexture(std::string assetID);
    
protected:

    Asset * initAsset() override;
    void killAsset(Asset * asset) override;
    
};

};
};

#endif