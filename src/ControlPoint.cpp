//ControlPoint.cpp
//Author Kristiyan Aladjov

#include "ControlPoint.h"

ControlPoint::ControlPoint(int _x, int _y, Magick::Color _velSample)
{
    m_posX = _x;
    m_posY = _y;
    m_velocity = _velSample;
}
