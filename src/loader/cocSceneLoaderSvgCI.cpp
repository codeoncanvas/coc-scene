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
#include "cocSceneShape.h"
#include "cocSceneTexture.h"
#include "cocAssets.h" // coc-assets >> https://github.com/codeoncanvas/coc-assets

#include "cinder/Xml.h"
#include "cinder/svg/Svg.h"
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/transform2.hpp>

namespace coc {
namespace scene {

using namespace ci;

//--------------------------------------------------------------
bool isNumeric(char c) {
	return ( c >= '0' && c <= '9' ) || c == '.' || c == '-' || c == 'e' || c == 'E' || c == '+';
}

float parseFloat(const char **sInOut) {
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

std::vector<float> parseFloatList( const char **c ) {
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

std::vector<ci::svg::Value> parseValueList( const char **c, bool requireParens = true )
{
	std::vector<ci::svg::Value> result;
	while( **c && isspace( **c ) ) (*c)++;
	if( requireParens ) {
		if( **c != '(' )
			return result; // failure
		(*c)++;
	}
	do {
		result.push_back( ci::svg::Value::parse( c ) );
		while( **c && ( **c == ',' || isspace( **c ) ) ) (*c)++;
	} while( **c && **c != ')' );
	
	// get rid of trailing closing paren
	if( requireParens && **c ) (*c)++;
	
	return result;
}

std::vector<ci::svg::Value> readValueList( const std::string &s, bool requireParens = true ) {
	const char *temp = s.c_str();
	return parseValueList( &temp, requireParens );
}

std::vector<ci::svg::Value> readValueList( const char *c, bool requireParens = true ) {
	const char *temp = c;
	return parseValueList( &temp, requireParens );
}

ci::svg::Value readValue( const std::string &s, float minV, float maxV )
{
	const char *temp = s.c_str();
	ci::svg::Value result = ci::svg::Value::parse( &temp );
	if( result.mValue < minV ) result = minV;
	if( result.mValue > maxV ) result = maxV;
	return result;
}

ci::svg::Value readValue( const std::string &s )
{
	const char *temp = s.c_str();
	ci::svg::Value result = ci::svg::Value::parse( &temp );
	return result;
}

//--------------------------------------------------------------
LoaderSvgCI::LoaderSvgCI() {
    bDefs = false;
    svgFolder = "";
}

LoaderSvgCI::~LoaderSvgCI() {
    //
}

void LoaderSvgCI::load(Object * object, std::string svgPath) {

    fs::path path(svgPath);
    svgFolder = path.remove_filename().string();
    
    DataSourceRef source = loadFile(svgPath);
    XmlTree xml( source, XmlTree::ParseOptions().ignoreDataChildren( false ) );
    const XmlTree & xmlRoot( xml.getChild( "svg" ) );
    
	if(xmlRoot.hasChild("switch")) {
		parseGroup(object, xmlRoot.getChild("switch"));
    } else {
		parseGroup(object, xmlRoot);
    }
    
    for(int i=0; i<assetPaths.size(); i++) {
        const std::string & assetPath = assetPaths[i];
        getAssets()->addAsset(assetPath, AssetTypeTexture);
        getAssets()->load(assetPath);
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

        pushStyle();

        parseNode(child, xml);
        parseGroup(child, xml);
        
        popStyle();
        
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
            
            pushStyle();
            
            parseNode(child, xml);
            parseRect(child, xml);
    
            popStyle();
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
    
        if(bDefs == true) {
        
            defs.insert(std::pair<std::string, const ci::XmlTree &>(defID, xml));
        
        } else {

            Texture * child = new Texture();
            object->addChild(child);
            
            pushStyle();
            
            parseNode(child, xml);
            parseImage(child, xml);
    
            popStyle();
        }
        
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
    
	for(std::list<ci::XmlTree::Attr>::const_iterator attIt = xml.getAttributes().begin(); attIt != xml.getAttributes().end(); ++attIt ) {
		if(attIt->getName() == "style") {
			parseStyleAttribute( attIt->getValue(), *styleStack.back());
        } else {
			parseProperty(attIt->getName(), attIt->getValue(), *styleStack.back());
        }
	}
    
    if(object->objectType == ObjectTypeShape) {

        Shape * shape = (Shape *)object;

        bool bFillFound = false;
        bool bStrokeFound = false;
        
        for(int i=styleStack.size()-1; i>=0; i--) {
            LoaderSvgStyle * style = styleStack[i];
            
            if((style->fill != NULL) && (bFillFound == false)) {
                shape->colorFill = *style->fill;
                bFillFound = true;
            }
            
            if((style->stroke != NULL) && (bStrokeFound == false)) {
                shape->colorStroke = *style->stroke;
                bStrokeFound = true;
            }
        }
    }
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

    float x = xml.getAttributeValue<float>("x", 0);
    float y = xml.getAttributeValue<float>("y", 0);
	float width = xml.getAttributeValue<float>("width", 0);
    float height = xml.getAttributeValue<float>("height", 0);
    
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

void LoaderSvgCI::parseImage(Texture * object, const ci::XmlTree & xml) {

    float x = xml.getAttributeValue<float>("x", 0);
    float y = xml.getAttributeValue<float>("y", 0);
	float width = xml.getAttributeValue<float>("width", 0);
    float height = xml.getAttributeValue<float>("height", 0);
    
    object->x = x;
    object->y = y;
    object->width = width;
    object->height = height;
    
	if(xml.hasAttribute( "xlink:href" ) == false) {
        return;
    }
    std::string s = xml.getAttributeValue<std::string>( "xlink:href" );
    if( s.find( "data:" ) == 0 ) {
        // TODO: load data directly.
        return;
    }
    
    fs::path assetPath(svgFolder);
    assetPath.append("/" + s); // TODO: is there a better way of appending which handles extra slashes or lack of?
    object->assetID = assetPath.string();
    
    assetPaths.push_back(assetPath.string());
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
void LoaderSvgCI::parseStyleAttribute(const std::string & stylePropertyString, LoaderSvgStyle & style) {
	std::vector<std::string> valuePairs = split( stylePropertyString, ';' );
	for(std::vector<std::string>::const_iterator pairIt = valuePairs.begin(); pairIt != valuePairs.end(); ++pairIt ) {
		std::vector<std::string> valuePair = split( *pairIt, ':' );
		if(valuePair.size() != 2) {
			continue;
        }
		parseProperty(valuePair[0], valuePair[1], style);
	}
}

void LoaderSvgCI::parseProperty(const std::string & key, const std::string & value, LoaderSvgStyle & style) {
	
    if(key == "fill" ) {
    
        style.fill = parseColor(value.c_str());
        
	} else if( key == "stroke" ) {
    
        style.stroke = parseColor(value.c_str());
        
	} else if( key == "opacity" ) {
    
		float opacity = readValue( value.c_str(), 0, 1 ).asUser();
        style.opacity = new float(opacity);
        
	} else if( key == "fill-opacity" ) {
    
		float fillOpacity = readValue( value.c_str(), 0, 1 ).asUser();
		style.fillOpacity = new float(fillOpacity);
        
	} else if( key == "stroke-opacity" ) {
    
		float strokeOpacity = readValue( value.c_str(), 0, 1 ).asUser();
		style.strokeOpacity = new float(strokeOpacity);
        
	} else if( key == "stroke-width" ) {
    
		if( value != "inherit" ) {
			float strokeWidth = (float)atof( value.c_str() );
            style.strokeWidth = new float(strokeWidth);
		}
        
	} else if( key == "fill-rule" ) {
    
		// TODO: fill-rule
        
	} else if( key == "stroke-linecap" ) {
    
		// TODO: stroke-linecap
        
	} else if( key == "stroke-linejoin" ) {
    
		// TODO: stroke-linejoin
        
	} else if( key == "font-family" ) {
    
		// TODO: font-family
        
	} else if( key == "font-size" ) {
    
		// TODO: font-size
        
	} else if( key == "font-weight" ) {
    
		// TODO: font-weight
        
	} else if( key == "display" ) {
    
		bool displayNone = false;
		if( value == "none" ) {
			displayNone = true;
        }
		style.displayNone = new bool(displayNone);
        
	} else if( key == "visibility" ) {
    
		bool visible = true;
		if( value == "hidden" || value == "collapse" ) {
			visible = false;
        }
		style.visible = new bool(visible);
	}
}

glm::vec4 * LoaderSvgCI::parseColor(const char * value) {

	while( *value && isspace( *value ) ) {
		value++;
    }
	
	if( ! *value ) {
		return NULL;
    }
	
	if( ! strncmp( value, "inherit", 7 ) ) {
		return NULL;
	}
    
	if( value[0] == '#' ) { // hex color
		uint32_t v = 0;
		if( strlen( value ) > 4 ) {
			for( int c = 0; c < 6; ++c ) {
				char ch = toupper( value[1+c] );
				uint32_t col = ch - ( ( ch > '9' ) ? ( 'A' - 10 ) : '0' );
				v += col << ( (5-c) * 4 );
			}
		}
		else { // 3-digit hex shorthand; double each digit
			for( int c = 0; c < 3; ++c ) {
				char ch = toupper( value[1+c] );
				uint32_t col = ch - ( ( ch > '9' ) ? ( 'A' - 10 ) : '0' );
				v += col << ( (5-(c*2+0)) * 4 );
				v += col << ( (5-(c*2+1)) * 4 );
			}
		}
        
        glm::vec4 * color = new glm::vec4();
        color->r = (v >> 16) / 255.0f;
        color->g = (( v >> 8 ) & 255) / 255.0f;
        color->b = (v & 255) / 255.0f;
        color->a = 1.0;
		return color;
	
    } else if( ! strncmp( value, "none", 4 ) ) {
    
		return NULL;
        
	} else if( ! strncmp( value, "rgb", 3 ) ) {
	
        	std::vector<ci::svg::Value> values = readValueList( value + 3 );
		if( values.size() == 3 ) {
            glm::vec4 * color = new glm::vec4();
            color->r = values[0].asUser( 255 ) / 255.0f;
            color->g = values[1].asUser( 255 ) / 255.0f;
            color->b = values[2].asUser( 255 ) / 255.0f;
            color->a = 1.0;
			return color;
		}
		return NULL;
	}
    
	return NULL;
}

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

//--------------------------------------------------------------
void LoaderSvgCI::pushStyle() {
    styleStack.push_back(new LoaderSvgStyle());
}

void LoaderSvgCI::popStyle() {
    delete styleStack.back();
    styleStack.pop_back();
}


};
};

#endif