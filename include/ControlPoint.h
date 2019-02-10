#ifndef CONTROL_POINT_H
#define CONTROL_POINT_H

#include <vector>
#include <Magick++.h>

class ControlPoint
{
private:
    int m_posX, m_posY;
    Magick::Color m_velocity;
    int m_frame;

public:
    ControlPoint(int _x, int _y, Magick::Color _velSample);
};

#endif //CONTROL_POINT_H
