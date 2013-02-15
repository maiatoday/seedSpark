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
    addVelocity(ofPoint(ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(-10, 10)));
}

void	Spark::update()
{
}

void	Spark::draw()
{
	ofSetColor(255,0,255,255);
	ofRect(getX(),getY(),15, 15);

}

