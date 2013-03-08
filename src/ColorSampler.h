#ifndef COLORSAMPLER_H
#define COLORSAMPLER_H

#include <ofImage.h>

#include <vector>

class ColorSampler: public ofImage {
public:
	ColorSampler();
	ColorSampler(std::string _filename);
	virtual ~ColorSampler();
	ofColor getSampleColor();
	void loadColors(std::string _filename, bool unique = false);
protected:
private:
	std::vector<ofColor*> goodColors;
	ofColor defaultColor;
	unsigned char* pPixels;
	void clearColors();

};

#endif // COLORSAMPLER_H
