#include "exp.h"
namespace CABT
{
	namespace exp3
	{
		int my_method_subdivision_times = 1;
#define order 2
#if order==2
		tet2::subdivision_mode mode = tet2::octasect;
		CABT::tet2_constant_data data;
		CABT::subdivide_tree<CABT::mat20_4> tree;
		CABT::tet2 tet;
		CABT::hocgv2 hocg;
#elif order==3
		tet3::subdivision_mode mode = tet3::octasect;
		CABT::tet3_constant_data data;
		CABT::subdivide_tree<CABT::mat35_4> tree;
		CABT::tet3 tet;
		CABT::hocgv3 hocg;
#endif
		int batch_size = 1740;
		int M = (order + 1) * (order + 2) * (order + 3) / 6;
		int N = (order + 2) * (order + 3) * (order + 4) / 6;
		typedef Eigen::Matrix<scalar, 3, (order + 1)* (order + 2)* (order + 3) / 6> mat3m;
		typedef Eigen::Matrix<scalar, 3, (order + 2)* (order + 3)* (order + 4) / 6> mat3n;
		typedef Eigen::Matrix<scalar, (order + 2)* (order + 3)* (order + 4) / 6, 4> matn4;
		scalar init_time = scalar(1);
		void compute_mymethod_time()
		{
			std::vector<mat3m> val, dir;
			val.resize(batch_size);
			dir.resize(batch_size);
			CABT::read_batch_test_data(order, batch_size, val, dir,
				std::string("C:\\Git Code\\HighOrderDeformation\\src\\simulation_data\\twist-beam-P1-data.txt"));

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
					/*dprint(i);
					if (i != 100)
					{
						continue;
					}*/
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
			auto max_it = std::max_element(time_ms.begin(), time_ms.end());
			int index = std::distance(time_ms.begin(), max_it);
			dprint("index", index, *max_it);
			dprint("my time:", std::accumulate(time_ms.begin(), time_ms.end(), 0.0));
			//std::ofstream outFile(my_collision_step_name, std::ios::binary);
			//std::setprecision(15);
			//for (int i = 0; i < batch_size; ++i)
			//{
			//	double x = step_val[i];// > 0.8 ? 0.8 : step_val[i];
			//	outFile.write(reinterpret_cast<const char*>(&x), sizeof(double));
			//}
			//outFile.close();

			//outFile = std::ofstream(my_collision_time_name, std::ios::binary);
			//std::setprecision(15);
			//for (int i = 0; i < batch_size; ++i)
			//{
			//	double avg = time_ms[i] / iter_times;
			//	outFile.write(reinterpret_cast<const char*>(&avg), sizeof(double));
			//}
			//outFile.close();
		}

		void run_exp3()
		{
			compute_mymethod_time();
		}
	}
}
