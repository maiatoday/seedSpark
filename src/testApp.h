#pragma once
#include "ofxOpenNI.h"
#include "ofMain.h"
#include "LuckyDip.h"

class testApp: public ofBaseApp {

public:
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

	int nearThreshold, farThreshold;

	ofImage allUserMasks, user1Mask, user2Mask, depthRangeMask;

	float filterFactor;

	//------------------ particle methods and variables
	LuckyDip lucky;
	void setupParticles();
	void updateParticles();
	void drawParticles();

};
