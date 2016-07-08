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
    coc::scene::Shape rect0;
};

void SceneSampleApp::setup() {
    
    scene.setup();
    
    rect0.x = 100;
    rect0.y = 100;
    rect0.width = 100;
    rect0.height = 100;
    rect0.colorStroke = glm::vec4(1.0, 0.0, 0.0, 1.0);
    
    scene.addChild(rect0);
}

void SceneSampleApp::update() {
    
    rect0.rotation = rect0.rotation + 0.01;
    
    scene.update();
}

void SceneSampleApp::draw() {

    gl::clear( Color( 0, 0, 0 ) );
    scene.draw();
}

CINDER_APP( SceneSampleApp, RendererGl )
