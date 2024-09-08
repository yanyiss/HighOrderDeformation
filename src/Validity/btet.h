#pragma once
#include "..\src\MeshViewer\MeshDefinition.h"
#include "scalar_def.h"
#include "constant_data.h"
#include "dprint.h"
#include <Eigen/Core>
namespace CABT
{
#if 1
	template <int order, int sample_num, typename ConstantData>
	class detector
	{
	public:
		detector() {}
		virtual ~detector() {}
	public:
		int M = (order + 1) * (order + 2) * (order + 3) / 6;
		int N = (order + 2) * (order + 3) * (order + 4) / 6;
		typedef Eigen::Matrix<scalar, 3, (order + 1)* (order + 2)* (order + 3) / 6> mat3m;
		typedef Eigen::Matrix<scalar, 3, (order + 2)* (order + 3)* (order + 4) / 6> mat3n;
		typedef Eigen::Matrix<scalar, (order + 2)* (order + 3)* (order + 4) / 6, 4> matn4;
		typedef Eigen::Matrix<scalar, (order + 2)* (order + 3)* (order + 4) / 6, sample_num> matns;
		

		mat3m control_val;
		mat3m control_dir;
		ConstantData* constant_data = nullptr;


		void calc_sampling_jacobi_det(scalar t, matn4& cof)
		{
			auto& omtensor2vec = constant_data->omtensor2vec;
			auto& ontensor2vec = constant_data->ontensor2vec;
			mat3n knot;
			knot.setConstant(-1);
			scalar inverse = scalar(1) / scalar(order + 1);
			for (int i = 0; i < order + 2; ++i)
			{
				for (int j = 0; j < order + 2 - i; ++j)
				{
					for (int k = 0; k < order + 2 - i - j; ++k)
					{
						knot(0, ontensor2vec(i, j, k)) = scalar(i) * inverse;
						knot(1, ontensor2vec(i, j, k)) = scalar(j) * inverse;
						knot(2, ontensor2vec(i, j, k)) = scalar(k) * inverse;
					}
				}
			}
			mat3_3 jacobi;
			switch (order)
			{
			case 2:
			{
				mat3m val;
				int id4ijk;
				scalar x;
				for (int n = 0; n < 4; ++n)
				{
					val = control_val + scalar(n) / scalar(3) * t * control_dir;
					for (int i = 0; i < order + 2; ++i)
					{
						for (int j = 0; j < order + 2 - i; ++j)
						{
							for (int k = 0; k < order + 2 - i - j; ++k)
							{
								id4ijk = ontensor2vec(i, j, k);
								x = 1.0 - knot(0, id4ijk) - knot(1, id4ijk) - knot(2, id4ijk);
								jacobi.col(0) = 2.0 *
									((val.col(omtensor2vec(1, 0, 0)) - val.col(omtensor2vec(0, 0, 0))) * x
										+ (val.col(omtensor2vec(2, 0, 0)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk)
										+ (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk)
										+ (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
								jacobi.col(1) = 2.0 *
									((val.col(omtensor2vec(0, 1, 0)) - val.col(omtensor2vec(0, 0, 0))) * x
										+ (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk)
										+ (val.col(omtensor2vec(0, 2, 0)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk)
										+ (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
								jacobi.col(2) = 2.0 *
									((val.col(omtensor2vec(0, 0, 1)) - val.col(omtensor2vec(0, 0, 0))) * x
										+ (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk)
										+ (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk)
										+ (val.col(omtensor2vec(0, 0, 2)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
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
			}
			break;
			case 3:
			{
				mat3m val;
				int id4ijk;
				scalar u, v, w, x;
				for (int n = 0; n < 4; ++n)
				{
					val = control_val + scalar(n) / scalar(3) * t * control_dir;
					for (int i = 0; i < order + 2; ++i)
					{
						for (int j = 0; j < order + 2 - i; ++j)
						{
							for (int k = 0; k < order + 2 - i - j; ++k)
							{
								id4ijk = ontensor2vec(i, j, k);
								u = knot(0, id4ijk);
								v = knot(1, id4ijk);
								w = knot(2, id4ijk);
								x = 1.0 - knot(0, id4ijk) - knot(1, id4ijk) - knot(2, id4ijk);
								jacobi.col(0) = 3.0 *
									((val.col(omtensor2vec(1, 0, 0)) - val.col(omtensor2vec(0, 0, 0))) * x * x
										+ (val.col(omtensor2vec(2, 0, 0)) - val.col(omtensor2vec(1, 0, 0))) * u * x
										+ (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(0, 1, 0))) * v * x
										+ (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(0, 0, 1))) * w * x
										+ (val.col(omtensor2vec(2, 1, 0)) - val.col(omtensor2vec(1, 1, 0))) * u * v
										+ (val.col(omtensor2vec(2, 0, 1)) - val.col(omtensor2vec(1, 0, 1))) * u * w
										+ (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(0, 1, 1))) * v * w
										+ (val.col(omtensor2vec(3, 0, 0)) - val.col(omtensor2vec(2, 0, 0))) * u * u
										+ (val.col(omtensor2vec(1, 2, 0)) - val.col(omtensor2vec(0, 2, 0))) * v * v
										+ (val.col(omtensor2vec(1, 0, 2)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
								jacobi.col(1) = 3.0 *
									((val.col(omtensor2vec(0, 1, 0)) - val.col(omtensor2vec(0, 0, 0))) * x * x
										+ (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(1, 0, 0))) * u * x
										+ (val.col(omtensor2vec(0, 2, 0)) - val.col(omtensor2vec(0, 1, 0))) * v * x
										+ (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 0, 1))) * w * x
										+ (val.col(omtensor2vec(1, 2, 0)) - val.col(omtensor2vec(1, 1, 0))) * u * v
										+ (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(1, 0, 1))) * u * w
										+ (val.col(omtensor2vec(0, 2, 1)) - val.col(omtensor2vec(0, 1, 1))) * v * w
										+ (val.col(omtensor2vec(2, 1, 0)) - val.col(omtensor2vec(2, 0, 0))) * u * u
										+ (val.col(omtensor2vec(0, 3, 0)) - val.col(omtensor2vec(0, 2, 0))) * v * v
										+ (val.col(omtensor2vec(0, 1, 2)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
								jacobi.col(2) = 3.0 *
									((val.col(omtensor2vec(0, 0, 1)) - val.col(omtensor2vec(0, 0, 0))) * x * x
										+ (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(1, 0, 0))) * u * x
										+ (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 1, 0))) * v * x
										+ (val.col(omtensor2vec(0, 0, 2)) - val.col(omtensor2vec(0, 0, 1))) * w * x
										+ (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(1, 1, 0))) * u * v
										+ (val.col(omtensor2vec(1, 0, 2)) - val.col(omtensor2vec(1, 0, 1))) * u * w
										+ (val.col(omtensor2vec(0, 1, 2)) - val.col(omtensor2vec(0, 1, 1))) * v * w
										+ (val.col(omtensor2vec(2, 0, 1)) - val.col(omtensor2vec(2, 0, 0))) * u * u
										+ (val.col(omtensor2vec(0, 2, 1)) - val.col(omtensor2vec(0, 2, 0))) * v * v
										+ (val.col(omtensor2vec(0, 0, 3)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
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
			}
			break;
			default:
				dprint("order can only be 2 or 3");
				exit(0);
				break;
			}

		}

		scalar compute_jacobidet(scalar& time)
		{
			matn4 cof;
			calc_sampling_jacobi_det(scalar(time.inf()), cof);
			scalar t0 = cof.minCoeff();
			scalar t1 = (constant_data->transform * cof).minCoeff();
			dprint("min det:", t0, t1);
#if 1
			if (t0.inf() < 0)
			{
				write_bug();
				system("pause");
			}
#endif
			return t0;
		}

		void write_bug()
		{
			std::ofstream outFile("C:\\Git Code\\HighOrderDeformation\\src\\info.txt", std::ios::binary);
			std::setprecision(15);
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < M; ++j)
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
				for (int j = 0; j < M; ++j)
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
	};

    template <int order, int sample_num, typename ConstantData, typename SubTree>
    class tet_detector : public detector<order, sample_num, ConstantData>
    {
    public:
        tet_detector() {}
        ~tet_detector() {}
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        enum message
        {
            NoCollision,      // there is no collision in (0, time)
            Collision,        // there is an explicit and exact collision in (0, time)
            NumericalFailure, // there is a collision but the time is not exact because of numerical problems
            InitCollision     // the initial closure has collision
        };


        scalar elp = scalar(1e-4, 1e-4);
        int subdivision_times = 3;
		SubTree* sub_tree = nullptr;

		void init(mat3m& val, mat3m& dir, ConstantData* constant_data_, SubTree* sub_tree_)
		{
			control_val = std::move(val); control_dir = std::move(dir); constant_data = constant_data_; sub_tree = sub_tree_;
		}

        void newton_raphson(const vec4s& cubic_cof, scalar time, scalar dif, scalar& toi, scalar elp)
        {
            auto eval = [&](scalar& x) {return cubic_cof(0) + x * (cubic_cof(1) + x * (cubic_cof(2) + x * cubic_cof(3))); };
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
            }
        }

        void search_cubic_root(const vec4s& cubic_cof, scalar& time, message& mes)
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
						else if (time.sup() < x1.inf() && eval(time).inf() > 0)
						{
							mes = NoCollision;
						}
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
						else if (eval(time).inf() > 0)
						{
							mes = NoCollision;
						}
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
						else if (eval(time) > 0)
						{
							mes = NoCollision;
						}
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

		void tet_status(matn4& cof, scalar& time, message& mes)
		{
			message mes_ = NoCollision;
			mes = NoCollision;
			for (int i = 0; i < N; ++i)
			{
				search_cubic_root(cof.row(i), time, mes_);
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
		}

		void get_min_time_recursion(int level, int count, scalar& time)
		{
			if (level >= subdivision_times) return;
			level += 1;
			count *= 8;
			for (int i = 0; i < 8; ++i)
			{
				/*dprint(level, count, i);
				dprint(sub_tree->tree_cof[level][count].rows(), sub_tree->tree_cof[level][count].cols());
				dprint(constant_data->son_transform[i].rows(), constant_data->son_transform[i].cols());
				dprint(sub_tree->tree_cof[level - 1][count / 8].rows(), sub_tree->tree_cof[level - 1][count / 8].cols());
				dprint(constant_data->son_transform[i] * sub_tree->tree_cof[level - 1][count / 8]);*/
				sub_tree->tree_cof[level][count] = constant_data->son_transform[i] * sub_tree->tree_cof[level - 1][count / 8];
				message mes = InitCollision;
				tet_status(sub_tree->tree_cof[level][count], time, mes);
				if (mes == InitCollision) { dprint("InitCollision"); exit(0); }
				else if (mes == Collision) { get_min_time_recursion(level, count, time); }
				++count;
			}
		}

		void run(scalar& time)
		{
			matn4 cof;
			calc_sampling_jacobi_det(time, cof);
			for (int i = 0; i < N; ++i)
			{
				if (cof(i, 0).inf() < 0)
				{
					dprint("flipping occurs in the initialization");
					system("pause");
				}
			}

			//Lagrange cofficients ---> Bernstein cofficients
			cof = constant_data->transform * cof * constant_data->time_transform;
			cof.col(1) /= time;
			cof.col(2) /= time * time;
			cof.col(3) /= time * time * time;
			sub_tree->tree_cof[0][0] = std::move(cof);

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
        
    };

	typedef tet_detector<2, 4, tet2_constant_data, subdivide_tree<mat20_4>> tet2;
	typedef tet_detector<3, 100, tet3_constant_data, subdivide_tree<mat35_4>> tet3;
    
#else
    class tet_detector
    {
    public:
        tet_detector(){}
        virtual ~tet_detector() {}

    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        enum message
        {
            NoCollision,      // there is no collision in (0, time)
            Collision,        // there is an explicit and exact collision in (0, time)
            NumericalFailure, // there is a collision but the time is not exact because of numerical problems
            InitCollision     // the initial closure has collision
        };
        scalar elp = scalar(1e-4, 1e-4);
        void newton_raphson(const vec4s& cubic_cof, scalar time, scalar dif, scalar& val, scalar elp);
        void search_cubic_root(const vec4s& cubic_cof, scalar& time, message& mes);  
        virtual void write_bug() = 0;


    };

    class tet2 : public tet_detector
    {
    public:
        tet2() { }
        ~tet2() { }


    public:
		int subdivision_times = 3;
		tet2_constant_data* constant_data = nullptr;
		subdivide_tree<mat20_4>* sub_tree = nullptr;
        mat3_10 control_val;
        mat3_10 control_dir;
        void init(mat3_10& val, mat3_10& dir, tet2_constant_data* constant_data_, subdivide_tree<mat20_4>* sub_tree_)
        {
            control_val = std::move(val); control_dir = std::move(dir); constant_data = constant_data_; sub_tree = sub_tree_;
        }
        void calc_sampling_jacobi_det(scalar t, mat20_4 &cof);
        //void cardano(complex<double> a, complex<double> b, complex<double> c, complex<double>d, complex<double>& x1, complex<double>& x2, complex<double>& x3);
       // void calc_cubic_root_with_cardano(scalar a, scalar b, scalar c, scalar d, scalar& time);
        void tet_status(mat20_4& cof, scalar& time, message& mes);
        void get_min_time_recursion(int level, int count, scalar& time);
        void run(scalar& time);
        scalar compute_jacobidet(scalar& time);
        void write_bug();
    };
    
    class tet3 : public tet_detector
    {
    public:
        tet3() { }
        ~tet3() { }


    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        int subdivision_times = 3;
        tet3_constant_data* constant_data = nullptr;
        subdivide_tree<mat35_4>* sub_tree = nullptr;
        mat3_20 control_val;
        mat3_20 control_dir;
        void init(mat3_20& val, mat3_20& dir, tet3_constant_data* constant_data_, subdivide_tree<mat35_4>* sub_tree_)
        {
            control_val = std::move(val); control_dir = std::move(dir); constant_data = constant_data_; sub_tree = sub_tree_;
        }
        void calc_sampling_jacobi_det(scalar t, mat35_4& cof);
        void tet_status(mat35_4& cof, scalar& time, message& mes);
        void get_min_time_recursion(int level, int count, scalar& time);
        void run(scalar& time);
        scalar compute_jacobidet(scalar& time);
        void write_bug();
    };
#endif
}