#pragma once

#include "Dependencies\SFML\include\SFML\Graphics.hpp"

namespace
{
	constexpr float SCALE = 25.0f;

	void ConvertPixelsToMeters(float &a, float &b)
	{
		a /= 25.0f;
		b /= 25.0f;
	}

	
	void ConvertMetersToPixels(float& a, float& b)
	{
		a *= 25.0f;
		b *= 25.0f;
	}

}