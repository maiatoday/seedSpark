#include "testApp.h"
testApp::testApp() :
    fullscreen(false), sparkCount(START_SPARK_COUNT), toggle(false), counter(0)
{

    lucky = new LuckyDip("data/images/lucky");
}

testApp::~testApp()
{
    delete lucky;
}
//--------------------------------------------------------------
void testApp::setup()
{
    if (XML.loadFile("mySettings.xml"))
    {
        sparkCount = XML.getValue("ROOM:SPARK_COUNT", START_SPARK_COUNT);
        fullscreen = (XML.getValue("ROOM:FULLSCREEN", 1) == 1) ? true : false;
        USE_KINECT = (XML.getValue("ROOM:KINECT", 1) == 1) ? true : false;
        doVideoWrite = (XML.getValue("ROOM:VIDEO", 1) == 1) ? true : false;
    }
    if (USE_KINECT)
    {
        setupKinect();
    }
    ofBackground(0, 0, 0);
    ofSetFullscreen(fullscreen);
    ofHideCursor();
    setScreenRatios();
    setupParticles();
//	maskPaths.allocate(width, height);
    maskPaths.allocate(kinectWidth, kinectHeight);
//	bigMask.loadImage("images/defaultMask.png");
}

//--------------------------------------------------------------
void testApp::update()
{
    if (USE_KINECT)
    {
        updateKinect();
    }
    updateParticles();
//	bigMask = allUserMasks;
//	bigMask.resize(width, height);
//	maskPaths.setTexture(bigMask.getTextureReference(), 0);
    maskPaths.setTexture(allUserMasks.getTextureReference(), 0);
    maskPaths.begin(1);
    ofPushMatrix();
    ofScale(toKinectWidth, toKinectHeight, toKinectWidth);
    drawParticlePositions();
    ofPopMatrix();
    maskPaths.end(1);
    maskPaths.update();
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}


//--------------------------------------------------------------
void testApp::draw()
{
    maskPaths.draw(0, 0, width, height);
    if (USE_KINECT)
    {
//		drawKinect();
//		drawAllUserMask();
    }
    drawParticles(); // this draws the images
    if (doVideoWrite)
    {
#ifdef DO_VIDEO
        saveScreen.grabScreen(0, 0, width, height);
        TIS.saveThreaded(saveScreen);
#endif
    }

}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
    addRandomForce();
    switch (key)
    {
    case '`':
        doVideoWrite = !doVideoWrite;
        break;
    case ' ':
    {
        toggle = !toggle;
//		if (toggle) {
//			lucky->loadLuckyColors("images/luckyColors2.jpg");
//		} else {
//			lucky->loadLuckyColors("images/luckyColors3.jpg");
//		}
        int whichColors = ofRandom(0, 8);
        switch (whichColors)
        {
        default:
        case 1:
            lucky->loadLuckyColors("images/luckyColors1.jpg");
            break;
        case 2:
            lucky->loadLuckyColors("images/luckyColors2.jpg");
            break;
        case 3:
            lucky->loadLuckyColors("images/luckyColors3.jpg");
            break;
        case 4:
            lucky->loadLuckyColors("images/luckyColors4.jpg");
            break;
        case 5:
            lucky->loadLuckyColors("images/luckyColors5.jpg");
            break;
        case 6:
            lucky->loadLuckyColors("images/luckyColors6.jpg");
            break;
        case 7:
            lucky->loadLuckyColors("images/luckyColors7.jpg");
            break;;
        case 8:
            lucky->loadLuckyColors("images/luckyColors8.jpg");
            break;
        }
        changeParticleColors();
        counter++;
        if (counter == 8)
            counter = 0;
    }
    break;

    case '1':
        lucky->loadLuckyColors("images/luckyColors1.jpg");
        changeParticleColors();
        break;

    case '2':
        lucky->loadLuckyColors("images/luckyColors2.jpg");
        changeParticleColors();
        break;


    case '3':
        lucky->loadLuckyColors("images/luckyColors3.jpg");
        changeParticleColors();
        break;


    case '4':
        lucky->loadLuckyColors("images/luckyColors4.jpg");
        changeParticleColors();
        break;


    case '5':
        lucky->loadLuckyColors("images/luckyColors5.jpg");
        changeParticleColors();
        break;


    case '6':
        lucky->loadLuckyColors("images/luckyColors6.jpg");
        changeParticleColors();
        break;


    case '7':
        lucky->loadLuckyColors("images/luckyColors7.jpg");
        changeParticleColors();
        break;


    case '8':
        lucky->loadLuckyColors("images/luckyColors8jpg");
        changeParticleColors();
        break;


    case 'x':
        clearMaskPath();
        lucky->loadLuckyColors("images/luckyColorsNight.jpg");
        changeParticleColors();
        break;
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

    addRandomForce();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}

void testApp::setupKinect()
{
    isLive = true;
    isTracking = true;
    isTrackingHands = false;
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

    if (isTrackingHands)
    {
        recordHandTracker.setup(&recordContext, 4);
        recordHandTracker.setSmoothing(filterFactor);		// built in openni hand track smoothing...
        recordHandTracker.setFilterFactors(filterFactor);// custom smoothing/filtering (can also set per hand with setFilterFactor)...set them all to 0.1f to begin with
    }
    recordContext.toggleRegisterViewport();
    recordContext.toggleMirror();

}
void testApp::updateKinect()
{
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
    if (isTracking && isMasking)
    {
        allUserMasks.setFromPixels(recordUser.getUserPixels(), recordUser.getWidth(), recordUser.getHeight(),
                                   OF_IMAGE_GRAYSCALE);
        user1Mask.setFromPixels(recordUser.getUserPixels(1), recordUser.getWidth(), recordUser.getHeight(),
                                OF_IMAGE_GRAYSCALE);
        user2Mask.setFromPixels(recordUser.getUserPixels(2), recordUser.getWidth(), recordUser.getHeight(),
                                OF_IMAGE_GRAYSCALE);
    }

}
void testApp::drawKinect()
{
    ofSetColor(255, 255, 255);

    glPushMatrix();
    glScalef(0.75, 0.75, 0.75);

    if (isLive)
    {

        recordDepth.draw(0, 0, 640, 480);
        recordImage.draw(640, 0, 640, 480);

        depthRangeMask.draw(0, 480, 320, 240);// can use this with openCV to make masks, find contours etc when not dealing with openNI 'User' like objects

        if (isTracking)
        {
            recordUser.draw();

            if (isMasking)
                drawMasks();

        }
        if (isTrackingHands)
            recordHandTracker.drawHands();
    }

}
void testApp::drawMasks()
{
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
    allUserMasks.draw(640, 0, 640, 480);
    glDisable(GL_BLEND);
    glPopMatrix();
    user1Mask.draw(320, 480, 320, 240);
    user2Mask.draw(640, 480, 320, 240);

}

void testApp::drawAllUserMask()
{
    ofPushStyle();
    ofSetColor(255, 255, 255, 80);
    glPushMatrix();
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
    allUserMasks.draw(0, 0, width, height);
//	glDisable(GL_BLEND);
    glPopMatrix();
    ofPopStyle();

}

void testApp::clearMaskPath()
{
    maskPaths.begin(1);
    ofBackground(0,0,0);
    maskPaths.end(1);
    maskPaths.update();
}

void testApp::setScreenRatios(void)
{
    int windowMode = ofGetWindowMode();

//	kinectWidth = recordUser.getWidth();
//	kinectHeight = recordUser.getHeight();
    kinectWidth = 640;
    kinectHeight = 480;
    if (windowMode == OF_FULLSCREEN)
    {
        width = ofGetScreenWidth();
        height = ofGetScreenHeight();
    }
    else if (windowMode == OF_WINDOW)
    {
        width = ofGetWidth();
        height = ofGetHeight();
    }
    fromKinectWidth = (float) width / (float) kinectWidth;
    fromKinectHeight = (float) height / (float) kinectHeight;
    toKinectWidth = (float) kinectWidth / (float) width;
    toKinectHeight = (float) kinectHeight / (float) height;
    physics.setWorldSize(ofPoint(0, 0, 0), ofPoint(width, height, height));
}

#define	GRAVITY					1
#define SECTOR_COUNT			10
#define MIN_MASS				1
#define MAX_MASS				3

#define MIN_BOUNCE				0.2
#define MAX_BOUNCE				0.9
#define NODE_MIN_RADIUS			2
#define NODE_MAX_RADIUS			7
#define FORCE_AMOUNT			10
void testApp::setupParticles()
{
//	physics.setGravity(ofPoint(0, GRAVITY / 5, 0));
    physics.setGravity(ofPoint(0, 0, 0));

    // set world dimensions, not essential, but speeds up collision
//	physics.setWorldSize(ofPoint(0, 0, 0), ofPoint(width, height, width));
    physics.setSectorCount(SECTOR_COUNT);
    physics.setDrag(0.97f);
    physics.setDrag(1);		// FIXTHIS
    physics.disableCollision();

    initScene();
    for (int i = 0; i < sparkCount; i++)
    {
        addRandomParticle();
    }

}
void testApp::initScene()
{
    // clear all particles and springs etc
    physics.clear();

}
void testApp::addRandomParticle()
{
    float posX = ofRandom(0, width);
    float posY = ofRandom(0, height);
    float posZ = ofRandom(-width / 2, width / 2);
    float mass = ofRandom(MIN_MASS, MAX_MASS);
    float bounce = ofRandom(MIN_BOUNCE, MAX_BOUNCE);
    float radius = ofMap(mass, MIN_MASS, MAX_MASS, NODE_MIN_RADIUS * fromKinectWidth,
                         NODE_MAX_RADIUS * fromKinectWidth);

    // physics.makeParticle returns a particle pointer so you can customize it
    Spark* p = makeSpark(ofPoint(posX, posY, posZ), 1.0f, 1.0f);

    // and set a bunch of properties (you don't have to set all of them, there are defaults)
    p->setMass(mass)->setBounce(bounce)->setRadius(radius)->enableCollision()->makeFree();
}

Spark* testApp::makeSpark(ofPoint pos, float m = 1.0f, float d = 1.0f)
{
    Spark* p = new Spark(pos, m, d);
    p->setGlyph(lucky->getSampleGlyph());
    p->setLucky(lucky);
    physics.addParticle(p);
    p->release();	// cos addParticle(p) retains it
    return p;
}
void testApp::addRandomForce()
{
    float f = FORCE_AMOUNT;
    for (unsigned int i = 0; i < physics.numberOfParticles(); i++)
    {
        ofxMSAParticle *p = physics.getParticle(i);
        if (p->isFree())
            p->addVelocity(ofPoint(ofRandom(-f, f), ofRandom(-f, f), ofRandom(-f, f)));
    }
}
void testApp::updateParticles()
{
    physics.update();

    for (unsigned int i = 0; i < physics.numberOfParticles(); i++)
    {
        Spark *p = static_cast<Spark*>(physics.getParticle(i));

        int x = p->getX() * toKinectWidth;
        int y = p->getY() * toKinectHeight;
        //        int z = p->getZ();
        if (USE_KINECT && isTracking && isMasking)
        {
            char c = allUserMasks.getPixelsRef()[allUserMasks.width * y + x];
            p->update(c, false);
        }
    }

}
void testApp::drawParticlePositions()
{
    for (unsigned int i = 0; i < physics.numberOfParticles(); i++)
    {
        Spark *p = static_cast<Spark*>(physics.getParticle(i));
        p->drawPosition();
    }

}
void testApp::changeParticleColors()
{
    for (unsigned int i = 0; i < physics.numberOfParticles(); i++)
    {
        Spark *p = static_cast<Spark*>(physics.getParticle(i));
        p->setNewColor();
    }

}
void testApp::drawParticles()
{
    physics.draw();

}
