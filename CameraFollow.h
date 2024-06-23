#pragma once
#include <raylib.h>

float lerp(float a, float b, float f);

enum FollowMode
{
	Instant,
	Interpolate	
};

class CameraFollow
{
	public:
		CameraFollow(Camera2D* _camera, FollowMode _mode);
		CameraFollow(Camera2D* _camera, FollowMode _mode, float _speed);
		void Follow(Vector2 target);
	private:
		Camera2D* camera;
		FollowMode mode;
		Vector2 prevTarget{0,0};
		float speed;
};


