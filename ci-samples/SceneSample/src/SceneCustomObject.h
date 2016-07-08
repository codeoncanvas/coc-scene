
#pragma once

#include "cocSceneObject.h"
#include "cinder/gl/gl.h"

class SceneCustomObject : public coc::scene::Object {

public:

    SceneCustomObject(std::string objID="") : coc::scene::Object(objID) {
        //
    }
    
    void draw() const override {
        ci::gl::ScopedColor color(ci::Color(0.0, 0.0, 1.0));
        ci::gl::drawSolidCircle(glm::vec2(0, 0), 5);
    }

};
