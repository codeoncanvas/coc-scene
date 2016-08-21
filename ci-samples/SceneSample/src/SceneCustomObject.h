
#pragma once

#include "cocSceneObject.h"
#include "cinder/gl/gl.h"

class SceneCustomObject : public coc::scene::Object {

public:

    SceneCustomObject(std::string objID="") : coc::scene::Object(objID) {
        std::cout << "SceneCustomObject constructor" << std::endl;
    }
    
    ~SceneCustomObject() {
        std::cout << "SceneCustomObject destructor" << std::endl;
    }
    
    void drawSelf() override {
        ci::gl::ScopedColor color(ci::Color(0.5, 0.5, 1.0));
        ci::gl::drawSolidCircle(glm::vec2(0, 0), 10);
    }

};
