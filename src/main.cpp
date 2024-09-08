﻿//#include "surfacemeshprocessing.h"
//#include <QtWidgets/QApplication>


#include <iostream>
#include <Eigen/Core>
#include "..\src\Validity\btet.h"
#include "..\src\Validity\hocgv.h"
#include <random>
#include <ctime>

std::vector<CABT::scalar> tlist0;
std::vector<CABT::scalar> tlist1;

CABT::tet2_constant_data data2;
CABT::subdivide_tree<CABT::mat20_4> tree20_4;
CABT::tet3_constant_data data3;
CABT::subdivide_tree<CABT::mat35_4> tree35_4;
double regular_pos[30] = { 0.807663 , 0.372121 , 0.4991 , 0.769641 , 0.379124 , 0.239324 , 0.75124 , 0.396562 , 0.0312357 ,
0.681321 , 0.426393 , 0.320528 , 0.616128 , 0.432535 , 0.0313826 , 0.550644 , 0.499718 , 0.163866 ,
0.672163 , 0.313374 , 0.295082 , 0.634206 , 0.316486 , 0.030531 , 0.545913 , 0.386881 , 0.124033 , 0.550612 , 0.279501 , 0.127056};
double irregular_pos[30] = { 0,0,0, 0,0,1e-5, 0,0,2e-5, 0,0.5,0, 0,0.5,1e-5, 0,1,0, 0.5,0,0, 0.5,0,1e-5, 0.5,0.5,0, 1,0,0};

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
	tet.compute_jacobidet(step_time);
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
	CABT::scalar step_time(1);
	clock_t start = clock();
	for (int i = 0; i < 10000; ++i)
	{
		//dprint("\n\ni", i);
		if (i % 1000 == 0)
		{
			dprint(i);
		}
		for (int j = 0; j < 10; ++j) { for (int k = 0; k < 3; ++k) { val(k, j) = regular_pos[j * 3 + k]; } }
		for (int j = 0; j < 10; ++j) { for (int k = 0; k < 3; ++k) { dir(k, j) = disReal(gen); } }

		tet.init(val, dir, &data2, &tree20_4);
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
	hocg.compute_jacobidet(step_time);
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
	CABT::scalar step_time(1);
	clock_t start = clock();
	for (int i = 0; i < 10000; ++i)
	{
		//dprint("\n\ni", i);
		if (i % 1000 == 0)
		{
			dprint(i);
		}
		for (int j = 0; j < 10; ++j) { for (int k = 0; k < 3; ++k) { val(k, j) = regular_pos[j * 3 + k]; } }
		for (int j = 0; j < 10; ++j) { for (int k = 0; k < 3; ++k) { dir(k, j) = disReal(gen); } }

		hocg.init(val, dir, &data2);
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
	tet.compute_jacobidet(step_time0);

	hocg.init(valt, dirt, &data2);
	hocg.run(step_time1);
	dprint("time:", step_time1);
	hocg.compute_jacobidet(step_time1);
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

#if 1
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
	for (int i = 0; i < 1000; ++i)
	{
		//dprint("\n\ni", i);
		if (i % 100 == 0)
		{
			dprint(i);
		}
		for (int j = 0; j < 20; ++j) { for (int k = 0; k < 3; ++k) { val(k, j) = regular_pos3[j * 3 + k]; } }
		for (int j = 0; j < 20; ++j) { for (int k = 0; k < 3; ++k) { dir(k, j) = disReal(gen); } }

		tet.init(val, dir, &data3, &tree35_4);
		//dprint(step_time.inf());
		tet.run(step_time);
		//dprint(step_time.inf());

#if 1
		outFile << i << " ";
		dprint("step_time:", step_time);
		outFile << tet.compute_jacobidet(step_time) << std::endl;
#endif
	}
	outFile.close();
	dprint(clock() - start);
}
#pragma endregion

int main(int argc, char *argv[])
{
#if 1
	int m_switch[6] = { 0,1,0,1,0,0 };
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
	}
	if (m3_switch[3])
	{
		runHocgv_batch();
	}
	if (m3_switch[4])
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
