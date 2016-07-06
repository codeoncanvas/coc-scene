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
};

void SceneSampleApp::setup() {
    
    scene.setup();
}

void SceneSampleApp::update() {
    
    scene.update();
}

void SceneSampleApp::draw() {

    gl::clear( Color( 0, 0, 0 ) );
    scene.draw();
}

CINDER_APP( SceneSampleApp, RendererGl )
