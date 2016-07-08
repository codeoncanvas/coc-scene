
#pragma once

#include "cocSceneObject.h"
#include "cinder/gl/gl.h"

class SceneDelegateObject : public coc::scene::ObjectDelegate {

public:

    void setup(coc::scene::Object & object) override {
        //
    };
    
    void update(coc::scene::Object & object) override {
        object.rotation = object.rotation + 0.01;
    };
    
    void draw(const coc::scene::Object & object) const override {
        //
    };

};
