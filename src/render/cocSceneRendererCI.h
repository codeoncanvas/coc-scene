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
    
    void pushModelMatrix(const glm::mat4 & matrix) const override;
    void popModelMatrix() const override;
    
    void drawShape(const coc::scene::Shape & shape) const override;
    void drawShapeRect(const coc::scene::Shape & shape) const override;
    void drawShapeCircle(const coc::scene::Shape & shape) const override;
    void drawTexture(const coc::scene::Texture & texture) const override;
};
};
};

#endif