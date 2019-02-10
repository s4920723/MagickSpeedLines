// main.cpp
// Author Kristiyan Aladjov
// Attempt to implement speed lines through ImageMagick++

#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

#include <list>
#include <vector>
#include <string>
#include <random>
#include <memory>
#include <Magick++.h>

#include "ControlPoint.h"
#include "SpeedLine.h"

void loadImageSeq(std::vector<Magick::Image> &_imgArray, std::string _dirName);
void initializeLines(Magick::Image &_firstFrameUV, Magick::Image &_firstFrameVel, std::vector<std::unique_ptr<SpeedLine>> &_SpeedLines, int _numOfLines);
void trackPoints(std::vector<Magick::Image> &_UVframes, std::vector<Magick::Image> &_VELframes, std::vector<std::unique_ptr<SpeedLine>> &_SpeedLines);
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

    loadImageSeq(UVseq, "/home/impy/Documents/innovations/testSequence/uv");
    loadImageSeq(VELseq, "/home/impy/Documents/innovations/testSequence/velocity");
    initializeLines(UVseq.front(), VELseq.front(), SpeedLines, numSpeedLines);

}


void loadImageSeq(std::vector<Magick::Image> &_imgArray, std::string _directoryName)
{
    boost::filesystem::path p(_directoryName);

    //Check if directory exists
    if (boost::filesystem::is_directory(p))
    {
        for (auto& imageFile : boost::make_iterator_range(boost::filesystem::directory_iterator(p), {}))
        {
           _imgArray.push_back(Magick::Image(imageFile.path().string()));
        }
    }
}


void initializeLines(Magick::Image &_firstFrameUV, Magick::Image &_firstFrameVel, std::vector<std::unique_ptr<SpeedLine>> &_SpeedLines, int _numOfLines)
{
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<> distrX(0, static_cast<int>(_firstFrameUV.rows()));
    std::uniform_int_distribution<> distrY(0, static_cast<int>(_firstFrameUV.columns()));

    for (int i=0; i < _numOfLines; i++)
    {
        int randX, randY;
        do
        {
            randX = distrX(eng);
            randY = distrY(eng);
        }while(_firstFrameUV.pixelColor(randX, randY) == Magick::Color(0,0,0) && _firstFrameVel.pixelColor(randX, randY) == Magick::Color(0,0,0,0));
        _SpeedLines.push_back(std::unique_ptr<SpeedLine>( new SpeedLine(randX, randY, _firstFrameUV.pixelColor(randX, randY), _firstFrameVel.pixelColor(randX, randY))));
    }
}


void trackPoints(std::vector<Magick::Image> &_UVframes, std::vector<Magick::Image> &_VELframes, std::vector<std::unique_ptr<SpeedLine>> &_SpeedLines)
{
    for (long int i=1; i <= _SpeedLines.size(); i++) 	// Go through every speed line
    {
        for (long int j=1; j <= _UVframes.size(); j++)		// Go through every frame
        {
            for (long int x=0; x <= _UVframes[j].rows(); x++)	// Go through every row
            {
                for (long int y=0; y <= _UVframes[j].columns(); y++)	// Go through every column
                {
                    if (_UVframes[j].pixelColor(x, y) == _SpeedLines[i]->getUV())
                    {
                        _SpeedLines[i]->addControlPoint(x, y, _VELframes[j].pixelColor(x, y));

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
    for (auto &currentSpeedline : _SpeedLines)
    {
       drawList.push_back(Magick::DrawableLine(currentSpeedline.));
    }
}
