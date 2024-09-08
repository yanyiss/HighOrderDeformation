#pragma once
#include "..\src\MeshViewer\MeshDefinition.h"
#include "scalar_def.h"
#include "constant_data.h"
#include "btet.h"
#include "dprint.h"
#include <Eigen/Core>
#include <queue>
namespace CABT
{
#if 1
	template <int order, int sample_num, typename ConstantData>
	class hocgv_detector : public detector<order, sample_num, ConstantData>
	{
	public:
		hocgv_detector() {}
		~hocgv_detector() {}

	public:
		enum message
		{
			regular,
			flipped,
			uncertain
		};
		struct sub_tet
		{
		public:
			EIGEN_MAKE_ALIGNED_OPERATOR_NEW
				sub_tet(int level_, scalar& time_interval_, matn4& cof_)
			{
				level = level_;
				time_interval = time_interval_;
				cof = std::move(cof_);
				switch (order)
				{
				case 2:
					inclusion = scalar(cof.minCoeff().inf(),
						std::min({ cof(0,0).inf(),cof(3,0).inf(),cof(9,0).inf(),cof(19,0).inf(),
							cof(0,3).inf(),cof(3,3).inf(),cof(9,3).inf(),cof(19,3).inf() }));
					break;
				case 3:
					inclusion = scalar(cof.minCoeff().inf(),
						std::min({ cof(0,0).inf(),cof(4,0).inf(),cof(14,0).inf(),cof(34,0).inf(),
							cof(0,3).inf(),cof(4,3).inf(),cof(14,3).inf(),cof(34,3).inf() }));
					break;
				default:
					dprint("order can only be 2 or 3");
					exit(0);
					break;
				}
			}
			~sub_tet() {}

		public:
			int level;
			scalar time_interval;
			scalar inclusion;
			matn4 cof;

			bool operator > (const sub_tet& right) const
			{
				if (time_interval.inf() != right.time_interval.inf())
					return time_interval.inf() > right.time_interval.inf();
				else
					return inclusion.sup() > right.inclusion.sup();
			}
		};

		double delta = 1e-4;
		int max_subdivide_times = 5;
		std::priority_queue<sub_tet, std::vector<sub_tet>, std::greater<sub_tet>> tet_queue;

		void init(mat3m& val, mat3m& dir, ConstantData* constant_data_)
		{
			control_val = std::move(val); control_dir = std::move(dir); constant_data = constant_data_; 
			tet_queue.swap(std::priority_queue<sub_tet, std::vector<sub_tet>, std::greater<sub_tet>>());
		}

		void test_regularity(sub_tet& current_tet, message& mes)
		{
			/*if (current_tet.inclusion.inf() > 0)
				mes = regular;
			else if (current_tet.inclusion.sup() < 0)
				mes = flipped;
			else
				mes = uncertain;*/
			auto& cof = current_tet.cof;
			if (cof.minCoeff().inf() > 0)
				mes = regular;
			else if (cof(0, 0).inf() < 0 || cof(3, 0).inf() < 0 || cof(9, 0).inf() < 0 || cof(19, 0).inf() < 0 ||
				cof(0, 3).inf() < 0 || cof(3, 3).inf() < 0 || cof(9, 3).inf() < 0 || cof(19, 3).inf() < 0)
				mes = flipped;
			else
				mes = uncertain;
		}

		void run(scalar& time)
		{
			matn4 cof;
			time = scalar(time.inf());
			//dprint(time);
			calc_sampling_jacobi_det(time, cof);
			for (int i = 0; i < N; ++i)
			{
				if (cof(i, 0).inf() < 0)
				{
					dprint("flipping occurs in the initialization");
					system("pause");
				}
			}
			//Lagrange cofficients ===> Bernstein cofficients
			cof = constant_data->transform * cof * constant_data->bern_transform;
			cof.col(1) /= time;
			cof.col(2) /= time * time;
			cof.col(3) /= time * time * time;

			scalar time_interval(0, time.inf());
			tet_queue.emplace(0, time_interval, cof);
			int level = 0;
			message mes;
			double t0 = time_interval.inf();
			double t1 = time_interval.sup();
			while (true)
			{
				if (time_interval.sup() < time_interval.inf() + delta && time_interval.inf() > 0)
					break;
				if (tet_queue.empty())
				{
					t0 = time_interval.sup();
					break;
				}
				sub_tet current_tet = tet_queue.top();
				tet_queue.pop();
				level = std::max(level, current_tet.level);
				if (level > max_subdivide_times)
					break;
				t0 = current_tet.time_interval.inf();
				test_regularity(current_tet, mes);
				matn4 temp_cof;
#if 0
				dprint("\ncurrent level:", current_tet.level);
				dprint("current interval:", current_tet.time_interval);
				dprint("inclusion:", current_tet.inclusion);
				dprint("t0, t1:", t0, t1);
				dprint("message:", mes);
				dprint("tet_queue size:", tet_queue.size());
#endif
				switch (mes)
				{
				case regular:
					//dprint("regular");
					break;
				case flipped:
					//subdivide on time
				{
					//dprint("flipped");
					double mid = (current_tet.time_interval.inf() + current_tet.time_interval.sup()) / 2.0;
					temp_cof = current_tet.cof * constant_data->former_transform;
					tet_queue.emplace(current_tet.level + 1,
						scalar(current_tet.time_interval.inf(), mid), temp_cof);
					temp_cof = current_tet.cof * constant_data->latter_transform;
					tet_queue.emplace(current_tet.level + 1,
						scalar(mid, current_tet.time_interval.sup()), temp_cof);
					t1 = min(t1, current_tet.time_interval.sup());
				}
				break;
				case uncertain:
					//subdivide on time and space
				{
					//dprint("uncertain");
					double mid = (current_tet.time_interval.inf() + current_tet.time_interval.sup()) / 2.0;
					matn4 former_cof = current_tet.cof * constant_data->former_transform;
					matn4 latter_cof = current_tet.cof * constant_data->latter_transform;
					for (int i = 0; i < 8; ++i)
					{
						temp_cof = constant_data->son_transform[i] * former_cof;
						tet_queue.emplace(current_tet.level + 1,
							scalar(current_tet.time_interval.inf(), mid), temp_cof);
						temp_cof = constant_data->son_transform[i] * latter_cof;
						tet_queue.emplace(current_tet.level + 1,
							scalar(mid, current_tet.time_interval.sup()), temp_cof);
					}
				}
				break;
				}

			}
			time = scalar(t0, t1);
		}

	};


	typedef hocgv_detector<2, 100, tet2_constant_data> hocgv2;
	typedef hocgv_detector<3, 100, tet3_constant_data> hocgv3;

#else

	struct sub_tet
	{
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
		sub_tet() {}
		virtual ~sub_tet() {}

	public:
		int level;
		scalar time_interval;
		scalar inclusion;

		bool operator > (const sub_tet& right) const
		{
			if (time_interval.inf() != right.time_interval.inf())
				return time_interval.inf() > right.time_interval.inf();
			else
				return inclusion.sup() > right.inclusion.sup();
		}
	};

	class sub_tet_20_4 : public sub_tet
	{
	public:
		sub_tet_20_4(int level_, scalar& time_interval_, mat20_4& cof_)
		{
			level = level_;
			time_interval = time_interval_;
			cof = std::move(cof_);
			inclusion = scalar(cof.minCoeff().inf(),
				std::min({ cof(0,0).inf(),cof(3,0).inf(),cof(9,0).inf(),cof(19,0).inf(),
					cof(0,3).inf(),cof(3,3).inf(),cof(9,3).inf(),cof(19,3).inf() }));
		}
		~sub_tet_20_4() {}
	public:
		mat20_4 cof;
	};

	class sub_tet_35_4 : public sub_tet
	{
	public:
		sub_tet_35_4(int level_, scalar& time_interval_, mat35_4& cof_)
		{
			level = level_;
			time_interval = time_interval_;
			cof = std::move(cof_);
			inclusion = scalar(cof.minCoeff().inf(),
				std::min({ cof(0,0).inf(),cof(4,0).inf(),cof(14,0).inf(),cof(34,0).inf(),
					cof(0,3).inf(),cof(4,3).inf(),cof(14,3).inf(),cof(34,3).inf() }));
		}
		~sub_tet_35_4() {}
	public:
		mat35_4 cof;
	};

	class hocgv_detector
	{
	public:
		hocgv_detector() {}
		virtual ~hocgv_detector() {}

	public:
		enum message
		{
			regular,
			flipped,
			uncertain
		};
	};

	class hocgv2 : public hocgv_detector
	{
	public:
		hocgv2(){}
		~hocgv2(){}

	public:
		tet2_constant_data* constant_data = nullptr;
		mat3_10 control_val;
		mat3_10 control_dir;
		double delta = 1e-4;
		int max_subdivide_times = 5;
        //Compared to B, A should be on the top if A.time_interval.inf() < B.time_interval.inf()
        std::priority_queue<sub_tet_20_4, std::vector<sub_tet_20_4>, std::greater<sub_tet_20_4>> tet_queue;



		void calc_sampling_jacobi_det(scalar t, mat20_4& cof);
		void init(mat3_10& val, mat3_10& dir, tet2_constant_data* constant_data_)
		{
			control_val = std::move(val); control_dir = std::move(dir); constant_data = constant_data_;
			tet_queue.swap(std::priority_queue<sub_tet_20_4, std::vector<sub_tet_20_4>, std::greater<sub_tet_20_4>>());
		}
		void test_regularity(mat20_4& cof, message& mes);
		void run(scalar &time);

		scalar compute_jacobidet(scalar& time);
		void write_bug();
	};

	class hocgv3 : public hocgv_detector
	{
	public:
		hocgv3() {}
		~hocgv3() {}

	public:
		tet3_constant_data* constant_data = nullptr;
		mat3_20 control_val;
		mat3_20 control_dir;
		double delta = 1e-4;
		int max_subdivide_times = 5;
		//Compared to B, A should be on the top if A.time_interval.inf() < B.time_interval.inf()
		std::priority_queue<sub_tet_35_4, std::vector<sub_tet_35_4>, std::greater<sub_tet_35_4>> tet_queue;



		void calc_sampling_jacobi_det(scalar t, mat35_4& cof);
		void init(mat3_20& val, mat3_20& dir, tet3_constant_data* constant_data_)
		{
			control_val = std::move(val); control_dir = std::move(dir); constant_data = constant_data_;
			tet_queue.swap(std::priority_queue<sub_tet_35_4, std::vector<sub_tet_35_4>, std::greater<sub_tet_35_4>>());
		}
		void test_regularity(mat35_4& cof, message& mes);
		void run(scalar& time);

		scalar compute_jacobidet(scalar& time);
		void write_bug();
	};
#endif
}