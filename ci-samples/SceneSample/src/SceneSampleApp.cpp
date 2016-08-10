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
//    ObjectRef rect0;
//    ObjectRef rect1;
//    ObjectRef circle;
//    SceneDelegateObject rect1Delegate;
};

void SceneSampleApp::setup() {

    sceneRoot = Object::create("sceneRoot");
    sceneRunner.setup(sceneRoot);
    
    svg = LoaderSvgCI::loadSvg(getAssetPath("svg/coc_scene_svg_02.svg").string());
    sceneRoot->addChild(svg);

//    Shape * shapeRect0 = new Shape("shapeRect0");
//    shapeRect0->x = getWindowWidth() * 0.5;
//    shapeRect0->y = getWindowHeight() * 0.5;
//    shapeRect0->width = 100;
//    shapeRect0->height = 100;
//    shapeRect0->transformationPointX = shapeRect0->width * 0.5;
//    shapeRect0->transformationPointY = shapeRect0->height * 0.5;
//    shapeRect0->scale = 1.0;
//    shapeRect0->colorStroke = glm::vec4(1.0, 0.0, 0.0, 1.0);
//    
//    Shape * shapeRect1 = new Shape("shapeRect1");
//    shapeRect1->x = 50;
//    shapeRect1->y = 50;
//    shapeRect1->width = 50;
//    shapeRect1->height = 50;
//    shapeRect1->colorFill = glm::vec4(1.0, 0.0, 0.0, 1.0);
//    shapeRect1->delegate = &rect1Delegate;
//    
//    SceneCustomObject * customObj = new SceneCustomObject("customCircle");
//    customObj->x = getWindowWidth() * 0.5;
//    customObj->y = getWindowHeight() * 0.5;
//    
//    rect0 = ObjectRef(shapeRect0);
//    rect1 = ObjectRef(shapeRect1);
//    circle = ObjectRef(customObj);
//    
//    sceneRoot->addChild(svg);
//    sceneRoot->addChild(rect0);
//    sceneRoot->addChild(circle);
//    
//    rect0->addChild(rect1);
}

void SceneSampleApp::update() {
    
//    rect0->rotation = rect0->rotation + 0.01;
    
    sceneRunner.update();
}

void SceneSampleApp::draw() {

    gl::clear(Color(0, 0, 0));
    
    sceneRunner.draw();
}

CINDER_APP( SceneSampleApp, RendererGl )
