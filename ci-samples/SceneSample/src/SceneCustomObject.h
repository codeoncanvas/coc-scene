
#pragma once

#include "cocSceneObject.h"

class SceneCustomObject : public coc::scene::Object {

public:

    SceneCustomObject(std::string objID="");
    ~SceneCustomObject();
    
    void draw() const override;

};
