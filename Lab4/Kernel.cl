
float funcX2pX(float x)
{
	float exp = 2;
	return powr(x, exp) + x;
}

float funcX3mX2pX(float x)
{
	return powr(x, 3) - powr(x, 2) + x;
}

float funcX2sinX(float x)
{
	return powr(x, 2) * sin(x);
}

float funcMx2sinX(float x)
{
	return powr(x, 2) * sin(x) * (-1);
}

float funcX2sinXp4xDxPcosX(float x)
{
	float den = x + cos(x);

	return (sin(x) * powr(x, 2) + x * 4) / den;
}

kernel void calcIntegralFunc5(global const float* left, global const float* right, float rectWidth, global float* result)
{
	float res = 0.0;

	int i = get_global_id(0);

	for (float x = left[i]; x < right[i] + rectWidth / 2; x += rectWidth)
	{
		res += funcX2sinXp4xDxPcosX(x) * rectWidth;
	}

	result[i] = res;
}