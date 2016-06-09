//
//	    ┌─┐╔═╗┌┬┐┌─┐
//      │  ║ ║ ││├┤
//      └─┘╚═╝─┴┘└─┘
//	 ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
//	 │  ├─┤║║║└┐┌┘├─┤└─┐
//	 └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
//	http://codeoncanvas.cc
//
// Copyright (c) 2016, Code on Canvas Pty Ltd
//

#pragma once

#include "cocCore.h"

namespace coc {
namespace scene {

void pushModelMatrix(glm::mat4 mat);
void popModelMatrix();

void pushColor(glm::vec4 color);
void popColor();

};
};