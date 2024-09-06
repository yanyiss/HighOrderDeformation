#include "btet.h"
namespace CABT
{
	void tet2::calc_sampling_jacobi_det(scalar t, mat20_4& cof)
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
		cof = constant_data->transform * cof * constant_data->time_transform;
		cof.col(1) /= t;
		cof.col(2) /= t * t;
		cof.col(3) /= t * t * t;
	}

	void tet2::newton_raphson(const vec4s& cubic_cof, scalar time, scalar dif, scalar& toi, scalar elp)
	{
		//auto eval = [&](scalar& x) { return  cubic_cof(3) * x * x * x + cubic_cof(2) * x * x + cubic_cof(1) * x + cubic_cof(0); };
		auto eval = [&](scalar& x) {return cubic_cof(0) + x * (cubic_cof(1) + x * (cubic_cof(2) + x * cubic_cof(3))); };
		/*static int t0 = 0;
		static int t1 = 0;
		++t0;*/
		while (true)
		{
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
			//++t1;
		}
		/*if (t0 % 10000 == 0)
		{
			dprint(t0, t1);
		}*/
	}

#define aa 1
	void tet2::search_cubic_root(const vec4s& cubic_cof, scalar& time, message& mes)
	{
		vec4s abcd;
		for (int i = 0; i < 4; ++i) { abcd(i) = cubic_cof(i).inf(); }
		scalar& a = abcd(3); scalar& b = abcd(2); scalar& c = abcd(1); scalar& d = abcd(0);

		//STEP 1
		//test if there is negative cofficient when t==0
		if (d.inf() <= 0)
		{
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
					mes = NoCollision;
				}
				else
				{
					if (x1.sup() < 0)
					{
						mes = NoCollision;
					}
#if aa
					else if (time.sup() < x1.inf() && eval(time).inf() > 0)
					{
						mes = NoCollision;
					}
#endif
					else
					{
						//newton_raphson
						toi = x0.inf() > 0 ? x0.inf() : 0;
						newton_raphson(abcd, time, difeval(-b / (scalar(3) * a)), toi, elp);
						time = toi;
						mes = Collision;
					}
				}
			}
		}
		else if (a.inf() == 0)
		{
			dprint("there is a.inf() == 0 !!!!!!!!!");
			write_bug();
			exit(0);
			if (b.inf() == 0)
			{
				if (c.inf() >= 0)
				{
					mes = NoCollision;
				}
				else
				{
					toi = -d / c;
					if (toi.inf() < time.inf())
					{
						time = toi.inf(); 
						mes = Collision;
					}
				}
			}
			else
			{
				scalar delta = c * c - 4 * b * d;
				if (delta.sup() < 0)
				{
					mes = NoCollision;
				}
				else
				{
					if (delta.inf() < 0)
					{
						delta = scalar(0, delta.sup());
					}
					delta = CGAL::sqrt(delta);
					scalar x0 = (-c + delta) / (2 * b);
					scalar x1 = (-c - delta) / (2 * b);
					toi = time.inf();
					if ((x0.sup() < 0 || x0.inf() > toi.inf()) && (x1.sup() < 0 || x1.inf() > toi.inf()))
					{
						mes = NoCollision;
					}
					else if ((x0.inf() < 0 && 0 < x0.sup()) || (x1.inf() < 0 && 0 < x1.sup()))
					{
						mes = NumericalFailure;

					}
					else
					{
						if (x0.inf() > 0 && x0.inf() < toi.inf())
						{
							toi = x0.inf();
						}
						if (x1.inf() > 0 && x1.inf() < toi.inf())
						{
							toi = x1.inf();
						}
						time = toi.inf();
						mes = Collision;
					}
				}
			}
		}
		else // a.inf() < 0
		{
			scalar delta = b * b - scalar(3) * a * c;
			if (delta.sup() < 0)
			{
				if (eval(time).inf() > 0)
				{
					mes = NoCollision;
				}
				else
				{
					toi = scalar(0);
					newton_raphson(abcd, time, std::min(difeval(scalar(0)).inf(), difeval(time).inf()),
						toi, elp);
					time = toi;
					mes = Collision;
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
					if (time.inf() < x1.sup())
					{
						mes = NoCollision;
					}
#if aa
					else if (eval(time).inf() > 0)
					{
						mes = NoCollision;
					}
#endif
					else
					{
						//newton raphson
						toi = x1.inf() > 0 ? x1.inf() : 0;
						newton_raphson(abcd, time, difeval(time).inf(), toi, elp);
						time = toi;
						mes = Collision;
					}
				}
				else
				{
					//newton raphson
					if (0 < x0.inf())
					{
						if (time.sup() < x0.inf() && eval(time).inf() > 0)
						{
							mes = NoCollision;
						}
						else
						{
							toi = scalar(0);
							newton_raphson(abcd, time, difeval(scalar(0)).inf(), toi, elp);
							time = toi;
							mes = Collision;
						}
					}
#if aa
					else if (eval(time) > 0)
					{
						mes = NoCollision;
					}
#endif
					else
					{
						toi = scalar(0);
						newton_raphson(abcd, time, difeval(2 * x1 - x0).inf(), toi, elp);
						time = toi;
						mes = Collision;
					}
				}
			}
		}
	
	}

	void tet2::tet_status(mat20_4& cof, scalar& time, message& mes)
	{
		//if no root in (0, time) return false;
		//else set time = the min root t, and return true;
		message mes_ = NoCollision;
		//static int tgg = 0;
		mes = NoCollision;
		for (int i = 0; i < 20; ++i)
		{
			//++tgg;
			search_cubic_root(cof.row(i), time, mes_);
			auto eval = [&](scalar& a, scalar& b, scalar& c, scalar& d, scalar& x) { return a * x * x * x + b * x * x + c * x + d; };
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
			}
			else if (mes_ == InitCollision)
			{
				break;
			}
		}
		/*if (tgg  == 0)
		{
			dprint("tgg", tgg);
		}*/
	}

	void tet2::get_min_time_recursion(int level, int count, scalar& time)
	{
		dprint(level, count);
		//subdivision_times = 3;
		if (level >= subdivision_times)
			return;
		level += 1;
		count *= 8;
		dprint("******************");
		for (int i = 0; i < 8; ++i)
		{
			//dprint(level, count, i);
			sub_tree->tree_cof[level][count] = constant_data->son_transform[i] * sub_tree->tree_cof[level - 1][count / 8];
			message mes = InitCollision;
			tet_status(sub_tree->tree_cof[level][count], time, mes);
			if (mes == InitCollision) { dprint("InitCollision"); exit(0); }
			else if (mes == Collision)
			{
				get_min_time_recursion(level, count, time);
			}
			++count;
		}
	}

	void tet2::run(scalar& time)
	{
		//sub_tree->tree_cof[0][0].setConstant(scalar(1.0));
		calc_sampling_jacobi_det(time, sub_tree->tree_cof[0][0]);

		message mes(Collision);
		tet_status(sub_tree->tree_cof[0][0], time, mes);
		if (mes == InitCollision)
		{
			dprint("InitCollision");
			exit(0);
		}
		else if (mes == Collision)
		{
			get_min_time_recursion(0, 0, time);
		}
	}

	scalar tet2::compute_jacobidet(scalar& time)
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
		//time=scalar(0.437);
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
			//dprint(n, sample_det0.minCoeff(), sample_det1.minCoeff());


			//dprint("every of det");
			//for (int i = 0; i < 8; ++i)
			//{
			//	auto d0 = constant_data->son_transform[i] * det;
			//	min_son[0] = d0.minCoeff();
			//	for (int j = 0; j < 8; ++j)
			//	{
			//		auto d1 = constant_data->son_transform[j] * d0;
			//		//for (int k = 0; k < 20; ++k)
			//		//{
			//		//	//dprint(k, d1(k));
			//		//	if (d1(k).inf() < 0)
			//		//	{
			//		//		dprint(i, j);
			//		//		break;
			//		//	}
			//		//}
			//		min_son[1] = d1.minCoeff();
			//		for (int k = 0; k < 8; ++k)
			//		{
			//			auto d2 = constant_data->son_transform[k] * d1;
			//			for (int l = 0; l < 20; ++l)
			//			{
			//				if (d2(l).is_same(sub_tree->tree_cof[3][k + j * 8 + i * 64](l, 3)))
			//				{
			//					int p = 0;
			//				}
			//				/*if (i == 0 && j == 0 && k == 0)
			//				{
			//					dprint(l, d2(l));
			//				}*/
			//				//dprint(k, d1(k));
			//				if (d2(l).inf() < 0)
			//				{
			//					dprint(i, j, k);
			//					break;
			//				}
			//			}
			//			min_son[2] = d2.minCoeff();
			//			//for (int l = 0; l < 8; ++l)
			//			//{
			//			//	auto d3 = constant_data->son_transform[l] * d2;
			//			//	//for (int ls = 0; ls < 20; ++ls)
			//			//	//{
			//			//	//	//dprint(k, d1(k));
			//			//	//	if (d3(ls).inf() < 0)
			//			//	//	{
			//			//	//		dprint(i, j, k, l);
			//			//	//		break;
			//			//	//	}
			//			//	//}
			//			//	min_son[3] = d3.minCoeff();
			//			//}
			//		}
			//	}
			//}
		}
		//dprint("min_son", min_son[0],min_son[1],min_son[2],min_son[3]);

		//sample_det0 > 0 is neccesary
		//sample_det1 > 0 is sufficient
		dprint("min and max det", sample_det0.minCoeff(), sample_det1.minCoeff());
		if (sample_det0.minCoeff() < 0)
		{
			//system("pause");
		}
#if 0
		if (sample_det0.minCoeff() < 0)
		{
			write_bug();
			system("pause");
		}
#endif
		return sample_det1.minCoeff();
	}

	void tet2::write_bug()
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