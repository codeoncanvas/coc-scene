#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cocScene.h"
#include "SceneCustomObject.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace coc::scene;

class SceneSampleApp : public App {
  public:
	void setup() override;
	void update() override;
	void draw() override;
    
    ObjectRef sceneRoot;
    ShapeRef rect0;
    ShapeRef rect1;
};

void SceneSampleApp::setup() {

    sceneRoot = Object::create("sceneRoot");
    
    ObjectRef svg = LoaderSvgCI::loadSvg(getAssetPath("svg/coc_scene_svg_02.svg").string());
    sceneRoot->addChild(svg);
    
    ObjectRef svgClone = coc::scene::Clone(svg); // deep clone of object and its children.
    svgClone->x = 300;
    svgClone->y = 100;
    sceneRoot->addChild(svgClone);

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
    rect0->addChild(rect1);
    
    SceneCustomObject * customObj;
    customObj = new SceneCustomObject("circle");
    customObj->x = getWindowWidth() * 0.5;
    customObj->y = getWindowHeight() * 0.5;
    sceneRoot->addChild( ObjectRef(customObj) );
}

void SceneSampleApp::update() {
    
    rect0->rotation = rect0->rotation + 0.01;
    rect1->rotation = rect1->rotation + 0.01;
    
    sceneRoot->update();
}

void SceneSampleApp::draw() {

    gl::clear(Color(0, 0, 0));
    
    sceneRoot->draw();
}

CINDER_APP( SceneSampleApp, RendererGl )
