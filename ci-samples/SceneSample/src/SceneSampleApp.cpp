#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SceneSampleApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void SceneSampleApp::setup()
{
}

void SceneSampleApp::mouseDown( MouseEvent event )
{
}

void SceneSampleApp::update()
{
    //
}

void SceneSampleApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( SceneSampleApp, RendererGl )
