#include "ColorSampler.h"

using namespace std;
#define MAX_COLOR_SAMPLES (20)
ColorSampler::ColorSampler() {
	defaultColor.a = 0xff;
	defaultColor.r = 0xff;
	defaultColor.g = 0xff;
	defaultColor.b = 0xff;

}
ColorSampler::ColorSampler(string _filename) {
	//ctor
	loadColors(_filename);
	defaultColor.a = 0xff;
	defaultColor.r = 0xff;
	defaultColor.g = 0xff;
	defaultColor.b = 0xff;
}

ColorSampler::~ColorSampler() {
	//dtor

	// bleargh vector of pointers so must delete objects
	clearColors();
}

void ColorSampler::loadColors(string _filename, bool unique) {

	bool loadOk = loadImage(_filename);
	if (loadOk) {
		clearColors();
		int bytesPerPixel = 1;
		switch (type) {
		case OF_IMAGE_COLOR:
			bytesPerPixel = 3;
			break;
		case OF_IMAGE_COLOR_ALPHA:
			bytesPerPixel = 4;
			break;
		case OF_IMAGE_GRAYSCALE:
		default:
			bytesPerPixel = 1;
			break;
		}
		if ((type == OF_IMAGE_COLOR_ALPHA) || (type == OF_IMAGE_COLOR)) {
			pPixels = getPixels();
//            for (int i = 0; (i<width*height*bytesPerPixel && goodColors.size() < MAX_COLOR_SAMPLES); i += bytesPerPixel ) {
			for (int i = 0; (i < width * height * bytesPerPixel); i += bytesPerPixel) {
				//get the pixel color
				ofColor* newColor = new ofColor();
				newColor->r = pPixels[i];
				newColor->g = pPixels[i + 1];
				newColor->b = pPixels[i + 2];
				newColor->a = 0xff;

				bool colorFound = true;
				if (unique) {
					//check if we already have it in our vector
					colorFound = false;
					for (unsigned int j = 0; j < goodColors.size(); j++) {
						if ((newColor->r == goodColors[j]->r) && (newColor->g == goodColors[j]->g)
								&& (newColor->b == goodColors[j]->b)) {
							colorFound = true;
							break;
						}
					}
				}
				if (colorFound) {
					goodColors.push_back(newColor);
				} else {
					delete newColor;
				}
			}
		}
	}

}

void ColorSampler::clearColors() {

	for (unsigned int i = 0; i < goodColors.size(); i++)
		delete goodColors[i];
	goodColors.clear();

}

ofColor ColorSampler::getSampleColor() {
	if (goodColors.size() > 0) {
		float rr = ofRandom(0, goodColors.size() - 1);
		return *goodColors[(int) rr];
	}
	return defaultColor;
}

