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

#include "cocSceneObject.h"

namespace coc {

namespace scene {

Object::Object() {
    objectID = "";
    objectType = 0;
    parent = NULL;
}

Object::~Object() {
    //
}

};

};