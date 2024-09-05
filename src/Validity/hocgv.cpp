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
		if (cof.minCoeff().inf() > 0)
			mes = regular;
		else if (cof(0, 0).inf() < 0 || cof(3, 0).inf() < 0 || cof(9, 0).inf() < 0 || cof(19, 0).inf() < 0 || 
			cof(0, 3).inf() < 0 || cof(3, 3).inf() < 0 || cof(9, 3).inf() < 0 || cof(19, 3).inf() < 0)
			mes = flipped;
		else
			mes = uncertain;
	}

	void hocgv::run(scalar& time)
	{
		max_subdivide_times = 5;
		mat20_4 cof;
		time = scalar(time.inf());
		calc_sampling_jacobi_det(time, cof);
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
				break;
			sub_tet current_tet = tet_queue.top();
			tet_queue.pop();
			level = std::max(level, current_tet.level);
			if (level > max_subdivide_times)
				break;
			t0 = current_tet.time_interval.inf();
			test_regularity(current_tet.cof, mes);
			mat20_4 temp_cof;
#if 0
			dprint("\ncurrent level:", current_tet.level);
			dprint("current interval:", current_tet.time_interval);
			dprint("inclusion:", current_tet.inclusion);
			dprint("time interval:", t0, t1);
			dprint("message:", mes);
			dprint("tet_queue size:", tet_queue.size());
#endif
			switch (mes)
			{
			case CABT::hocgv::regular:
				//dprint("regular");
				break;
			case CABT::hocgv::flipped:
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
			case CABT::hocgv::uncertain:
				//subdivide on time and space
			{
				//dprint("uncertain");
				double mid = (current_tet.time_interval.inf() + current_tet.time_interval.sup()) / 2.0;
				mat20_4 former_cof = current_tet.cof * constant_data->former_transform;
				mat20_4 latter_cof = current_tet.cof * constant_data->latter_transform;
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

	scalar hocgv::compute_jacobidet(scalar& time)
	{
		auto& o3tensor2vec = constant_data->o3tensor2vec;
		auto& o2tensor2vec = constant_data->o2tensor2vec;
		mat3_20 knot; knot.setConstant(-1);
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

#define sample_num 100
		typedef Eigen::Matrix<scalar, sample_num, 1> vecsns;
		Eigen::VectorXd sample_det0, sample_det1;
		sample_det0.resize(sample_num); sample_det1.resize(sample_num);
		sample_det0.setConstant(DBL_MAX); sample_det1.setConstant(DBL_MAX);
		scalar min_son[4] = { scalar(DBL_MAX),scalar(DBL_MAX),scalar(DBL_MAX),scalar(DBL_MAX) };
		//time=scalar(0.461049480549675);
		for (int n = 0; n < sample_num; ++n)
		{
			mat3_10 val = control_val + scalar(n + 1) / scalar(sample_num) * time.inf() * control_dir;
			vec20s det;
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
						det(id4ijk) = jacobi(0, 0) * jacobi(1, 1) * jacobi(2, 2)
							+ jacobi(0, 1) * jacobi(1, 2) * jacobi(2, 0)
							+ jacobi(0, 2) * jacobi(1, 0) * jacobi(2, 1)
							- jacobi(2, 0) * jacobi(1, 1) * jacobi(0, 2)
							- jacobi(1, 0) * jacobi(0, 1) * jacobi(2, 2)
							- jacobi(0, 0) * jacobi(2, 1) * jacobi(1, 2);
					}
				}
			}
			sample_det0(n) = det.minCoeff().inf();
			det = constant_data->transform * det;
			sample_det1(n) = det.minCoeff().inf();
		}
		//sample_det0 > 0 is neccesary
		//sample_det1 > 0 is sufficient
		dprint("min and max det", sample_det0.minCoeff(), sample_det1.minCoeff());
		if (sample_det0.minCoeff() < 0)
		{
			//system("pause");
		}
#if 0
		write_bug();
		if (sample_det0.minCoeff() < 0)
		{
			system("pause");
		}
#endif
		return sample_det1.minCoeff();
	}

	void hocgv::write_bug()
	{
		std::ofstream outFile("C:\\Git Code\\HighOrderDeformation\\src\\info.txt", std::ios::binary);
		std::setprecision(15);
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				scalar x = control_val(i, j);
				double xinf = x.inf();
				double xsup = x.sup();
				outFile.write(reinterpret_cast<const char*>(&xinf), sizeof(double));
				outFile.write(reinterpret_cast<const char*>(&xsup), sizeof(double));
				//dprint(i, j, xinf, xsup);
			}
		}
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				scalar x = control_dir(i, j);
				double xinf = x.inf();
				double xsup = x.sup();
				outFile.write(reinterpret_cast<const char*>(&xinf), sizeof(double));
				outFile.write(reinterpret_cast<const char*>(&xsup), sizeof(double));
				//dprint(i, j, xinf, xsup);
			}
		}
		outFile.close();
	}
}