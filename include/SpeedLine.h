#ifndef SPEED_LINE_H
#define SPEED_LINE_H

#include <Magick++.h>
#include <memory>
#include <vector>
#include "ControlPoint.h"

class SpeedLine
{
private:
    Magick::Color m_UVcol;
    std::vector<std::unique_ptr<ControlPoint>> m_ControlPoints;

public:
    SpeedLine(int _firstX, int _firstY, Magick::Color _UVcol, Magick::Color _VELcol);
    Magick::Color getUV();
    void addControlPoint(int _x, int _y, Magick::Color _velSample);
    std::list<Magick::Coordinate> drawLine(int _lifetime, int _currentFrame);
};

#endif //SPEED_LINE_H:w

