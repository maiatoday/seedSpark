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
class Spark : public ofxMSAParticle {
public:
	Spark();
	Spark(ofPoint pos, float m = 1.0f, float d = 1.0f);
	Spark(ofxMSAParticle &p);
	virtual ~Spark();
	void init();
};

#endif /* SPARK_H_ */
