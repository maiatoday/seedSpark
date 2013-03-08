/*
 * LuckyDip.cpp
 *
 *  Created on: Feb 12, 2013
 *      Author: maia
 */

#include "LuckyDip.h"
#include <sys/types.h>
#include <dirent.h>

using namespace std;
#define MAX_GLYPH_SAMPLES (50)

LuckyDip::LuckyDip(string _dirname) {    //ctor
    defaultGlyph.loadImage("images/defaultGlyph.png");

    DIR *dir; //the directory
    struct dirent *dp;
    //open the directory
    try {
        dir  = opendir(_dirname.c_str());
        if (dir != NULL) {
            while ((dp = readdir(dir)) != NULL) {
                if (dp->d_type == DT_REG) {
                    // images are loaded relative to the data directory so we chop this part off first
                    string filename(_dirname.substr(strlen("bin/data/"),_dirname.length()));
                    filename.append("/");
                    filename.append(dp->d_name);

                    if (isImageFile(filename)) {
                        ofImage newGlyph;
                        if (newGlyph.loadImage(filename)) {
                            goodGlyphs.push_back(newGlyph);
                        }
                    }
                }
            }
            closedir(dir);
        } else {
            cout << "can't open directory" << _dirname << endl;
        }
    } catch (std::exception& e) {
        cout << e.what() <<" opening/reading " << _dirname << endl;
    }
    luckyColors.loadColors("images/luckyColors.jpg");

}

LuckyDip::~LuckyDip() {
    goodGlyphs.clear();
}

const ofImage& LuckyDip::getSampleGlyph()
{
    if (goodGlyphs.size() > 0) {
        float rr = ofRandom(0, goodGlyphs.size()-1);
        return goodGlyphs[(int) rr];
    }
    return defaultGlyph;
}

bool LuckyDip::isImageFile(std::string _filename)
{
    bool fileOk = false;
    string extension = _filename.substr(_filename.length() - 4, _filename.length()-1);
    // only allow png files because they have transparency
    if (extension == ".png")
        fileOk = true;
    return fileOk;
}

ofColor LuckyDip::getColor()
{
    return luckyColors.getSampleColor();
}

void LuckyDip::loadLuckyColors(std::string _basefilename) {
	cout << "loading colors opening/reading " << _basefilename << endl;
	luckyColors.loadColors(_basefilename, false);
}
