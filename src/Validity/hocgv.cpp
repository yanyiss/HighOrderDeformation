#include "hocgv.h"
namespace CABT
{
	void hocgv::calc_sampling_jacobi_det(scalar t, mat20_4& cof)
	{
		auto& o3tensor2vec = constant_data->o3tensor2vec;
		auto& o2tensor2vec = constant_data->o2tensor2vec;
		mat3_20 knot;
		knot.setConstant(-1);
		scalar inverse3 = scalar(1) / scalar(3);
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4 - i; ++j)
			{
				for (int k = 0; k < 4 - i - j; ++k)
				{
					knot(0, o3tensor2vec(i, j, k)) = scalar(i) * inverse3;
					knot(1, o3tensor2vec(i, j, k)) = scalar(j) * inverse3;
					knot(2, o3tensor2vec(i, j, k)) = scalar(k) * inverse3;
				}
			}
		}
		mat3_3 jacobi;
		for (int n = 0; n < 4; ++n)
		{
			mat3_10 val = control_val + scalar(n) / scalar(3) * t * control_dir;
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4 - i; ++j)
				{
					for (int k = 0; k < 4 - i - j; ++k)
					{
						int id4ijk = o3tensor2vec(i, j, k);
						jacobi.col(0) = 2.0 *
							((val.col(o2tensor2vec(1, 0, 0)) - val.col(o2tensor2vec(0, 0, 0))) * (1.0 - knot(0, id4ijk) - knot(1, id4ijk) - knot(2, id4ijk))
								+ (val.col(o2tensor2vec(2, 0, 0)) - val.col(o2tensor2vec(1, 0, 0))) * knot(0, id4ijk)
								+ (val.col(o2tensor2vec(1, 1, 0)) - val.col(o2tensor2vec(0, 1, 0))) * knot(1, id4ijk)
								+ (val.col(o2tensor2vec(1, 0, 1)) - val.col(o2tensor2vec(0, 0, 1))) * knot(2, id4ijk));
						jacobi.col(1) = 2.0 *
							((val.col(o2tensor2vec(0, 1, 0)) - val.col(o2tensor2vec(0, 0, 0))) * (1.0 - knot(0, id4ijk) - knot(1, id4ijk) - knot(2, id4ijk))
								+ (val.col(o2tensor2vec(1, 1, 0)) - val.col(o2tensor2vec(1, 0, 0))) * knot(0, id4ijk)
								+ (val.col(o2tensor2vec(0, 2, 0)) - val.col(o2tensor2vec(0, 1, 0))) * knot(1, id4ijk)
								+ (val.col(o2tensor2vec(0, 1, 1)) - val.col(o2tensor2vec(0, 0, 1))) * knot(2, id4ijk));
						jacobi.col(2) = 2.0 *
							((val.col(o2tensor2vec(0, 0, 1)) - val.col(o2tensor2vec(0, 0, 0))) * (1.0 - knot(0, id4ijk) - knot(1, id4ijk) - knot(2, id4ijk))
								+ (val.col(o2tensor2vec(1, 0, 1)) - val.col(o2tensor2vec(1, 0, 0))) * knot(0, id4ijk)
								+ (val.col(o2tensor2vec(0, 1, 1)) - val.col(o2tensor2vec(0, 1, 0))) * knot(1, id4ijk)
								+ (val.col(o2tensor2vec(0, 0, 2)) - val.col(o2tensor2vec(0, 0, 1))) * knot(2, id4ijk));
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
		for (int i = 0; i < 20; ++i)
		{
			if (cof(i, 0).inf() < 0)
			{
				dprint("flipping occurs in the initialization");
				system("pause");
			}
		}

		//Lagrange cofficients ---> Bernstein cofficients
		cof = constant_data->transform * cof * constant_data->bern_transform;
		cof.col(1) /= t;
		cof.col(2) /= t * t;
		cof.col(3) /= t * t * t;
	}


	void hocgv::test_regularity(mat20_4& cof, message& mes)
	{

	}

	void hocgv::run(scalar& time)
	{
		mat20_4 cof;
		calc_sampling_jacobi_det(time, cof);
		scalar time_interval(0, time.inf());
		tet_queue.emplace(0, time_interval, cof);
		int level = 0;
		while (true)
		{
			if (time_interval.sup() < time_interval.inf() + delta && time_interval.inf() > 0)
				break;
			if (tet_queue.empty())
				break;
			sub_tet current_tet = tet_queue.top();
			tet_queue.pop();
			level = max(level, current_tet.level);
			if (level > max_subdivide_times)
				break;

			message mes;
			test_regularity(current_tet.cof, mes);
			switch (mes)
			{
			case CABT::hocgv::positive:
				continue;
				break;
			case CABT::hocgv::negative:
				//subdivide on time
			{
				double mid = (current_tet.time_interval.inf() + current_tet.time_interval.sup()) / 2.0;
				tet_queue.emplace(current_tet.level + 1,
					scalar(current_tet.time_interval.inf(), mid),
					current_tet.cof * constant_data->former_transform);
				tet_queue.emplace(current_tet.level + 1,
					scalar(mid, current_tet.time_interval.sup()),
					current_tet.cof * constant_data->latter_transform);
			}
				break;
			case CABT::hocgv::uncertain:
				//subdivide on time and space
			{
				double mid = (current_tet.time_interval.inf() + current_tet.time_interval.sup()) / 2.0;
				for (int i = 0; i < 8; ++i)
				{
					tet_queue.emplace(current_tet.level + 1,
						scalar(current_tet.time_interval.inf(), mid),
						constant_data->son_transform[i] * current_tet.cof * constant_data->former_transform);
					tet_queue.emplace(current_tet.level + 1,
						scalar(mid, current_tet.time_interval.sup()),
						constant_data->son_transform[i] * current_tet.cof * constant_data->latter_transform);
				}
			}
				break;
			}

		}
	}
}