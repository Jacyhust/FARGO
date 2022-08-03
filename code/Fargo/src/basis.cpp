#include "basis.h"

float cal_inner_product(float* v1, float* v2, int dim)
{
	//float res = 0.0;
	//for (int i = 0; i < dim; ++i) {
	//	res += v1[i] * v2[i];
	//}
	//return res;

	return calIp_fast(v1, v2, dim);
}

float cal_inner_product_trans(float* v1, float** mat, int dim)
{
	float res = 0.0f;
	return res;
}


