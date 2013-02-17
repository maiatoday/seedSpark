/*
 * LuckyDip.h
 *
 *  Created on: Feb 12, 2013
 *      Author: maia
 */

#ifndef LUCKYDIP_H_
#define LUCKYDIP_H_
#include <ofImage.h>

#include <vector>
/**
 * As the LuckyDip for an image or a colour. It will give a time/weather appropriate image or color choosen from a pool.
 */
class LuckyDip {
public:
	LuckyDip(std::string _basefilename);
	virtual ~LuckyDip();
	const ofImage& getSampleGlyph();

protected:
	bool isImageFile(std::string _filename);
private:
	std::vector<ofImage> goodGlyphs;
	ofImage defaultGlyph;
};

#endif /* LUCKYDIP_H_ */
