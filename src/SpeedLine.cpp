// SpeedLine.cpp
// Author Kristiyan Aladjov
// A class that manages control points and draws a speed line

#include "SpeedLine.h"

SpeedLine::SpeedLine(int _firstX, int _firstY, Magick::Color _UVcol)
{
    addControlPoint(_firstX, _firstY);
    m_UVcol = _UVcol;
}

Magick::Color SpeedLine::getUV()
{
    return m_UVcol;
}

void SpeedLine::addControlPoint(int _x, int _y)
{
    m_ControlPoints.push_back(std::unique_ptr<ControlPoint>( new ControlPoint(_x, _y) ));
}

std::list<Magick::Coordinate> SpeedLine::drawLine(int _lifetime, int _currentFrame)
{
    std::list<Magick::Coordinate> polypoints;
    for (int i=0; i < _lifetime; i++)
    {
        m_ControlPoints[_currentFrame - i].
    }
    Magick::Drawable	 speedlineShape;
    return polypoints;
}
