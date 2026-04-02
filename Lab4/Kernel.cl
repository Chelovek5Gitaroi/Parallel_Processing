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
	
	if (fabs(den) <= 0.0000001)
	{
		return 0;
	}
	
	return (sin(x) * powr(x, 2) + x * 4) / den;
}

kernel void calcIntegral(global const float* left, global const float* right, float rectWidth, global float* result)
{
	int lid = get_local_id(0);

	int gid = get_global_id(0);
	float x = left[gid];

	local float buf[SIZE];

	buf[lid] = FUNC(x) * rectWidth;
	
	barrier(CLK_LOCAL_MEM_FENCE);

	for (int i = 2; i <= SIZE; i <<= 1)
	{
		if (lid % i == 0)
		{
			buf[lid] += buf[lid + (i >> 1)];
		}

		barrier(CLK_LOCAL_MEM_FENCE);
	}

	if (lid == 0)
	{
		result[get_group_id(0)] = buf[0];
	}
}