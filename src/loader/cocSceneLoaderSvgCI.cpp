/**
 *
 *      ┌─┐╔═╗┌┬┐┌─┐
 *      │  ║ ║ ││├┤
 *      └─┘╚═╝─┴┘└─┘
 *   ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
 *   │  ├─┤║║║└┐┌┘├─┤└─┐
 *   └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
 *
 * Copyright (c) 2016 Code on Canvas Pty Ltd, http://CodeOnCanvas.cc
 *
 **/

#if defined( COC_CI )

#include "cocSceneLoaderSvgCI.h"
#include "cocSceneShapeSvg.h"
#include "cocSceneShape.h"
#include "cocSceneTexture.h"

#include "cinder/Xml.h"
#include "cinder/svg/Svg.h"
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/transform2.hpp>

namespace coc {
namespace scene {

using namespace ci;
using namespace ci::app;

LoaderSvgCI::LoaderSvgCI() {
    bDefs = false;
}

LoaderSvgCI::~LoaderSvgCI() {
    //
}

void LoaderSvgCI::load(Object * object, std::string svgPath) {

    DataSourceRef source = loadFile(getAssetPath(svgPath));
    XmlTree xml( source, XmlTree::ParseOptions().ignoreDataChildren( false ) );
    const XmlTree & xmlRoot( xml.getChild( "svg" ) );
    
	if(xmlRoot.hasChild("switch")) {
		parseGroup(object, xmlRoot.getChild("switch"));
    } else {
		parseGroup(object, xmlRoot);
    }
}

void LoaderSvgCI::parseGroup(Object * object, const XmlTree & xml) {

	for(XmlTree::ConstIter treeIt = xml.begin(); treeIt != xml.end(); ++treeIt) {
    
        parseGroupItem(object, *treeIt);
	}
}

void LoaderSvgCI::parseGroupItem(Object * object, const ci::XmlTree & xml) {

    std::string tag = xml.getTag();
    
    std::string defID = "";
    if(bDefs == true) {
        defID = xml["id"];
    }
    
    if(tag == "g") {

        Object * child = new Object();
        object->addChild(child);
        parseNode(child, xml);
        parseGroup(child, xml);
        
    } else if(tag == "defs") {
    
        bDefs = true;
        parseGroup(object, xml);
        bDefs = false;
        
    } else if(tag == "use") {
    
        parseUse(object, xml);
        
    } else if(tag == "rect") {
    
        if(bDefs == true) {
        
            defs.insert(std::pair<std::string, const ci::XmlTree &>(defID, xml));
        
        } else {

            Shape * child = new Shape();
            object->addChild(child);
            parseNode(child, xml);
            parseRect(child, xml);
        }
        
    } else if(tag == "path") {
    
        parsePath(object, xml);
        
    } else if(tag == "polygon") {
    
        parsePolygon(object, xml);
        
    } else if(tag == "polyline") {
    
        parsePolyline(object, xml);
        
    } else if(tag == "line") {
    
        parseLine(object, xml);
        
    } else if(tag == "circle") {
    
        parseCircle(object, xml);
        
    } else if(tag == "ellipse") {
    
        parseEllipse(object, xml);
        
    } else if(tag == "image") {
    
        parseImage(object, xml);
        
    } else if(tag == "linearGradient") {
    
        parseLinearGradient(object, xml);
        
    } else if(tag == "radialGradient") {
    
        parseRadialGradient(object, xml);
        
    } else if(tag == "text") {
    
        parseText(object, xml);
    }
}

void LoaderSvgCI::parseNode(Object * object, const ci::XmlTree & xml) {

    std::string objID = xml["id"];
    
    glm::vec3 scale(1, 1, 1);
    glm::quat orientation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    
    glm::mat3 m3;
    if(xml.hasAttribute( "transform")) {
        m3 = parseTransform( xml["transform"] );
        
        // TODO: lots of uncertainty around the conversion between mat3 to mat4.
        // glm doesn't provide a way to convert between mat3 to matm4 :(
        // wondering if i should maybe use mat3 inside the scene graph,
        // but then glm doesn't support decomposition for mat3.
        
        glm::mat4 m4(m3[0][0], m3[0][1], 0, 0,
                     m3[1][0], m3[1][1], 0, 0,
                     0,        0,        1, 0,
                     m3[2][0], m3[2][1], 0, 1);
        
        glm::decompose(m4, scale, orientation, translation, skew, perspective);
    }
    
    object->objectID = objID;
    object->x = translation.x;
    object->y = translation.y;
}

void LoaderSvgCI::parseDefs(Object * object, const ci::XmlTree & xml) {
    //
}

void LoaderSvgCI::parseUse(Object * object, const ci::XmlTree & xml) {

	if(xml.hasAttribute( "xlink:href") == false) {
        return;
    }
    std::string ref = xml.getAttributeValue<std::string>( "xlink:href" );
    
    if(ref.size() <= 1) {
        return;
    }
    if(ref[0] != '#') {
        return;
    }
    
    std::string defID = ref.substr(1, std::string::npos);
    const ci::XmlTree & xmlDef = defs.find(defID)->second;
    parseGroupItem(object, xmlDef);
}

void LoaderSvgCI::parseRect(Object * object, const ci::XmlTree & xml) {

    float x = 0;
    float y = 0;
	float width = 0;
    float height = 0;
	
	if(xml.hasAttribute("x")) {
		x = ci::svg::Value::parse(xml["x"] ).asUser();
    }
	if(xml.hasAttribute("y")) {
		y = ci::svg::Value::parse(xml["y"]).asUser();
    }
	if(xml.hasAttribute("width")) {
		width = ci::svg::Value::parse(xml["width"]).asUser();
    }
	if(xml.hasAttribute("height")) {
		height = ci::svg::Value::parse(xml["height"]).asUser();
    }
    
    object->x = x;
    object->y = y;
    object->width = width;
    object->height = height;
}

void LoaderSvgCI::parsePath(Object * object, const ci::XmlTree & xml) {
    //
}

void LoaderSvgCI::parsePolygon(Object * object, const ci::XmlTree & xml) {
    //
}

void LoaderSvgCI::parsePolyline(Object * object, const ci::XmlTree & xml) {
    //
}

void LoaderSvgCI::parseLine(Object * object, const ci::XmlTree & xml) {
    //
}

void LoaderSvgCI::parseCircle(Object * object, const ci::XmlTree & xml) {
    //
}

void LoaderSvgCI::parseEllipse(Object * object, const ci::XmlTree & xml) {
    //
}

void LoaderSvgCI::parseImage(Object * object, const ci::XmlTree & xml) {
    //
}

void LoaderSvgCI::parseLinearGradient(Object * object, const ci::XmlTree & xml) {
    //
}

void LoaderSvgCI::parseRadialGradient(Object * object, const ci::XmlTree & xml) {
    //
}

void LoaderSvgCI::parseText(Object * object, const ci::XmlTree & xml) {
    //
}

//--------------------------------------------------------------
glm::mat3 LoaderSvgCI::parseTransform( const std::string &value )
{
	const char *c = value.c_str();
	glm::mat3 curMat;
	glm::mat3 nextMat;
	while( parseTransformComponent( &c, &nextMat ) ) {
		curMat = curMat * nextMat;
	}
	return curMat;
}

bool LoaderSvgCI::parseTransformComponent( const char **c, glm::mat3 *result )
{
	// skip leading whitespace
	while( **c && ( isspace( **c ) || ( **c == ',' ) ) )
		(*c)++;
	
	glm::mat3 m;
	if( ! strncmp( *c, "scale", 5 ) ) {
		*c += 5; //strlen( "scale" );
		std::vector<float> v = parseFloatList( c );
		if( v.size() == 1 ) {
			m = glm::scale( glm::mat3(), vec2( v[0] ) );
		}
		else if( v.size() == 2 ) {
			m = glm::scale( glm::mat3(), vec2( v[0], v[1] ) );
		}
		else
			throw ci::svg::TransformParseExc();
	}
	else if( ! strncmp( *c, "translate", 9 ) ) {
		*c += 9; //strlen( "translate" );
		std::vector<float> v = parseFloatList( c );
		if( v.size() == 1 )
			m = glm::translate( glm::mat3(), vec2( v[0], 0 ) );
		else if( v.size() == 2 ) {
			m = glm::translate( glm::mat3(), vec2( v[0], v[1] ) );
		}
		else
			throw ci::svg::TransformParseExc();
	}
	else if( ! strncmp( *c, "rotate", 6 ) ) {
		*c += 6; //strlen( "rotate" );
		std::vector<float> v = parseFloatList( c );
		if( v.size() == 1 ) {
			float a = toRadians( v[0] );
			m = glm::rotate( glm::mat3(), a );
			//m33[0] = math<float>::cos( a ); m33[1] = math<float>::sin( a );
			//m33[3] = -math<float>::sin( a ); m33[4] = math<float>::cos( a );
		}
		else if( v.size() == 3 ) { // rotate around point
			float a = toRadians( v[0] );
			vec2 origin( v[1], v[2] );
			m = glm::translate( glm::mat3(), origin );
			m = glm::rotate( m, a );
			m = glm::translate( m, -origin );
		}
		else
			throw ci::svg::TransformParseExc();
	}
	else if( ! strncmp( *c, "matrix", 6 ) ) {
		*c += 6; //strlen( "matrix" );
		std::vector<float> v = parseFloatList( c );
		if( v.size() == 6 )
			m = glm::mat3( v[0], v[1], 0, v[2], v[3], 0, v[4], v[5], 1 );
		else
			throw ci::svg::TransformParseExc();
	}
	else if( ! strncmp( *c, "skewX", 5 ) ) {
		*c += 5; //strlen( "skewX" );
		std::vector<float> v = parseFloatList( c );
		if( v.size() == 1 ) {
			float a = toRadians( v[0] );
			m = glm::shearY2D( glm::mat3(), std::tan( a ) );
		}
		else
			throw ci::svg::TransformParseExc();
	}
	else if( ! strncmp( *c, "skewY", 5 ) ) {
		*c += 5; //strlen( "skewY" );
		std::vector<float> v = parseFloatList( c );
		if( v.size() == 1 ) {
			float a = toRadians( v[0] );
			//m33[1] = math<float>::tan( a );
			m = glm::shearX2D( glm::mat3(), std::tan( a ) );
		}
		else
			throw ci::svg::TransformParseExc();
	}
	else
		return false;

	*result = m;
	return true;		
}

std::vector<float> LoaderSvgCI::parseFloatList( const char **c ) {
	std::vector<float> result;
	while( **c && isspace( **c ) ) (*c)++;
	if( **c != '(' )
		return result; // failure
	(*c)++;
	do {
		result.push_back( parseFloat( c ) );
		while( **c && ( **c == ',' || isspace( **c ) ) ) (*c)++;
	} while( **c && **c != ')' );
	
	// get rid of trailing closing paren
	if( **c ) (*c)++;
	
	return result;
}

float LoaderSvgCI::parseFloat(const char **sInOut) {
	char temp[256];
	size_t i = 0;
	const char *s = *sInOut;
	while( *s && (isspace(*s) || *s == ',') )
		s++;
	if( ! s )
		throw ci::svg::PathParseExc();
	if( isNumeric( *s ) ) {
		while( *s == '-' || *s == '+' ) {
			if( i < sizeof(temp) )
				temp[i++] = *s;
			s++;
		}
		bool parsingExponent = false;
		bool seenDecimal = false;
		while( *s && ( parsingExponent || (*s != '-' && *s != '+')) && isNumeric(*s) ) {
			if( *s == '.' && seenDecimal )
				break;
			else if( *s == '.' )
				seenDecimal = true;
			if( i < sizeof(temp) )
				temp[i++] = *s;
			if( *s == 'e' || *s == 'E' )
				parsingExponent = true;
			else
				parsingExponent = false;
			s++;
		}
		temp[i] = 0;
		float result = (float)atof( temp );
		*sInOut = s;
		return result;
	}
	else
		throw ci::svg::FloatParseExc();
}

bool LoaderSvgCI::isNumeric(char c) {
	return ( c >= '0' && c <= '9' ) || c == '.' || c == '-' || c == 'e' || c == 'E' || c == '+';
}


//void LoaderSvgCI::load(Object * parent, const ci::XmlTree & xml) {
//
//    const std::list<Node *> & children = group->getChildren();
//    for(const Node * node : children) {
//
//        // TODO: lots of uncertainty around the conversion between mat3 to mat4.
//        // glm doesn't provide a way to convert between mat3 to matm4 :(
//        // wondering if i should maybe use mat3 inside the scene graph,
//        // but then glm doesn't support decomposition for mat3.
//        
//        glm::mat3 m3 = node->getTransform();
//        glm::mat4 m4(m3[0][0], m3[0][1], 0, 0,
//                     m3[1][0], m3[1][1], 0, 0,
//                     0,        0,        1, 0,
//                     m3[2][0], m3[2][1], 0, 1);
//        
//        glm::vec3 scale;
//        glm::quat orientation;
//        glm::vec3 translation;
//        glm::vec3 skew;
//        glm::vec4 perspective;
//        glm::decompose(m4, scale, orientation, translation, skew, perspective);
//        
//        Object * child = NULL;
//        std::string objID = node->getId();
//        
//        if(dynamic_cast<const ci::svg::Use *>(node)) {
//        
//            node = ((ci::svg::Use *)node)->getReferenced();
//        }
//        
//        if(dynamic_cast<const Group *>(node)) {
//        
//            child = new Object(objID);
//            
//        } else if(dynamic_cast<const ci::svg::Path *>(node)) {
//        
//            child = new ShapeSvg(ShapeSvgTypePath, node, objID);
//            
//        } else if(dynamic_cast<const ci::svg::Polygon *>(node)) {
//        
//            child = new ShapeSvg(ShapeSvgTypePolygon, node, objID);
//            
//        } else if(dynamic_cast<const ci::svg::Polyline *>(node)) {
//        
//            child = new ShapeSvg(ShapeSvgTypePolyline, node, objID);
//            
//        } else if(dynamic_cast<const ci::svg::Line *>(node)) {
//        
//            child = new ShapeSvg(ShapeSvgTypeLine, node, objID);
//            
//        } else if(dynamic_cast<const ci::svg::Rect *>(node)) {
//        
//            child = new ShapeSvg(ShapeSvgTypeRect, node, objID);
//            
//        } else if(dynamic_cast<const ci::svg::Circle *>(node)) {
//        
//            child = new ShapeSvg(ShapeSvgTypeCircle, node, objID);
//            
//        } else if(dynamic_cast<const ci::svg::Ellipse *>(node)) {
//        
//            child = new ShapeSvg(ShapeSvgTypeEllipse, node, objID);
//            
//        } else if(dynamic_cast<const ci::svg::Image *>(node)) {
//        
//            //
//            
//        } else if(dynamic_cast<const ci::svg::LinearGradient *>(node)) {
//        
//            //
//            
//        } else if(dynamic_cast<const ci::svg::RadialGradient *>(node)) {
//        
//            //
//            
//        } else if(dynamic_cast<const ci::svg::Text *>(node)) {
//        
//            //
//        }
//        
//        if(child == NULL) {
//            continue;
//        }
//        
//        if(child->objectType == ObjectTypeShapeSvg) {
//
//            ci::Shape2d shape2d = node->getShape();
//            ci::Rectf boundingBox = shape2d.calcPreciseBoundingBox();
//
//            child->x = boundingBox.getX1();
//            child->y = boundingBox.getY1();
//            child->width = boundingBox.getWidth();
//            child->height = boundingBox.getHeight();
//        }
//    
//        child->x = child->x + translation.x;
//        child->y = child->y + translation.y;
//        child->bDeleteOnExit = true;
//        child->setup();
//        
//        parent->addChild(child);
//
//        if(child->objectType == ObjectTypeBase) {
//            
//            // since its not a shape,
//            // it must be a group.
//            // drill down further!
//            
//            load(child, (Group * )node);
//        }
//    }
//}

};
};

#endif