#pragma once
#include "scalar_def.hpp"
#include "constant_data.hpp"
#include "btet.hpp"
#include "dprint.hpp"
#include <Eigen/Core>
#include <queue>
namespace CABT
{
#if 1
	template <int order, typename ConstantData>
	class hocgv_detector// : public detector<order, ConstantData>
	{
	public:
		hocgv_detector() {}
		~hocgv_detector() {}

	public:
#pragma region detector
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
		int dif_order = 3 * order - 3;
		int M = (order + 1) * (order + 2) * (order + 3) / 6;
		int N = order * (3 * order - 1) * (3 * order - 2) / 2;
		typedef Eigen::Matrix<scalar, 3, (order + 1)* (order + 2)* (order + 3) / 6> mat3m;
		typedef Eigen::Matrix<scalar, 3, order* (3 * order - 1)* (3 * order - 2) / 2> mat3n;
		typedef Eigen::Matrix<scalar, order* (3 * order - 1)* (3 * order - 2) / 2, 4> matn4;

		enum subdivision_mode
		{
			bisect,
			quadtrisect,
			octasect
		};
		subdivision_mode mode = octasect;

		mat3m control_val;
		mat3m control_dir;
		ConstantData *constant_data = nullptr;

		void calc_sampling_jacobi_det(scalar t, matn4& cof)
		{
			auto& omtensor2vec = constant_data->omtensor2vec;
			auto& ontensor2vec = constant_data->ontensor2vec;
			mat3n knot;
			knot.setConstant(-1);
			scalar inverse = scalar(1) / scalar(dif_order);
			for (int i = 0; i <= dif_order; ++i)
			{
				for (int j = 0; j <= dif_order - i; ++j)
				{
					for (int k = 0; k <= dif_order - i - j; ++k)
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
					for (int i = 0; i <= 3; ++i)
					{
						for (int j = 0; j <= 3 - i; ++j)
						{
							for (int k = 0; k <= 3 - i - j; ++k)
							{
								id4ijk = ontensor2vec(i, j, k);
								x = 1.0 - knot(0, id4ijk) - knot(1, id4ijk) - knot(2, id4ijk);
								jacobi.col(0) = 2.0 * ((val.col(omtensor2vec(1, 0, 0)) - val.col(omtensor2vec(0, 0, 0))) * x + (val.col(omtensor2vec(2, 0, 0)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk) + (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk) + (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
								jacobi.col(1) = 2.0 * ((val.col(omtensor2vec(0, 1, 0)) - val.col(omtensor2vec(0, 0, 0))) * x + (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk) + (val.col(omtensor2vec(0, 2, 0)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk) + (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
								jacobi.col(2) = 2.0 * ((val.col(omtensor2vec(0, 0, 1)) - val.col(omtensor2vec(0, 0, 0))) * x + (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk) + (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk) + (val.col(omtensor2vec(0, 0, 2)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
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
				int ii, jj, kk, ll;
				int n_1 = 5;
				int fractorize[6] = { 1,1,2,6,24,120 };
				auto scalar_power = [&](scalar& s, int power)
					{
						switch (power)
						{
						case 0:
							return scalar(1);
						case 1:
							return s;
						case 2:
							return s * s;
						case 3:
							return s * s * s;
						case 4:
							return s * s * s * s;
						case 5:
							return s * s * s * s * s;
						default:
							dprint("error in power");
							exit(0);
						}
					};
				auto BernEval = [&]()
					{
						return fractorize[n_1] / (fractorize[ii] * fractorize[jj] * fractorize[kk] * fractorize[ll]) *
							scalar_power(u, ii) * scalar_power(v, jj) * scalar_power(w, kk) * scalar_power(x, ll);
					};
				auto JacobiEval = [&]()
					{
						jacobi.setZero();
						for (ii = 0; ii <= 5; ++ii)
						{
							for (jj = 0; jj <= 5 - ii; ++jj)
							{
								for (kk = 0; kk <= 5 - ii - jj; ++kk)
								{
									ll = 5 - ii - jj - kk;
									jacobi.col(0) += (val.col(omtensor2vec(ii + 1, jj, kk)) - val.col(omtensor2vec(ii, jj, kk))) * BernEval();
									jacobi.col(1) += (val.col(omtensor2vec(ii, jj + 1, kk)) - val.col(omtensor2vec(ii, jj, kk))) * BernEval();
									jacobi.col(2) += (val.col(omtensor2vec(ii, jj, kk + 1)) - val.col(omtensor2vec(ii, jj, kk))) * BernEval();
								}
							}
						}
						jacobi *= scalar(6.0);
					};
				for (int n = 0; n < 4; ++n)
				{
					val = control_val + scalar(n) / scalar(3) * t * control_dir;
					for (int i = 0; i <= 6; ++i)
					{
						for (int j = 0; j <= 6 - i; ++j)
						{
							for (int k = 0; k <= 6 - i - j; ++k)
							{
								id4ijk = ontensor2vec(i, j, k);
								u = knot(0, id4ijk);
								v = knot(1, id4ijk);
								w = knot(2, id4ijk);
								x = 1.0 - knot(0, id4ijk) - knot(1, id4ijk) - knot(2, id4ijk);
								
								JacobiEval();
								//jacobi.col(0) = 3.0 * ((val.col(omtensor2vec(1, 0, 0)) - val.col(omtensor2vec(0, 0, 0))) * x * x + (val.col(omtensor2vec(2, 0, 0)) - val.col(omtensor2vec(1, 0, 0))) * u * x + (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(0, 1, 0))) * v * x + (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(0, 0, 1))) * w * x + (val.col(omtensor2vec(2, 1, 0)) - val.col(omtensor2vec(1, 1, 0))) * u * v + (val.col(omtensor2vec(2, 0, 1)) - val.col(omtensor2vec(1, 0, 1))) * u * w + (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(0, 1, 1))) * v * w + (val.col(omtensor2vec(3, 0, 0)) - val.col(omtensor2vec(2, 0, 0))) * u * u + (val.col(omtensor2vec(1, 2, 0)) - val.col(omtensor2vec(0, 2, 0))) * v * v + (val.col(omtensor2vec(1, 0, 2)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
								//jacobi.col(1) = 3.0 * ((val.col(omtensor2vec(0, 1, 0)) - val.col(omtensor2vec(0, 0, 0))) * x * x + (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(1, 0, 0))) * u * x + (val.col(omtensor2vec(0, 2, 0)) - val.col(omtensor2vec(0, 1, 0))) * v * x + (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 0, 1))) * w * x + (val.col(omtensor2vec(1, 2, 0)) - val.col(omtensor2vec(1, 1, 0))) * u * v + (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(1, 0, 1))) * u * w + (val.col(omtensor2vec(0, 2, 1)) - val.col(omtensor2vec(0, 1, 1))) * v * w + (val.col(omtensor2vec(2, 1, 0)) - val.col(omtensor2vec(2, 0, 0))) * u * u + (val.col(omtensor2vec(0, 3, 0)) - val.col(omtensor2vec(0, 2, 0))) * v * v + (val.col(omtensor2vec(0, 1, 2)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
								//jacobi.col(2) = 3.0 * ((val.col(omtensor2vec(0, 0, 1)) - val.col(omtensor2vec(0, 0, 0))) * x * x + (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(1, 0, 0))) * u * x + (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 1, 0))) * v * x + (val.col(omtensor2vec(0, 0, 2)) - val.col(omtensor2vec(0, 0, 1))) * w * x + (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(1, 1, 0))) * u * v + (val.col(omtensor2vec(1, 0, 2)) - val.col(omtensor2vec(1, 0, 1))) * u * w + (val.col(omtensor2vec(0, 1, 2)) - val.col(omtensor2vec(0, 1, 1))) * v * w + (val.col(omtensor2vec(2, 0, 1)) - val.col(omtensor2vec(2, 0, 0))) * u * u + (val.col(omtensor2vec(0, 2, 1)) - val.col(omtensor2vec(0, 2, 0))) * v * v + (val.col(omtensor2vec(0, 0, 3)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
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

		scalar compute_jacobidet(scalar &time, int sample_num)
		{
			Eigen::Matrix<scalar, -1, -1> cof;
			cof.resize(N, sample_num);

			auto &omtensor2vec = constant_data->omtensor2vec;
			auto &ontensor2vec = constant_data->ontensor2vec;
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
				for (int n = 0; n < sample_num; ++n)
				{
					val = control_val + scalar(n) / scalar(sample_num - 1) * time * control_dir;
					for (int i = 0; i < order + 2; ++i)
					{
						for (int j = 0; j < order + 2 - i; ++j)
						{
							for (int k = 0; k < order + 2 - i - j; ++k)
							{
								id4ijk = ontensor2vec(i, j, k);
								x = 1.0 - knot(0, id4ijk) - knot(1, id4ijk) - knot(2, id4ijk);
								jacobi.col(0) = 2.0 * ((val.col(omtensor2vec(1, 0, 0)) - val.col(omtensor2vec(0, 0, 0))) * x + (val.col(omtensor2vec(2, 0, 0)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk) + (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk) + (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
								jacobi.col(1) = 2.0 * ((val.col(omtensor2vec(0, 1, 0)) - val.col(omtensor2vec(0, 0, 0))) * x + (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk) + (val.col(omtensor2vec(0, 2, 0)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk) + (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
								jacobi.col(2) = 2.0 * ((val.col(omtensor2vec(0, 0, 1)) - val.col(omtensor2vec(0, 0, 0))) * x + (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(1, 0, 0))) * knot(0, id4ijk) + (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 1, 0))) * knot(1, id4ijk) + (val.col(omtensor2vec(0, 0, 2)) - val.col(omtensor2vec(0, 0, 1))) * knot(2, id4ijk));
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
				for (int n = 0; n < sample_num; ++n)
				{
					val = control_val + scalar(n) / scalar(sample_num - 1) * time * control_dir;
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
								jacobi.col(0) = 3.0 * ((val.col(omtensor2vec(1, 0, 0)) - val.col(omtensor2vec(0, 0, 0))) * x * x + (val.col(omtensor2vec(2, 0, 0)) - val.col(omtensor2vec(1, 0, 0))) * u * x + (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(0, 1, 0))) * v * x + (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(0, 0, 1))) * w * x + (val.col(omtensor2vec(2, 1, 0)) - val.col(omtensor2vec(1, 1, 0))) * u * v + (val.col(omtensor2vec(2, 0, 1)) - val.col(omtensor2vec(1, 0, 1))) * u * w + (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(0, 1, 1))) * v * w + (val.col(omtensor2vec(3, 0, 0)) - val.col(omtensor2vec(2, 0, 0))) * u * u + (val.col(omtensor2vec(1, 2, 0)) - val.col(omtensor2vec(0, 2, 0))) * v * v + (val.col(omtensor2vec(1, 0, 2)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
								jacobi.col(1) = 3.0 * ((val.col(omtensor2vec(0, 1, 0)) - val.col(omtensor2vec(0, 0, 0))) * x * x + (val.col(omtensor2vec(1, 1, 0)) - val.col(omtensor2vec(1, 0, 0))) * u * x + (val.col(omtensor2vec(0, 2, 0)) - val.col(omtensor2vec(0, 1, 0))) * v * x + (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 0, 1))) * w * x + (val.col(omtensor2vec(1, 2, 0)) - val.col(omtensor2vec(1, 1, 0))) * u * v + (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(1, 0, 1))) * u * w + (val.col(omtensor2vec(0, 2, 1)) - val.col(omtensor2vec(0, 1, 1))) * v * w + (val.col(omtensor2vec(2, 1, 0)) - val.col(omtensor2vec(2, 0, 0))) * u * u + (val.col(omtensor2vec(0, 3, 0)) - val.col(omtensor2vec(0, 2, 0))) * v * v + (val.col(omtensor2vec(0, 1, 2)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
								jacobi.col(2) = 3.0 * ((val.col(omtensor2vec(0, 0, 1)) - val.col(omtensor2vec(0, 0, 0))) * x * x + (val.col(omtensor2vec(1, 0, 1)) - val.col(omtensor2vec(1, 0, 0))) * u * x + (val.col(omtensor2vec(0, 1, 1)) - val.col(omtensor2vec(0, 1, 0))) * v * x + (val.col(omtensor2vec(0, 0, 2)) - val.col(omtensor2vec(0, 0, 1))) * w * x + (val.col(omtensor2vec(1, 1, 1)) - val.col(omtensor2vec(1, 1, 0))) * u * v + (val.col(omtensor2vec(1, 0, 2)) - val.col(omtensor2vec(1, 0, 1))) * u * w + (val.col(omtensor2vec(0, 1, 2)) - val.col(omtensor2vec(0, 1, 1))) * v * w + (val.col(omtensor2vec(2, 0, 1)) - val.col(omtensor2vec(2, 0, 0))) * u * u + (val.col(omtensor2vec(0, 2, 1)) - val.col(omtensor2vec(0, 2, 0))) * v * v + (val.col(omtensor2vec(0, 0, 3)) - val.col(omtensor2vec(0, 0, 2))) * w * w);
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

			scalar t0 = cof.minCoeff();
			dprint("min det:", t0);
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
					outFile.write(reinterpret_cast<const char *>(&xinf), sizeof(double));
					outFile.write(reinterpret_cast<const char *>(&xsup), sizeof(double));
					// dprint(i, j, xinf, xsup);
				}
			}
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < M; ++j)
				{
					scalar x = control_dir(i, j);
					double xinf = x.inf();
					double xsup = x.sup();
					outFile.write(reinterpret_cast<const char *>(&xinf), sizeof(double));
					outFile.write(reinterpret_cast<const char *>(&xsup), sizeof(double));
					// dprint(i, j, xinf, xsup);
				}
			}
			outFile.close();
		}
#pragma endregion
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
			sub_tet(int level_, scalar time_interval_, matn4& cof_, int* corner_id)
			{
				level = level_;
				time_interval = time_interval_;
				cof = std::move(cof_);
				inclusion = scalar(cof.minCoeff().inf(),
					std::min({ cof(corner_id[0],0).sup(),cof(corner_id[1],0).sup(),
						cof(corner_id[2],0).sup(),cof(corner_id[3],0).sup(),
						cof(corner_id[0],3).sup(),cof(corner_id[1],3).sup(),
						cof(corner_id[2],3).sup(),cof(corner_id[3],3).sup() }));
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

		double delta = 1e-12;
		int max_subdivide_times = 3;
		std::priority_queue<sub_tet, std::vector<sub_tet>, std::greater<sub_tet>> tet_queue;
		matn4 cof_;

		void init(mat3m& val, mat3m& dir, ConstantData* constant_data_, scalar time = scalar(1))
		{
			control_val = std::move(val); control_dir = std::move(dir); constant_data = constant_data_;
			std::priority_queue<sub_tet, std::vector<sub_tet>, std::greater<sub_tet>> empty_temp;
			tet_queue.swap(empty_temp);
			calc_sampling_jacobi_det(time, cof_);
		}

		void test_regularity(sub_tet& current_tet, message& mes)
		{
			if (current_tet.inclusion.inf() > 0)
				mes = regular;
			else if (current_tet.inclusion.sup() < 0)
				mes = flipped;
			else
				mes = uncertain;
			/*auto& cof = current_tet.cof;
			if (cof.minCoeff().inf() > 0)
				mes = regular;
			else if (cof(0, 0).inf() < 0 || cof(3, 0).inf() < 0 || cof(9, 0).inf() < 0 || cof(19, 0).inf() < 0 ||
				cof(0, 3).inf() < 0 || cof(3, 3).inf() < 0 || cof(9, 3).inf() < 0 || cof(19, 3).inf() < 0)
				mes = flipped;
			else
				mes = uncertain;*/
		}

		double run(scalar& time, double stop_time = DBL_MAX)
		{
			if (time.inf() <= 0)
			{
				time = scalar(0);
				dprint("input zero");
				exit(0);
				return -1;
			}
			time = scalar(time.inf());
			//dprint(time);
			for (int i = 0; i < N; ++i)
			{
				if (cof_(i, 0).inf() < 0)
				{
					dprint("HOCGV: flipping occurs in the initialization");
					system("pause");
				}
			}
			//Lagrange cofficients ===> Bernstein cofficients
			cof_ = constant_data->transform * cof_ * constant_data->bern_transform;
			/*cof.col(1) /= time;
			cof.col(2) /= time * time;
			cof.col(3) /= time * time * time;*/

			scalar time_interval(0, time.inf());
			tet_queue.emplace(0, time_interval, cof_, constant_data->corner_id);
			int level = 0;
			message mes;
			double t0 = time_interval.inf();
			double t1 = time_interval.sup();
			double conservative_threshold = t0;
			while (true)
			{
				//dprint(time_interval.sup(), time_interval.inf(), time_interval.inf() + delta);
				if (t0 >= stop_time)
					break;
				if (t1 < t0 + delta && t0 > 0)
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
				conservative_threshold = t0;
				t0 = current_tet.time_interval.inf();
				//dprint(t0, conservative_threshold);
				test_regularity(current_tet, mes);
				matn4 temp_cof;
#if 0
				dprint("current level*********************************************:", current_tet.level);
				dprint("current interval:", current_tet.time_interval);
				//dprint("inclusion:", current_tet.inclusion);
				dprintwithprecision(15, "t0, t1:", t0, t1);
				//dprint("message:", mes);
				dprint("tet_queue size:", tet_queue.size());
#endif
				//static int lls = 0;
				static int lll = 0;
				switch (mes)
				{
				case regular:
					//dprint("regular");
					break;
				case flipped:
					//subdivide on time
				{
					//dprint("flipped22222222222222222222222222");
					double mid = (current_tet.time_interval.inf() + current_tet.time_interval.sup()) / 2.0;
					temp_cof = current_tet.cof * constant_data->former_transform;
					tet_queue.emplace(current_tet.level + 1,
						scalar(current_tet.time_interval.inf(), mid), temp_cof, constant_data->corner_id);
					temp_cof = current_tet.cof * constant_data->latter_transform;
					tet_queue.emplace(current_tet.level + 1,
						scalar(mid, current_tet.time_interval.sup()), temp_cof, constant_data->corner_id);
					t1 = min(t1, current_tet.time_interval.sup());
					//++lls;
				}
				break;
				case uncertain:
					//subdivide on time and space
				{
					++lll;
					//dprint("lll", lll);
					//dprint("uncertain3333333333333333333333333333");
					double mid = (current_tet.time_interval.inf() + current_tet.time_interval.sup()) / 2.0;
					matn4 former_cof = current_tet.cof * constant_data->former_transform;
					matn4 latter_cof = current_tet.cof * constant_data->latter_transform;
					for (int i = 0; i < 8; ++i)
					{
						temp_cof = constant_data->son_transform[i] * former_cof;
						tet_queue.emplace(current_tet.level + 1,
							scalar(current_tet.time_interval.inf(), mid), temp_cof, constant_data->corner_id);
						temp_cof = constant_data->son_transform[i] * latter_cof;
						tet_queue.emplace(current_tet.level + 1,
							scalar(mid, current_tet.time_interval.sup()), temp_cof, constant_data->corner_id);
					}
					//++lll;
				}
				break;
				}
				/*if (lll % 100 == 0)
				{
					dprint("lll:", lll, lls);
				}*/
			}
			if (t0 > time.inf())
			{
				t0 = time.inf(); t1 = t0;
			}
			time = scalar(t0, t1);
			std::priority_queue<sub_tet, std::vector<sub_tet>, std::greater<sub_tet>> empty_temp;
			tet_queue.swap(empty_temp);
			//dprint(t0, conservative_threshold);
			//dprint("\n\n\n");
			return conservative_threshold;
		}

	};


	typedef hocgv_detector<2, tet2_constant_data> hocgv2;
	typedef hocgv_detector<3, tet3_constant_data> hocgv3;

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