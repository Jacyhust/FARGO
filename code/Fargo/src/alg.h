#pragma once
#include <string>
#include "Preprocess.h"
#include "mf_alsh.h"
#include "performance.h"
#include "basis.h"

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

struct resOutput
{
	std::string algName;
	int L;
	int K;
	float time;
	float recall;
	float ratio;
	float cost;
};

extern std::string data_fold, index_fold;
extern std::string data_fold1, data_fold2;

#if defined(unix) || defined(__unix__)
inline void localtime_s(tm* ltm, time_t* now) {}
#endif


inline void Alg1_mfalsh(std::string file1, std::string file2, std::string file3, float c_, int m_, int k_, int L_, int K_, Preprocess& prep)
{
	//std::string pos = "E:\\";
	//std::string data_fold = pos + ("Dataset_for_c\\"), index_fold = pos + ("Dataset_for_c\\MIPS\\MF_ALSH\\");
	//std::string data_fold1 = pos + ("Dataset_for_c\\"), data_fold2 = data_fold + ("MIPS\\");
	std::string query_result = data_fold2 + ("ALSHS/MF_ALSH_result.csv");

	Parameter param(prep, L_, K_, 1);

	Partition parti(c_, prep);
	mf_alsh::Hash myslsh(prep, param, index_fold.append(file2), parti, data_fold + "MyfunctionXTheta.data");

	int vary_k[] = { 1,10,20,30,40,50,60,70,80,90,100 };
	for (int r = 0; r < 11; r++)
	{
		k_ = vary_k[r];
		lsh::timer timer;
		std::cout << std::endl << "RUNNING QUERY ..." << std::endl;

		int Qnum = 100;
		lsh::progress_display pd(Qnum);
		Performance<mf_alsh::Query> perform;
		for (int j = 0; j < Qnum; j++)
		{
			mf_alsh::Query query(j, c_, k_, myslsh, prep, m_);
			perform.update(query, prep);
			++pd;
		}

		float mean_time = (float)perform.time_total / perform.num;
		std::cout << "AVG QUERY TIME:    " << mean_time * 1000 << "ms." << std::endl << std::endl;
		std::cout << "AVG RECALL:        " << ((float)perform.NN_num) / (perform.num * k_) << std::endl;
		std::cout << "AVG RATIO:         " << ((float)perform.ratio) / (perform.res_num) << std::endl;
		std::cout << "AVG COST:          " << ((float)perform.cost) / ((long long)perform.num * (long long)prep.data.N) << std::endl;

		//std::cout << "\nAVG Cost of each partition:" << std::endl;
		//int len = perform.costs.size();
		//for (int i = 0; i < len; i++)
		//{
		//	std::cout << "Partition " << std::setw(3) << i << " :"
		//		<< std::setw(6) << ((float)perform.costs[i]) / (perform.num)
		//		<< ","
		//		<< std::setw(6) << ((float)perform.costs[i]) / (perform.num) / parti.nums[i]
		//		<< std::endl;
		//}

		time_t now = time(0);
		tm* ltm = new tm[1];;
		localtime_s(ltm, &now);

		std::ofstream os(query_result, std::ios_base::app);
		os.seekp(0, std::ios_base::end); // �ƶ����ļ�β
		int tmp = (int)os.tellp();
		if (tmp == 0) {
			os << "Dataset,c,k,S,RATIO,RECALL,AVG_TIME,COST,DATE" << std::endl;
		}
		std::string dataset = file1;
		dataset.erase(dataset.end() - 5, dataset.end());
		os << dataset << ',' << c_ << ',' << k_ << ',' << param.S << ','
			<< ((float)perform.ratio) / (perform.res_num) << ','
			<< ((float)perform.NN_num) / (perform.num * k_) << ','
			<< mean_time << ','
			<< ((float)perform.cost) / ((long long)perform.num * (long long)prep.data.N) << ','
			<< ltm->tm_mon + 1 << '-' << ltm->tm_mday << ' ' << ltm->tm_hour << ':' << ltm->tm_min
			<< std::endl;
		os.close();  delete []ltm;
	}
}

inline resOutput Alg0_mfalsh(mf_alsh::Hash& myslsh, float c_, int m_, int k_, int L_, int K_, Preprocess& prep)
{
	//std::string pos = "E:\\";
	//std::string data_fold = pos + ("Dataset_for_c\\"), index_fold = pos + ("Dataset_for_c\\MIPS\\MF_ALSH\\");
	//std::string data_fold1 = pos + ("Dataset_for_c\\"), data_fold2 = data_fold + ("MIPS\\");
	std::string query_result = ("results/MF_ALSH_result.csv");


	lsh::timer timer;
	std::cout << std::endl << "RUNNING QUERY ..." << std::endl;

	int Qnum = 100;
	lsh::progress_display pd(Qnum);
	Performance<mf_alsh::Query> perform;
	for (int j = 0; j < Qnum; j++)
	{
		mf_alsh::Query query(j, c_, k_, myslsh, prep, m_);
		perform.update(query, prep);
		++pd;
	}

	float mean_time = (float)perform.time_total / perform.num;
	std::cout << "AVG QUERY TIME:    " << mean_time * 1000 << "ms." << std::endl << std::endl;
	std::cout << "AVG RECALL:        " << ((float)perform.NN_num) / (perform.num * k_) << std::endl;
	std::cout << "AVG RATIO:         " << ((float)perform.ratio) / (perform.res_num) << std::endl;
	std::cout << "AVG COST:          " << ((float)perform.cost) / ((long long)perform.num * (long long)prep.data.N) << std::endl;

	time_t now = time(0);
	tm* ltm = new tm[1];;
	localtime_s(ltm, &now);

	// std::ofstream os(query_result, std::ios_base::app);
	// os.seekp(0, std::ios_base::end); // �ƶ����ļ�β
	// int tmp = (int)os.tellp();
	// if (tmp == 0) {
	// 	os << "Dataset,c,k,S,RATIO,RECALL,AVG_TIME,COST,DATE" << std::endl;
	// }
	// std::string dataset = file1;
	// dataset.erase(dataset.end() - 5, dataset.end());
	// os << dataset << ',' << c_ << ',' << k_ << ',' << param.S << ','
	// 	<< ((float)perform.ratio) / (perform.res_num) << ','
	// 	<< ((float)perform.NN_num) / (perform.num * k_) << ','
	// 	<< mean_time << ','
	// 	<< ((float)perform.cost) / ((long long)perform.num * (long long)prep.data.N) << ','
	// 	<< ltm->tm_mon + 1 << '-' << ltm->tm_mday << ' ' << ltm->tm_hour << ':' << ltm->tm_min
	// 	<< std::endl;
	// os.close();  delete []ltm;

	resOutput res;
	res.algName = "FARGO";
	res.L = myslsh.L;
	res.K = myslsh.K;
	res.time = mean_time * 1000;
	res.recall = ((float)perform.NN_num) / (perform.num * k_);
	res.ratio = ((float)perform.ratio) / (perform.res_num);
	res.cost = ((float)perform.cost) / ((long long)perform.num * (long long)myslsh.N);
	//delete[] ltm;
	return res;
}

//void Alg1_mfalsh(std::string file1, std::string file2, std::string file3, float c_, int m_, int k_, int L_, int K_, Preprocess& prep);

void saveAndShow(float c, int k, std::string& dataset, std::vector<resOutput>& res);

//alg=:
//0:MF_ALSH
//1:H2_ALSH
//2:Simple_LSH
//3:Range_LSH
//4:Sign_ALSH
//5:RPT
//6:L2_ALSH
void setParam(int alg, std::string dataset, int& m, int& L, int& K, float& W);

void expe_k();
