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
    SpeedLine(int _firstX, int _firstY);
    void setUV(Magick::Color _col);
    Magick::Color getUV();
    void addControlPoint(int _x, int _y);
    void drawLine();
};

#endif //SPEED_LINE_H
