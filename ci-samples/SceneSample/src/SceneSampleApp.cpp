#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cocScene.h"
#include "SceneCustomObject.h"
#include "SceneDelegateObject.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace coc::scene;

class SceneSampleApp : public App {
  public:
	void setup() override;
	void update() override;
	void draw() override;
    
    Runner sceneRunner;
    ObjectRef sceneRoot;
    ObjectRef svg;
    ShapeRef rect0;
    ShapeRef rect1;
    SceneDelegateObject rect1Delegate;
    SceneCustomObject * customObj;
};

void SceneSampleApp::setup() {

    sceneRoot = Object::create("sceneRoot");
    sceneRunner.setup(sceneRoot);
    
    svg = LoaderSvgCI::loadSvg(getAssetPath("svg/coc_scene_svg_02.svg").string());
    sceneRoot->addChild(svg);

    rect0 = Shape::create("rect0");
    rect0->x = getWindowWidth() * 0.5;
    rect0->y = getWindowHeight() * 0.5;
    rect0->width = 100;
    rect0->height = 100;
    rect0->transformationPointX = rect0->width * 0.5;
    rect0->transformationPointY = rect0->height * 0.5;
    rect0->scale = 1.0;
    rect0->colorStroke = glm::vec4(1.0, 0.0, 0.0, 1.0);
    sceneRoot->addChild(rect0);
    
    rect1 = Shape::create("rect1");
    rect1->x = 50;
    rect1->y = 50;
    rect1->width = 50;
    rect1->height = 50;
    rect1->colorFill = glm::vec4(1.0, 0.0, 0.0, 1.0);
    rect1->delegate = &rect1Delegate;
    rect0->addChild(rect1);
    
    customObj = new SceneCustomObject("circle");
    customObj->x = getWindowWidth() * 0.5;
    customObj->y = getWindowHeight() * 0.5;
    sceneRoot->addChild( ObjectRef(customObj) );
}

void SceneSampleApp::update() {
    
    rect0->rotation = rect0->rotation + 0.01;
    
    sceneRunner.update();
}

void SceneSampleApp::draw() {

    gl::clear(Color(0, 0, 0));
    
    sceneRunner.draw();
}

CINDER_APP( SceneSampleApp, RendererGl )
