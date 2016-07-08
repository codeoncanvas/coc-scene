
#include "SceneCustomObject.h"
#include "cinder/gl/gl.h"

SceneCustomObject::SceneCustomObject(std::string objID) : coc::scene::Object(objID) {
    //
}

SceneCustomObject::~SceneCustomObject() {
    //
}

void SceneCustomObject::draw() const {
    ci::gl::ScopedColor color(ci::Color(0.0, 0.0, 1.0));
    ci::gl::drawSolidCircle(glm::vec2(0, 0), 5);
}