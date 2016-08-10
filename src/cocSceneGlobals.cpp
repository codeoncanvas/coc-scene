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
#include "cocAssetsCI.h" // coc-assets >> https://github.com/codeoncanvas/coc-assets
#include "cocAssetsOF.h" // coc-assets >> https://github.com/codeoncanvas/coc-assets

namespace coc {
namespace scene {

coc::Assets * assets = NULL;
void setAssets(coc::Assets * value) {
    assets = value;
}
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

};
};