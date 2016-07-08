#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cocScene.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SceneSampleApp : public App {
  public:
	void setup() override;
	void update() override;
	void draw() override;
    
    coc::scene::Scene scene;
    coc::scene::Shape rect0 = coc::scene::Shape("r0");
    coc::scene::Shape rect1 = coc::scene::Shape("r1");
};

void SceneSampleApp::setup() {
    
    scene.setup();
    
    rect0.x = getWindowWidth() * 0.5;
    rect0.y = getWindowHeight() * 0.5;
    rect0.width = 100;
    rect0.height = 100;
    rect0.transformationPointX = rect0.width * 0.5;
    rect0.transformationPointY = rect0.height * 0.5;
    rect0.scale = 1.0;
    rect0.colorStroke = glm::vec4(1.0, 0.0, 0.0, 1.0);
    
    rect1.x = 50;
    rect1.y = 50;
    rect1.width = 50;
    rect1.height = 50;
    rect1.color = glm::vec4(1.0, 0.0, 0.0, 1.0);
    
    scene.addChild(rect0);
    rect0.addChild(rect1);
}

void SceneSampleApp::update() {
    
    rect0.rotation = rect0.rotation + 0.01;
    rect1.rotation = rect1.rotation + 0.01;
    
    scene.update();
}

void SceneSampleApp::draw() {

    gl::clear(Color(0, 0, 0));
    
    scene.draw();
    
    gl::ScopedColor color(Color(1.0, 0.0, 0.0));
    gl::drawSolidCircle(glm::vec2(getWindowWidth() * 0.5, getWindowHeight() * 0.5), 5);
}

CINDER_APP( SceneSampleApp, RendererGl )
