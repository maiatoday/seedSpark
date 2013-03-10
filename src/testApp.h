#pragma once
#include "ofxOpenNI.h"
#include "ofMain.h"
#include "LuckyDip.h"
#include "Spark.h"
#include "ofxMSAPhysics.h"
#include "ofxFX.h"
#include "ofxThreadedImageSaver.h"
#include "ofxXmlSettings.h"

#define DO_VIDEO true

#define START_SPARK_COUNT		200

class testApp: public ofBaseApp {

public:
    testApp();
    ~testApp();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	//------------------ kinect methods and variables
	bool USE_KINECT;
	void setupKinect();
	void updateKinect();
	void drawKinect();
	bool isLive, isTracking, isCloud, isCPBkgnd, isMasking;
	bool isTrackingHands, isFiltering;

	ofxOpenNIContext recordContext;
	ofxDepthGenerator recordDepth;

	ofxImageGenerator recordImage;

	ofxHandGenerator recordHandTracker;

	ofxUserGenerator recordUser;

	void drawMasks();
	void drawAllUserMask();

	int nearThreshold, farThreshold;

	ofImage allUserMasks, user1Mask, user2Mask, depthRangeMask;

	float filterFactor;
	//------------------ kinect size conversions

    void setScreenRatios(void);
	int width;
	int kinectWidth;
	int height;
	int kinectHeight;
	float fromKinectWidth;
	float fromKinectHeight;
	float toKinectWidth;
	float toKinectHeight;

	//------------------ particle methods and variables
	void setupParticles();
	void updateParticles();
	void drawParticles();
	void drawParticlePositions();
	void changeParticleColors();
	void initScene();
	void addRandomParticle();
    void addRandomForce();
	Spark* makeSpark(ofPoint pos, float m, float d);
	ofxMSAPhysics physics;

	//---------------- from XML settings
    bool fullscreen;
    int sparkCount;
    ofxXmlSettings XML;

	//----------------- visuals
    bool toggle;
    int counter;
    LuckyDip* lucky;
    ofxMask maskPaths;
	ofImage bigMask;

    bool doVideoWrite;
#ifdef DO_VIDEO
    ofImage saveScreen;
    ofxThreadedImageSaver TIS;
#endif

};
