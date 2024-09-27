#include "exp.h"
namespace CABT
{
	namespace exp2
	{
		int my_method_subdivision_times = 1;
		void run_morphing(std::vector<mat3_10>& val, std::vector<mat3_10>& dir, double &init_time)
		{
			scalar::Protector p;

			CABT::tet2_constant_data data;
			CABT::subdivide_tree<CABT::mat20_4> tree;
			CABT::tet2 tet;
			CABT::hocgv2 hocg;
			int batch_size = val.size();

#pragma region warm_up
			auto start = std::chrono::high_resolution_clock::now();
			auto end = std::chrono::high_resolution_clock::now();
#if 1
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

			{
				std::vector<double> step_val(batch_size, 0);
				std::vector<double> time_ms(batch_size, 0);
				CABT::scalar step_time(init_time);
				for (int i = 0; i < batch_size; ++i)
				{
					auto vali = val[i]; auto diri = dir[i];
					tet.init(vali, diri, &data, &tree, step_time);
					tet.subdivision_times = my_method_subdivision_times;

					start = std::chrono::high_resolution_clock::now();
					tet.run(step_time);
					end = std::chrono::high_resolution_clock::now();

					step_val[i] = step_time.inf();
					time_ms[i] += std::chrono::duration<double, std::milli>(end - start).count();
				}
				dprint("step and time: ", std::accumulate(step_val.begin(), step_val.end(), 0.0),
					std::accumulate(time_ms.begin(), time_ms.end(), 0.0));
			}
			{
				std::vector<double> step_val(batch_size, 0);
				std::vector<double> time_ms(batch_size, 0);
				CABT::scalar step_time(init_time);
				for (int i = 0; i < batch_size; ++i)
				{
					auto vali = val[i]; auto diri = dir[i];
					hocg.init(vali, diri, &data, step_time);
					hocg.max_subdivide_times = 15;
					start = std::chrono::high_resolution_clock::now();
					hocg.run(step_time/*, threshold[i]*/);
					end = std::chrono::high_resolution_clock::now();

					step_val[i] = step_time.inf();
					time_ms[i] += std::chrono::duration<double, std::milli>(end - start).count();
				}
				dprint("step and time: ", std::accumulate(step_val.begin(), step_val.end(), 0.0),
					std::accumulate(time_ms.begin(), time_ms.end(), 0.0));
			}
		}
	}
}
