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


void initializeLines(Magick::Image &_firstFrame, std::vector<std::unique_ptr<SpeedLine> > &_SpeedLines, int _numOfLines);
void trackPoints(std::vector<Magick::Image> &UVframes, std::vector<SpeedLine> &SpeedLines);

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
        _SpeedLines.push_back(std::unique_ptr<SpeedLine>( new SpeedLine(randX, randY)));

    }
}

void trackPoints(std::vector<Magick::Image> &UVframes, std::vector<SpeedLine> &SpeedLines)
{
    for (int i=1; i <= SpeedLines.size(); i++) 						// Go through every speed line
    {
        for (int j=1; j <= UVframes.size(); j++)					// Go through every frame
        {
            for (int x=0; x <= UVframes[j].rows(); x++)				//
            {
                for (int y=0; y <= UVframes[j].columns(); y++)
                {
                    if (UVframes[j].pixelColor(x, y) == SpeedLines[i].ControlPoints[j-1].getUV())
                    {

                    }
                }
            }
        }
    }
}
