#include "Light.h"
#include "Globals.h"
#include "Glew/include/GL/glew.h"

Light::Light(LightType type, fPoint position, float4 ambient, float4 diffuse, float4 specular,
	float constantAttenuation, float linearAttenuation, float quadraticAttenuation)
{
	this->type = type;
	float fourthPositionValue = 1.0f;
	if (type == LT_DIRECTIONAL_LIGHT) {
		fourthPositionValue = 0.0f;
	}
	this->position = new float[4]{ position.x, position.y, position.z, fourthPositionValue };
	this->ambient = new float[4]{ ambient.x, ambient.y, ambient.z, ambient.w };
	this->diffuse = new float[4]{ diffuse.x, diffuse.y, diffuse.z, diffuse.w };
	this->specular = new float[4]{ specular.x, specular.y, specular.z, specular.w };
	this->constantAttenuation = constantAttenuation;
	this->linearAttenuation = linearAttenuation;
	this->quadraticAttenuation = quadraticAttenuation;
}

Light::Light(LightType type, fPoint position, float4 ambient, float4 diffuse, float4 specular,
	fPoint direction, float exponent, float cutoff, float constantAttenuation, float linearAttenuation, float quadraticAttenuation)
{
	this->type = type;
	float fourthPositionValue = 1.0f;
	this->position = new float[4]{ position.x, position.y, position.z, fourthPositionValue };
	this->ambient = new float[4]{ ambient.x, ambient.y, ambient.z, ambient.w };
	this->diffuse = new float[4]{ diffuse.x, diffuse.y, diffuse.z, diffuse.w };
	this->specular = new float[4]{ specular.x, specular.y, specular.z, specular.w };
	this->direction = new float[3]{ direction.x, direction.y, direction.z };
	this->exponent = exponent;
	this->cutoff = cutoff;
	this->constantAttenuation = constantAttenuation;
	this->linearAttenuation = linearAttenuation;
	this->quadraticAttenuation = quadraticAttenuation;
}

Light::~Light()
{
	RELEASE(position);
	RELEASE(ambient);
	RELEASE(diffuse);
	RELEASE(specular);
	RELEASE(direction);	
}