#include "alg.h"

#if defined(unix) || defined(__unix__)
std::string data_fold = "./../../wd/dataset/", index_fold = " ";
std::string data_fold1 = data_fold, data_fold2 = data_fold+("MIPS/");
#else
std::string data_fold = "E:/Dataset_for_c/", index_fold = " ";
std::string data_fold1 = data_fold, data_fold2 = data_fold+("MIPS/");

#endif





#if defined(unix) || defined(__unix__)
struct llt
{
	int date, h, m, s;
	llt(size_t diff) { set(diff); }
	void set(size_t diff)
	{
		date = diff / 86400;
		diff = diff % 86400;
		h = diff / 3600;
		diff = diff % 3600;
		m = diff / 60;
		s = diff % 60;
	}
};
#endif

void saveAndShow(float c, int k, std::string& dataset, std::vector<resOutput>& res)
{
	time_t now = time(0);
	tm* ltm = new tm[1];
	localtime_s(ltm, &now);
	std::string query_result = ("results/Running_result.txt");
	std::ofstream os(query_result, std::ios_base::app);
	os.seekp(0, std::ios_base::end); // 

	//time_t now = std::time(0);
	time_t zero_point = 1635153971 - 17 * 3600 - 27 * 60;//Let me set the time at 2021.10.25. 17:27 as the zero point
	size_t diff = (size_t)(now - zero_point);
#if defined(unix) || defined(__unix__)
	llt lt(diff);
#endif

	double date = ((float)(now - zero_point)) / 86400;
	float hour = date - floor(date);
	hour *= 24;
	float minute= hour = date - floor(date);


	std::stringstream ss;

	ss << "*******************************************************************************************************\n"
		<< "The result of ALSHS for " << dataset << " is as follow: c="<<c<<", k="<<k
		<<"\n"
		<< "******************************************************************************************************\n";

	ss << std::setw(12) << "algName"
		<< std::setw(12) << "L"
		<< std::setw(12) << "K"
		<< std::setw(12) << "Time"
		<< std::setw(12) << "Recall"
		<< std::setw(12) << "Ratio"
		<< std::setw(12) << "Cost"
		<< std::endl
		<< std::endl;
	for (int i = 0; i < res.size(); ++i) {
		ss << std::setw(12) << res[i].algName
			<< std::setw(12) << res[i].L
			<< std::setw(12) << res[i].K
			<< std::setw(12) << res[i].time
			<< std::setw(12) << res[i].recall
			<< std::setw(12) << res[i].ratio
			<< std::setw(12) << res[i].cost
			<< std::endl;
	}
#if defined(unix) || defined(__unix__)
	ss << "\n******************************************************************************************************\n"
		<< "                                                                                    "
		<< lt.date << '-' << lt.h << ':' << lt.m << ':' << lt.s
		<< "\n*****************************************************************************************************\n\n\n";
#else
	ss << "\n******************************************************************************************************\n"
		<< "                                                                                    "
		<< ltm->tm_mon + 1 << '-' << ltm->tm_mday << ' ' << ltm->tm_hour << ':' << ltm->tm_min
		<< "\n*****************************************************************************************************\n\n\n";
#endif
	

	std::cout << ss.str();
	os << ss.str();
	os.close();  delete []ltm;
	//delete[] ltm;
}

//alg=:
//0:MF_ALSH
//1:H2_ALSH
//2:Simple_LSH
//3:Range_LSH
//4:Sign_ALSH  
//5:RPT
//6:L2_ALSH
void setParam(int alg, std::string dataset, int& m, int& L, int& K, float& W)
{
	enum algs { GMP_ALSH, H2_ALSH, Simple_LSH, Range_LSH, Sign_ALSH, RPT, L2_ALSH };
	if (dataset == "gist") {
		switch (alg) {
		case GMP_ALSH: {
			L = 5;
			K = 12;
			break;
		}
		case H2_ALSH: {
			break;
		}
		case Simple_LSH: {
			L = 20;
			K = 14;
			break;
		}
		case Range_LSH: {
			m = 200;
			L = 20;
			K = 12;
			break;
		}
		case Sign_ALSH: {
			L = 50;
			K = 16;
			break;
		}
		case RPT: {
			L = 50;
			K = 16;
			break;
		}
		case L2_ALSH: {
			L = 20;
			K = 6;
			W = 1.0f;
			break;
		}
		default:
			break;
		}

	}
	else if (dataset == "tiny") {
		switch (alg) {
		case GMP_ALSH: {
			L = 5;
			K = 12;
			break;
		}
		case H2_ALSH: {
			break;
		}
		case Simple_LSH: {
			L = 8;
			K = 7;
			break;
		}
		case Range_LSH: {
			m = 500;
			L = 8;
			K = 7;
			break;
		}
		case Sign_ALSH: {
			L = 6;
			K = 10;
			break;
		}
		case RPT: {
			L = 8;
			K = 8;
			break;
		}
		case L2_ALSH: {
			L = 12;
			K = 5;
			W = 2.0f;
			break;
		}
		default:
			break;
		}
	}
	else if (dataset == "NUS") {
		switch (alg) {
		case GMP_ALSH: {
			L = 5;
			K = 12;
			break;
		}
		case H2_ALSH: {
			break;
		}
		case Simple_LSH: {
			L = 20;
			K = 6;
			break;
		}
		case Range_LSH: {
			m = 50;
			L = 20;
			K = 6;
			break;
		}
		case Sign_ALSH: {
			L = 20;
			K = 6;
			break;
		}
		case RPT: {
			L = 20;
			K = 6;
			break;
		}
		case L2_ALSH: {
			L = 20;
			K = 5;
			W = 1.0f;
			break;
		}
		default:
			break;
		}
	}
	else if (dataset == "yahoo_large") {
		switch (alg) {
		case GMP_ALSH: {
			L = 5;
			K = 12;
			break;
		}
		case H2_ALSH: {
			break;
		}
		case Simple_LSH: {
			L = 50;
			K = 9;
			break;
		}
		case Range_LSH: {
			m = 40;
			L = 50;
			K = 5;
			break;
		}
		case Sign_ALSH: {
			L = 30;
			K = 8;
			break;
		}
		case RPT: {
			L = 20;
			K = 9;
			break;
		}
		case L2_ALSH: {
			L = 50;
			K = 6;
			W = 1.5f;
			break;
		}
		default:
			break;
		}
	}
	else if (dataset == "MovieLens") {
		switch (alg) {
		case GMP_ALSH: {
			L = 5;
			K = 12;
			break;
		}
		case H2_ALSH: {
			break;
		}
		case Simple_LSH: {
			L = 200;
			K = 7;
			break;
		}
		case Range_LSH: {
			m = 40;
			L = 50;
			K = 5;
			break;
		}
		case Sign_ALSH: {
			L = 50;
			K = 5;
			break;
		}
		case RPT: {
			L = 50;
			K = 5;
			break;
		}
		case L2_ALSH: {
			L = 50;
			K = 6;
			W = 2.0f;
			break;
		}
		default:
			break;
		}
	}
	else if (dataset == "trevi") {
		switch (alg) {
		case GMP_ALSH: {
			L = 5;
			K = 12;
			break;
		}
		case H2_ALSH: {
			break;
		}
		case Simple_LSH: {
			L = 10;
			K = 12;
			break;
		}
		case Range_LSH: {
			m = 40;
			L = 20;
			K = 6;
			break;
		}
		case Sign_ALSH: {
			L = 10;
			K = 12;
			break;
		}
		case RPT: {
			L = 10;
			K = 12;
			break;
		}
		case L2_ALSH: {
			L = 10;
			K = 5;
			W = 1.0f;
			break;
		}
		default:
			break;
		}
	}
	else if (dataset == "audio") {
		switch (alg) {
		case GMP_ALSH: {
			L = 5;
			K = 12;
			break;
		}
		case H2_ALSH: {
			break;
		}
		case Simple_LSH: {
			L = 25;
			K = 5;
			break;
		}
		case Range_LSH: {
			m = 40;
			L = 25;
			K = 5;
			break;
		}
		case Sign_ALSH: {
			L = 50;
			K = 6;
			break;
		}
		case RPT: {
			L = 30;
			K = 6;
			break;
		}
		case L2_ALSH: {
			L = 40;
			K = 5;
			W = 4.0f;
			break;
		}
		default:
			break;
		}
	}
	else if (dataset == "netflix") {
		switch (alg) {
		case GMP_ALSH: {
			L = 5;
			K = 12;
			break;
		}
		case H2_ALSH: {
			break;
		}
		case Simple_LSH: {
			L = 20;
			K = 6;
			break;
		}
		case Range_LSH: {
			m = 40;
			L = 30;
			K = 5;
			break;
		}
		case Sign_ALSH: {
			L = 20;
			K = 6;
			break;
		}
		case RPT: {
			L = 20;
			K = 6;
			break;
		}
		case L2_ALSH: {
			L = 20;
			K = 5;
			W = 2.0f;
			break;
		}
		default:
			break;
		}
	}
	else if (dataset == "mnist") {
		switch (alg) {
		case GMP_ALSH: {
			L = 5;
			K = 12;
			break;
		}
		case H2_ALSH: {
			break;
		}
		case Simple_LSH: {
			L = 20;
			K = 7;
			break;
		}
		case Range_LSH: {
			m = 40;
			L = 20;
			K = 8;
			break;
		}
		case Sign_ALSH: {
			L = 10;
			K = 8;
			break;
		}
		case RPT: {
			L = 10;
			K = 7;
			break;
		}
		case L2_ALSH: {
			L = 50;
			K = 5;
			W = 1.2f;
			break;
		}
		default:
			break;
		}
	}
	else if (dataset == "sift") {
		switch (alg) {
		case GMP_ALSH: {
			L = 10;
			K = 12;
			break;
		}
		case H2_ALSH: {
			break;
		}
		case Simple_LSH: {
			L = 5;
			K = 9;
			break;
		}
		case Range_LSH: {
			m = 2000;
			L = 5;
			K = 9;
			break;
		}
		case Sign_ALSH: {
			L = 7;
			K = 8;
			break;
		}
		case RPT: {
			L = 10;
			K = 14;
			break;
		}
		case L2_ALSH: {
			L = 5;
			K = 5;
			W = 1.5f;
			break;
		}
		default:
			break;
		}

	}
	else if (dataset == "deep1m"){
		switch (alg) {
		case GMP_ALSH: {
			L = 5;
			K = 12;
			break;
		}
		case H2_ALSH: {
			break;
		}
		case Simple_LSH: {
			L = 10;
			K = 8;
			break;
		}
		case Range_LSH: {
			m = 200;
			L = 10;
			K = 8;
			break;
		}
		case Sign_ALSH: {
			L = 10;
			K = 8;
			break;
		}
		case RPT: {
			L = 10;
			K = 8;
			break;
		}
		case L2_ALSH: {
			L = 20;
			K = 5;
			W = 3.0f;
			break;
		}
		default:
			break;
		}

	}
	else if (dataset == "cifar") {
		switch (alg) {
		case GMP_ALSH: {
			L = 5;
			K = 9;
			break;
		}
		case H2_ALSH: {
			break;
		}
		case Simple_LSH: {
			L = 10;
			K = 9;
			break;
		}
		case Range_LSH: {
			m = 40;
			L = 10;
			K = 8;
			break;
		}
		case Sign_ALSH: {
			L = 10;
			K = 9;
			break;
		}
		case RPT: {
			L = 10;
			K = 9;
			break;
		}
		case L2_ALSH: {
			L = 20;
			K = 5;
			W = 1.0f;
			break;
		}
		default:
			break;
		}
	}
}
void expe_k()
{
	std::string dataset = "mnist";
	std::string* argvStr = new std::string[4];
	argvStr[1] = (dataset + ".data");
	argvStr[2] = (dataset + ".index");
	argvStr[3] = (dataset + ".ben");

	float c = 0.8f;
	float c0 = 2.0;
	int k = 50;
	float S0 = 0.85f;
	int M = 2;

	int m, L, K;
	float W = 1.0f;

	std::cout << "Using ALSHS for " << argvStr[1] << std::endl;
	//std::string pos = "E:\\";
	//std::string data_fold = pos + ("Dataset_for_c\\"), index_fold = pos + ("Dataset_for_c\\MIPS\\ALSHS\\");
	//std::string data_fold1 = data_fold, data_fold2 = data_fold + ("MIPS\\ALSHS\\");
	Preprocess prep(data_fold1 + (argvStr[1]), data_fold2 + (argvStr[3]));

	std::vector<resOutput> res;
	m = std::max(prep.data.N / 20000, 20);
	L = 5;
	K = 12;

	setParam(0, dataset, m, L, K, W);
	Alg1_mfalsh(argvStr[1], argvStr[2], argvStr[3], c, m, k, L, K, prep);

	c = 0.8;

	//saveAndShow(c, k, dataset, res);

	delete[]argvStr;
	return ;
}