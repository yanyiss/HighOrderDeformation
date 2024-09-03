#include "..\src\MeshViewer\MeshDefinition.h"
#include "scalar_def.h"
#include "constant_data.h"
#include "dprint.h"
#include <Eigen/Core>
namespace CABT
{
    class tet2
    {
    public:
        tet2() { }
        ~tet2() { }


    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        int subdivision_times = 3;
        tet2_constant_data* constant_data;
        subdivide_tree* sub_tree;
        mat3_10 control_val;
        mat3_10 control_dir;
        scalar elp = scalar(1e-4, 1e-4);
        enum message
        {
            NoCollision,      // there is no collision in (0, time)
            Collision,        // there is an explicit and exact collision in (0, time)
            NumericalFailure, // there is a collision but the time is not exact because of numerical problems
            InitCollision     // the initial closure has collision
        };
        void init(mat3_10& val, mat3_10& dir, tet2_constant_data* constant_data_, subdivide_tree* sub_tree_)
        {
            control_val = std::move(val); control_dir = std::move(dir); constant_data = constant_data_; sub_tree = sub_tree_;
        }
        void calc_sampling_jacobi_det(scalar t, mat20_4 &cof);
        //void cardano(complex<double> a, complex<double> b, complex<double> c, complex<double>d, complex<double>& x1, complex<double>& x2, complex<double>& x3);
       // void calc_cubic_root_with_cardano(scalar a, scalar b, scalar c, scalar d, scalar& time);
        void newton_raphson(const vec4s &cubic_cof, scalar time, scalar dif, scalar &val, scalar elp);
#if 0
        void search_cubic_root(const vec4s& cubic_cof, scalar& time, message& mes, bool if_calc_root);
        void tet_status(mat20_4& cof, scalar& time, message& mes, bool if_calc_root);
        void get_min_time(mat20_4& cof, scalar& time);
        mat4_4 time_transform;
        void run(scalar& time)
        {
            scalar t[4] = { scalar(1),time,time * time,time * time * time };
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    time_transform.row(i) = constant_data->time_transform.row(i) / t[i];
                }
            }

            mat20_4 cof;
            calc_sampling_jacobi_det(time, cof);
            get_min_time(cof, time);
        }
#else
        void search_cubic_root(const vec4s& cubic_cof, scalar& time, message& mes);
        void tet_status(mat20_4& cof, scalar& time, message& mes);
        void get_min_time_recursion(int level, int count, scalar& time);
        void run(scalar& time);
#endif
        scalar compute_jacobidet(scalar& time);
        void write_bug();
    };
    
}