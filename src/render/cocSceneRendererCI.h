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

class RendererCI;
typedef std::shared_ptr<RendererCI> RendererCiRef;

class RendererCI : public coc::scene::Renderer {

public:

    RendererCI();
    ~RendererCI();
    
    static RendererCiRef create();
    
    void setup() override;
    
    void pushModelMatrix(const glm::mat4 & matrix) const override;
    void popModelMatrix() const override;
    
    void drawShape(const coc::scene::ShapeRef & shape) const override;
    void drawShapeRect(const coc::scene::ShapeRef & shape) const override;
    void drawShapeCircle(const coc::scene::ShapeRef & shape) const override;
    void drawTexture(const coc::scene::TextureRef & texture) const override;
};
};
};

#endif