#pragma once

#define PI			3.141592
#define DEG2RAD(x)	(x*PI/180.0)
#define RAD2DEG(x)	(x*180.0/PI)

#define SAFE_DELETE(p)			{if(p) {delete (p); (p)=NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p)=NULL;}}
