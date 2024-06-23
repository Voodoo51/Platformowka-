#include "CameraFollow.h"

float lerp(float a, float b, float f)
{
	return a * (1.0 - f) + (b * f);
}

CameraFollow::CameraFollow(Camera2D* _camera, FollowMode _mode)
{
	camera = _camera;
	mode = _mode;
}


CameraFollow::CameraFollow(Camera2D* _camera, FollowMode _mode, float _speed)
{
	camera = _camera;
	mode = _mode;
	speed = _speed;
}


void CameraFollow::Follow(Vector2 target)
{
	if(mode == Instant)
	{
		camera->target = target;
	}
	else if(mode == Interpolate)
	{
		prevTarget.x = lerp(prevTarget.x, target.x, speed); 	
		prevTarget.y = lerp(prevTarget.y, target.y, speed); 	
		camera->target = prevTarget;
	}
}



