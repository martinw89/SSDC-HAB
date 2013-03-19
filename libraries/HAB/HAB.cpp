/*
	HAB.cpp - Library for Arduino operation in a high altitude ballon
	Created by Martin Wilson, November 12th 2012.
	Released as Creative Commons BY-SA-NC
*/

#include "Arduino.h"
#include "HAB.h"


HAB::HAB()
{
	_interval = 5000; //_interval = time between readings in millisec
	_vref = 5;
    _sdpin = 10;
}
	
float HAB::interval()
{
	return _interval;
}

int HAB::setInterval(int interval)
{
    _interval = interval;
    return _interval;
}

float HAB::vref()
{
	return _vref;
}

int HAB::sdpin()
{
    return _sdpin;
}