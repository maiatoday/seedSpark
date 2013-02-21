/*
 * Spark.h
 *
 *  Created on: Feb 12, 2013
 *      Author: maia
 */

#ifndef SPARK_H_
#define SPARK_H_

#include "ofxMSAParticle.h"
/**
 * Sparks show seeds when dormant or a lucky image when touched.
 */
class Spark: public ofxMSAParticle {
public:
	Spark();
	Spark(ofPoint pos, float m = 1.0f, float d = 1.0f);
	Spark(ofxMSAParticle &p);
	virtual ~Spark();
	virtual void init();
	virtual void update(char maskPixel, bool newFrontUser);
	virtual void draw();
	void drawPosition();

	void setGlyph(const ofImage& glyph) {
		this->glyph = glyph;
	}

protected:
	bool frontUser;
	char userId;
	void drawSeed(ofPoint pos);
	void drawSpark(ofPoint pos);
	int startAngle;
	int bladeInc;
	ofImage glyph;
};

#endif /* SPARK_H_ */
