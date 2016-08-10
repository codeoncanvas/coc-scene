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

#include "cocSceneRendererOF.h"

#if defined( COC_OF )

namespace coc {
namespace scene {

RendererOF::RendererOF() : coc::scene::Renderer() {
    //
}

RendererOF::~RendererOF() {
    //
}

RendererOfRef RendererOF::create() {
    return RendererOfRef(new RendererOF());
}

void RendererOF::setup() {
    //
}

void RendererOF::draw(const coc::scene::ObjectRef & object) const {
    //
}

};
};

#endif