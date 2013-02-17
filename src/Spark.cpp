/*
 * Spark.cpp
 *
 *  Created on: Feb 12, 2013
 *      Author: maia
 */

#include "Spark.h"

Spark::Spark(): ofxMSAParticle()
{
    init();
}


Spark::Spark(ofPoint pos, float m, float d) : ofxMSAParticle(pos, m, d)
{
    init();
}

Spark::Spark(ofxMSAParticle &p) : ofxMSAParticle(p)
{
    init();
}

Spark::~Spark() {
	// TODO Auto-generated destructor stub
}

void Spark::init()
{
//    pMyFont = NULL;
//    outsideColor.a = 255;
//    outsideColor.r = 130;
//    outsideColor.g = 0;
//    outsideColor.b = 160;
//
//    insideColor.a = 130;
//    insideColor.r = 130;
//    insideColor.g = 130;
//    insideColor.b = 250;
//
//    outsideTextColor.a = 255;
//    outsideTextColor.r = 255;
//    outsideTextColor.g = 255;
//    outsideTextColor.b = 255;
//    myAlpha = 255;
//    label = 0;
//    maxDistWidthSquare = MAX_DIST_SQR;
//
	frontUser = false;
	userId = 0;
    addVelocity(ofPoint(ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(-10, 10)));
}

void	Spark::update(char maskPixel, bool newFrontUser)
{
	if (maskPixel != userId) {
		// we changed users or left a user
	}
	userId = maskPixel;
	frontUser = newFrontUser;
}

void	Spark::draw()
{
	if (userId == 0) {
		// not over a user
		ofSetColor(128,128,128,128);
	} else if (frontUser){
		// over the front user
		ofSetColor(255,0,255,255);
	} else {
		// over a user
		ofSetColor(255,128,0,255);

	}
	ofRect(getX(),getY(),15, 15);

}

