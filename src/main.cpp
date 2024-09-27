

#if 1
#include <iostream>
#include <Eigen/Core>
#include "..\src\Validity\btet.hpp"
#include "..\src\Validity\hocgv.hpp"
#include "..\src\Exp\exp.h"
#include <random>
#include <ctime>
#include <chrono>

std::vector<CABT::scalar> tlist0;
std::vector<CABT::scalar> tlist1;

CABT::tet2_constant_data data2;
CABT::subdivide_tree<CABT::mat20_4> tree20_4;
CABT::tet3_constant_data data3;
CABT::subdivide_tree<CABT::mat84_4> tree35_4;
double regular_pos[30] = { 0.807663 , 0.372121 , 0.4991 , 0.769641 , 0.379124 , 0.239324 , 0.75124 , 0.396562 , 0.0312357 ,
0.681321 , 0.426393 , 0.320528 , 0.616128 , 0.432535 , 0.0313826 , 0.550644 , 0.499718 , 0.163866 ,
0.672163 , 0.313374 , 0.295082 , 0.634206 , 0.316486 , 0.030531 , 0.545913 , 0.386881 , 0.124033 , 0.550612 , 0.279501 , 0.127056};
double irregular_pos[30] = { 0,0,0, 0,0,1e-3, 0,0,2e-3, 0,0.5,0, 0,0.5,1e-3, 0,1,0, 0.5,0,0, 0.5,0,1e-3, 0.5,0.5,0, 1,0,0};

double regular_pos3[60] = { 0, 0, 0,  0, 0, 0.3333,  0, 0, 0.6667,  0, 0, 1,  0, 0.3333, 0,
0, 0.3333, 0.3333,  0, 0.3333, 0.6667,  0, 0.6667, 0,  0, 0.6667, 0.3333,  0, 1, 0,
0.3333, 0, 0,  0.3333, 0, 0.3333,  0.3333, 0, 0.6667,  0.3333, 0.3333, 0,  0.3333, 0.3333, 0.3333,
0.3333, 0.6667, 0,  0.6667, 0, 0,  0.6667, 0, 0.3333,  0.6667, 0.3333, 0,  1, 0, 0 };

#pragma region order 2
void runMymethod_example()
{
	CABT::mat3_10 val, dir;
	CABT::tet2 tet;
	std::ifstream inFile("C:\\Git Code\\HighOrderDeformation\\src\\info.txt", std::ios::binary);
	double inf;
	double sup;
	CABT::scalar step_time(1);
	if (inFile.is_open()) {
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				inFile.read(reinterpret_cast<char*>(&inf), sizeof(double));
				inFile.read(reinterpret_cast<char*>(&sup), sizeof(double));
				val(i, j) = CABT::scalar(inf, sup);
			}
		}
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				inFile.read(reinterpret_cast<char*>(&inf), sizeof(double));
				inFile.read(reinterpret_cast<char*>(&sup), sizeof(double));
				dir(i, j) = CABT::scalar(inf, sup);
			}
		}
		inFile.close();
	}
	else {
		std::cerr << "无法打开文件。\n";
		return;
	}

	tet.init(val, dir, &data2, &tree20_4);
	//dprint(step_time.inf());
	tet.run(step_time);
	dprint("time:", step_time.inf());
	//tet.compute_jacobidet(step_time);
}

void runMymethod_batch()
{
	CABT::mat3_10 val, dir;
	CABT::tet2 tet;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> disReal(0.0, 1.0); // 在 [0.0, 1.0] 范围内生成均匀分布的浮点数

	std::ofstream outFile("C:\\Git Code\\HighOrderDeformation\\src\\data.txt");
	dprint("begin");
	CABT::scalar sum(0);
	clock_t start = clock();
	for (int i = 0; i < 10000; ++i)
	{
		//dprint("\n\ni", i);
		CABT::scalar step_time(1);
		if (i % 1000 == 0)
		{
			dprint(i);
		}
		for (int j = 0; j < 10; ++j) { for (int k = 0; k < 3; ++k) { val(k, j) = irregular_pos[j * 3 + k]; } }
		for (int j = 0; j < 10; ++j) { for (int k = 0; k < 3; ++k) { dir(k, j) = disReal(gen); } }

		tet.init(val, dir, &data2, &tree20_4);
		//dprint(step_time.inf());
		tet.run(step_time);
		//dprint(step_time.inf());
		sum += step_time;
#if 0
		outFile << i << " ";
		dprint("step_time:", step_time);
		outFile << tet.compute_jacobidet(step_time) << std::endl;
#endif
	}
	outFile.close();
	dprint("time:", clock() - start);
	dprint("time sum:", sum);
}

void runHocgv_example()
{
	CABT::mat3_10 val, dir;
	CABT::hocgv2 hocg;

	std::ifstream inFile("C:\\Git Code\\HighOrderDeformation\\src\\info.txt", std::ios::binary);
	double inf;
	double sup;
	CABT::scalar step_time(1);
	if (inFile.is_open()) {
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				inFile.read(reinterpret_cast<char*>(&inf), sizeof(double));
				inFile.read(reinterpret_cast<char*>(&sup), sizeof(double));
				val(i, j) = CABT::scalar(inf, sup);
			}
		}
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				inFile.read(reinterpret_cast<char*>(&inf), sizeof(double));
				inFile.read(reinterpret_cast<char*>(&sup), sizeof(double));
				dir(i, j) = CABT::scalar(inf, sup);
			}
		}
		inFile.close();
	}
	else {
		std::cerr << "无法打开文件。\n";
		return;
	}

	hocg.init(val, dir, &data2);
	hocg.run(step_time);
	dprint("time:", step_time);
	//hocg.compute_jacobidet(step_time);
}

void runHocgv_batch()
{
	CABT::mat3_10 val, dir;
	CABT::hocgv2 hocg;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> disReal(0.0, 1.0); // 在 [0.0, 1.0] 范围内生成均匀分布的浮点数

	std::ofstream outFile("C:\\Git Code\\HighOrderDeformation\\src\\data.txt");
	dprint("begin");
	CABT::scalar sum(0);
	clock_t start = clock();
	for (int i = 0; i < 10000; ++i)
	{
		CABT::scalar step_time(1);
		//dprint("\n\ni", i);
		if (i % 1000 == 0)
		{
			dprint(i);
		}
		for (int j = 0; j < 10; ++j) { for (int k = 0; k < 3; ++k) { val(k, j) = irregular_pos[j * 3 + k]; } }
		for (int j = 0; j < 10; ++j) { for (int k = 0; k < 3; ++k) { dir(k, j) = disReal(gen); } }

		hocg.init(val, dir, &data2);
		//dprint(step_time.inf());
		hocg.run(step_time);
		//dprint(step_time.inf());
		sum += step_time;

#if 0
		outFile << i << " ";
		dprint("step_time:", step_time);
		outFile << hocg.compute_jacobidet(step_time) << std::endl;
#endif
	}
	outFile.close();
	dprint(clock() - start);
	dprint("time sum:", sum);
}

void run_example()
{
	CABT::mat3_10 val, dir;
	CABT::tet2 tet;
	CABT::hocgv2 hocg;
	std::ifstream inFile("C:\\Git Code\\HighOrderDeformation\\src\\info.txt", std::ios::binary);
	double inf;
	double sup;
	CABT::scalar step_time0(1);
	CABT::scalar step_time1(1);
	if (inFile.is_open()) {
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				inFile.read(reinterpret_cast<char*>(&inf), sizeof(double));
				inFile.read(reinterpret_cast<char*>(&sup), sizeof(double));
				val(i, j) = CABT::scalar(inf, sup);
			}
		}
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				inFile.read(reinterpret_cast<char*>(&inf), sizeof(double));
				inFile.read(reinterpret_cast<char*>(&sup), sizeof(double));
				dir(i, j) = CABT::scalar(inf, sup);
			}
		}
		inFile.close();
	}
	else {
		std::cerr << "无法打开文件。\n";
		return;
	}

	auto valt = val;
	auto dirt = dir;

	tet.init(val, dir, &data2, &tree20_4);
	tet.run(step_time0);
	dprint("time:", step_time0);
	//tet.compute_jacobidet(step_time0);

	hocg.init(valt, dirt, &data2);
	hocg.run(step_time1);
	dprint("time:", step_time1);
	//hocg.compute_jacobidet(step_time1);
}

void run_batch()
{
	CABT::mat3_10 val, dir;
	CABT::tet2 tet;
	CABT::hocgv2 hocg;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> disReal(0.0, 1.0); // 在 [0.0, 1.0] 范围内生成均匀分布的浮点数

	dprint("begin");
	CABT::scalar step_time0(1);
	CABT::scalar step_time1(1);
	clock_t start = clock();
	std::ofstream outFile("C:\\Git Code\\HighOrderDeformation\\src\\data.txt");
	int count = 0;
	double dif = 0;
	for (int i = 0; i < 1000; ++i)
	{
		//dprint("\n\ni", i);
		if (i % 100 == 0)
		{
			dprint(i);
		}
		for (int j = 0; j < 10; ++j) { for (int k = 0; k < 3; ++k) { val(k, j) = regular_pos[j * 3 + k]; } }
		for (int j = 0; j < 10; ++j) { for (int k = 0; k < 3; ++k) { dir(k, j) = disReal(gen); } }

		auto valt = val;
		auto dirt = dir;

		//step_time0 = CABT::scalar(1);
		tet.init(val, dir, &data2, &tree20_4);
		tet.run(step_time0);
		dprint(i);
		dprint("step_time0:", step_time0);

		//step_time1 = CABT::scalar(1);
		hocg.init(valt, dirt, &data2);
		hocg.run(step_time1);
		dprint("step_time1:", step_time1);

#if 0
		dprint("step_time:");
		tet.compute_jacobidet(step_time0);
		hocg.compute_jacobidet(step_time1);
#endif
		if (step_time0.inf() > step_time1.inf())
			++count;
		dif += step_time0.inf() - step_time1.inf();
		outFile << i << " " << step_time0 << " " << step_time1 << std::endl;
		outFile << count << " " << dif << std::endl;
		outFile << std::endl;
	}
	outFile.close();
	dprint(clock() - start);
}

void run_same_batch_test_time()
{
	int size = 10000;
#if 1
	CABT::write_batch_test_data(2, size);
	exit(0);
#endif
	std::vector<CABT::mat3_10> val0, val1, dir0, dir1;
	CABT::tet2 tet;
	CABT::hocgv2 hocg;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> disReal(0.0, 1.0); // 在 [0.0, 1.0] 范围内生成均匀分布的浮点数

	val0.resize(size);
	val1.resize(size);
	dir0.resize(size);
	dir1.resize(size);
	CABT::read_batch_test_data(2, size, val0, dir0);
	/*dprint(val0[0]);
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < 10; ++j) { for (int k = 0; k < 3; ++k) { val0[i](k, j) = regular_pos[j * 3 + k]; } }
		for (int j = 0; j < 10; ++j) { for (int k = 0; k < 3; ++k) { dir0[i](k, j) = disReal(gen); } }
	}
	dprint(val0[0]);
	exit(0);*/
	val1 = val0;
	dir1 = dir0;

#if 1
	//for (int k = 3; k <= 3; ++k)
	//{
	//	dprint("k", k);
	//	CABT::scalar sum(0);
	//	auto valk = val0;
	//	auto dirk = dir0;
	//	auto start = std::chrono::high_resolution_clock::now();
	//	for (int i = 0; i < size; ++i)
	//	{
	//		//dprint(i);
	//		CABT::scalar step_time(0.1);
	//		tet.init(valk[i], dirk[i], &data2, &tree20_4);
	//		tet.subdivision_times = k;
	//		tet.run(step_time);
	//		sum += step_time;
	//	}
	//	auto end = std::chrono::high_resolution_clock::now();
	//	std::chrono::duration<double, std::milli> elapsed = end - start;
	//	dprint("my method time:", elapsed.count());
	//	//dprint(step_time);
	//	dprint("time sum:", sum);
	//}
	//for (int k = 3; k <= 3; ++k)
	//{
	//	dprint("k", k);
	//	CABT::scalar sum(0);
	//	auto valk = val0;
	//	auto dirk = dir0;
	//	auto start = std::chrono::high_resolution_clock::now();
	//	for (int i = 0; i < size; ++i)
	//	{
	//		//dprint(i);
	//		CABT::scalar step_time(1);
	//		tet.init(valk[i], dirk[i], &data2, &tree20_4);
	//		tet.subdivision_times = k;
	//		tet.run(step_time);
	//		sum += step_time;
	//	}
	//	auto end = std::chrono::high_resolution_clock::now();
	//	std::chrono::duration<double, std::milli> elapsed = end - start;
	//	dprint("my method time:", elapsed.count());
	//	//dprint(step_time);
	//	dprint("time sum:", sum);
	//}
	for (int k = 12; k <= 12; ++k)
	{
		dprint("k:", k);
		CABT::scalar sum(0);
		auto valk = val1;
		auto dirk = dir1;
		auto start = std::chrono::high_resolution_clock::now();
		int queue_size = 0;
		for (int i = 0; i < size; ++i)
		{
			CABT::scalar step_time(1);
			hocg.init(valk[i], dirk[i], &data2);
			hocg.max_subdivide_times = k;
			hocg.run(step_time);
			queue_size += hocg.tet_queue.size();
			sum += step_time;
			/*dprint(step_time);
			exit(0);*/
		}
		dprint("avg queue size:", queue_size / size);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> elapsed = end - start;
		dprint("hocgv time:", elapsed.count());
		//dprint(step_time);
		dprint("time sum:", sum);
	}

	
	//return;

	


#else
	for (int i = 0; i < size; ++i)
	{
		//dprint(i);
		CABT::scalar step_time0(0.5);
		tet.init(val0[i], dir0[i], &data2, &tree20_4);
		tet.run(step_time0);

		CABT::scalar step_time1(0.5);
		hocg.init(val1[i], dir1[i], &data2);
		hocg.run(step_time1);

		dprint(i, step_time0, step_time1);
		if (step_time0.inf() > step_time1.sup())
		{
			tet.compute_jacobidet(step_time0, 100);
			exit(0);
		}
	}
#endif
}
#pragma endregion

#pragma region order 3
void runMymethod3_batch()
{
	CABT::mat3_20 val, dir;
	CABT::tet3 tet;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> disReal(0.0, 1.0); // 在 [0.0, 1.0] 范围内生成均匀分布的浮点数

	std::ofstream outFile("C:\\Git Code\\HighOrderDeformation\\src\\data.txt");
	dprint("begin");
	CABT::scalar step_time(1);
	clock_t start = clock();
	for (int i = 0; i < 10000; ++i)
	{
		//dprint("\n\ni", i);
		if (i % 1000 == 0)
		{
			dprint(i);
		}
		for (int j = 0; j < 20; ++j) { for (int k = 0; k < 3; ++k) { val(k, j) = regular_pos3[j * 3 + k]; } }
		for (int j = 0; j < 20; ++j) { for (int k = 0; k < 3; ++k) { dir(k, j) = disReal(gen); } }

		tet.init(val, dir, &data3, &tree35_4);
		//dprint(step_time.inf());
		tet.run(step_time);
		//dprint(step_time.inf());

#if 0
		outFile << i << " ";
		dprint("step_time:", step_time);
		outFile << tet.compute_jacobidet(step_time) << std::endl;
#endif
	}
	outFile.close();
	dprint(clock() - start);
}

void runHocgv3_batch()
{
	CABT::mat3_20 val, dir;
	CABT::hocgv3 hocg;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> disReal(0.0, 1.0); // 在 [0.0, 1.0] 范围内生成均匀分布的浮点数

	std::ofstream outFile("C:\\Git Code\\HighOrderDeformation\\src\\data.txt");
	dprint("begin");
	CABT::scalar step_time(1);
	clock_t start = clock();
	for (int i = 0; i < 10000; ++i)
	{
		//dprint("\n\ni", i);
		if (i % 1000 == 0)
		{
			dprint(i);
		}
		for (int j = 0; j < 20; ++j) { for (int k = 0; k < 3; ++k) { val(k, j) = regular_pos3[j * 3 + k]; } }
		for (int j = 0; j < 20; ++j) { for (int k = 0; k < 3; ++k) { dir(k, j) = disReal(gen); } }

		hocg.init(val, dir, &data3);
		//dprint(step_time.inf());
		hocg.run(step_time);
		//dprint(step_time.inf());

#if 0
		outFile << i << " ";
		dprint("step_time:", step_time);
		outFile << hocg.compute_jacobidet(step_time) << std::endl;
#endif
	}
	outFile.close();
	dprint(clock() - start);
}
#pragma endregion


int main(int argc, char *argv[])
{

#if USE_PROTECTOR
	CABT::scalar::Protector p;
#endif

#if 1
	CABT::exp1::run_exp1();
	return 1;
#endif

#if 0
	CABT::exp3::run_exp3();
	return 1;
#endif

#if 1
	int m_switch[7] = { 0, 0, 0, 0, 0, 0, 1 };
#else
	int m_switch[6] = { 0,1,0,1,0,0 };
#endif
	if (m_switch[0])
	{
		runMymethod_example();
	}
	if (m_switch[1])
	{
		runMymethod_batch();
	}
	if (m_switch[2])
	{
		runHocgv_example();
	}
	if (m_switch[3])
	{
		runHocgv_batch();
	}
	if (m_switch[4])
	{
		run_example();
	}
	if (m_switch[5])
	{
		run_batch();
	}
	if (m_switch[6])
	{
		run_same_batch_test_time();
	}

#if 1
	int m3_switch[6] = { 0,0,0,0,0,0 };
#else
	int m3_switch[6] = { 0,1,0,1,0,0 };
#endif
	/*if (m3_switch[0])
	{
		runMymethod_example();
	}*/
	if (m3_switch[1])
	{
		runMymethod3_batch();
	}
	/*if (m3_switch[2])
	{
		runHocgv_example();
	}*/
	if (m3_switch[3])
	{
		runHocgv3_batch();
	}
	/*if (m3_switch[4])
	{
		run_example();
	}
	if (m3_switch[5])
	{
		run_batch();
	}*/


	return 1;



	//QApplication app(argc, argv);

	//SurfaceMeshProcessing mainWin;
	///*mainWin.setGeometry(100,100,mainWin.sizeHint().width(),mainWin.sizeHint().height());
	//mainWin.resize( mainWin.sizeHint() );*/
	//mainWin.showMaximized();

	//if( argc > 1 )
	//{
	//	mainWin.open_mesh_from_main(argv[1]);
	//}

	//return app.exec();
}
#else
#include "surfacemeshprocessing.h"
#include <QtWidgets/QApplication>
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	SurfaceMeshProcessing mainWin;
	/*mainWin.setGeometry(100,100,mainWin.sizeHint().width(),mainWin.sizeHint().height());
	mainWin.resize( mainWin.sizeHint() );*/
	mainWin.showMaximized();

	if( argc > 1 )
	{
		mainWin.open_mesh_from_main(argv[1]);
	}

	return app.exec();
}
#endif
