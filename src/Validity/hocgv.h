#include "..\src\MeshViewer\MeshDefinition.h"
#include "scalar_def.h"
#include "constant_data.h"
#include "dprint.h"
#include <Eigen/Core>
#include <queue>
namespace CABT
{
	class hocgv
	{
	public:
		hocgv(){}
		~hocgv(){}

	public:
		tet2_constant_data* constant_data;
		mat3_10 control_val;
		mat3_10 control_dir;
		double delta = 1e-4;
		int max_subdivide_times = 5;
		enum message
		{
			positive,
			negative,
			uncertain
		};
        struct sub_tet
        {
            EIGEN_MAKE_ALIGNED_OPERATOR_NEW
            sub_tet(){}
            sub_tet(int level_, scalar& time_interval_, mat20_4& cof_)
                : level(level_), time_interval(time_interval_), cof(std::move(cof_)) {}
			~sub_tet(){}

            int level;
            scalar time_interval;
            mat20_4 cof;
            bool operator>(const sub_tet& right) const {
                return time_interval.inf() > right.time_interval.inf();
            }
        };
        //Compared to B, A should be on the top if A.time_interval.inf() < B.time_interval.inf()
        std::priority_queue<sub_tet, std::vector<sub_tet>, std::greater<sub_tet>> tet_queue;



		void calc_sampling_jacobi_det(scalar t, mat20_4& cof);
		void init(mat3_10& val, mat3_10& dir, tet2_constant_data* constant_data_)
		{
			control_val = std::move(val); control_dir = std::move(dir); constant_data = constant_data_;
		}
		void test_regularity(mat20_4& cof, message& mes);
		void run(scalar &time);
	};
}