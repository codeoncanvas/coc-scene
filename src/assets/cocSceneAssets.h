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

//--------------------------------------------------------------
enum AssetType {
    AssetTypeNone = 0,
    AssetTypeTexture
};

//--------------------------------------------------------------
class Asset {
public:
    Asset() {
        type = AssetTypeNone;
        assetPath = "";
        assetID = "";
        bLoaded = false;
    }
    
    AssetType type;
    std::string assetPath;
    std::string assetID;
    bool bLoaded;
};

//--------------------------------------------------------------
class AssetTexture : public Asset {
public:
    AssetTexture() : Asset() {
        type = AssetTypeTexture;
    }
};

//--------------------------------------------------------------
class Assets {

public:

    Assets();
    ~Assets();
    
    virtual const Asset & addAsset(std::string assetPath, std::string assetID="");
    virtual void removeAsset(std::string assetID);
    
    virtual void load(std::string assetID);
    virtual void unload(std::string assetID);
    
    virtual void update(float timeDelta=0);
    
    const Asset * getAsset(std::string assetID) const;
    
protected:

    virtual Asset * initAsset();
    virtual void killAsset(Asset * asset);
    
    Asset * getAssetPtr(std::string assetID) const;
    
    std::vector<Asset *> assets;
};

};
};