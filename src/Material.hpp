#pragma once

// Note: this "system" will probably be rewritten at a later stage as i 
// do not know 100% how it will work with all the different shaders.
// If materials get too big we can use some form of manager that holds all instead 
// of having them in the model (this should also be done for textures as they are currently loaded multiple times)

struct Material
{
	float ambient;
	float diffuse;
	float specular;
};