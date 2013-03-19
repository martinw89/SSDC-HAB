/*
	HAB.h - Library for Arduino operation in a high altitude ballon
	Created by Martin Wilson, November 12th 2012.
	Released as Creative Commons BY-SA-NC
*/

#ifndef HAB_H
	#define HAB_H
	#include "Arduino.h"
	
	class HAB
	{
		public:
			HAB();
			float interval();
			float vref();
            int sdpin();
            int setInterval(int interval);
		private:
			float _interval; //Time between readings in millisec
			float _vref;
            int _sdpin;
	};
	
#endif