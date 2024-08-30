#include "surfacemeshprocessing.h"
#include <QtWidgets/QApplication>



#include "..\src\Validity\btet.h"
#include <random>
#include <ctime>
int main(int argc, char *argv[])
{
#if 1
	CABT::tet2_constant_data data;
	CABT::subdivide_tree tree;
	std::random_device rd; 
	std::mt19937 gen(rd());
	double vv[30] = { 0.807663 , 0.372121 , 0.4991 ,
0.769641 , 0.379124 , 0.239324 ,
0.75124 , 0.396562 , 0.0312357 ,
0.681321 , 0.426393 , 0.320528 ,
0.616128 , 0.432535 , 0.0313826 ,
0.550644 , 0.499718 , 0.163866 ,
0.672163 , 0.313374 , 0.295082 ,
0.634206 , 0.316486 , 0.030531 ,
0.545913 , 0.386881 , 0.124033 ,
0.550612 , 0.279501 , 0.127056
	};
	std::uniform_real_distribution<> disReal(0.0, 1.0); // 在 [0.0, 1.0] 范围内生成均匀分布的浮点数

	std::ofstream outFile("C:\\Git Code\\HighOrderDeformation\\src\\data.txt");
	dprint("begin");
	clock_t start = clock();
	for (int i = 0; i < 10000; ++i)
	{
		//dprint("\n\ni", i);
		if (i % 100 == 0)
		{
			dprint(i);
		}
		CABT::mat3_10 val, dir;
		for (int j = 0; j < 10; ++j) { for (int k = 0; k < 3; ++k) { val(k, j) = vv[j * 3 + k]; } }

		for (int j = 0; j < 10; ++j) { for (int k = 0; k < 3; ++k) { dir(k, j) = disReal(gen); } }

		CABT::tet2 tet;
		CABT::scalar time = CABT::scalar(1);
		tet.init(val, dir, &data, &tree);
		//dprint(time.inf());
		tet.run(time);
		//dprint(time.inf());

		/*outFile << i << " ";
		dprint("time:");
		outFile << tet.compute_jacobidet(time) << std::endl;*/
	}
	outFile.close();
	dprint(clock() - start);
	return 1;
#else
	CABT::tet2 tet;
	CABT::tet2_constant_data data;
	CABT::subdivide_tree tree;
	CABT::mat3_10 val, dir;
	CABT::scalar time(1);
	std::random_device rd;  // 用于生成种子
	std::mt19937 gen(rd()); // Mersenne Twister 19937 引擎

	std::ifstream inFile("C:\\Git Code\\HighOrderDeformation\\src\\example7.txt", std::ios::binary);
	double inf;
	double sup;
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
		return 0;
	}

	tet.init(val, dir, &data, &tree);
	dprint(time.inf());
	tet.run(time);
	dprint(time.inf());
	tet.compute_jacobidet(time);
	return 1;
#endif




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
