#include "exp.h"
#include "..\src\Validity\filesOperator.hpp"
//using order-2 tet as the following
//val = { 0.807663 , 0.372121 , 0.4991 , 0.769641 , 0.379124 , 0.239324 , 0.75124 , 0.396562 , 0.0312357 ,
//				0.681321 , 0.426393 , 0.320528 , 0.616128 , 0.432535 , 0.0313826 , 0.550644 , 0.499718 , 0.163866 ,
//				0.672163 , 0.313374 , 0.295082 , 0.634206 , 0.316486 , 0.030531 , 0.545913 , 0.386881 , 0.124033 , 0.550612 , 0.279501 , 0.127056 };

namespace CABT
{
	namespace exp1
	{
		int my_method_subdivision_times = 1;
#define order 3
#if order==2
		tet2::subdivision_mode mode = tet2::octasect;
		CABT::tet2_constant_data data;
		CABT::subdivide_tree<CABT::mat20_4> tree;
		CABT::tet2 tet;
		CABT::hocgv2 hocg;
		std::string random_data_name = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\regular_batch_fixed_val_rand_dir_2.txt";
		std::string collision_step_name = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\collision_step_2.txt";
#elif order==3
		tet3::subdivision_mode mode = tet3::octasect;
		CABT::tet3_constant_data data;
		CABT::subdivide_tree<CABT::mat84_4> tree;
		CABT::tet3 tet;
		CABT::hocgv3 hocg;
		std::string random_data_name = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\regular_batch_fixed_val_rand_dir_3.txt";
		std::string collision_step_name = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\collision_step_3.txt";
#endif

		int M = (order + 1) * (order + 2) * (order + 3) / 6;
		int N = order * (3 * order - 1) * (3 * order - 2) / 2;
		typedef Eigen::Matrix<scalar, 3, (order + 1)* (order + 2)* (order + 3) / 6> mat3m;
		typedef Eigen::Matrix<scalar, 3, order* (3 * order - 1)* (3 * order - 2) / 2> mat3n;
		typedef Eigen::Matrix<scalar, order* (3 * order - 1)* (3 * order - 2) / 2, 4> matn4;

		std::string threshold_name = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\threshold.txt";
		std::string my_collision_step_name = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\my_collision_step.txt";
		std::string my_collision_time_name = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\my_collision_time.txt";
		std::string ho_collision_step_name = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\ho_collision_step.txt";
		std::string ho_collision_time_name = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\ho_collision_time.txt";

		scalar init_time = scalar(1);

		int batch_size = 10000;

		void reset_filename()
		{
			std::string order_str = std::to_string(order);
			std::string my_method_subdivision_times_str = std::to_string(my_method_subdivision_times);
			std::string mode_str = std::to_string(mode);
			std::string para = order_str + "_" + my_method_subdivision_times_str + "_" + mode_str;
			create_para_subfile(threshold_name, para);
			create_para_subfile(my_collision_step_name, para);
			create_para_subfile(my_collision_time_name, para);
			create_para_subfile(ho_collision_step_name, para);
			create_para_subfile(ho_collision_time_name, para);
		}

		void read_index(std::vector<int>& index)
		{
			std::ifstream inFile("C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\1_2\\indice.txt");
			index.resize(6607);
			if (inFile.is_open()) {
				for (int i = 0; i < 6607; ++i)
				{
					inFile.read(reinterpret_cast<char*>(&index[i]), sizeof(int));
				}
				inFile.close();
			}
			else {
				std::cerr << "无法打开文件。\n";
				exit(0);
				return;
			}

			std::ifstream file("C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\1_2\\indice.txt");  // 打开文件
			index.resize(6607);

			// 检查文件是否成功打开
			if (!file.is_open()) {
				std::cerr << "Failed to open file: " << std::endl;
				return;
			}

			int number = 0;
			while (file >> index[number]) {  // 使用 >> 操作符逐个读取整数
				++number;
			}

			file.close();
		}

		void generate_test_data()
		{
			write_batch_test_data(order, batch_size, random_data_name);
		}

		void compute_exact_collision_time(double threshold)
		{
			std::vector<mat3m> val, dir;
			val.resize(batch_size);
			dir.resize(batch_size);
			CABT::read_batch_test_data(order, batch_size, val, dir, random_data_name);
			std::ofstream outFile(collision_step_name, std::ios::binary);
			std::setprecision(15);
			for (int i = 0; i < batch_size; ++i)
			{
				CABT::scalar step_time(1);
				hocg.init(val[i], dir[i], &data);
				hocg.max_subdivide_times = 600000000;
				hocg.delta = threshold;
				hocg.run(step_time);

				double inf = step_time.inf();
				double sup = step_time.sup();
				outFile.write(reinterpret_cast<const char*>(&inf), sizeof(double));
				//outFile.write(reinterpret_cast<const char*>(&sup), sizeof(double));

				dprintwithprecision(15, i, inf, sup);
			}
			outFile.close();
			exit(0);
		}

		void compute_mymethod_time()
		{
			std::vector<mat3m> val, dir;
			val.resize(batch_size);
			dir.resize(batch_size);
			tet.mode = mode;
			CABT::read_batch_test_data(order, batch_size, val, dir, random_data_name);

#pragma region warm_up
			auto start = std::chrono::high_resolution_clock::now();
			auto end = std::chrono::high_resolution_clock::now();
#if 0
			auto valk = val; auto dirk = dir;
			for (int i = 0; i < batch_size; ++i)
			{
				CABT::scalar step_time(1);
				tet.init(valk[i], dirk[i], &data, &tree);
				tet.subdivision_times = 1;
				tet.run(step_time);
			}
#endif
#pragma endregion

			int iter_times = 1;
			std::vector<double> step_val(batch_size, 0);
			std::vector<double> time_ms(batch_size, 0);
			/*std::vector<int> index;
			read_index(index);
			int count = 0;*/
			for (int iter = 0; iter < iter_times; ++iter)
			{
				dprint("iter:", iter);
				CABT::scalar step_time(init_time);
				for (int i = 0; i < batch_size; ++i)
				{
					/*if (i == index[count])
						++count;
					else
						continue;*/
					auto vali = val[i]; auto diri = dir[i];
					tet.init(vali, diri, &data, &tree, step_time);
					tet.subdivision_times = my_method_subdivision_times;
					start = std::chrono::high_resolution_clock::now();
					tet.run(step_time);
					end = std::chrono::high_resolution_clock::now();

					step_val[i] = step_time.inf();
					time_ms[i] += std::chrono::duration<double, std::milli>(end - start).count();
				}
				dprint("step:", step_time.inf());
			}
			dprint("my time:", std::accumulate(time_ms.begin(), time_ms.end(), 0.0));
			std::ofstream outFile(my_collision_step_name, std::ios::binary);
			std::setprecision(15);
			for (int i = 0; i < batch_size; ++i)
			{
				double x = step_val[i];// > 0.8 ? 0.8 : step_val[i];
				outFile.write(reinterpret_cast<const char*>(&x), sizeof(double));
			}
			outFile.close();

			outFile = std::ofstream(my_collision_time_name, std::ios::binary);
			std::setprecision(15);
			for (int i = 0; i < batch_size; ++i)
			{
				double avg = time_ms[i] / iter_times;
				outFile.write(reinterpret_cast<const char*>(&avg), sizeof(double));
			}
			outFile.close();
		}

		void compute_conservative_threshold()
		{
			std::vector<double> threshold(batch_size, 0);
			std::ifstream inFile(my_collision_step_name, std::ios::binary);
			if (inFile.is_open()) {
				for (int i = 0; i < batch_size; ++i)
				{
					inFile.read(reinterpret_cast<char*>(&threshold[i]), sizeof(double));
				}
				inFile.close();
			}
			else {
				std::cerr << "无法打开文件。\n";
				exit(0);
			}
			std::vector<mat3m> val, dir;
			val.resize(batch_size);
			dir.resize(batch_size);
			CABT::read_batch_test_data(2, batch_size, val, dir, random_data_name);

			std::ofstream outFile(threshold_name, std::ios::binary);
			std::setprecision(15);
			double conservative_threshold = 0;
			for (int i = 0; i < batch_size; ++i)
			{
				CABT::scalar step_time(1);
				hocg.init(val[i], dir[i], &data);
				hocg.max_subdivide_times = 50000;
				conservative_threshold = hocg.run(step_time, threshold[i]);
				outFile.write(reinterpret_cast<const char*>(&conservative_threshold), sizeof(double));
			}
			outFile.close();
		}

		void compute_hocgvstep_with_threshold()
		{
			std::vector<double> threshold(batch_size, 0);
			std::ifstream inFile(my_collision_step_name, std::ios::binary);
			if (inFile.is_open()) {
				for (int i = 0; i < batch_size; ++i)
				{
					inFile.read(reinterpret_cast<char*>(&threshold[i]), sizeof(double));
				}
				inFile.close();
			}
			else {
				std::cerr << "无法打开文件。\n";
				exit(0);
			}


			std::vector<mat3m> val, dir;
			val.resize(batch_size);
			dir.resize(batch_size);
			CABT::read_batch_test_data(order, batch_size, val, dir,random_data_name);

			std::vector<int> id(batch_size);
			for (int i = 0; i < batch_size; ++i) id[i] = i;
			std::swap(id[0], id[413]);
			std::swap(id[1], id[1994]);
			std::swap(id[2], id[5836]);
			/*shuffle_vector(dir);
			shuffle_vector(id);*/

#pragma region warm_up
			auto start = std::chrono::high_resolution_clock::now();
			auto end = std::chrono::high_resolution_clock::now();
#if 0
			auto valk = val; auto dirk = dir;
			for (int i = 0; i < batch_size; ++i)
			{
				CABT::scalar step_time(1);
				hocg.init(valk[i], dirk[i], &data);
				hocg.max_subdivide_times = 5;
				hocg.run(step_time);
			}
#endif
#pragma endregion

			/*dprint(threshold[204]);
			return;*/
			int iter_times = 1;
			std::vector<double> step_val(batch_size, 0);
			std::vector<double> time_ms(batch_size, 0);
			/*std::vector<int> index;
			read_index(index);
			int count = 0;*/
			for (int iter = 0; iter < iter_times; ++iter)
			{
				dprint("iter", iter);
				CABT::scalar step_time(init_time);
				for (int i = 0; i < batch_size; ++i)
				{
					/*if (i == index[count])
						++count;
					else
						continue;*/
					dprint(i, id[i]);
					auto vali = val[i]; auto diri = dir[i];
					hocg.init(vali, diri, &data, step_time);
					hocg.max_subdivide_times = 15;
					start = std::chrono::high_resolution_clock::now();
					//hocg.delta = threshold[i];
					hocg.run(step_time/*, threshold[i]*/);
					end = std::chrono::high_resolution_clock::now();

					step_val[i] = step_time.inf();
					time_ms[i] += std::chrono::duration<double, std::milli>(end - start).count();
					dprint("step and time:", i, step_val[i], time_ms[i]);
				}
				//dprint("step:", step_time.inf());
			}
			dprint("ho time:", std::accumulate(time_ms.begin(), time_ms.end(), 0.0));
			//return;

			std::ofstream outFile(ho_collision_step_name, std::ios::binary);
			std::setprecision(15);
			for (int i = 0; i < batch_size; ++i)
			{
				outFile.write(reinterpret_cast<const char*>(&step_val[i]), sizeof(double));
			}
			outFile.close();

			outFile = std::ofstream(ho_collision_time_name, std::ios::binary);
			std::setprecision(15);
			for (int i = 0; i < batch_size; ++i)
			{
				double avg = time_ms[i] / iter_times;
				outFile.write(reinterpret_cast<const char*>(&avg), sizeof(double));
			}
			outFile.close();
		}

		void run_exp1()
		{
			reset_filename();
#if 0
			generate_test_data();
			exit(0);
#endif
#if 0
			compute_exact_collision_time(1e-6);
#endif
#if 1
			compute_mymethod_time();
#endif
#if 0
			compute_conservative_threshold();
#endif
#if 0
			compute_hocgvstep_with_threshold();
#endif
		}
	}
}
