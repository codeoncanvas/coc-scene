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

#include "cocSceneRenderer.h"

#if defined( COC_CI )

namespace coc {
namespace scene {

class RendererCI : public coc::scene::Renderer {

public:

    RendererCI();
    ~RendererCI();
    
    void setup() override;
    void update() override;
    
    void drawShape(const coc::scene::Shape & shape) override;
    void drawShapeRect(const coc::scene::Shape & shape) override;
    void drawShapeCircle(const coc::scene::Shape & shape) override;
    void drawTexture(const coc::scene::Texture & texture) override;
    
};
};
};

#endif