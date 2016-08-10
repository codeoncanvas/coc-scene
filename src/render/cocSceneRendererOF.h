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

#if defined( COC_OF )

namespace coc {
namespace scene {

class RendererOF;
typedef std::shared_ptr<RendererOF> RendererOfRef;

class RendererOF : public coc::scene::Renderer {

public:

    RendererOF();
    ~RendererOF();
    
    static RendererOfRef create();
    
    void setup() override;
    void draw(const coc::scene::ObjectRef & object) const override;
    
};
};
};

#endif