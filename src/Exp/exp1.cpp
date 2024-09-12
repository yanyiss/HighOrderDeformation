#include "exp.h"
#include "..\src\Validity\filesOperator.h"
//using order-2 tet as the following
//val = { 0.807663 , 0.372121 , 0.4991 , 0.769641 , 0.379124 , 0.239324 , 0.75124 , 0.396562 , 0.0312357 ,
//				0.681321 , 0.426393 , 0.320528 , 0.616128 , 0.432535 , 0.0313826 , 0.550644 , 0.499718 , 0.163866 ,
//				0.672163 , 0.313374 , 0.295082 , 0.634206 , 0.316486 , 0.030531 , 0.545913 , 0.386881 , 0.124033 , 0.550612 , 0.279501 , 0.127056 };

namespace CABT
{
	namespace exp1
	{
		int my_method_subdivision_times = 1;
		tet2::subdivision_mode mode = tet2::octasect;

		std::string random_data_name = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\regular_batch_fixed_val_rand_dir.txt";
		std::string collision_step_name = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\collision_step.txt";
		std::string threshold_name = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\threshold.txt";
		std::string my_collision_step_name = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\my_collision_step.txt";
		std::string my_collision_time_name = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\my_collision_time.txt";
		std::string ho_collision_step_name = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\ho_collision_step.txt";
		std::string ho_collision_time_name = "C:\\Git Code\\HighOrderDeformation\\src\\test_data\\exp1\\ho_collision_time.txt";

		scalar init_time = scalar(1);

		int batch_size = 10000;
		CABT::tet2_constant_data data2;
		CABT::subdivide_tree<CABT::mat20_4> tree20_4;
		CABT::tet3_constant_data data3;
		CABT::subdivide_tree<CABT::mat35_4> tree35_4;

		void reset_filename()
		{
			std::string my_method_subdivision_times_str = std::to_string(my_method_subdivision_times);
			std::string mode_str = std::to_string(mode);
			std::string para = my_method_subdivision_times_str + "_" + mode_str;
			create_para_subfile(threshold_name, para);
			create_para_subfile(my_collision_step_name, para);
			create_para_subfile(my_collision_time_name, para);
			create_para_subfile(ho_collision_step_name, para);
			create_para_subfile(ho_collision_time_name, para);
		}

		void generate_test_data()
		{
			write_batch_test_data(2, batch_size, random_data_name);
		}

		void compute_exact_collision_time(double threshold)
		{
			std::vector<CABT::mat3_10> val, dir;
			val.resize(batch_size);
			dir.resize(batch_size);
			CABT::hocgv2 hocg;
			CABT::read_batch_test_data(2, batch_size, val, dir, random_data_name);
			std::ofstream outFile(collision_step_name, std::ios::binary);
			std::setprecision(15);
			for (int i = 0; i < batch_size; ++i)
			{
				CABT::scalar step_time(1);
				hocg.init(val[i], dir[i], &data2);
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
		}

		void compute_mymethod_time()
		{
			std::vector<CABT::mat3_10> val, dir;
			val.resize(batch_size);
			dir.resize(batch_size);
			CABT::tet2 tet;
			tet.mode = mode;
			CABT::read_batch_test_data(2, batch_size, val, dir, random_data_name);

#pragma region warm_up
			auto start = std::chrono::high_resolution_clock::now();
			auto end = std::chrono::high_resolution_clock::now();
#if 0
			auto valk = val; auto dirk = dir;
			for (int i = 0; i < batch_size; ++i)
			{
				CABT::scalar step_time(1);
				tet.init(valk[i], dirk[i], &data2, &tree20_4);
				tet.subdivision_times = 1;
				tet.run(step_time);
			}
#endif
#pragma endregion

			int iter_times = 1;
			std::vector<double> step_val(batch_size, 0);
			std::vector<double> time_ms(batch_size, 0);
			for (int iter = 0; iter < iter_times; ++iter)
			{
				dprint("iter:", iter);
				for (int i = 0; i < batch_size; ++i)
				{
					CABT::scalar step_time(init_time);
					auto vali = val[i]; auto diri = dir[i];
					start = std::chrono::high_resolution_clock::now();
					tet.init(vali, diri, &data2, &tree20_4);
					tet.subdivision_times = my_method_subdivision_times;
					tet.run(step_time);
					end = std::chrono::high_resolution_clock::now();

					step_val[i] = step_time.inf();
					time_ms[i] += std::chrono::duration<double, std::milli>(end - start).count();
				}
			}
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
			std::vector<CABT::mat3_10> val, dir;
			val.resize(batch_size);
			dir.resize(batch_size);
			CABT::hocgv2 hocg;
			CABT::read_batch_test_data(2, batch_size, val, dir, random_data_name);

			std::ofstream outFile(threshold_name, std::ios::binary);
			std::setprecision(15);
			double conservative_threshold = 0;
			for (int i = 0; i < batch_size; ++i)
			{
				CABT::scalar step_time(1);
				hocg.init(val[i], dir[i], &data2);
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


			std::vector<CABT::mat3_10> val, dir;
			val.resize(batch_size);
			dir.resize(batch_size);
			CABT::hocgv2 hocg;
			CABT::read_batch_test_data(2, batch_size, val, dir,random_data_name);

#pragma region warm_up
			auto start = std::chrono::high_resolution_clock::now();
			auto end = std::chrono::high_resolution_clock::now();
#if 1
			auto valk = val; auto dirk = dir;
			for (int i = 0; i < batch_size; ++i)
			{
				CABT::scalar step_time(1);
				hocg.init(valk[i], dirk[i], &data2);
				hocg.max_subdivide_times = 5;
				hocg.run(step_time);
			}
#endif
#pragma endregion

			/*dprint(threshold[204]);
			return;*/
			int iter_times = 10;
			std::vector<double> step_val(batch_size, 0);
			std::vector<double> time_ms(batch_size, 0);
			for (int iter = 0; iter < iter_times; ++iter)
			{
				dprint("iter", iter);
				for (int i = 0; i < batch_size; ++i)
				{
					//dprint(i);
					CABT::scalar step_time(init_time);
					auto vali = val[i]; auto diri = dir[i];
					start = std::chrono::high_resolution_clock::now();
					hocg.init(vali, diri, &data2);
					hocg.max_subdivide_times = 5000;
					//hocg.delta = threshold[i];
					hocg.run(step_time, threshold[i]);
					end = std::chrono::high_resolution_clock::now();

					step_val[i] = step_time.inf();
					time_ms[i] += std::chrono::duration<double, std::milli>(end - start).count();
					//dprint("time:", time_ms[i]);
				}
			}
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
