// main.cpp
// Author Kristiyan Aladjov
// Attempt to implement speed lines through ImageMagick++

#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <random>
#include <memory>
#include <Magick++.h>

#include "ControlPoint.h"
#include "SpeedLine.h"

void getImageSeq(std::vector<Magick::Image> &_imgArray, std::string _seqName, int _numFrames);
void initializeLines(Magick::Image &_firstFrame, std::vector<std::unique_ptr<SpeedLine> > &_SpeedLines, int _numOfLines);
void trackPoints(std::vector<Magick::Image> &_UVframes, std::vector<std::unique_ptr<SpeedLine>> &_SpeedLines);
void drawSpeedlines(std::vector<std::unique_ptr<SpeedLine> > &_SpeedLines);

int main()
{
    int numSpeedLines = 4;
    int minSpeed;
    int maxSpeed;


    Magick::InitializeMagick("");

    std::vector<Magick::Image> UVseq;
    std::vector<Magick::Image> VELseq;
    std::vector<std::unique_ptr<SpeedLine>> SpeedLines;
    Magick::Image testImage("testImage.jpg");

    // Get image sequence size
    unsigned long int seqX = UVseq.front().rows();
    unsigned long int seqY = UVseq.front().columns();

    // Initialize array of lines and set first control point
    initializeLines(testImage, SpeedLines, numSpeedLines);
}


void getImageSeq(std::vector<Magick::Image> &_imgArray, std::string _seqName, int _numFrames)
{
    for (int i=0; i <= _numFrames; i++)
    {
        _imgArray.push_back(new Magick::Image());
    }
}


void initializeLines(Magick::Image &_firstFrame, std::vector<std::unique_ptr<SpeedLine>> &_SpeedLines, int _numOfLines)
{
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<> distrX(0, static_cast<int>(_firstFrame.rows()));
    std::uniform_int_distribution<> distrY(0, static_cast<int>(_firstFrame.columns()));

    for (int i=0; i < _numOfLines; i++)
    {
        int randX, randY;
        do
        {
            randX = distrX(eng);
            randY = distrY(eng);
        }while(_firstFrame.pixelColor(randX, randY).alpha() == 0.0);
        _SpeedLines.push_back(std::unique_ptr<SpeedLine>( new SpeedLine(randX, randY, _firstFrame.pixelColor(randX, randY))));
    }
}


void trackPoints(std::vector<Magick::Image> &_UVframes, std::vector<std::unique_ptr<SpeedLine>> &_SpeedLines)
{
    for (int i=1; i <= _SpeedLines.size(); i++) 	// Go through every speed line
    {
        for (int j=1; j <= _UVframes.size(); j++)		// Go through every frame
        {
            for (int x=0; x <= _UVframes[j].rows(); x++)	// Go through every row
            {
                for (int y=0; y <= _UVframes[j].columns(); y++)	// Go through every column
                {
                    if (_UVframes[j].pixelColor(x, y) == _SpeedLines[i]->getUV())
                    {
                        _SpeedLines[i]->addControlPoint(x, y);

                    }
                }
            }
        }
    }
}

void drawSpeedlines(std::vector<std::unique_ptr<SpeedLine>> &_SpeedLines)
{
    std::list<Magick::Drawable> drawList;
    drawList.push_back(Magick::DrawableStrokeColor("black"));
    drawList.push_back(Magick::DrawableStrokeWidth(0.0));
    drawList.push_back(Magick::DrawableFillColor("black"));
    for (int i=0; i <= _SpeedLines.size(); i++)
    {
       drawList.push_back(Magick::DrawablePolygon())
    }
}
