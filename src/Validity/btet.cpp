#include "btet.h"
namespace CABT
{
	void tet2::calc_sampling_jacobi_det(scalar t, mat20_4& cof)
	{
		auto& o3tensor2vec = constant_data->o3tensor2vec;
		auto& o2tensor2vec = constant_data->o2tensor2vec;
		mat3_20 knot;
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
			for (int j = 0; j < 4; ++j)
			{
				dprint(i, j, cof(i, j).inf(), cof(i, j).sup());
			}
		}
			for (int i = 0; i < 20; ++i)
		{
			/*cof(i, 1) = -5.5 * cof(i, 0) + 9 * cof(i, 1) - 4.5 * cof(i, 2) + cof(i, 3);
			cof(i, 2) = 9 * cof(i, 0) - 22.5 * cof(i, 1) + 18 * cof(i, 2) - 4.5 * cof(i, 3);
			cof(i, 3) = -4.5 * cof(i, 0) + 13.5 * cof(i, 1) - 13.5 * cof(i, 2) + 4.5 * cof(i, 3);*/
			//!!!!!!!!!!!!!!!!!!!!!
			//! !!!!!!!!!!!!!!!!!!!!!
			//! !!!!!!!!!!!!!!!!!!!!!!
			//scalar(-9)/scalar(2) may be equalize to int(9)/int(2) ???????
			//!!!!!!!!!!!!!!!
			//cof(i, 0) -> be itself
			scalar cofi1 = scalar(-11) / scalar(2) * cof(i, 0) + scalar(9) * cof(i, 1) - scalar(9) / scalar(2) * cof(i, 2) + cof(i, 3);
			scalar cofi2 = scalar(9) * cof(i, 0) - scalar(45) / scalar(2) * cof(i, 1) + scalar(18) * cof(i, 2) - scalar(9) / scalar(2) * cof(i, 3);
			scalar cofi3 = scalar(-9) / scalar(2) * cof(i, 0) + scalar(27) / scalar(2) * cof(i, 1) - scalar(27) / scalar(2) * cof(i, 2)
				+ scalar(9) / scalar(2) * cof(i, 3);
			cof(i, 1) = cofi1 / t; cof(i, 2) = cofi2 / (t * t); cof(i, 3) = cofi3 / (t * t * t);
		}
	}

	//bool tet2::calc_cubic_root_with_cardano(scalar a, scalar b, scalar c, scalar d, scalar& time)
	//{
	//	a = a.inf(); b = b.inf(); c = c.inf(); d = d.inf();
	//	scalar toi = time;
	//	//this is a function to be implemented which returns cubic root of a Interval_nt
	//	auto sqrt3 = [&](scalar c) { return c; };
	//	auto sqrtcomplex3 = [&](std::complex<scalar> c) { return c; };
	//	if (a.inf() == 0)
	//	{
	//		if (b.inf() == 0)
	//		{
	//			if (c.inf() >= 0)
	//			{
	//				return false;
	//			}
	//			else
	//			{
	//				scalar t = -d / c;
	//				if (t.inf() < toi.inf())
	//				{
	//					time = t.inf(); return true;
	//				}
	//			}
	//		}
	//		else
	//		{
	//			scalar delta = c * c - 4 * b * d;
	//			if (delta.inf() >= 0)
	//			{
	//				delta = CGAL::sqrt(delta);
	//				scalar x0 = (-c - delta) / (2 * b);
	//				scalar x1 = (-c + delta) / (2 * b);
	//				if ((x0.inf() < 0 && 0 < x0.sup()) || (x1.inf() < 0 && 0 < x0.sup()))
	//				{
	//					time = scalar(0); return true;
	//				}
	//				if ((x0.sup() < 0 || x0.inf() > toi.inf()) && (x1.sup() < 0 || x1.inf() > toi.inf()))
	//				{
	//					return false;
	//				}
	//				if (x0.inf() > 0 && x0.inf() < toi.inf())
	//				{
	//					toi = x0.inf();
	//				}
	//				if (x1.inf() > 0 && x1.inf() < toi.inf())
	//				{
	//					toi = x1.inf();
	//				}
	//				time = toi.inf(); return true;
	//			}
	//		}
	//	}
	//	else
	//	{
	//		scalar p = c / a - b * b / (3 * a * a);
	//		scalar q = d / a - b * c / (3 * a * a) + 2 * b * b * b / (27 * a * a * a);
	//		scalar delta = q * q / 4 + p * p * p / 27;
	//		if (delta.inf() > 0)
	//		{
	//			delta = CGAL::sqrt(delta);
	//			scalar x = sqrt3(-q / 2 + delta) + sqrt3(-q / 2 - delta);
	//			if (x.inf() > 0 && x.inf() < toi.inf())
	//			{
	//				time = x.inf(); return true;
	//			}
	//			if (x.inf() < 0 && 0 < x.sup())
	//			{
	//				time = scalar(0); return true;
	//			}
	//			return false;
	//		}
	//		else if (delta.sup() < 0)
	//		{
	//			delta = CGAL::sqrt(-delta);
	//			std::complex<scalar> element(-q / 2, delta);
	//			element = sqrtcomplex3(element);
	//			scalar x0 = 2 * element.real();
	//			scalar x1 = -element.real() - CGAL::sqrt(scalar(3)) * element.imag();
	//			scalar x2 = -element.real() + CGAL::sqrt(scalar(3)) * element.imag();
	//		}
	//	}
	//}

	void tet2::newton_raphson(scalar a, scalar b, scalar c, scalar d, scalar time, scalar dif, scalar& toi, scalar elp)
	{
		auto eval = [&](scalar& x) { return a * x * x * x + b * x * x + c * x + d; };
		while (true)
		{
			scalar ftoi = eval(toi);
			if (ftoi.inf() < elp || toi.inf() > time.inf())
				break;
			toi = (toi - eval(toi) / dif).inf();
		}
	}

	void tet2::search_cubic_root(scalar a, scalar b, scalar c, scalar d, scalar& time, message& mes, bool if_calc_root)
	{
		a = a.inf(); b = b.inf(); c = c.inf(); d = d.inf();

		//STEP 1
		//test if there is negative jacobian when t==0
		if (d.inf() <= 0)
		{
			dprint("negative jacobian when t==0");
			mes = InvalidInit;
			return;
		}

		//STEP 2
		//filter because most of those tets are positive all the time
		//Reference: Penetration-free Projective Dynamics on the GPU
		auto eval = [&](scalar& x) { return a * x * x * x + b * x * x + c * x + d; };
		auto difeval = [&](scalar& x) { return 3 * a * x * x + 2 * b * x + c; };
		if (a.inf() > 0)
		{
			scalar delta = b * b - 3 * a * c;
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
				scalar x0 = (-b - delta) / (3 * a);
				scalar x1 = (-b + delta) / (3 * a);
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
					else
					{
						//newton_raphson
						scalar toi = x0.inf();
						if (if_calc_root)
						{
							newton_raphson(a, b, c, d, time, difeval(-b / (3 * a)), toi, elp);
						}
						mes = Collision;
					}
				}
			}
		}
		else if (a.inf() == 0)
		{
			if (b.inf() == 0)
			{
				if (c.inf() == 0)
				{
					mes = NoCollision;
				}
				else
				{
					scalar toi = -d / c;
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
					scalar toi = time.inf();
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
			scalar delta = b * b - 3 * a * c;
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
				scalar x0 = (-b + delta) / (3 * a);
				scalar x1 = (-b - delta) / (3 * a);
				scalar fx0 = eval(x0);
				if (fx0.inf() > 0)
				{
					//newton raphson
					scalar toi = x0.inf();
					if (if_calc_root)
					{
						newton_raphson(a, b, c, d, time, difeval(time).inf(), toi, elp);
					}
					mes = Collision;
				}
				else
				{
					//newton raphson
					scalar toi = x0.inf();
					if (if_calc_root)
					{
						newton_raphson(a, b, c, d, time, difeval(scalar(0)).inf(), toi, elp);
					}
					mes = Collision;
				}
			}
		}
	
	}

	void tet2::tet_status(mat20_4& cof, scalar &time, message &mes, bool if_calc_root)
	{
		//if no root in (0, time) return false;
		//else set time = the min root t, and return true;
		scalar primal_time = time;
		message mes_ = NoCollision;
		mes = NoCollision;
		for (int i = 0; i < 20; ++i)
		{
			search_cubic_root(cof(3, i), cof(2, i), cof(1, i), cof(0, i), time, mes_, if_calc_root);
			if (mes_ > Collision)
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
		}
	}

	void tet2::get_min_time(mat20_4 &cof, scalar &time)
	{
		message mes;
		sub_tree->tree_cof[0][0] = cof;
		tet_status(cof, time, mes, false);
		if (mes == NoCollision)
		{
			dprint("yesssssss");
			return;
		}
		int index[4] = { 1,8,64,256 };
		for (int i = 1; i < 4; ++i)
		{
			bool flag = false;
			for (int j = 0; j < index[i]; ++j)
			{
				sub_tree->tree_cof[i][j] = constant_data->son_transform[j % 8] * sub_tree->tree_cof[i - 1][j / 8];
				tet_status(sub_tree->tree_cof[i][j], time, mes, i == 3 ? true : false);
				if (mes == Collision)
				{
					flag = true;
				}
			}
			if (!flag)
			{
				break;
			}
		}
	}
	/*
	
	void tet2::cardano(complex<double> a, complex<double> b, complex<double> c, complex<double>d, complex<double>& x1, complex<double>& x2, complex<double>& x3)
	{
		complex<double> u = (9.0 * a * b * c - 27.0 * a * a * d - 2.0 * b * b * b) / (54.0 * a * a * a);
		complex<double> v = sqrt(3.0 * (4.0 * a * c * c * c - b * b * c * c - 18.0 * a * b * c * d + 27.0 * a * a * d * d + 4.0 * b * b * b * d)) / (18.0 * a * a);

		complex<double> m;
		if (norm(u + v) >= norm(u - v))
		{
			m = pow(u + v, 1.0 / 3.0);
		}
		else
		{
			m = pow(u - v, 1.0 / 3.0);
		}

		complex<double> n;
		if (norm(m) != 0)
		{
			n = (b * b - 3.0 * a * c) / (9.0 * a * a * m);
		}
		else
		{
			n = 0;
		}

		complex<double> omega1 = complex<double>(-0.5, sqrt(3.0) / 2.0);
		complex<double> omega2 = complex<double>(-0.5, -sqrt(3.0) / 2.0);

		x1 = m + n - b / (3.0 * a);
		x2 = omega1 * m + omega2 * n - b / (3.0 * a);
		x3 = omega2 * m + omega1 * n - b / (3.0 * a);
	}*/
}