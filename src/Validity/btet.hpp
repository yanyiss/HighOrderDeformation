#pragma once
#include "scalar_def.hpp"
#include "constant_data.hpp"
#include "dprint.hpp"
#include <Eigen/Core>
#include <random>
namespace CABT
{
#if 1
	static void write_batch_simulation_data(std::vector<mat3_10> &val, std::vector<mat3_10> &dir,
								std::string file_dir = "C:\\Git Code\\HighOrderDeformation\\src\\simulation_data\\twist-beam-P1-data.txt")
	{
		std::ofstream outFile(file_dir, std::ios::binary);
		std::setprecision(15);
		int batch_size = val.size();
		int M = 10;
		for (int b = 0; b < batch_size; ++b)
		{
			for (int i = 0; i < M; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					outFile.write(reinterpret_cast<const char *>(&val[b](j, i)), sizeof(double));
				}
			}
		}
		for (int b = 0; b < batch_size; ++b)
		{
			for (int i = 0; i < M; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					outFile.write(reinterpret_cast<const char *>(&dir[b](j, i)), sizeof(double));
				}
			}
		}
		outFile.close();
	}

	static void write_batch_test_data(int order, int batch_size, 
		std::string file_dir= "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\regular_batch_fixed_val_rand_dir.txt")
	{
		int M = (order + 1) * (order + 2) * (order + 3) / 6;
		std::vector<double> val;
		switch (order)
		{
		case 2:
#if 1
			val = { 0.807663 , 0.372121 , 0.4991 , 0.769641 , 0.379124 , 0.239324 , 0.75124 , 0.396562 , 0.0312357 ,
				0.681321 , 0.426393 , 0.320528 , 0.616128 , 0.432535 , 0.0313826 , 0.550644 , 0.499718 , 0.163866 ,
				0.672163 , 0.313374 , 0.295082 , 0.634206 , 0.316486 , 0.030531 , 0.545913 , 0.386881 , 0.124033 , 0.550612 , 0.279501 , 0.127056 };
#else
			val = { 0,0,0, 0,0,1e-3, 0,0,2e-3, 0,0.5,0, 0,0.5,1e-3, 0,1,0, 0.5,0,0, 0.5,0,1e-3, 0.5,0.5,0, 1,0,0};
#endif
			break;
		case 3:
			val = { 0, 0, 0,  0, 0, 0.3333,  0, 0, 0.6667,  0, 0, 1,  0, 0.3333, 0,
					0, 0.3333, 0.3333,  0, 0.3333, 0.6667,  0, 0.6667, 0,  0, 0.6667, 0.3333,  0, 1, 0,
					0.3333, 0, 0,  0.3333, 0, 0.3333,  0.3333, 0, 0.6667,  0.3333, 0.3333, 0,  0.3333, 0.3333, 0.3333,
					 0.3333, 0.6667, 0,  0.6667, 0, 0,  0.6667, 0, 0.3333,  0.6667, 0.3333, 0,  1, 0, 0 };
			break;
		default:
			break;
		}
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> disReal(0.0, 1.0); // 在 [0.0, 1.0] 范围内生成均匀分布的浮点数

		std::ofstream outFile(file_dir, std::ios::binary);
		std::setprecision(15);
		for (int i = 0; i < 3 * M; ++i)
		{
			outFile.write(reinterpret_cast<const char*>(&val[i]), sizeof(double));
		}
		for (int i = 0; i < 3 * M * batch_size; ++i)
		{
			scalar x = disReal(gen);
			outFile.write(reinterpret_cast<const char*>(&x), sizeof(double));
		}
		outFile.close();
	}

	template <typename mat_size>
	void read_batch_test_data(int order, int batch_size, std::vector<mat_size> &val, std::vector<mat_size> &dir,
		std::string file_dir = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\regular_batch_fixed_val_rand_dir.txt")
	{
		std::ifstream inFile(file_dir, std::ios::binary);
		double x;
		int M = (order + 1) * (order + 2) * (order + 3) / 6;
		if (inFile.is_open()) {
			for (int b = 0; b < batch_size; ++b)
			{
				for (int i = 0; i < M; ++i)
				{
					for (int j = 0; j < 3; ++j)
					{
						inFile.read(reinterpret_cast<char*>(&x), sizeof(double));
						val[b](j, i) = CABT::scalar(x);
					}
				}
			}
			for (int b = 0; b < batch_size; ++b)
			{
				for (int i = 0; i < M; ++i)
				{
					for (int j = 0; j < 3; ++j)
					{
						inFile.read(reinterpret_cast<char*>(&x), sizeof(double));
						dir[b](j, i) = CABT::scalar(x);
					}
				}
			}
			inFile.close();
		}
		else {
			std::cerr << "无法打开文件。\n";
			exit(0);
			return;
		}
	}


//	template <int order, typename ConstantData>
//	class detector
//	{
//	public:
//		detector() {}
//		virtual ~detector() {}
//	public:
//		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
//		int dif_order = 3 * order - 3;
//		int M = (order + 1) * (order + 2) * (order + 3) / 6;
//		int N = order * (3 * order - 1) * (3 * order - 2) / 2;
//		typedef Eigen::Matrix<scalar, 3, (order + 1)* (order + 2)* (order + 3) / 6> mat3m;
//		typedef Eigen::Matrix<scalar, 3, order* (3 * order - 1)* (3 * order - 2) / 2> mat3n;
//		typedef Eigen::Matrix<scalar, order* (3 * order - 1)* (3 * order - 2) / 2, 4> matn4;
//		
//		enum subdivision_mode
//		{
//			bisect,
//			quadtrisect,
//			octasect
//		};
//		subdivision_mode mode = octasect;
//
//		mat3m control_val;
//		mat3m control_dir;
//		ConstantData* constant_data = nullptr;
//
//
//		void calc_sampling_jacobi_det(scalar t, matn4& cof)
//		{
//			auto& omtensor2vec = constant_data->omtensor2vec;
//			auto& ontensor2vec = constant_data->ontensor2vec;
//			mat3n knot;
//			knot.setConstant(-1);
//			scalar inverse = scalar(1) / scalar(order + 1);
//			for (int i = 0; i < order + 2; ++i)
//			{
//				for (int j = 0; j < order + 2 - i; ++j)
//				{
//					for (int k = 0; k < order + 2 - i - j; ++k)
//					{
//						knot(0, ontensor2vec(i, j, k)) = scalar(i) * inverse;
//						knot(1, ontensor2vec(i, j, k)) = scalar(j) * inverse;
//						knot(2, ontensor2vec(i, j, k)) = scalar(k) * inverse;
//					}
//				}
//			}
//			mat3_3 jacobi;
//			switch (order)
//			{
//			case 2:
//			{
//				mat3m val;
//				int id4ijk;
//				scalar x;
//				for (int n = 0; n < 4; ++n)
//				{
//					val = control_val + scalar(n) / scalar(3) * t * control_dir;
//					for (int i = 0; i < order + 2; ++i)
//					{
//						for (int j = 0; j < order + 2 - i; ++j)
//						{
//							for (int k = 0; k < order + 2 - i - j; ++k)
//							{
//								id4ijk = ontensor2vec(i, j, k);
//								x = 1.0 - knot(0, id4ijk) - knot(1, id4ijk) - knot(2, id4ijk);
//								jacobi.col(0) = 2.0 *
//									((val.col(omtensor2vec(1, 0, 0)) - val.col(omtensor2vec(0, 0, 0))) * x
//										+ (val.col(omtensor2vec(2, 0, 0)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk)
//										+ (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk)
//										+ (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
//								jacobi.col(1) = 2.0 *
//									((val.col(omtensor2vec(0, 1, 0)) - val.col(omtensor2vec(0, 0, 0))) * x
//										+ (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk)
//										+ (val.col(omtensor2vec(0, 2, 0)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk)
//										+ (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
//								jacobi.col(2) = 2.0 *
//									((val.col(omtensor2vec(0, 0, 1)) - val.col(omtensor2vec(0, 0, 0))) * x
//										+ (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk)
//										+ (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk)
//										+ (val.col(omtensor2vec(0, 0, 2)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
//								cof(id4ijk, n) = jacobi(0, 0) * jacobi(1, 1) * jacobi(2, 2)
//									+ jacobi(0, 1) * jacobi(1, 2) * jacobi(2, 0)
//									+ jacobi(0, 2) * jacobi(1, 0) * jacobi(2, 1)
//									- jacobi(2, 0) * jacobi(1, 1) * jacobi(0, 2)
//									- jacobi(1, 0) * jacobi(0, 1) * jacobi(2, 2)
//									- jacobi(0, 0) * jacobi(2, 1) * jacobi(1, 2);
//							}
//						}
//					}
//				}
//			}
//			break;
//			case 3:
//			{
//				mat3m val;
//				int id4ijk;
//				scalar u, v, w, x;
//				for (int n = 0; n < 4; ++n)
//				{
//					val = control_val + scalar(n) / scalar(3) * t * control_dir;
//					for (int i = 0; i < order + 2; ++i)
//					{
//						for (int j = 0; j < order + 2 - i; ++j)
//						{
//							for (int k = 0; k < order + 2 - i - j; ++k)
//							{
//								id4ijk = ontensor2vec(i, j, k);
//								u = knot(0, id4ijk);
//								v = knot(1, id4ijk);
//								w = knot(2, id4ijk);
//								x = 1.0 - knot(0, id4ijk) - knot(1, id4ijk) - knot(2, id4ijk);
//								jacobi.col(0) = 3.0 *
//									((val.col(omtensor2vec(1, 0, 0)) - val.col(omtensor2vec(0, 0, 0))) * x * x
//										+ (val.col(omtensor2vec(2, 0, 0)) - val.col(omtensor2vec(1, 0, 0))) * u * x
//										+ (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(0, 1, 0))) * v * x
//										+ (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(0, 0, 1))) * w * x
//										+ (val.col(omtensor2vec(2, 1, 0)) - val.col(omtensor2vec(1, 1, 0))) * u * v
//										+ (val.col(omtensor2vec(2, 0, 1)) - val.col(omtensor2vec(1, 0, 1))) * u * w
//										+ (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(0, 1, 1))) * v * w
//										+ (val.col(omtensor2vec(3, 0, 0)) - val.col(omtensor2vec(2, 0, 0))) * u * u
//										+ (val.col(omtensor2vec(1, 2, 0)) - val.col(omtensor2vec(0, 2, 0))) * v * v
//										+ (val.col(omtensor2vec(1, 0, 2)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
//								jacobi.col(1) = 3.0 *
//									((val.col(omtensor2vec(0, 1, 0)) - val.col(omtensor2vec(0, 0, 0))) * x * x
//										+ (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(1, 0, 0))) * u * x
//										+ (val.col(omtensor2vec(0, 2, 0)) - val.col(omtensor2vec(0, 1, 0))) * v * x
//										+ (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 0, 1))) * w * x
//										+ (val.col(omtensor2vec(1, 2, 0)) - val.col(omtensor2vec(1, 1, 0))) * u * v
//										+ (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(1, 0, 1))) * u * w
//										+ (val.col(omtensor2vec(0, 2, 1)) - val.col(omtensor2vec(0, 1, 1))) * v * w
//										+ (val.col(omtensor2vec(2, 1, 0)) - val.col(omtensor2vec(2, 0, 0))) * u * u
//										+ (val.col(omtensor2vec(0, 3, 0)) - val.col(omtensor2vec(0, 2, 0))) * v * v
//										+ (val.col(omtensor2vec(0, 1, 2)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
//								jacobi.col(2) = 3.0 *
//									((val.col(omtensor2vec(0, 0, 1)) - val.col(omtensor2vec(0, 0, 0))) * x * x
//										+ (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(1, 0, 0))) * u * x
//										+ (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 1, 0))) * v * x
//										+ (val.col(omtensor2vec(0, 0, 2)) - val.col(omtensor2vec(0, 0, 1))) * w * x
//										+ (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(1, 1, 0))) * u * v
//										+ (val.col(omtensor2vec(1, 0, 2)) - val.col(omtensor2vec(1, 0, 1))) * u * w
//										+ (val.col(omtensor2vec(0, 1, 2)) - val.col(omtensor2vec(0, 1, 1))) * v * w
//										+ (val.col(omtensor2vec(2, 0, 1)) - val.col(omtensor2vec(2, 0, 0))) * u * u
//										+ (val.col(omtensor2vec(0, 2, 1)) - val.col(omtensor2vec(0, 2, 0))) * v * v
//										+ (val.col(omtensor2vec(0, 0, 3)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
//								cof(id4ijk, n) = jacobi(0, 0) * jacobi(1, 1) * jacobi(2, 2)
//									+ jacobi(0, 1) * jacobi(1, 2) * jacobi(2, 0)
//									+ jacobi(0, 2) * jacobi(1, 0) * jacobi(2, 1)
//									- jacobi(2, 0) * jacobi(1, 1) * jacobi(0, 2)
//									- jacobi(1, 0) * jacobi(0, 1) * jacobi(2, 2)
//									- jacobi(0, 0) * jacobi(2, 1) * jacobi(1, 2);
//							}
//						}
//					}
//				}
//			}
//			break;
//			default:
//				dprint("order can only be 2 or 3");
//				exit(0);
//				break;
//			}
//
//		}
//
//		scalar compute_jacobidet(scalar& time, int sample_num)
//		{
//			Eigen::Matrix<scalar,-1,-1> cof;
//			cof.resize(N, sample_num);
//
//
//			auto& omtensor2vec = constant_data->omtensor2vec;
//			auto& ontensor2vec = constant_data->ontensor2vec;
//			mat3n knot;
//			knot.setConstant(-1);
//			scalar inverse = scalar(1) / scalar(order + 1);
//			for (int i = 0; i < order + 2; ++i)
//			{
//				for (int j = 0; j < order + 2 - i; ++j)
//				{
//					for (int k = 0; k < order + 2 - i - j; ++k)
//					{
//						knot(0, ontensor2vec(i, j, k)) = scalar(i) * inverse;
//						knot(1, ontensor2vec(i, j, k)) = scalar(j) * inverse;
//						knot(2, ontensor2vec(i, j, k)) = scalar(k) * inverse;
//					}
//				}
//			}
//			mat3_3 jacobi;
//			switch (order)
//			{
//			case 2:
//			{
//				mat3m val;
//				int id4ijk;
//				scalar x;
//				for (int n = 0; n < sample_num; ++n)
//				{
//					val = control_val + scalar(n) / scalar(sample_num - 1) * time * control_dir;
//					for (int i = 0; i < order + 2; ++i)
//					{
//						for (int j = 0; j < order + 2 - i; ++j)
//						{
//							for (int k = 0; k < order + 2 - i - j; ++k)
//							{
//								id4ijk = ontensor2vec(i, j, k);
//								x = 1.0 - knot(0, id4ijk) - knot(1, id4ijk) - knot(2, id4ijk);
//								jacobi.col(0) = 2.0 *
//									((val.col(omtensor2vec(1, 0, 0)) - val.col(omtensor2vec(0, 0, 0))) * x
//										+ (val.col(omtensor2vec(2, 0, 0)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk)
//										+ (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk)
//										+ (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
//								jacobi.col(1) = 2.0 *
//									((val.col(omtensor2vec(0, 1, 0)) - val.col(omtensor2vec(0, 0, 0))) * x
//										+ (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk)
//										+ (val.col(omtensor2vec(0, 2, 0)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk)
//										+ (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
//								jacobi.col(2) = 2.0 *
//									((val.col(omtensor2vec(0, 0, 1)) - val.col(omtensor2vec(0, 0, 0))) * x
//										+ (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk)
//										+ (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk)
//										+ (val.col(omtensor2vec(0, 0, 2)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
//								cof(id4ijk, n) = jacobi(0, 0) * jacobi(1, 1) * jacobi(2, 2)
//									+ jacobi(0, 1) * jacobi(1, 2) * jacobi(2, 0)
//									+ jacobi(0, 2) * jacobi(1, 0) * jacobi(2, 1)
//									- jacobi(2, 0) * jacobi(1, 1) * jacobi(0, 2)
//									- jacobi(1, 0) * jacobi(0, 1) * jacobi(2, 2)
//									- jacobi(0, 0) * jacobi(2, 1) * jacobi(1, 2);
//							}
//						}
//					}
//				}
//			}
//			break;
//			case 3:
//			{
//				mat3m val;
//				int id4ijk;
//				scalar u, v, w, x;
//				for (int n = 0; n < sample_num; ++n)
//				{
//					val = control_val + scalar(n) / scalar(sample_num - 1) * time * control_dir;
//					for (int i = 0; i < order + 2; ++i)
//					{
//						for (int j = 0; j < order + 2 - i; ++j)
//						{
//							for (int k = 0; k < order + 2 - i - j; ++k)
//							{
//								id4ijk = ontensor2vec(i, j, k);
//								u = knot(0, id4ijk);
//								v = knot(1, id4ijk);
//								w = knot(2, id4ijk);
//								x = 1.0 - knot(0, id4ijk) - knot(1, id4ijk) - knot(2, id4ijk);
//								jacobi.col(0) = 3.0 *
//									((val.col(omtensor2vec(1, 0, 0)) - val.col(omtensor2vec(0, 0, 0))) * x * x
//										+ (val.col(omtensor2vec(2, 0, 0)) - val.col(omtensor2vec(1, 0, 0))) * u * x
//										+ (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(0, 1, 0))) * v * x
//										+ (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(0, 0, 1))) * w * x
//										+ (val.col(omtensor2vec(2, 1, 0)) - val.col(omtensor2vec(1, 1, 0))) * u * v
//										+ (val.col(omtensor2vec(2, 0, 1)) - val.col(omtensor2vec(1, 0, 1))) * u * w
//										+ (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(0, 1, 1))) * v * w
//										+ (val.col(omtensor2vec(3, 0, 0)) - val.col(omtensor2vec(2, 0, 0))) * u * u
//										+ (val.col(omtensor2vec(1, 2, 0)) - val.col(omtensor2vec(0, 2, 0))) * v * v
//										+ (val.col(omtensor2vec(1, 0, 2)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
//								jacobi.col(1) = 3.0 *
//									((val.col(omtensor2vec(0, 1, 0)) - val.col(omtensor2vec(0, 0, 0))) * x * x
//										+ (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(1, 0, 0))) * u * x
//										+ (val.col(omtensor2vec(0, 2, 0)) - val.col(omtensor2vec(0, 1, 0))) * v * x
//										+ (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 0, 1))) * w * x
//										+ (val.col(omtensor2vec(1, 2, 0)) - val.col(omtensor2vec(1, 1, 0))) * u * v
//										+ (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(1, 0, 1))) * u * w
//										+ (val.col(omtensor2vec(0, 2, 1)) - val.col(omtensor2vec(0, 1, 1))) * v * w
//										+ (val.col(omtensor2vec(2, 1, 0)) - val.col(omtensor2vec(2, 0, 0))) * u * u
//										+ (val.col(omtensor2vec(0, 3, 0)) - val.col(omtensor2vec(0, 2, 0))) * v * v
//										+ (val.col(omtensor2vec(0, 1, 2)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
//								jacobi.col(2) = 3.0 *
//									((val.col(omtensor2vec(0, 0, 1)) - val.col(omtensor2vec(0, 0, 0))) * x * x
//										+ (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(1, 0, 0))) * u * x
//										+ (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 1, 0))) * v * x
//										+ (val.col(omtensor2vec(0, 0, 2)) - val.col(omtensor2vec(0, 0, 1))) * w * x
//										+ (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(1, 1, 0))) * u * v
//										+ (val.col(omtensor2vec(1, 0, 2)) - val.col(omtensor2vec(1, 0, 1))) * u * w
//										+ (val.col(omtensor2vec(0, 1, 2)) - val.col(omtensor2vec(0, 1, 1))) * v * w
//										+ (val.col(omtensor2vec(2, 0, 1)) - val.col(omtensor2vec(2, 0, 0))) * u * u
//										+ (val.col(omtensor2vec(0, 2, 1)) - val.col(omtensor2vec(0, 2, 0))) * v * v
//										+ (val.col(omtensor2vec(0, 0, 3)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
//								cof(id4ijk, n) = jacobi(0, 0) * jacobi(1, 1) * jacobi(2, 2)
//									+ jacobi(0, 1) * jacobi(1, 2) * jacobi(2, 0)
//									+ jacobi(0, 2) * jacobi(1, 0) * jacobi(2, 1)
//									- jacobi(2, 0) * jacobi(1, 1) * jacobi(0, 2)
//									- jacobi(1, 0) * jacobi(0, 1) * jacobi(2, 2)
//									- jacobi(0, 0) * jacobi(2, 1) * jacobi(1, 2);
//							}
//						}
//					}
//				}
//			}
//			break;
//			default:
//				dprint("order can only be 2 or 3");
//				exit(0);
//				break;
//			}
//
//
//			scalar t0 = cof.minCoeff();
//			dprint("min det:", t0);
//#if 1
//			if (t0.inf() < 0)
//			{
//				write_bug();
//				system("pause");
//			}
//#endif
//			return t0;
//		}
//
//		void write_bug()
//		{
//			std::ofstream outFile("C:\\Git Code\\HighOrderDeformation\\src\\info.txt", std::ios::binary);
//			std::setprecision(15);
//			for (int i = 0; i < 3; ++i)
//			{
//				for (int j = 0; j < M; ++j)
//				{
//					scalar x = control_val(i, j);
//					double xinf = x.inf();
//					double xsup = x.sup();
//					outFile.write(reinterpret_cast<const char*>(&xinf), sizeof(double));
//					outFile.write(reinterpret_cast<const char*>(&xsup), sizeof(double));
//					//dprint(i, j, xinf, xsup);
//				}
//			}
//			for (int i = 0; i < 3; ++i)
//			{
//				for (int j = 0; j < M; ++j)
//				{
//					scalar x = control_dir(i, j);
//					double xinf = x.inf();
//					double xsup = x.sup();
//					outFile.write(reinterpret_cast<const char*>(&xinf), sizeof(double));
//					outFile.write(reinterpret_cast<const char*>(&xsup), sizeof(double));
//					//dprint(i, j, xinf, xsup);
//				}
//			}
//			outFile.close();
//		}
//
//		/*scalar calc_real_root()
//		{
//
//		}*/
//	};

    template <int order, typename ConstantData, typename SubTree>
    class tet_detector// : public detector<order, ConstantData>
    {
    public:
        tet_detector() {}
        ~tet_detector() {}
    public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW

#pragma region detector
		int dif_order = 3 * order - 3;
		int M = (order + 1) * (order + 2) * (order + 3) / 6;
		int N = order * (3 * order - 1) * (3 * order - 2) / 2;
		typedef Eigen::Matrix<scalar, 3, (order + 1)* (order + 2)* (order + 3) / 6> mat3m;
		typedef Eigen::Matrix<scalar, 3, order* (3 * order - 1)* (3 * order - 2) / 2> mat3n;
		typedef Eigen::Matrix<scalar, order* (3 * order - 1)* (3 * order - 2) / 2, 4> matn4;

		enum subdivision_mode
		{
			bisect,
			quadtrisect,
			octasect
		};
		subdivision_mode mode = octasect;

		mat3m control_val;
		mat3m control_dir;
		ConstantData *constant_data = nullptr;

		void calc_sampling_jacobi_det(scalar t, matn4& cof)
		{
			auto& omtensor2vec = constant_data->omtensor2vec;
			auto& ontensor2vec = constant_data->ontensor2vec;
			mat3n knot;
			knot.setConstant(-1);
			scalar inverse = scalar(1) / scalar(dif_order);
			for (int i = 0; i <= dif_order; ++i)
			{
				for (int j = 0; j <= dif_order - i; ++j)
				{
					for (int k = 0; k <= dif_order - i - j; ++k)
					{
						knot(0, ontensor2vec(i, j, k)) = scalar(i) * inverse;
						knot(1, ontensor2vec(i, j, k)) = scalar(j) * inverse;
						knot(2, ontensor2vec(i, j, k)) = scalar(k) * inverse;
					}
				}
			}
			mat3_3 jacobi;
			switch (order)
			{
			case 2:
			{
				mat3m val;
				int id4ijk;
				scalar x;
				for (int n = 0; n < 4; ++n)
				{
					val = control_val + scalar(n) / scalar(3) * t * control_dir;
					for (int i = 0; i <= 3; ++i)
					{
						for (int j = 0; j <= 3 - i; ++j)
						{
							for (int k = 0; k <= 3 - i - j; ++k)
							{
								id4ijk = ontensor2vec(i, j, k);
								x = 1.0 - knot(0, id4ijk) - knot(1, id4ijk) - knot(2, id4ijk);
								jacobi.col(0) = 2.0 * ((val.col(omtensor2vec(1, 0, 0)) - val.col(omtensor2vec(0, 0, 0))) * x + (val.col(omtensor2vec(2, 0, 0)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk) + (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk) + (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
								jacobi.col(1) = 2.0 * ((val.col(omtensor2vec(0, 1, 0)) - val.col(omtensor2vec(0, 0, 0))) * x + (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk) + (val.col(omtensor2vec(0, 2, 0)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk) + (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
								jacobi.col(2) = 2.0 * ((val.col(omtensor2vec(0, 0, 1)) - val.col(omtensor2vec(0, 0, 0))) * x + (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk) + (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk) + (val.col(omtensor2vec(0, 0, 2)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
								cof(id4ijk, n) = jacobi(0, 0) * jacobi(1, 1) * jacobi(2, 2)
									+ jacobi(0, 1) * jacobi(1, 2) * jacobi(2, 0)
									+ jacobi(0, 2) * jacobi(1, 0) * jacobi(2, 1)
									- jacobi(2, 0) * jacobi(1, 1) * jacobi(0, 2)
									- jacobi(1, 0) * jacobi(0, 1) * jacobi(2, 2)
									- jacobi(0, 0) * jacobi(2, 1) * jacobi(1, 2);
							}
						}
					}
				}
			}
			break;
			case 3:
			{
				mat3m val;
				int id4ijk;
				scalar u, v, w, x;
				int ii, jj, kk, ll;
				int n_1 = 5;
				int fractorize[6] = { 1,1,2,6,24,120 };
				auto scalar_power = [&](scalar& s, int power)
					{
						switch (power)
						{
						case 0:
							return scalar(1);
						case 1:
							return s;
						case 2:
							return s * s;
						case 3:
							return s * s * s;
						case 4:
							return s * s * s * s;
						case 5:
							return s * s * s * s * s;
						default:
							dprint("error in power");
							exit(0);
						}
					};
				auto BernEval = [&]()
					{
						return fractorize[n_1] / (fractorize[ii] * fractorize[jj] * fractorize[kk] * fractorize[ll]) *
							scalar_power(u, ii) * scalar_power(v, jj) * scalar_power(w, kk) * scalar_power(x, ll);
					};
				auto JacobiEval = [&]()
					{
						jacobi.setZero();
						for (ii = 0; ii <= 5; ++ii)
						{
							for (jj = 0; jj <= 5 - ii; ++jj)
							{
								for (kk = 0; kk <= 5 - ii - jj; ++kk)
								{
									ll = 5 - ii - jj - kk;
									jacobi.col(0) += (val.col(omtensor2vec(ii + 1, jj, kk)) - val.col(omtensor2vec(ii, jj, kk))) * BernEval();
									jacobi.col(1) += (val.col(omtensor2vec(ii, jj + 1, kk)) - val.col(omtensor2vec(ii, jj, kk))) * BernEval();
									jacobi.col(2) += (val.col(omtensor2vec(ii, jj, kk + 1)) - val.col(omtensor2vec(ii, jj, kk))) * BernEval();
								}
							}
						}
						jacobi *= scalar(6.0);
					};
				for (int n = 0; n < 4; ++n)
				{
					val = control_val + scalar(n) / scalar(3) * t * control_dir;
					for (int i = 0; i <= 6; ++i)
					{
						for (int j = 0; j <= 6 - i; ++j)
						{
							for (int k = 0; k <= 6 - i - j; ++k)
							{
								id4ijk = ontensor2vec(i, j, k);
								u = knot(0, id4ijk);
								v = knot(1, id4ijk);
								w = knot(2, id4ijk);
								x = 1.0 - knot(0, id4ijk) - knot(1, id4ijk) - knot(2, id4ijk);

								JacobiEval();
								//jacobi.col(0) = 3.0 * ((val.col(omtensor2vec(1, 0, 0)) - val.col(omtensor2vec(0, 0, 0))) * x * x + (val.col(omtensor2vec(2, 0, 0)) - val.col(omtensor2vec(1, 0, 0))) * u * x + (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(0, 1, 0))) * v * x + (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(0, 0, 1))) * w * x + (val.col(omtensor2vec(2, 1, 0)) - val.col(omtensor2vec(1, 1, 0))) * u * v + (val.col(omtensor2vec(2, 0, 1)) - val.col(omtensor2vec(1, 0, 1))) * u * w + (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(0, 1, 1))) * v * w + (val.col(omtensor2vec(3, 0, 0)) - val.col(omtensor2vec(2, 0, 0))) * u * u + (val.col(omtensor2vec(1, 2, 0)) - val.col(omtensor2vec(0, 2, 0))) * v * v + (val.col(omtensor2vec(1, 0, 2)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
								//jacobi.col(1) = 3.0 * ((val.col(omtensor2vec(0, 1, 0)) - val.col(omtensor2vec(0, 0, 0))) * x * x + (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(1, 0, 0))) * u * x + (val.col(omtensor2vec(0, 2, 0)) - val.col(omtensor2vec(0, 1, 0))) * v * x + (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 0, 1))) * w * x + (val.col(omtensor2vec(1, 2, 0)) - val.col(omtensor2vec(1, 1, 0))) * u * v + (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(1, 0, 1))) * u * w + (val.col(omtensor2vec(0, 2, 1)) - val.col(omtensor2vec(0, 1, 1))) * v * w + (val.col(omtensor2vec(2, 1, 0)) - val.col(omtensor2vec(2, 0, 0))) * u * u + (val.col(omtensor2vec(0, 3, 0)) - val.col(omtensor2vec(0, 2, 0))) * v * v + (val.col(omtensor2vec(0, 1, 2)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
								//jacobi.col(2) = 3.0 * ((val.col(omtensor2vec(0, 0, 1)) - val.col(omtensor2vec(0, 0, 0))) * x * x + (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(1, 0, 0))) * u * x + (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 1, 0))) * v * x + (val.col(omtensor2vec(0, 0, 2)) - val.col(omtensor2vec(0, 0, 1))) * w * x + (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(1, 1, 0))) * u * v + (val.col(omtensor2vec(1, 0, 2)) - val.col(omtensor2vec(1, 0, 1))) * u * w + (val.col(omtensor2vec(0, 1, 2)) - val.col(omtensor2vec(0, 1, 1))) * v * w + (val.col(omtensor2vec(2, 0, 1)) - val.col(omtensor2vec(2, 0, 0))) * u * u + (val.col(omtensor2vec(0, 2, 1)) - val.col(omtensor2vec(0, 2, 0))) * v * v + (val.col(omtensor2vec(0, 0, 3)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
								cof(id4ijk, n) = jacobi(0, 0) * jacobi(1, 1) * jacobi(2, 2)
									+ jacobi(0, 1) * jacobi(1, 2) * jacobi(2, 0)
									+ jacobi(0, 2) * jacobi(1, 0) * jacobi(2, 1)
									- jacobi(2, 0) * jacobi(1, 1) * jacobi(0, 2)
									- jacobi(1, 0) * jacobi(0, 1) * jacobi(2, 2)
									- jacobi(0, 0) * jacobi(2, 1) * jacobi(1, 2);
							}
						}
					}
				}
			}
			break;
			default:
				dprint("order can only be 2 or 3");
				exit(0);
				break;
			}
		}

		scalar compute_jacobidet(scalar &time, int sample_num)
		{
			Eigen::Matrix<scalar, -1, -1> cof;
			cof.resize(N, sample_num);

			auto &omtensor2vec = constant_data->omtensor2vec;
			auto &ontensor2vec = constant_data->ontensor2vec;
			mat3n knot;
			knot.setConstant(-1);
			scalar inverse = scalar(1) / scalar(order + 1);
			for (int i = 0; i < order + 2; ++i)
			{
				for (int j = 0; j < order + 2 - i; ++j)
				{
					for (int k = 0; k < order + 2 - i - j; ++k)
					{
						knot(0, ontensor2vec(i, j, k)) = scalar(i) * inverse;
						knot(1, ontensor2vec(i, j, k)) = scalar(j) * inverse;
						knot(2, ontensor2vec(i, j, k)) = scalar(k) * inverse;
					}
				}
			}
			mat3_3 jacobi;
			switch (order)
			{
			case 2:
			{
				mat3m val;
				int id4ijk;
				scalar x;
				for (int n = 0; n < sample_num; ++n)
				{
					val = control_val + scalar(n) / scalar(sample_num - 1) * time * control_dir;
					for (int i = 0; i < order + 2; ++i)
					{
						for (int j = 0; j < order + 2 - i; ++j)
						{
							for (int k = 0; k < order + 2 - i - j; ++k)
							{
								id4ijk = ontensor2vec(i, j, k);
								x = 1.0 - knot(0, id4ijk) - knot(1, id4ijk) - knot(2, id4ijk);
								jacobi.col(0) = 2.0 * ((val.col(omtensor2vec(1, 0, 0)) - val.col(omtensor2vec(0, 0, 0))) * x + (val.col(omtensor2vec(2, 0, 0)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk) + (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk) + (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
								jacobi.col(1) = 2.0 * ((val.col(omtensor2vec(0, 1, 0)) - val.col(omtensor2vec(0, 0, 0))) * x + (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk) + (val.col(omtensor2vec(0, 2, 0)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk) + (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
								jacobi.col(2) = 2.0 * ((val.col(omtensor2vec(0, 0, 1)) - val.col(omtensor2vec(0, 0, 0))) * x + (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk) + (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk) + (val.col(omtensor2vec(0, 0, 2)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
								cof(id4ijk, n) = jacobi(0, 0) * jacobi(1, 1) * jacobi(2, 2)
												 + jacobi(0, 1) * jacobi(1, 2) * jacobi(2, 0)
												 + jacobi(0, 2) * jacobi(1, 0) * jacobi(2, 1)
												 - jacobi(2, 0) * jacobi(1, 1) * jacobi(0, 2)
												 - jacobi(1, 0) * jacobi(0, 1) * jacobi(2, 2)
												 - jacobi(0, 0) * jacobi(2, 1) * jacobi(1, 2);
							}
						}
					}
				}
			}
			break;
			case 3:
			{
				mat3m val;
				int id4ijk;
				scalar u, v, w, x;
				for (int n = 0; n < sample_num; ++n)
				{
					val = control_val + scalar(n) / scalar(sample_num - 1) * time * control_dir;
					for (int i = 0; i < order + 2; ++i)
					{
						for (int j = 0; j < order + 2 - i; ++j)
						{
							for (int k = 0; k < order + 2 - i - j; ++k)
							{
								id4ijk = ontensor2vec(i, j, k);
								u = knot(0, id4ijk);
								v = knot(1, id4ijk);
								w = knot(2, id4ijk);
								x = 1.0 - knot(0, id4ijk) - knot(1, id4ijk) - knot(2, id4ijk);
								jacobi.col(0) = 3.0 * ((val.col(omtensor2vec(1, 0, 0)) - val.col(omtensor2vec(0, 0, 0))) * x * x + (val.col(omtensor2vec(2, 0, 0)) - val.col(omtensor2vec(1, 0, 0))) * u * x + (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(0, 1, 0))) * v * x + (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(0, 0, 1))) * w * x + (val.col(omtensor2vec(2, 1, 0)) - val.col(omtensor2vec(1, 1, 0))) * u * v + (val.col(omtensor2vec(2, 0, 1)) - val.col(omtensor2vec(1, 0, 1))) * u * w + (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(0, 1, 1))) * v * w + (val.col(omtensor2vec(3, 0, 0)) - val.col(omtensor2vec(2, 0, 0))) * u * u + (val.col(omtensor2vec(1, 2, 0)) - val.col(omtensor2vec(0, 2, 0))) * v * v + (val.col(omtensor2vec(1, 0, 2)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
								jacobi.col(1) = 3.0 * ((val.col(omtensor2vec(0, 1, 0)) - val.col(omtensor2vec(0, 0, 0))) * x * x + (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(1, 0, 0))) * u * x + (val.col(omtensor2vec(0, 2, 0)) - val.col(omtensor2vec(0, 1, 0))) * v * x + (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 0, 1))) * w * x + (val.col(omtensor2vec(1, 2, 0)) - val.col(omtensor2vec(1, 1, 0))) * u * v + (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(1, 0, 1))) * u * w + (val.col(omtensor2vec(0, 2, 1)) - val.col(omtensor2vec(0, 1, 1))) * v * w + (val.col(omtensor2vec(2, 1, 0)) - val.col(omtensor2vec(2, 0, 0))) * u * u + (val.col(omtensor2vec(0, 3, 0)) - val.col(omtensor2vec(0, 2, 0))) * v * v + (val.col(omtensor2vec(0, 1, 2)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
								jacobi.col(2) = 3.0 * ((val.col(omtensor2vec(0, 0, 1)) - val.col(omtensor2vec(0, 0, 0))) * x * x + (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(1, 0, 0))) * u * x + (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 1, 0))) * v * x + (val.col(omtensor2vec(0, 0, 2)) - val.col(omtensor2vec(0, 0, 1))) * w * x + (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(1, 1, 0))) * u * v + (val.col(omtensor2vec(1, 0, 2)) - val.col(omtensor2vec(1, 0, 1))) * u * w + (val.col(omtensor2vec(0, 1, 2)) - val.col(omtensor2vec(0, 1, 1))) * v * w + (val.col(omtensor2vec(2, 0, 1)) - val.col(omtensor2vec(2, 0, 0))) * u * u + (val.col(omtensor2vec(0, 2, 1)) - val.col(omtensor2vec(0, 2, 0))) * v * v + (val.col(omtensor2vec(0, 0, 3)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
								cof(id4ijk, n) = jacobi(0, 0) * jacobi(1, 1) * jacobi(2, 2)
												 + jacobi(0, 1) * jacobi(1, 2) * jacobi(2, 0)
												 + jacobi(0, 2) * jacobi(1, 0) * jacobi(2, 1)
												 - jacobi(2, 0) * jacobi(1, 1) * jacobi(0, 2)
												 - jacobi(1, 0) * jacobi(0, 1) * jacobi(2, 2)
												 - jacobi(0, 0) * jacobi(2, 1) * jacobi(1, 2);
							}
						}
					}
				}
			}
			break;
			default:
				dprint("order can only be 2 or 3");
				exit(0);
				break;
			}

			scalar t0 = cof.minCoeff();
			dprint("min det:", t0);
#if 1
			if (t0.inf() < 0)
			{
				write_bug();
				system("pause");
			}
#endif
			return t0;
		}

		void write_bug()
		{
			std::ofstream outFile("C:\\Git Code\\HighOrderDeformation\\src\\info.txt", std::ios::binary);
			std::setprecision(15);
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < M; ++j)
				{
					scalar x = control_val(i, j);
					double xinf = x.inf();
					double xsup = x.sup();
					outFile.write(reinterpret_cast<const char *>(&xinf), sizeof(double));
					outFile.write(reinterpret_cast<const char *>(&xsup), sizeof(double));
					// dprint(i, j, xinf, xsup);
				}
			}
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < M; ++j)
				{
					scalar x = control_dir(i, j);
					double xinf = x.inf();
					double xsup = x.sup();
					outFile.write(reinterpret_cast<const char *>(&xinf), sizeof(double));
					outFile.write(reinterpret_cast<const char *>(&xsup), sizeof(double));
					// dprint(i, j, xinf, xsup);
				}
			}
			outFile.close();
		}
#pragma endregion
        enum message
        {
            NoCollision,      // there is no collision in (0, time)
            Collision,        // there is an explicit and exact collision in (0, time)
            NumericalFailure, // there is a collision but the time is not exact because of numerical problems
            InitCollision     // the initial closure has collision
        };


        scalar elp = scalar(1e-7, 1e-7);
        int subdivision_times = 3;
		SubTree *sub_tree = nullptr;

		void init(mat3m& val, mat3m& dir, ConstantData* constant_data_, SubTree* sub_tree_, scalar time = scalar(1))
		{
			control_val = std::move(val); control_dir = std::move(dir); constant_data = constant_data_; sub_tree = sub_tree_;
			calc_sampling_jacobi_det(time, sub_tree->tree_cof[0][0]);
		}

        void newton_raphson(const vec4s& cubic_cof, scalar time, scalar dif, scalar& toi, scalar elp)
        {
            auto eval = [&](scalar& x) {return cubic_cof(0) + x * (cubic_cof(1) + x * (cubic_cof(2) + x * cubic_cof(3))); };
			//static int dd = 0;
            while (true)
            {
				/*++dd;
				if (dd % 10000 == 0)
				{
					dprint(dd, dif);
				}*/
                scalar ftoi = eval(toi);
                if (toi.inf() > time.inf())
                {
                    toi = time.inf();
                    break;
                }
                if (ftoi.inf() < elp)
                {
                    break;
                }
                toi = (toi - eval(toi) / dif).inf();
            }
			int p = 0;
        }

        void search_cubic_root(const vec4s& cubic_cof, scalar& time, message& mes, bool if_calc_root)
        {

			/*static int rrr[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
			for (int i = 0; i < 14; ++i)
			{
				dprint(i, rrr[i]);
			}*/

			vec4s abcd;
			for (int i = 0; i < 4; ++i) { abcd(i) = cubic_cof(i).inf(); }
			scalar& a = abcd(3); scalar& b = abcd(2); scalar& c = abcd(1); scalar& d = abcd(0);

			//STEP 1
			//test if there is negative cofficient when t==0
			if (d.inf() <= 0)
			{
				//*******************
				//contidion 0
				mes = InitCollision;
				time = scalar(0);
				dprint("InitCollision");
				system("pause");
				return;
			}

			//STEP 2
			//filter because most of those tets are positive all the time
			//Reference: Penetration-free Projective Dynamics on the GPU
			//auto eval = [&](scalar& x) { return a * x * x * x + b * x * x + c * x + d; };
			//auto difeval = [&](scalar& x) { return scalar(3) * a * x * x + 2 * b * x + c; };
			auto eval = [&](scalar& x) { return d + x * (c + x * (b + x * a)); };
			auto difeval = [&](scalar& x) {return c + x * (2 * b + x * scalar(3) * a); };
			scalar toi = time;

			if (a.inf() > 0)
			{
				scalar delta = b * b - scalar(3) * a * c;
				if (delta.sup() <= 0)
				{
					//*******************
					//contidion 1
					mes = NoCollision;
				}
				else
				{
					if (delta.inf() < 0)
					{
						delta = scalar(0, delta.sup());
					}
					delta = CGAL::sqrt(delta);
					scalar x0 = (-b - delta) / (scalar(3) * a);
					scalar x1 = (-b + delta) / (scalar(3) * a);
					scalar fx1 = eval(x1);
					if (fx1.inf() > 0)
					{
						//*******************
						//contidion 2
						mes = NoCollision;
					}
					else
					{
						if (x1.sup() < 0)
						{
							//*******************
							//contidion 3
							mes = NoCollision;
						}
						else if (time.sup() < x1.inf())
						{
							if (eval(time).inf() > 0)
							{
								//*******************
								//contidion 4
								mes = NoCollision;
							}
							else
							{
								if (if_calc_root)
								{
									//newton_raphson
									toi = x0.inf() > 0 ? x0.inf() : 0;
									if (a * b >= 0)
									{
										//*******************
										//contidion 5
										scalar difval = scalar(0);
										newton_raphson(abcd, time, difeval(difval), toi, elp);
										time = toi;
									}
									else
									{
										scalar difval = -b / (scalar(3) * a);
										if (difval.inf() < time.inf())
										{
											//*******************
											//contidion 6
											newton_raphson(abcd, time, difeval(difval), toi, elp);
											time = toi;
										}
										else
										{
											//*******************
											//contidion 7
											newton_raphson(abcd, time, difeval(time), toi, elp);
											time = toi;
										}
									}
								}
								mes = Collision;
							}
						}
						else
						{
							if (if_calc_root)
							{
								toi = x0.inf() > 0 ? x0.inf() : 0;
								if (a * b >= 0)
								{
									//*******************
									//contidion 8
									scalar difval = scalar(0);
									newton_raphson(abcd, time, difeval(difval), toi, elp);
									time = toi;
								}
								else
								{
									//*******************
									//contidion 9
									scalar difval = -b / (scalar(3) * a);
									newton_raphson(abcd, time, difeval(difval), toi, elp);
									time = toi;
								}
							}
							mes = Collision;
						}
					}
				}
			}
			else if (a.inf() == 0)
			{
				dprint("there is a.inf() == 0 !!!!!!!!!");
				dprintwithprecision(15, a, b, c, d);
				if (b.inf() == 0)
				{
					if (c.inf() >= 0)
					{
						//*******************
						//contidion 10
						mes = NoCollision;
					}
					else
					{
						toi = -d / c.inf();
						if (time.sup() < toi.inf())
						{
							//*******************
							//contidion 11
							mes = NoCollision;
						}
						else
						{
							//*******************
							//contidion 12
							time = toi.inf();
							mes = Collision;
						}
						//if (toi.inf() < time.inf())
						//{
						//	//*******************
						//	//contidion 11
						//	time = toi.inf();
						//	mes = Collision;
						//}
						//else
						//{
						//	//*******************
						//	//contidion 12
						//	mes = NoCollision;
						//}
					}
				}
				else if (b.inf() > 0)
				{
					scalar delta = c * c - 4 * b * d;
					if (delta.sup() < 0)
					{
						//*******************
						//contidion 13
						mes = NoCollision;
					}
					else
					{
						if (delta.inf() < 0)
						{
							delta = scalar(0, delta.sup());
						}
						delta = CGAL::sqrt(delta);
						scalar x0 = (-c - delta) / (2 * b);
						// we know that delta<|c|
						// so Sign(-c)=Sign(-c-delta)=Sign(x0)
						// to prevent error from calculating delta that leads to Sign(-c)=-Sign(x0), we postprocessing that
						if (c.inf() > 0)
						{
							x0 = scalar(x0.inf(), 0);
						}
						else
						{
							x0 = scalar(0, x0.sup());
						}
						if (x0.sup() < 0)
						{
							//*******************
							//contidion 14
							mes = NoCollision;
						}
						else if (x0.inf() > time.sup())
						{
							//*******************
							//contidion 15
							mes = NoCollision;
						}
						else
						{
							//*******************
							//contidion 16
							time = x0.inf();
							mes = Collision;
						}
						//if (x0.sup() < time.inf() && x0.inf() > 0)
						//{
						//	//*******************
						//	//contidion 14
						//	time = x0.inf();
						//	mes = Collision;
						//}
						//else
						//{
						//	//*******************
						//	//contidion 15
						//	mes = NoCollision;
						//}
					}
				}
				else
				{
					scalar delta = c * c - 4 * b * d;
					delta = CGAL::sqrt(delta);
					scalar x1 = (-c - delta) / (2 * b);
					// we know delta>=x1 in theoretical, which leads to x1>=0
					// we knot f(0)>0, so x1>0
					if (x1.inf() > time.sup())
					{
						//*******************
						//contidion 17
						mes = NoCollision;
					}
					else
					{
						//*******************
						//contidion 18
						time = x1.inf();
						mes = Collision;
					}
					//if (x1.inf() < time.inf())
					//{
					//	//*******************
					//	//contidion 16
					//	time = x1.inf();
					//	mes = Collision;
					//}
					//else
					//{
					//	//*******************
					//	//contidion 17
					//	mes = NoCollision;
					//}
				}
			}
			else // a.inf() < 0
			{
				scalar delta = b * b - scalar(3) * a * c;
				if (delta.sup() < 0)
				{
					if (eval(time).inf() > 0)
					{
						//*******************
						//contidion 19
						mes = NoCollision;
					}
					else
					{
						//*******************
						//contidion 20
						if (if_calc_root)
						{
							toi = scalar(0);
							//difeval(0)=c
							newton_raphson(abcd, time, std::min(c.inf(), difeval(time).inf()),
								toi, elp);
							time = toi;
						}
						mes = Collision;
						//++rrr[6];
					}
				}
				else
				{
					if (delta.inf() < 0)
					{
						delta = scalar(0, delta.sup());
					}
					delta = CGAL::sqrt(delta);
					scalar x0 = (-b + delta) / (scalar(3) * a);
					scalar x1 = (-b - delta) / (scalar(3) * a);
					scalar fx0 = eval(x0);
					if (fx0.inf() > 0)
					{
						//if (time.inf() < x1.inf())
						if (x1.inf() > time.sup())
						{
							//*******************
							//contidion 21
							mes = NoCollision;
							//++rrr[7];
						}
						else if (eval(time).inf() > 0)
						{
							//*******************
							//contidion 22
							mes = NoCollision;
							//++rrr[8];
						}
						else
						{
							//*******************
							//contidion 23
							if (if_calc_root)
							{
								//newton raphson
								toi = x1.inf() > 0 ? x1.inf() : 0;
								newton_raphson(abcd, time, difeval(time).inf(), toi, elp);
								time = toi;
							}
							mes = Collision;
							//++rrr[9];
						}
					}
					else
					{
						if (x0.inf() > time.sup())
						{
							if (eval(time).inf() > 0)
							{
								//*******************
								//contidion 24
								mes = NoCollision;
							}
							else
							{
								//*******************
								//contidion 25
								if (if_calc_root)
								{
									toi = scalar(0);
									newton_raphson(abcd, time, c.inf(), toi, elp);
									time = toi;
								}
								mes = Collision;
							}
						}
						else if (x0.sup() < 0)
						{
							if (eval(time).inf() > 0)
							{
								//*******************
								//contidion 26
								mes = NoCollision;
							}
							else
							{
								//*******************
								//contidion 27
								if (if_calc_root)
								{
									toi = scalar(0);
									newton_raphson(abcd, time, difeval(time).inf(), toi, elp);
									time = toi;
								}
								mes = Collision;
							}
						}
						else
						{
							//*******************
							//contidion 28
							if (if_calc_root)
							{
								toi = scalar(0);
								newton_raphson(abcd, time, c.inf(), toi, elp);
								time = toi;
							}
							mes = Collision;
						}

						////newton raphson
						//if (x0.inf() > 0)
						//{
						//	//if (time.sup() < x0.inf() && eval(time).inf() > 0)
						//	//{
						//	//	//*******************
						//	//	//contidion 23
						//	//	mes = NoCollision;
						//	//	//++rrr[10];
						//	//}
						//	//else
						//	//{
						//	//	//*******************
						//	//	//contidion 24
						//	//	if (if_calc_root)
						//	//	{
						//	//		toi = scalar(0);
						//	//		newton_raphson(abcd, time, c.inf(), toi, elp);
						//	//		time = toi;
						//	//	}
						//	//	mes = Collision;
						//	//	//++rrr[11];
						//	//}
						//}
						//else if (eval(time) > 0)
						//{
						//	//*******************
						//	//contidion 25
						//	mes = NoCollision;
						//	//++rrr[12];
						//}
						//else
						//{
						//	//*******************
						//	//contidion 26
						//	if (if_calc_root)
						//	{
						//		toi = scalar(0);
						//		newton_raphson(abcd, time, difeval(time).inf(), toi, elp);
						//		time = toi;
						//	}
						//	mes = Collision;
						//	//++rrr[13];
						//}
					}
				}
			}
        }

		void tet_status(matn4& cof, scalar& time, message& mes, bool if_calc_root)
		{
			//scalar::Protector P;
			message mes_ = NoCollision;
			mes = NoCollision;
			const auto& corner_id = constant_data->corner_id;
			const auto& interior_id = constant_data->interior_id;
#if 1
			for (int i = 0; i < 4; ++i)
			{
				search_cubic_root(cof.row(corner_id[i]), time, mes_, if_calc_root);
			}
			for (int i = 0; i < N - 4; ++i)
			{
				search_cubic_root(cof.row(interior_id[i]), time, mes_, if_calc_root);
				if (mes_ == NumericalFailure)
				{
					dprint("***************************");
					dprint("there is something wrong");
					dprint("***************************");
					system("pause");
					return;
				}
				else if (mes_ == Collision)
				{
					mes = mes_;
					if (!if_calc_root)
					{
						break;
					}
				}
				else if (mes_ == InitCollision)
				{
					mes = InitCollision;
					break;
				}
			}
#else
			for (int i = 0; i < N; ++i)
			{
				search_cubic_root(cof.row(i), time, mes_, if_calc_root);

				if (mes_ == NumericalFailure)
				{
					dprint("***************************");
					dprint("there is something wrong");
					dprint("***************************");
					system("pause");
					return;
				}
				else if (mes_ == Collision)
				{
					mes = mes_;
					if (!if_calc_root)
					{
						break;
					}
				}
				else if (mes_ == InitCollision)
				{
					mes = InitCollision;
					break;
				}
			}
#endif
		}

		void get_min_time_recursion(int level, int count, scalar &time)
		{
			if (level >= subdivision_times) return;
			//static int num[4] = { 0,0,0,0 };
			level += 1;
			count *= 8;
			bool if_calc_root = level == subdivision_times;
			for (int i = 0; i < 8; ++i)
			{
				sub_tree->tree_cof[level][count] = constant_data->son_transform[i] * sub_tree->tree_cof[level - 1][count / 8];
				//num[level]++;
				message mes = InitCollision;
				tet_status(sub_tree->tree_cof[level][count], time, mes, true);
				if (mes == InitCollision) { dprint("InitCollision"); exit(0); }
				else if (mes == Collision) { get_min_time_recursion(level, count, time); }
				++count;
			}
		}

		void bisect_space(int level, scalar& time)
		{
			if (level >= subdivision_times) return;
			//static int num[4] = { 0,0,0,0 };
			level += 1;
			bool if_calc_root = level == subdivision_times;
			for (int i = 0; i < 2; ++i)
			{
				sub_tree->tree_cof[level][i] = constant_data->bisect_transform[i] * sub_tree->tree_cof[level - 1][0];
				//num[level]++;
				message mes = InitCollision;
				tet_status(sub_tree->tree_cof[level][i], time, mes, if_calc_root);
				if (mes == InitCollision) { dprint("InitCollision"); exit(0); }
			}
		};

		void quadtrisect_space(int level, scalar& time)
		{
			if (level >= subdivision_times) return;
			//static int num[4] = { 0,0,0,0 };
			level += 1;
			bool if_calc_root = level == subdivision_times;
			for (int i = 0; i < 4; ++i)
			{
				sub_tree->tree_cof[level][i] = constant_data->quadtrisect_transform[i] * sub_tree->tree_cof[level - 1][0];
				//num[level]++;
				message mes = InitCollision;
				tet_status(sub_tree->tree_cof[level][i], time, mes, if_calc_root);
				if (mes == InitCollision) { dprint("InitCollision"); exit(0); }
			}
		};

		void run(scalar& time)
		{
			matn4& cof = sub_tree->tree_cof[0][0];
			for (int i = 0; i < N; ++i)
			{
				if (cof(i, 0).inf() < 0)
				{
					dprint("flipping occurs in the initialization: there is cof(i,0).inf() < 0");
					dprint(cof(i, 0));
					exit(0);
				}
			}

#if 0
			//Lagrange cofficients ---> Bernstein cofficients
			cof = constant_data->transform * cof * constant_data->time_transform;
			cof.col(1) /= time;
			cof.col(2) /= time * time;
			cof.col(3) /= time * time * time;
#else
			cof = constant_data->transform * cof;// *constant_data->time_transform;
			{
				auto cof_ = cof * constant_data->bern_transform;
				if (cof_.minCoeff().inf() > 0)
					return;
			}

			/*cof = cof * costant_data->time_transform;
			cof.col(1) /= time;
			cof.col(2) /= time * time;
			cof.col(3) /= time * time * time;*/
			mat4_4 tt;
			tt.col(0) = constant_data->time_transform.col(0);
			tt.col(1) = constant_data->time_transform.col(1) / time;
			tt.col(2) = constant_data->time_transform.col(2) / (time * time);
			tt.col(3) = constant_data->time_transform.col(3) / (time * time * time);
			cof = cof * tt;
#endif


			//sub_tree->tree_cof[0][0] = std::move(cof);

			message mes(Collision);
			tet_status(cof, time, mes, true);
			if (mes == InitCollision)
			{
				dprint("InitCollision");
				exit(0);
			}
			else if (mes == Collision)
			{
				switch (mode)
				{
				case bisect:
					bisect_space(0, time);
					break;
				case quadtrisect:
					quadtrisect_space(0, time);
					break;
				case octasect:
					get_min_time_recursion(0, 0, time);
				//{
				//	for (int i = 0; i < 8; ++i)
				//	{
				//		sub_tree->tree_cof[1][i] = constant_data->son_transform[i] * sub_tree->tree_cof[0][0];
				//		//num[level]++;
				//		message mes = InitCollision;
				//		tet_status(sub_tree->tree_cof[1][i], time, mes, true);
				//		//dprintwithprecision(15, "iiiiiiiiiii", i, time);
				//    }
				//}
					break;
				default:
					break;
				}
			}
		}
        
    };

	typedef tet_detector<2, tet2_constant_data, subdivide_tree<mat20_4>> tet2;
	typedef tet_detector<3, tet3_constant_data, subdivide_tree<mat84_4>> tet3;
    
#else
    class tet_detector
    {
    public:
        tet_detector(){}
        virtual ~tet_detector() {}

    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        enum message
        {
            NoCollision,      // there is no collision in (0, time)
            Collision,        // there is an explicit and exact collision in (0, time)
            NumericalFailure, // there is a collision but the time is not exact because of numerical problems
            InitCollision     // the initial closure has collision
        };
        scalar elp = scalar(1e-4, 1e-4);
        void newton_raphson(const vec4s& cubic_cof, scalar time, scalar dif, scalar& val, scalar elp);
        void search_cubic_root(const vec4s& cubic_cof, scalar& time, message& mes);  
        virtual void write_bug() = 0;


    };

    class tet2 : public tet_detector
    {
    public:
        tet2() { }
        ~tet2() { }


    public:
		int subdivision_times = 3;
		tet2_constant_data* constant_data = nullptr;
		subdivide_tree<mat20_4>* sub_tree = nullptr;
        mat3_10 control_val;
        mat3_10 control_dir;
        void init(mat3_10& val, mat3_10& dir, tet2_constant_data* constant_data_, subdivide_tree<mat20_4>* sub_tree_)
        {
            control_val = std::move(val); control_dir = std::move(dir); constant_data = constant_data_; sub_tree = sub_tree_;
        }
        void calc_sampling_jacobi_det(scalar t, mat20_4 &cof);
        //void cardano(complex<double> a, complex<double> b, complex<double> c, complex<double>d, complex<double>& x1, complex<double>& x2, complex<double>& x3);
       // void calc_cubic_root_with_cardano(scalar a, scalar b, scalar c, scalar d, scalar& time);
        void tet_status(mat20_4& cof, scalar& time, message& mes);
        void get_min_time_recursion(int level, int count, scalar& time);
        void run(scalar& time);
        scalar compute_jacobidet(scalar& time);
        void write_bug();
    };
    
    class tet3 : public tet_detector
    {
    public:
        tet3() { }
        ~tet3() { }


    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        int subdivision_times = 3;
        tet3_constant_data* constant_data = nullptr;
        subdivide_tree<mat35_4>* sub_tree = nullptr;
        mat3_20 control_val;
        mat3_20 control_dir;
        void init(mat3_20& val, mat3_20& dir, tet3_constant_data* constant_data_, subdivide_tree<mat35_4>* sub_tree_)
        {
            control_val = std::move(val); control_dir = std::move(dir); constant_data = constant_data_; sub_tree = sub_tree_;
        }
        void calc_sampling_jacobi_det(scalar t, mat35_4& cof);
        void tet_status(mat35_4& cof, scalar& time, message& mes);
        void get_min_time_recursion(int level, int count, scalar& time);
        void run(scalar& time);
        scalar compute_jacobidet(scalar& time);
        void write_bug();
    };
#endif
}