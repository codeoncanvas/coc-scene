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
#include "cocSceneAssetsCI.h"
#include "cocSceneAssetsOF.h"
#include "cocSceneSolver.h"
#include "cocSceneRendererCI.h"
#include "cocSceneRendererOF.h"

namespace coc {
namespace scene {

coc::scene::Assets * assets = NULL;
coc::scene::Assets * getAssets() {
    if(assets == NULL) {
#if defined( COC_OF )
        assets = new coc::scene::AssetsOF();
#elif defined( COC_CI )
        assets = new coc::scene::AssetsCI();
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