#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	setupKinect();
	setupParticles();
}

//--------------------------------------------------------------
void testApp::update() {
	updateKinect();
	updateParticles();
}

//--------------------------------------------------------------
void testApp::draw() {
	drawKinect();
	drawParticles();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) {

}

void testApp::setupKinect() {
	isLive = true;
	isTracking = false;
	isTrackingHands = true;
	isFiltering = false;
	isCloud = false;
	isCPBkgnd = true;
	isMasking = true;

	nearThreshold = 500;
	farThreshold = 1000;

	filterFactor = 0.1f;

	ofBackground(0, 0, 0);

	recordContext.setup();	// all nodes created by code -> NOT using the xml config file at all
	//recordContext.setupUsingXMLFile();
	recordDepth.setup(&recordContext);
	recordImage.setup(&recordContext);

	recordUser.setup(&recordContext);
	recordUser.setSmoothing(filterFactor);				// built in openni skeleton smoothing...
	recordUser.setUseMaskPixels(isMasking);
	recordUser.setUseCloudPoints(isCloud);
	recordUser.setMaxNumberOfUsers(MAX_NUMBER_USERS);// use this to set dynamic max number of users (NB: that a hard upper limit is defined by MAX_NUMBER_USERS in ofxUserGenerator)

	recordHandTracker.setup(&recordContext, 4);
	recordHandTracker.setSmoothing(filterFactor);		// built in openni hand track smoothing...
	recordHandTracker.setFilterFactors(filterFactor);// custom smoothing/filtering (can also set per hand with setFilterFactor)...set them all to 0.1f to begin with

	recordContext.toggleRegisterViewport();
	recordContext.toggleMirror();

}
void testApp::updateKinect() {
	// update all nodes
	recordContext.update();
	recordDepth.update();
	recordImage.update();

	// demo getting depth pixels directly from depth gen
	depthRangeMask.setFromPixels(recordDepth.getDepthPixels(nearThreshold, farThreshold), recordDepth.getWidth(),
			recordDepth.getHeight(), OF_IMAGE_GRAYSCALE);

	// update tracking/recording nodes
	if (isTracking)
		recordUser.update();

	// demo getting pixels from user gen
	if (isTracking && isMasking) {
		allUserMasks.setFromPixels(recordUser.getUserPixels(), recordUser.getWidth(), recordUser.getHeight(),
				OF_IMAGE_GRAYSCALE);
		user1Mask.setFromPixels(recordUser.getUserPixels(1), recordUser.getWidth(), recordUser.getHeight(),
				OF_IMAGE_GRAYSCALE);
		user2Mask.setFromPixels(recordUser.getUserPixels(2), recordUser.getWidth(), recordUser.getHeight(),
				OF_IMAGE_GRAYSCALE);
	}

}
void testApp::drawKinect() {
	ofSetColor(255, 255, 255);

	glPushMatrix();
	glScalef(0.75, 0.75, 0.75);

	if (isLive) {

		recordDepth.draw(0, 0, 640, 480);
		recordImage.draw(640, 0, 640, 480);

		depthRangeMask.draw(0, 480, 320, 240);// can use this with openCV to make masks, find contours etc when not dealing with openNI 'User' like objects

		if (isTracking) {
			recordUser.draw();

			if (isMasking)
				drawMasks();

		}
		if (isTrackingHands)
			recordHandTracker.drawHands();
	}

}
void testApp::drawMasks() {
	glPushMatrix();
	glEnable (GL_BLEND);
	glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
	allUserMasks.draw(640, 0, 640, 480);
	glDisable(GL_BLEND);
	glPopMatrix();
	user1Mask.draw(320, 480, 320, 240);
	user2Mask.draw(640, 480, 320, 240);

}

void testApp::setupParticles() {

}
void testApp::updateParticles() {

}
void testApp::drawParticles() {

}
