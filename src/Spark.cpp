/*
 * Spark.cpp
 *
 *  Created on: Feb 12, 2013
 *      Author: maia
 */

#include "Spark.h"

#define MAX_VELOCITY (2.0)

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
	pathColor.a = 255;
	pathColor.r = 255;
	pathColor.g = 128;
	pathColor.b = 0;
	frontUser = false;
	userId = 0;
	addVelocity(
			ofPoint(ofRandom(-MAX_VELOCITY, MAX_VELOCITY), ofRandom(-MAX_VELOCITY, MAX_VELOCITY),
					ofRandom(-MAX_VELOCITY, MAX_VELOCITY)));
	startAngle = ofRandom(-10, 40);
	bladeInc = ofRandom(-20, 20);
	spinAngleInc = ofRandom(-MAX_VELOCITY, MAX_VELOCITY);
	spinAngle = 0;
	lucky = NULL;
}

void Spark::update(char maskPixel, bool newFrontUser) {
	if (maskPixel != userId) {
		addVelocity(
				ofPoint(ofRandom(-MAX_VELOCITY, MAX_VELOCITY), ofRandom(-MAX_VELOCITY, MAX_VELOCITY),
						ofRandom(-MAX_VELOCITY, MAX_VELOCITY)));
	}
	spinAngle += spinAngleInc;
	if ((spinAngle > 0) && (spinAngle > 360)) {
		spinAngle = 0;
	}
	if ((spinAngleInc < 0) && (spinAngle < 0)) {
		spinAngle = 360;
	}
	userId = maskPixel;
	frontUser = newFrontUser;
}

void Spark::drawPosition() {
	ofPoint pos;
	pos.set(getX(), getY(), getZ());
	ofSetColor(pathColor);
	ofRect(pos, 1, 1);
	ofPushStyle();
	ofPopStyle();
}

void Spark::draw() {

	ofPoint pos;
	pos.set(getX(), getY(), getZ());
	ofPoint origin;
	origin.set(0, 0, 0);
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(pos);
	ofRotate(spinAngle);
	if (userId == 0) {
		// not over a user
		drawSeed(origin);
	} else {
		// over a user
		drawSpark(origin);

	}
	ofPopMatrix();
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
