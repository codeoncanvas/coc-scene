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

#include "cocSceneObject.h"

namespace coc {
namespace scene {

class Texture;
typedef std::shared_ptr<Texture> TextureRef;

class Texture : public coc::scene::Object {

public:

    Texture(std::string objID="");
    ~Texture();
    
    static TextureRef create(std::string objID="");
    
    virtual void copyTo(TextureRef object) const;
    virtual void copyFrom(const TextureRef & object);
    
    std::string assetID;

protected:
    
    virtual void drawSelf() override;

};

};
};
