/*
 * Spark.cpp
 *
 *  Created on: Feb 12, 2013
 *      Author: maia
 */

#include "Spark.h"

Spark::Spark() :
		ofxMSAParticle() {
	init();
}

Spark::Spark(ofPoint pos, float m, float d) :
		ofxMSAParticle(pos, m, d) {
	init();
}

Spark::Spark(ofxMSAParticle &p) :
		ofxMSAParticle(p) {
	init();
}

Spark::~Spark() {
	// TODO Auto-generated destructor stub
}

void Spark::init() {
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
	startAngle = ofRandom(-10, 40);
	bladeInc = ofRandom(-20, 20);
}

void Spark::update(char maskPixel, bool newFrontUser) {
	if (maskPixel != userId) {
		// we changed users or left a user
	}
	userId = maskPixel;
	frontUser = newFrontUser;
}

void Spark::draw() {

	ofPoint pos;
	pos.set(getX(), getY(), getZ());
	ofPushStyle();
	if (userId == 0) {
		// not over a user
		drawSeed(pos);
	} else {
		// over a user
		drawSpark(pos);

	}
	ofPopStyle();

}

void Spark::drawSeed(ofPoint pos) {

	ofColor lineColor;
	lineColor.set(128, 128, 128, 128);

	ofSetColor(lineColor);
	ofCircle(pos, 2);
	ofPath blade;
	blade.setArcResolution(100);
	blade.setFilled(false);
	blade.setStrokeColor(lineColor);
	blade.setStrokeWidth(2);
	int bladeAngle = startAngle;
	for (int i = 0; i < 3; i++) {
		blade.arc(pos, 7, 7, bladeAngle - 10, bladeAngle + 10);
		blade.newSubPath();
		blade.arc(pos, 10, 10, bladeAngle - 10, bladeAngle + 10);
		blade.newSubPath();
		blade.arc(pos, 15, 15, bladeAngle - 10, bladeAngle + 10);
		blade.newSubPath();
		blade.arc(pos, 20, 20, bladeAngle - 6, bladeAngle + 6);
		blade.newSubPath();
		blade.arc(pos, 25, 25, bladeAngle - 4, bladeAngle + 4);
		blade.newSubPath();
		bladeAngle += (120 + bladeInc);
	}
	blade.draw();

}
void Spark::drawSpark(ofPoint pos) {

//	ofSetColor(255, 128, 0, 255);
//	ofRect(getX(), getY(), 20, 20);
	ofEnableAlphaBlending();
	glyph.draw(pos);

}
