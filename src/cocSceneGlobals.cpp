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

#include "cocSceneGlobals.h"
#include "cocSceneSolver.h"
#include "cocSceneRendererCI.h"
#include "cocSceneRendererOF.h"
#include "cocAssetsCI.h" // coc-assets >> https://github.com/codeoncanvas/coc-assets
#include "cocAssetsOF.h" // coc-assets >> https://github.com/codeoncanvas/coc-assets

namespace coc {
namespace scene {

coc::Assets * assets = NULL;
coc::Assets * getAssets() {
    if(assets == NULL) {
#if defined( COC_OF )
        assets = new coc::AssetsOF();
#elif defined( COC_CI )
        assets = new coc::AssetsCI();
#endif
    }
    return assets;
}

coc::scene::Solver * solver = NULL;
coc::scene::Solver * getSolver() {
    if(solver == NULL) {
        solver = new coc::scene::Solver();
    }
    return solver;
}

coc::scene::Renderer * renderer = NULL;
coc::scene::Renderer * getRenderer() {
    if(renderer == NULL) {
#if defined( COC_OF )
        renderer = new coc::scene::RendererOF();
#elif defined( COC_CI )
        renderer = new coc::scene::RendererCI();
#endif
    }
    return renderer;
}

};
};