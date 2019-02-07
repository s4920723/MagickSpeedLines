// SpeedLine.cpp
// Author Kristiyan Aladjov
// A class that manages control points and draws a speed line

#include "SpeedLine.h"

SpeedLine::SpeedLine(int _firstX, int _firstY)
{
    addControlPoint(_firstX, _firstY);
}

void SpeedLine::setUV(Magick::Color col)
{
    m_UVcol = col;
}

Magick::Color SpeedLine::getUV()
{
    return m_UVcol;
}

void SpeedLine::addControlPoint(int _x, int _y)
{
    m_ControlPoints.push_back(std::unique_ptr<ControlPoint>( new ControlPoint(_x, _y) ));
}
