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

#include "cocSceneGlobals.h"

namespace coc {
namespace scene {

//--------------------------------------------------------------
std::vector<glm::mat4> modelMatixStack;
std::vector<glm::mat4> concatenatedModelMatixStack;

void pushModelMatrix(glm::mat4 mat) {
    modelMatixStack.push_back(mat);
    if(concatenatedModelMatixStack.size() == 0) {
        concatenatedModelMatixStack.push_back(mat);
    } else {
        concatenatedModelMatixStack.push_back(concatenatedModelMatixStack.back() * mat);
    }
}

void popModelMatrix() {
    modelMatixStack.pop_back();
    concatenatedModelMatixStack.pop_back();
}

//--------------------------------------------------------------
std::vector<glm::vec4> colorStack;
std::vector<glm::vec4> concatenatedColorStack;

void pushColor(glm::vec4 color) {
    colorStack.push_back(color);
    if(concatenatedColorStack.size() == 0) {
        concatenatedColorStack.push_back(color);
    } else {
        concatenatedColorStack.push_back(concatenatedColorStack.back() * color);
    }
}

void popColor() {
    colorStack.pop_back();
    concatenatedColorStack.pop_back();
}

};
};