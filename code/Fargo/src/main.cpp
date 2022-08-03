// ALSH_for_MIPS.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string.h>
#include <cstring>
#include <chrono>

#include "Preprocess.h"
#include "mf_alsh.h"
#include "basis.h"
#include "alg.h"
//#if defined(unix) || defined(__unix__)
//
//#else
//#include "vld.h"
//#endif
extern std::string data_fold, index_fold;
extern std::string data_fold1, data_fold2;

int main(int argc, char const* argv[])
{
	std::string dataset = "audio";
	if (argc > 1) {
		dataset = argv[1];
	}
	std::string argvStr[4];
	argvStr[1] = (dataset + ".data");
	argvStr[2] = (dataset + ".index");
	argvStr[3] = (dataset + ".ben");

	float c = 0.9f;
	float c0 = 1.5f;
	int k = 50;
	float S0 = 0.85f;
	int M = 2;
	int idx = 0;
	int m, L, K;
	float W = 1.0f;

	std::cout << "Using ALSHS for " << argvStr[1] << std::endl;
// #if defined(unix) || defined(__unix__)
// 	std::string data_fold = "./../../wd/dataset/", index_fold = " ";
// 	std::string data_fold1 = data_fold, data_fold2 = data_fold + ("MIPS/");

// #else
// 	std::string data_fold = "E:/Dataset_for_c/", index_fold = " ";
// 	std::string data_fold1 = data_fold, data_fold2 = data_fold + ("MIPS/");
// #endif
	Preprocess prep(data_fold1 + (argvStr[1]), data_fold2 + (argvStr[3]));
	//prep.data.dim=288;
	std::vector<resOutput> res;
	m = 2;
	L = 5;
	K = 12;
	c = 0.8;

	Parameter param(prep, L, K, 1);

	Partition parti(c, prep);
	mf_alsh::Hash myslsh(prep, param, index_fold.append(argvStr[2]), parti, data_fold2 + "MyfunctionXTheta.data");

	setParam(0, dataset, m, L, K, W);
	std::vector<int> ms = { 0,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,10000 };
	//std::vector<int> ms = { 2000,3000,4000,5000,10000 };
	for (auto& x : ms) {
		m = x + k;
		res.push_back(Alg0_mfalsh(myslsh, c, m, k, L, K, prep));
	}

	saveAndShow(c, k, dataset, res);
	return 0;
}
