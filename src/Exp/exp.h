#pragma once
#include "../src/Validity/btet.hpp"
#include "../src/Validity/hocgv.hpp"
#include <iostream>
#include <vector>
#include <algorithm> // std::shuffle
#include <numeric>
#include <random> 
namespace CABT
{
	//comparison with hocgv
	namespace exp1
	{
		void reset_filename();
		void read_index(std::vector<int>& index);
		template<typename T>
		void shuffle_vector(std::vector<T>& vec) {
			// 创建随机数生成器
			std::random_device rd;   // 随机设备（用于种子）
			std::mt19937 g(rd());    // 生成随机数的引擎（梅森旋转器）

			// 使用 std::shuffle 打乱 vector 中的元素
			std::shuffle(vec.begin(), vec.end(), g);
		}
		void generate_test_data();
		void compute_exact_collision_time(double threshold = 1e-4);
		void compute_mymethod_time();
		void compute_conservative_threshold();
		void compute_hocgvstep_with_threshold();
		void run_exp1();
	}

	namespace exp2
	{
		void run_morphing(std::vector<mat3_10>& val, std::vector<mat3_10>& dir, double& init_time);
	}

	namespace exp3
	{
		void compute_mymethod_time();
		void run_exp3();
	}
}