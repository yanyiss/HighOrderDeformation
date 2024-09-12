#pragma once
#include "../src/Validity/btet.h"
#include "../src/Validity/hocgv.h"
namespace CABT
{
	namespace exp1
	{
		void reset_filename();
		void generate_test_data();
		void compute_exact_collision_time(double threshold = 1e-4);
		void compute_mymethod_time();
		void compute_conservative_threshold();
		void compute_hocgvstep_with_threshold();
		void run_exp1();
	}

	namespace exp2
	{

	}
}