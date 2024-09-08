#pragma once 
#include "scalar_def.h"
#include <Eigen/Core>
namespace CABT
{
    class tet2_constant_data
    {
    public:
        tet2_constant_data()
        { 
            omtensor2vec = tensor3i(3, 3, 3);
            omtensor2vec.setConstant(-1);
            omtensor2vec(0, 0, 0) = 0; omtensor2vec(0, 0, 1) = 1; omtensor2vec(0, 0, 2) = 2; omtensor2vec(0, 1, 0) = 3; omtensor2vec(0, 1, 1) = 4;
            omtensor2vec(0, 2, 0) = 5; omtensor2vec(1, 0, 0) = 6; omtensor2vec(1, 0, 1) = 7; omtensor2vec(1, 1, 0) = 8; omtensor2vec(2, 0, 0) = 9;

            ontensor2vec = tensor3i(4, 4, 4);
            ontensor2vec.setConstant(-1);
            ontensor2vec(0, 0, 0) = 0; ontensor2vec(0, 0, 1) = 1; ontensor2vec(0, 0, 2) = 2; ontensor2vec(0, 0, 3) = 3; ontensor2vec(0, 1, 0) = 4;
            ontensor2vec(0, 1, 1) = 5; ontensor2vec(0, 1, 2) = 6; ontensor2vec(0, 2, 0) = 7; ontensor2vec(0, 2, 1) = 8; ontensor2vec(0, 3, 0) = 9;
            ontensor2vec(1, 0, 0) = 10; ontensor2vec(1, 0, 1) = 11; ontensor2vec(1, 0, 2) = 12; ontensor2vec(1, 1, 0) = 13; ontensor2vec(1, 1, 1) = 14;
            ontensor2vec(1, 2, 0) = 15; ontensor2vec(2, 0, 0) = 16; ontensor2vec(2, 0, 1) = 17; ontensor2vec(2, 1, 0) = 18; ontensor2vec(3, 0, 0) = 19;

            time_transform.setConstant(scalar(0));
            time_transform <<
                scalar(1), -scalar(11) / scalar(2), scalar(9), -scalar(9) / scalar(2),
                scalar(0), scalar(9), -scalar(45) / scalar(2), scalar(27) / scalar(2),
                scalar(0), -scalar(9) / scalar(2), scalar(18), -scalar(27) / scalar(2),
                scalar(0), scalar(1), -scalar(9) / scalar(2), scalar(9) / scalar(2);

            bern_transform.setConstant(scalar(0));
            bern_transform <<
                scalar(1), -scalar(5) / scalar(6), scalar(1) / scalar(3), scalar(0),
                scalar(0), scalar(3), -scalar(3) / scalar(2), scalar(0),
                scalar(0), -scalar(3) / scalar(2), scalar(3), scalar(0),
                scalar(0), scalar(1) / scalar(3), -scalar(5) / scalar(6), scalar(1);

            former_transform.setConstant(scalar(0));
            former_transform <<
                scalar(1), scalar(1) / scalar(2), scalar(1) / scalar(4), scalar(1) / scalar(8),
                scalar(0), scalar(1) / scalar(2), scalar(1) / scalar(2), scalar(3) / scalar(8),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(3) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8);
            
            latter_transform.setConstant(scalar(0));
            latter_transform <<
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(1) / scalar(4), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(1) / scalar(2), scalar(1) / scalar(2), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(2), scalar(1);

#if 1

#pragma region transform
            {
            transform <<
                // Row 1
                scalar(1), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 2
                -scalar(5) / scalar(6), scalar(3), -scalar(3) / scalar(2), scalar(1) / scalar(3), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 3
                scalar(1) / scalar(3), -scalar(3) / scalar(2), scalar(3), -scalar(5) / scalar(6), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 4
                scalar(0), scalar(0), scalar(0), scalar(1), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 5
                -scalar(5) / scalar(6), scalar(0), scalar(0), scalar(0), scalar(3),
                scalar(0), scalar(0), -scalar(3) / scalar(2), scalar(0), scalar(1) / scalar(3),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 6
                scalar(1) / scalar(3), -scalar(3) / scalar(4), -scalar(3) / scalar(4), scalar(1) / scalar(3), -scalar(3) / scalar(4),
                scalar(9) / scalar(2), -scalar(3) / scalar(4), -scalar(3) / scalar(4), -scalar(3) / scalar(4), scalar(1) / scalar(3),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 7
                scalar(0), scalar(0), scalar(0), -scalar(5) / scalar(6), scalar(0),
                scalar(0), scalar(3), scalar(0), -scalar(3) / scalar(2), scalar(1) / scalar(3),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 8
                scalar(1) / scalar(3), scalar(0), scalar(0), scalar(0), -scalar(3) / scalar(2),
                scalar(0), scalar(0), scalar(3), scalar(0), -scalar(5) / scalar(6),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 9
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(3), scalar(0),
                scalar(0), -scalar(3) / scalar(2), scalar(0), scalar(3), -scalar(5) / scalar(6),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 10
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 11
                -scalar(5) / scalar(6), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), -scalar(3) / scalar(2), scalar(0), scalar(0), scalar(1) / scalar(3),
                // Row 12
                scalar(1) / scalar(3), -scalar(3) / scalar(4), -scalar(3) / scalar(4), scalar(1) / scalar(3), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                -scalar(3) / scalar(4), scalar(9) / scalar(2), -scalar(3) / scalar(4), scalar(0), scalar(0),
                scalar(0), -scalar(3) / scalar(4), -scalar(3) / scalar(4), scalar(0), scalar(1) / scalar(3),
                // Row 13
                scalar(0), scalar(0), scalar(0), -scalar(5) / scalar(6), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3), scalar(0), scalar(0),
                scalar(0), scalar(0), -scalar(3) / scalar(2), scalar(0), scalar(1) / scalar(3),
                // Row 14
                scalar(1) / scalar(3), scalar(0), scalar(0), scalar(0), -scalar(3) / scalar(4),
                scalar(0), scalar(0), -scalar(3) / scalar(4), scalar(0), scalar(1) / scalar(3),
                -scalar(3) / scalar(4), scalar(0), scalar(0), scalar(9) / scalar(2), scalar(0),
                -scalar(3) / scalar(4), -scalar(3) / scalar(4), scalar(0), -scalar(3) / scalar(4), scalar(1) / scalar(3),
                // Row 15
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(3), scalar(0),
                scalar(0), -scalar(3) / scalar(4), scalar(0), -scalar(3) / scalar(4), scalar(1) / scalar(3),
                scalar(0), scalar(0), -scalar(3) / scalar(4), scalar(0), scalar(9) / scalar(2),
                -scalar(3) / scalar(4), scalar(0), -scalar(3) / scalar(4), -scalar(3) / scalar(4), scalar(1) / scalar(3),
                // Row 16
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), -scalar(5) / scalar(6),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3), scalar(0), scalar(0), -scalar(3) / scalar(2), scalar(1) / scalar(3),
                // Row 17
                scalar(1) / scalar(3), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                -scalar(3) / scalar(2), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(3), scalar(0), scalar(0), -scalar(5) / scalar(6),
                // Row 18
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(3), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), -scalar(3) / scalar(2), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3), scalar(0), -scalar(5) / scalar(6),
                // Row 19
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(3),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                -scalar(3) / scalar(2), scalar(0), scalar(0), scalar(3), -scalar(5) / scalar(6),
                // Row 20
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1);
            }
#pragma endregion

#pragma region son_transform[0]
            {
            son_transform[0] <<
                // Row 1
                scalar(1), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 2
                scalar(1) / scalar(2), scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 3
                scalar(1) / scalar(4), scalar(1) / scalar(2), scalar(1) / scalar(4), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 4
                scalar(1) / scalar(8), scalar(3) / scalar(8), scalar(3) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 5
                scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 6
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 7
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 8
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 9
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 10
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(8),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 11
                scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 12
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 13
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 14
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 15
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 16
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 17
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                // Row 18
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 19
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(0),
                // Row 20
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8);
            }
#pragma endregion

#pragma region son_transform[1]
            {
            son_transform[1] <<
                // Row 1
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8),
                // Row 2
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                // Row 3
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8),
                // Row 4
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8),
                // Row 5
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                // Row 6
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                // Row 7
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8),
                // Row 8
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8),
                // Row 9
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8),
                // Row 10
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8),
                // Row 11
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(2), scalar(0), scalar(0), scalar(1) / scalar(4),
                // Row 12
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4),
                // Row 13
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0), scalar(1) / scalar(4),
                // Row 14
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4),
                // Row 15
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(1) / scalar(4),
                // Row 16
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(1) / scalar(2), scalar(1) / scalar(4),
                // Row 17
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(2), scalar(0), scalar(0), scalar(1) / scalar(2),
                // Row 18
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0), scalar(1) / scalar(2),
                // Row 19
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2), scalar(1) / scalar(2),
                // Row 20
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1);

            }
#pragma endregion

#pragma region son_transform[2]
            {
            son_transform[2] <<
                // Row 1
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(8),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 2
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 3
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 4
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(3) / scalar(8), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 5
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 6
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 7
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(2), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 8
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0), scalar(1) / scalar(2),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 9
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2), scalar(1) / scalar(2),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 10
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 11
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 12
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 13
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 14
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 15
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 16
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 17
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(0),
                // Row 18
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                // Row 19
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(2), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                // Row 20
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8);
            }
#pragma endregion

#pragma region son_transform[3]
            {
            son_transform[3] <<
                // Row 1
                scalar(1) / scalar(8), scalar(3) / scalar(8), scalar(3) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 2
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(2), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 3
                scalar(0), scalar(0), scalar(1) / scalar(2), scalar(1) / scalar(2), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 4
                scalar(0), scalar(0), scalar(0), scalar(1), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 5
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 6
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 7
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0),
                scalar(0), scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 8
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 9
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(1) / scalar(2), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 10
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(3) / scalar(8), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 11
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 12
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 13
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 14
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 15
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 16
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 17
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 18
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0),
                // Row 19
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                // Row 20
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8);
            }
#pragma endregion

#pragma region son_transform[4]
            {
            son_transform[4] <<
                // Row 1
                scalar(1) / scalar(8), scalar(3) / scalar(8), scalar(3) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 2
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 3
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 4
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(3) / scalar(8), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 5
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 6
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 7
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 8
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 9
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                // Row 10
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8),
                // Row 11
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 12
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 13
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 14
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 15
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                // Row 16
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8),
                // Row 17
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 18
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                // Row 19
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8),
                // Row 20
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8);
            }
#pragma endregion

#pragma region son_transform[5]
            {
            son_transform[5] <<
                // Row 1
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8),
                // Row 2
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 3
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 4
                scalar(1) / scalar(8), scalar(3) / scalar(8), scalar(3) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 5
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(0),
                // Row 6
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 7
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 8
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 9
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 10
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(8),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 11
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                // Row 12
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 13
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 14
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(0),
                // Row 15
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 16
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 17
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8),
                // Row 18
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 19
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(0),
                // Row 20
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8);

            }
#pragma endregion

#pragma region son_transform[6]
            {
            son_transform[6] <<
                // Row 1
                scalar(1) / scalar(8), scalar(3) / scalar(8), scalar(3) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 2
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 3
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 4
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8),
                // Row 5
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 6
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 7
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8),
                // Row 8
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 9
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8),
                // Row 10
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8),
                // Row 11
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 12
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 13
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8),
                // Row 14
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 15
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                // Row 16
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8),
                // Row 17
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 18
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                // Row 19
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                // Row 20
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8);
            }
#pragma endregion

#pragma region son_transform[7]
            {
            son_transform[7] <<
                // Row 1
                scalar(1) / scalar(8), scalar(3) / scalar(8), scalar(3) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 2
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 3
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 4
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(3) / scalar(8), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 5
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 6
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 7
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 8
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 9
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 10
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(8),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 11
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 12
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 13
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 14
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 15
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 16
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 17
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 18
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                // Row 19
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(0),
                // Row 20
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8);
            }
#pragma endregion

#else

#pragma region transform
            {
            transform <<
                // Row 1
                scalar(1), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 2
                -scalar(5) / scalar(6), scalar(3), -scalar(3) / scalar(2), scalar(1) / scalar(3), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 3
                scalar(1) / scalar(3), -scalar(3) / scalar(2), scalar(3), -scalar(5) / scalar(6), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 4
                scalar(0), scalar(0), scalar(0), scalar(1), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 5
                -scalar(5) / scalar(6), scalar(0), scalar(0), scalar(0), scalar(3),
                scalar(0), scalar(0), -scalar(3) / scalar(2), scalar(0), scalar(1) / scalar(3),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 6
                scalar(1) / scalar(3), -scalar(3) / scalar(4), -scalar(3) / scalar(4), scalar(1) / scalar(3), -scalar(3) / scalar(4),
                scalar(9) / scalar(2), -scalar(3) / scalar(4), -scalar(3) / scalar(4), -scalar(3) / scalar(4), scalar(1) / scalar(3),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 7
                scalar(0), scalar(0), scalar(0), -scalar(5) / scalar(6), scalar(0),
                scalar(0), scalar(3), scalar(0), -scalar(3) / scalar(2), scalar(1) / scalar(3),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 8
                scalar(1) / scalar(3), scalar(0), scalar(0), scalar(0), -scalar(3) / scalar(2),
                scalar(0), scalar(0), scalar(3), scalar(0), -scalar(5) / scalar(6),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 9
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(3), scalar(0),
                scalar(0), -scalar(3) / scalar(2), scalar(0), scalar(3), -scalar(5) / scalar(6),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 10
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 11
                -scalar(5) / scalar(6), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), -scalar(3) / scalar(2), scalar(0), scalar(0), scalar(1) / scalar(3),
                // Row 12
                scalar(1) / scalar(3), -scalar(3) / scalar(4), -scalar(3) / scalar(4), scalar(1) / scalar(3), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                -scalar(3) / scalar(4), scalar(9) / scalar(2), -scalar(3) / scalar(4), scalar(0), scalar(0),
                scalar(0), -scalar(3) / scalar(4), -scalar(3) / scalar(4), scalar(0), scalar(1) / scalar(3),
                // Row 13
                scalar(0), scalar(0), scalar(0), -scalar(5) / scalar(6), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3), scalar(0), scalar(0),
                scalar(0), scalar(0), -scalar(3) / scalar(2), scalar(0), scalar(1) / scalar(3),
                // Row 14
                scalar(1) / scalar(3), scalar(0), scalar(0), scalar(0), -scalar(3) / scalar(4),
                scalar(0), scalar(0), -scalar(3) / scalar(4), scalar(0), scalar(1) / scalar(3),
                -scalar(3) / scalar(4), scalar(0), scalar(0), scalar(9) / scalar(2), scalar(0),
                -scalar(3) / scalar(4), -scalar(3) / scalar(4), scalar(0), -scalar(3) / scalar(4), scalar(1) / scalar(3),
                // Row 15
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(3), scalar(0),
                scalar(0), -scalar(3) / scalar(4), scalar(0), -scalar(3) / scalar(4), scalar(1) / scalar(3),
                scalar(0), scalar(0), -scalar(3) / scalar(4), scalar(0), scalar(9) / scalar(2),
                -scalar(3) / scalar(4), scalar(0), -scalar(3) / scalar(4), -scalar(3) / scalar(4), scalar(1) / scalar(3),
                // Row 16
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), -scalar(5) / scalar(6),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3), scalar(0), scalar(0), -scalar(3) / scalar(2), scalar(1) / scalar(3),
                // Row 17
                scalar(1) / scalar(3), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                -scalar(3) / scalar(2), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(3), scalar(0), scalar(0), -scalar(5) / scalar(6),
                // Row 18
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(3), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), -scalar(3) / scalar(2), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3), scalar(0), -scalar(5) / scalar(6),
                // Row 19
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(3),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                -scalar(3) / scalar(2), scalar(0), scalar(0), scalar(3), -scalar(5) / scalar(6),
                // Row 20
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1);
            }
#pragma endregion

#pragma region son_transform[0]
            {
            son_transform[0] <<
                // Row 1
                scalar(1), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 2
                scalar(1) / scalar(2), scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 3
                scalar(1) / scalar(4), scalar(1) / scalar(2), scalar(1) / scalar(4), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 4
                scalar(1) / scalar(8), scalar(3) / scalar(8), scalar(3) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 5
                scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 6
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 7
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 8
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 9
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 10
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(8),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 11
                scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 12
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 13
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 14
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 15
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 16
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 17
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                // Row 18
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 19
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(0),
                // Row 20
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8);
            }
#pragma endregion

#pragma region son_transform[1]
            {
            son_transform[1] <<
                // Row 1
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8),
                // Row 2
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                // Row 3
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8),
                // Row 4
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8),
                // Row 5
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                // Row 6
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                // Row 7
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8),
                // Row 8
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8),
                // Row 9
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8),
                // Row 10
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8),
                // Row 11
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(2), scalar(0), scalar(0), scalar(1) / scalar(4),
                // Row 12
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4),
                // Row 13
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0), scalar(1) / scalar(4),
                // Row 14
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4),
                // Row 15
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(1) / scalar(4),
                // Row 16
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(1) / scalar(2), scalar(1) / scalar(4),
                // Row 17
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(2), scalar(0), scalar(0), scalar(1) / scalar(2),
                // Row 18
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0), scalar(1) / scalar(2),
                // Row 19
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2), scalar(1) / scalar(2),
                // Row 20
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1);

            }
#pragma endregion

#pragma region son_transform[2]
            {
            son_transform[2] <<
                // Row 1
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(8),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 2
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 3
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 4
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(3) / scalar(8), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 5
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 6
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 7
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(2), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 8
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0), scalar(1) / scalar(2),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 9
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2), scalar(1) / scalar(2),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 10
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 11
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 12
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 13
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 14
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 15
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 16
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 17
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(0),
                // Row 18
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                // Row 19
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(2), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                // Row 20
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8);
            }
#pragma endregion

#pragma region son_transform[3]
            {
            son_transform[3] <<
                // Row 1
                scalar(1) / scalar(8), scalar(3) / scalar(8), scalar(3) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 2
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(2), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 3
                scalar(0), scalar(0), scalar(1) / scalar(2), scalar(1) / scalar(2), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 4
                scalar(0), scalar(0), scalar(0), scalar(1), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 5
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 6
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 7
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0),
                scalar(0), scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 8
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 9
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(1) / scalar(2), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 10
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(3) / scalar(8), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 11
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 12
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 13
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 14
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 15
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 16
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 17
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 18
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0),
                // Row 19
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                // Row 20
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8);
            }
#pragma endregion

#pragma region son_transform[4]
            {
            son_transform[4] <<
                // Row 1
                scalar(1) / scalar(8), scalar(3) / scalar(8), scalar(3) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 2
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 3
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 4
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8),
                // Row 5
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 6
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 7
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                // Row 8
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 9
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 10
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(3) / scalar(8), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 11
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 12
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 13
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8),
                // Row 14
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 15
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                // Row 16
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 17
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 18
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8),
                // Row 19
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                // Row 20
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8);
            }
#pragma endregion

#pragma region son_transform[5]
            {
            son_transform[5] <<
                // Row 1
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8),
                // Row 2
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 3
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 4
                scalar(1) / scalar(8), scalar(3) / scalar(8), scalar(3) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 5
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8),
                // Row 6
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 7
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 8
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                // Row 9
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 10
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8),
                // Row 11
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(0),
                // Row 12
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 13
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 14
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(0),
                // Row 15
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 16
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(0),
                // Row 17
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 18
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 19
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 20
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(8),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0);

            }
#pragma endregion

#pragma region son_transform[6]
            {
            son_transform[6] <<
                // Row 1
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8),
                // Row 2
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8),
                // Row 3
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                // Row 4
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8),
                // Row 5
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8),
                // Row 6
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                // Row 7
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                // Row 8
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8),
                // Row 9
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8),
                // Row 10
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8),
                // Row 11
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 12
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 13
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 14
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 15
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 16
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 17
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 18
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 19
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 20
                scalar(1) / scalar(8), scalar(3) / scalar(8), scalar(3) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0);
            }
#pragma endregion

#pragma region son_transform[7]
            {
            son_transform[7] <<
                // Row 1
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(0), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8),
                // Row 2
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(0),
                // Row 3
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 4
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(8),
                scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 5
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                // Row 6
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 7
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 8
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 9
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 10
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(3) / scalar(8), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 11
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                // Row 12
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 13
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4),
                scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 14
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 15
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 16
                scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 17
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 18
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 19
                scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8),
                scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                // Row 20
                scalar(1) / scalar(8), scalar(3) / scalar(8), scalar(3) / scalar(8), scalar(1) / scalar(8), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(0), scalar(0), scalar(0);
            }
#pragma endregion


#endif
        }
        ~tet2_constant_data() { }

    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        tensor3i omtensor2vec;
        tensor3i ontensor2vec;
        mat20_20 transform;
        mat4_4 time_transform;
        mat4_4 former_transform;
        mat4_4 latter_transform;
        mat4_4 bern_transform;
        mat20_20 son_transform[8];
    };

    class tet3_constant_data
    {
    public:
        tet3_constant_data()
        {
            omtensor2vec = tensor3i(4, 4, 4);
            omtensor2vec.setConstant(-1);
            omtensor2vec(0, 0, 0) = 0; omtensor2vec(0, 0, 1) = 1; omtensor2vec(0, 0, 2) = 2; omtensor2vec(0, 0, 3) = 3; omtensor2vec(0, 1, 0) = 4;
            omtensor2vec(0, 1, 1) = 5; omtensor2vec(0, 1, 2) = 6; omtensor2vec(0, 2, 0) = 7; omtensor2vec(0, 2, 1) = 8; omtensor2vec(0, 3, 0) = 9;
            omtensor2vec(1, 0, 0) = 10; omtensor2vec(1, 0, 1) = 11; omtensor2vec(1, 0, 2) = 12; omtensor2vec(1, 1, 0) = 13; omtensor2vec(1, 1, 1) = 14;
            omtensor2vec(1, 2, 0) = 15; omtensor2vec(2, 0, 0) = 16; omtensor2vec(2, 0, 1) = 17; omtensor2vec(2, 1, 0) = 18; omtensor2vec(3, 0, 0) = 19;

            ontensor2vec = tensor3i(5, 5, 5);
            ontensor2vec.setConstant(-1);
            ontensor2vec(0, 0, 0) = 0; ontensor2vec(0, 0, 1) = 1; ontensor2vec(0, 0, 2) = 2; ontensor2vec(0, 0, 3) = 3; ontensor2vec(0, 0, 4) = 4;
            ontensor2vec(0, 1, 0) = 5; ontensor2vec(0, 1, 1) = 6; ontensor2vec(0, 1, 2) = 7; ontensor2vec(0, 1, 3) = 8; ontensor2vec(0, 2, 0) = 9;
            ontensor2vec(0, 2, 1) = 10; ontensor2vec(0, 2, 2) = 11; ontensor2vec(0, 3, 0) = 12; ontensor2vec(0, 3, 1) = 13; ontensor2vec(0, 4, 0) = 14;
            ontensor2vec(1, 0, 0) = 15; ontensor2vec(1, 0, 1) = 16; ontensor2vec(1, 0, 2) = 17; ontensor2vec(1, 0, 3) = 18; ontensor2vec(1, 1, 0) = 19;
            ontensor2vec(1, 1, 1) = 20; ontensor2vec(1, 1, 2) = 21; ontensor2vec(1, 2, 0) = 22; ontensor2vec(1, 2, 1) = 23; ontensor2vec(1, 3, 0) = 24;
            ontensor2vec(2, 0, 0) = 25; ontensor2vec(2, 0, 1) = 26; ontensor2vec(2, 0, 2) = 27; ontensor2vec(2, 1, 0) = 28; ontensor2vec(2, 1, 1) = 29;
            ontensor2vec(2, 2, 0) = 30; ontensor2vec(3, 0, 0) = 31; ontensor2vec(3, 0, 1) = 32; ontensor2vec(3, 1, 0) = 33; ontensor2vec(4, 0, 0) = 34;

            time_transform.setConstant(scalar(0));
            time_transform <<
                scalar(1), -scalar(11) / scalar(2), scalar(9), -scalar(9) / scalar(2),
                scalar(0), scalar(9), -scalar(45) / scalar(2), scalar(27) / scalar(2),
                scalar(0), -scalar(9) / scalar(2), scalar(18), -scalar(27) / scalar(2),
                scalar(0), scalar(1), -scalar(9) / scalar(2), scalar(9) / scalar(2);

            bern_transform.setConstant(scalar(0));
            bern_transform <<
                scalar(1), -scalar(5) / scalar(6), scalar(1) / scalar(3), scalar(0),
                scalar(0), scalar(3), -scalar(3) / scalar(2), scalar(0),
                scalar(0), -scalar(3) / scalar(2), scalar(3), scalar(0),
                scalar(0), scalar(1) / scalar(3), -scalar(5) / scalar(6), scalar(1);

            former_transform.setConstant(scalar(0));
            former_transform <<
                scalar(1), scalar(1) / scalar(2), scalar(1) / scalar(4), scalar(1) / scalar(8),
                scalar(0), scalar(1) / scalar(2), scalar(1) / scalar(2), scalar(3) / scalar(8),
                scalar(0), scalar(0), scalar(1) / scalar(4), scalar(3) / scalar(8),
                scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8);

            latter_transform.setConstant(scalar(0));
            latter_transform <<
                scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(1) / scalar(4), scalar(0), scalar(0),
                scalar(3) / scalar(8), scalar(1) / scalar(2), scalar(1) / scalar(2), scalar(0),
                scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(2), scalar(1);


#pragma region transform
            {
                transform <<
                    // Row 1
                    scalar(1), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 2
                    -scalar(13) / scalar(12), scalar(4), -scalar(3), scalar(4) / scalar(3), -scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 3
                    scalar(13) / scalar(18), -scalar(32) / scalar(9), scalar(20) / scalar(3), -scalar(32) / scalar(9), scalar(13) / scalar(18),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 4
                    -scalar(1) / scalar(4), scalar(4) / scalar(3), -scalar(3), scalar(4), -scalar(13) / scalar(12),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 5
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 6
                    -scalar(13) / scalar(12), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(4), scalar(0), scalar(0), scalar(0), -scalar(3),
                    scalar(0), scalar(0), scalar(4) / scalar(3), scalar(0), -scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 7
                    scalar(13) / scalar(18), -scalar(16) / scalar(9), -scalar(2) / scalar(3), scalar(8) / scalar(9), -scalar(1) / scalar(4),
                    -scalar(16) / scalar(9), scalar(8), -scalar(8) / scalar(3), scalar(4) / scalar(9), -scalar(2) / scalar(3),
                    -scalar(8) / scalar(3), scalar(1) / scalar(3), scalar(8) / scalar(9), scalar(4) / scalar(9), -scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 8
                    -scalar(1) / scalar(4), scalar(8) / scalar(9), -scalar(2) / scalar(3), -scalar(16) / scalar(9), scalar(13) / scalar(18),
                    scalar(4) / scalar(9), -scalar(8) / scalar(3), scalar(8), -scalar(16) / scalar(9), scalar(1) / scalar(3),
                    -scalar(8) / scalar(3), -scalar(2) / scalar(3), scalar(4) / scalar(9), scalar(8) / scalar(9), -scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 9
                    scalar(0), scalar(0), scalar(0), scalar(0), -scalar(13) / scalar(12),
                    scalar(0), scalar(0), scalar(0), scalar(4), scalar(0),
                    scalar(0), -scalar(3), scalar(0), scalar(4) / scalar(3), -scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 10
                    scalar(13) / scalar(18), scalar(0), scalar(0), scalar(0), scalar(0),
                    -scalar(32) / scalar(9), scalar(0), scalar(0), scalar(0), scalar(20) / scalar(3),
                    scalar(0), scalar(0), -scalar(32) / scalar(9), scalar(0), scalar(13) / scalar(18),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 11
                    -scalar(1) / scalar(4), scalar(4) / scalar(9), scalar(1) / scalar(3), scalar(4) / scalar(9), -scalar(1) / scalar(4),
                    scalar(8) / scalar(9), -scalar(8) / scalar(3), -scalar(8) / scalar(3), scalar(8) / scalar(9), -scalar(2) / scalar(3),
                    scalar(8), -scalar(2) / scalar(3), -scalar(16) / scalar(9), -scalar(16) / scalar(9), scalar(13) / scalar(18),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 12
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(13) / scalar(18),
                    scalar(0), scalar(0), scalar(0), -scalar(32) / scalar(9), scalar(0),
                    scalar(0), scalar(20) / scalar(3), scalar(0), -scalar(32) / scalar(9), scalar(13) / scalar(18),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 13
                    -scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(4) / scalar(3), scalar(0), scalar(0), scalar(0), -scalar(3),
                    scalar(0), scalar(0), scalar(4), scalar(0), -scalar(13) / scalar(12),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 14
                    scalar(0), scalar(0), scalar(0), scalar(0), -scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(4) / scalar(3), scalar(0),
                    scalar(0), -scalar(3), scalar(0), scalar(4), -scalar(13) / scalar(12),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 15
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 16
                    -scalar(13) / scalar(12), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    -scalar(3), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(4) / scalar(3), scalar(0), scalar(0), -scalar(1) / scalar(4),
                    // Row 17
                    scalar(13) / scalar(18), -scalar(16) / scalar(9), -scalar(2) / scalar(3), scalar(8) / scalar(9), -scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    -scalar(16) / scalar(9), scalar(8), -scalar(8) / scalar(3), scalar(4) / scalar(9), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    -scalar(2) / scalar(3), -scalar(8) / scalar(3), scalar(1) / scalar(3), scalar(0), scalar(0),
                    scalar(0), scalar(8) / scalar(9), scalar(4) / scalar(9), scalar(0), -scalar(1) / scalar(4),
                    // Row 18
                    -scalar(1) / scalar(4), scalar(8) / scalar(9), -scalar(2) / scalar(3), -scalar(16) / scalar(9), scalar(13) / scalar(18),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(4) / scalar(9), -scalar(8) / scalar(3), scalar(8), -scalar(16) / scalar(9), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(3), -scalar(8) / scalar(3), -scalar(2) / scalar(3), scalar(0), scalar(0),
                    scalar(0), scalar(4) / scalar(9), scalar(8) / scalar(9), scalar(0), -scalar(1) / scalar(4),
                    // Row 19
                    scalar(0), scalar(0), scalar(0), scalar(0), -scalar(13) / scalar(12),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(4), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), -scalar(3), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(4) / scalar(3), scalar(0), -scalar(1) / scalar(4),
                    // Row 20
                    scalar(13) / scalar(18), scalar(0), scalar(0), scalar(0), scalar(0),
                    -scalar(16) / scalar(9), scalar(0), scalar(0), scalar(0), -scalar(2) / scalar(3),
                    scalar(0), scalar(0), scalar(8) / scalar(9), scalar(0), -scalar(1) / scalar(4),
                    -scalar(16) / scalar(9), scalar(0), scalar(0), scalar(0), scalar(8),
                    scalar(0), scalar(0), -scalar(8) / scalar(3), scalar(0), scalar(4) / scalar(9),
                    -scalar(2) / scalar(3), scalar(0), scalar(0), -scalar(8) / scalar(3), scalar(0),
                    scalar(1) / scalar(3), scalar(8) / scalar(9), scalar(0), scalar(4) / scalar(9), -scalar(1) / scalar(4),
                    // Row 21
                    -scalar(1) / scalar(4), scalar(4) / scalar(9), scalar(1) / scalar(3), scalar(4) / scalar(9), -scalar(1) / scalar(4),
                    scalar(4) / scalar(9), -scalar(4) / scalar(3), -scalar(4) / scalar(3), scalar(4) / scalar(9), scalar(1) / scalar(3),
                    -scalar(4) / scalar(3), scalar(1) / scalar(3), scalar(4) / scalar(9), scalar(4) / scalar(9), -scalar(1) / scalar(4),
                    scalar(4) / scalar(9), -scalar(4) / scalar(3), -scalar(4) / scalar(3), scalar(4) / scalar(9), -scalar(4) / scalar(3),
                    scalar(32) / scalar(3), -scalar(4) / scalar(3), -scalar(4) / scalar(3), -scalar(4) / scalar(3), scalar(4) / scalar(9),
                    scalar(1) / scalar(3), -scalar(4) / scalar(3), scalar(1) / scalar(3), -scalar(4) / scalar(3), -scalar(4) / scalar(3),
                    scalar(1) / scalar(3), scalar(4) / scalar(9), scalar(4) / scalar(9), scalar(4) / scalar(9), -scalar(1) / scalar(4),
                    // Row 22
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(13) / scalar(18),
                    scalar(0), scalar(0), scalar(0), -scalar(16) / scalar(9), scalar(0),
                    scalar(0), -scalar(2) / scalar(3), scalar(0), scalar(8) / scalar(9), -scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), -scalar(16) / scalar(9), scalar(0),
                    scalar(0), scalar(8), scalar(0), -scalar(8) / scalar(3), scalar(4) / scalar(9),
                    scalar(0), scalar(0), -scalar(2) / scalar(3), scalar(0), -scalar(8) / scalar(3),
                    scalar(1) / scalar(3), scalar(0), scalar(8) / scalar(9), scalar(4) / scalar(9), -scalar(1) / scalar(4),
                    // Row 23
                    -scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(8) / scalar(9), scalar(0), scalar(0), scalar(0), -scalar(2) / scalar(3),
                    scalar(0), scalar(0), -scalar(16) / scalar(9), scalar(0), scalar(13) / scalar(18),
                    scalar(4) / scalar(9), scalar(0), scalar(0), scalar(0), -scalar(8) / scalar(3),
                    scalar(0), scalar(0), scalar(8), scalar(0), -scalar(16) / scalar(9),
                    scalar(1) / scalar(3), scalar(0), scalar(0), -scalar(8) / scalar(3), scalar(0),
                    -scalar(2) / scalar(3), scalar(4) / scalar(9), scalar(0), scalar(8) / scalar(9), -scalar(1) / scalar(4),
                    // Row 24
                    scalar(0), scalar(0), scalar(0), scalar(0), -scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(8) / scalar(9), scalar(0),
                    scalar(0), -scalar(2) / scalar(3), scalar(0), -scalar(16) / scalar(9), scalar(13) / scalar(18),
                    scalar(0), scalar(0), scalar(0), scalar(4) / scalar(9), scalar(0),
                    scalar(0), -scalar(8) / scalar(3), scalar(0), scalar(8), -scalar(16) / scalar(9),
                    scalar(0), scalar(0), scalar(1) / scalar(3), scalar(0), -scalar(8) / scalar(3),
                    -scalar(2) / scalar(3), scalar(0), scalar(4) / scalar(9), scalar(8) / scalar(9), -scalar(1) / scalar(4),
                    // Row 25
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), -scalar(13) / scalar(12),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    -scalar(3), scalar(0), scalar(0), scalar(4) / scalar(3), -scalar(1) / scalar(4),
                    // Row 26
                    scalar(13) / scalar(18), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    -scalar(32) / scalar(9), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(20) / scalar(3), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), -scalar(32) / scalar(9), scalar(0), scalar(0), scalar(13) / scalar(18),
                    // Row 27
                    -scalar(1) / scalar(4), scalar(4) / scalar(9), scalar(1) / scalar(3), scalar(4) / scalar(9), -scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(8) / scalar(9), -scalar(8) / scalar(3), -scalar(8) / scalar(3), scalar(8) / scalar(9), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    -scalar(2) / scalar(3), scalar(8), -scalar(2) / scalar(3), scalar(0), scalar(0),
                    scalar(0), -scalar(16) / scalar(9), -scalar(16) / scalar(9), scalar(0), scalar(13) / scalar(18),
                    // Row 28
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(13) / scalar(18),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), -scalar(32) / scalar(9), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(20) / scalar(3), scalar(0), scalar(0),
                    scalar(0), scalar(0), -scalar(32) / scalar(9), scalar(0), scalar(13) / scalar(18),
                    // Row 29
                    -scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(4) / scalar(9), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(3),
                    scalar(0), scalar(0), scalar(4) / scalar(9), scalar(0), -scalar(1) / scalar(4),
                    scalar(8) / scalar(9), scalar(0), scalar(0), scalar(0), -scalar(8) / scalar(3),
                    scalar(0), scalar(0), -scalar(8) / scalar(3), scalar(0), scalar(8) / scalar(9),
                    -scalar(2) / scalar(3), scalar(0), scalar(0), scalar(8), scalar(0),
                    -scalar(2) / scalar(3), -scalar(16) / scalar(9), scalar(0), -scalar(16) / scalar(9), scalar(13) / scalar(18),
                    // Row 30
                    scalar(0), scalar(0), scalar(0), scalar(0), -scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(4) / scalar(9), scalar(0),
                    scalar(0), scalar(1) / scalar(3), scalar(0), scalar(4) / scalar(9), -scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(8) / scalar(9), scalar(0),
                    scalar(0), -scalar(8) / scalar(3), scalar(0), -scalar(8) / scalar(3), scalar(8) / scalar(9),
                    scalar(0), scalar(0), -scalar(2) / scalar(3), scalar(0), scalar(8),
                    -scalar(2) / scalar(3), scalar(0), -scalar(16) / scalar(9), -scalar(16) / scalar(9), scalar(13) / scalar(18),
                    // Row 31
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(13) / scalar(18),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), -scalar(32) / scalar(9),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(20) / scalar(3), scalar(0), scalar(0), -scalar(32) / scalar(9), scalar(13) / scalar(18),
                    // Row 32
                    -scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(4) / scalar(3), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    -scalar(3), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(4), scalar(0), scalar(0), -scalar(13) / scalar(12),
                    // Row 33
                    scalar(0), scalar(0), scalar(0), scalar(0), -scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(4) / scalar(3), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), -scalar(3), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(4), scalar(0), -scalar(13) / scalar(12),
                    // Row 34
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), -scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(4) / scalar(3),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    -scalar(3), scalar(0), scalar(0), scalar(4), -scalar(13) / scalar(12),
                    // Row 35
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1);
            }
#pragma endregion

#pragma region son_transform[0]
            {
                son_transform[0] <<
                    // Row 1
                    scalar(1), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 2
                    scalar(1) / scalar(2), scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 3
                    scalar(1) / scalar(4), scalar(1) / scalar(2), scalar(1) / scalar(4), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 4
                    scalar(1) / scalar(8), scalar(3) / scalar(8), scalar(3) / scalar(8), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 5
                    scalar(1) / scalar(16), scalar(1) / scalar(4), scalar(3) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 6
                    scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 7
                    scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 8
                    scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 9
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 10
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 11
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 12
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 13
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 14
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 15
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 16
                    scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 17
                    scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 18
                    scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 19
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 20
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 21
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 22
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 23
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 24
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 25
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 26
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(2), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 27
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 28
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 29
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 30
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 31
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 32
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    // Row 33
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 34
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(0),
                    // Row 35
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(1) / scalar(16);
            }
#pragma endregion

#pragma region son_transform[1]
            {
                son_transform[1] <<
                    // Row 1
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(1) / scalar(16),
                    // Row 2
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    // Row 3
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(4), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16),
                    // Row 4
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    // Row 5
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(16),
                    // Row 6
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    // Row 7
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    // Row 8
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(8),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    // Row 9
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    // Row 10
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    // Row 11
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    // Row 12
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(4),
                    scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    // Row 13
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0),
                    scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    // Row 14
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    // Row 15
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(16),
                    // Row 16
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8),
                    // Row 17
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                    // Row 18
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8),
                    // Row 19
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8),
                    // Row 20
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                    scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    // Row 21
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    // Row 22
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    // Row 23
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8),
                    // Row 24
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8),
                    // Row 25
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(8), scalar(0), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8),
                    // Row 26
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(2), scalar(0), scalar(0), scalar(1) / scalar(4),
                    // Row 27
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4),
                    // Row 28
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0), scalar(1) / scalar(4),
                    // Row 29
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                    scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4),
                    // Row 30
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(1) / scalar(4),
                    // Row 31
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(1) / scalar(2), scalar(1) / scalar(4),
                    // Row 32
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(2), scalar(0), scalar(0), scalar(1) / scalar(2),
                    // Row 33
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0), scalar(1) / scalar(2),
                    // Row 34
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2), scalar(1) / scalar(2),
                    // Row 35
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1);

            }
#pragma endregion

#pragma region son_transform[2]
            {
                son_transform[2] <<
                    // Row 1
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 2
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 3
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(4), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 4
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 5
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                    scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 6
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(8),
                    scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 7
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 8
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 9
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(3) / scalar(8), scalar(0), scalar(3) / scalar(8), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 10
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 11
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 12
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(2), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 13
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0), scalar(1) / scalar(2),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 14
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2), scalar(1) / scalar(2),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 15
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 16
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 17
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 18
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 19
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 20
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 21
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 22
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 23
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 24
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 25
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 26
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 27
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 28
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 29
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 30
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 31
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 32
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0),
                    scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(0),
                    // Row 33
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    // Row 34
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                    // Row 35
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(16);
            }
#pragma endregion

#pragma region son_transform[3]
            {
                son_transform[3] <<
                    // Row 1
                    scalar(1) / scalar(16), scalar(1) / scalar(4), scalar(3) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 2
                    scalar(0), scalar(1) / scalar(8), scalar(3) / scalar(8), scalar(3) / scalar(8), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 3
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(2), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 4
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2), scalar(1) / scalar(2),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 5
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 6
                    scalar(0), scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 7
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 8
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 9
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 10
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 11
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 12
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0),
                    scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 13
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0),
                    scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 14
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0),
                    scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 15
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                    scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 16
                    scalar(0), scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 17
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 18
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 19
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 20
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 21
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 22
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                    scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 23
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 24
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 25
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 26
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 27
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(4), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 28
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(2), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 29
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 30
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                    scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 31
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 32
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 33
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                    // Row 34
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    // Row 35
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(16);
            }
#pragma endregion

#pragma region son_transform[4]
            {
                son_transform[4] <<
                    // Row 1
                    scalar(1) / scalar(16), scalar(1) / scalar(4), scalar(3) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 2
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 3
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 4
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 5
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(16),
                    // Row 6
                    scalar(0), scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 7
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 8
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 9
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    // Row 10
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 11
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 12
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 13
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0),
                    scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 14
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 15
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                    scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 16
                    scalar(0), scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 17
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 18
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 19
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    // Row 20
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 21
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 22
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(3) / scalar(16),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    // Row 23
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 24
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 25
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 26
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 27
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 28
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(4),
                    scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    // Row 29
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 30
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(3) / scalar(16),
                    scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    // Row 31
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 32
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 33
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    // Row 34
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    // Row 35
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(16);
            }
#pragma endregion

#pragma region son_transform[5]
            {
                son_transform[5] <<
                    // Row 1
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(16),
                    // Row 2
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 3
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 4
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 5
                    scalar(1) / scalar(16), scalar(1) / scalar(4), scalar(3) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 6
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0),
                    scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    // Row 7
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 8
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 9
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 10
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    // Row 11
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 12
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 13
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    // Row 14
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 15
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(1) / scalar(16),
                    // Row 16
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0),
                    scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(0),
                    // Row 17
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 18
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 19
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 20
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(0),
                    // Row 21
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 22
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 23
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(0),
                    // Row 24
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 25
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(0),
                    // Row 26
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 27
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 28
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 29
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 30
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 31
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 32
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 33
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 34
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 35
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0);

            }
#pragma endregion

#pragma region son_transform[6]
            {
                son_transform[6] <<
                    // Row 1
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(16),
                    // Row 2
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0),
                    scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    // Row 3
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    // Row 4
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    // Row 5
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(4), scalar(0), scalar(0), scalar(1) / scalar(16),
                    // Row 6
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    // Row 7
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    // Row 8
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    // Row 9
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    // Row 10
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(4),
                    scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    // Row 11
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(8),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    // Row 12
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(4), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16),
                    // Row 13
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    // Row 14
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    // Row 15
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(16),
                    // Row 16
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 17
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 18
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 19
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 20
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 21
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 22
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 23
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 24
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 25
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 26
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 27
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 28
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 29
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 30
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 31
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 32
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 33
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 34
                    scalar(0), scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 35
                    scalar(1) / scalar(16), scalar(1) / scalar(4), scalar(3) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0);
            }
#pragma endregion

#pragma region son_transform[7]
            {
                son_transform[7] <<
                    // Row 1
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(8), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(16),
                    // Row 2
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0),
                    scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(0),
                    // Row 3
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(8), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 4
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 5
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(4), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 6
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    // Row 7
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 8
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 9
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 10
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(8),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 11
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 12
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(4), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 13
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(3) / scalar(16), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 14
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 15
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(4), scalar(0),
                    scalar(0), scalar(3) / scalar(8), scalar(0), scalar(1) / scalar(4), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 16
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    // Row 17
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 18
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 19
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0), scalar(0), scalar(3) / scalar(16),
                    scalar(3) / scalar(16), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 20
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 21
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 22
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(8),
                    scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 23
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 24
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(1) / scalar(8), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(3) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 25
                    scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(0),
                    scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 26
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(1) / scalar(8),
                    scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 27
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 28
                    scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0),
                    scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(0), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 29
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 30
                    scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 31
                    scalar(0), scalar(0), scalar(1) / scalar(16), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(0), scalar(1) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(8), scalar(1) / scalar(16),
                    scalar(1) / scalar(8), scalar(1) / scalar(16), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 32
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 33
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 34
                    scalar(0), scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16),
                    scalar(1) / scalar(16), scalar(3) / scalar(16), scalar(3) / scalar(16), scalar(1) / scalar(16), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    // Row 35
                    scalar(1) / scalar(16), scalar(1) / scalar(4), scalar(3) / scalar(8), scalar(1) / scalar(4), scalar(1) / scalar(16),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0),
                    scalar(0), scalar(0), scalar(0), scalar(0), scalar(0);
            }
#pragma endregion


        }
        ~tet3_constant_data() { }

    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
            //mat3_10 o2vec2tensor;
        tensor3i omtensor2vec;
        //mat3_20 o3vec2tensor;
        tensor3i ontensor2vec;
        mat35_35 transform;
        mat4_4 time_transform;
        mat4_4 former_transform;
        mat4_4 latter_transform;
        mat4_4 bern_transform;
        mat35_35 son_transform[8];
    };

    template <typename mat_size>
    class subdivide_tree
    {
    public:
        subdivide_tree() { init(); }
        ~subdivide_tree(){}
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        std::vector<std::vector<mat_size, Eigen::aligned_allocator<mat_size>>> tree_cof;
        void init()
        {
            for (int i = 0; i < 4; ++i)
            {
                std::vector<mat_size, Eigen::aligned_allocator<mat_size>> la;
                la.resize(pow(8, i));
                tree_cof.push_back(std::move(la));
            }
        }
    };
}

