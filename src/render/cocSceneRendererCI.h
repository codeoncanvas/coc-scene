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

namespace cinder {
    class SvgRendererGl;
}

namespace coc {
namespace scene {

class RendererCI : public coc::scene::Renderer {

public:

    RendererCI();
    ~RendererCI();
    
    void setup() override;
    
    void drawShape(const coc::scene::Shape & shape) const override;
    void drawShapeRect(const coc::scene::Shape & shape) const override;
    void drawShapeCircle(const coc::scene::Shape & shape) const override;
    void drawShapeSvg(const coc::scene::ShapeSvg & shape) const override;
    void drawTexture(const coc::scene::Texture & texture) const override;
    
    ci::SvgRendererGl * svgGL;
};
};
};

#endif