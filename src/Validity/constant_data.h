#include "scalar_def.h"
#include <Eigen/Core>
namespace CABT
{
    class tet2_constant_data
    {
    public:
        tet2_constant_data()
        { 

            //!!!!!!!!!!!!!!!记得看这样行列顺序是不是有问题
            /*o2vec2tensor << scalar(0), scalar(0), scalar(0),
                scalar(0), scalar(0), scalar(1) / scalar(2), 
                scalar(0), scalar(0), scalar(1),
                scalar(0), scalar(1) / scalar(2), scalar(0),
                scalar(0), scalar(1) / scalar(2), scalar(1) / scalar(2),
                scalar(0), scalar(1), scalar(0), 
                scalar(1) / scalar(2), scalar(0), scalar(0),
                scalar(1) / scalar(2), scalar(0), scalar(1) / scalar(2), 
                scalar(1) / scalar(2), scalar(1) / scalar(2), scalar(0), 
                scalar(1), scalar(0), scalar(0);*/

            o2tensor2vec = tensor3i(3, 3, 3);
            o2tensor2vec.setConstant(-1);
            o2tensor2vec(0, 0, 0) = 0; o2tensor2vec(0, 0, 1) = 1; o2tensor2vec(0, 0, 2) = 2; o2tensor2vec(0, 1, 0) = 3; o2tensor2vec(0, 1, 1) = 4;
            o2tensor2vec(0, 2, 0) = 5; o2tensor2vec(1, 0, 0) = 6; o2tensor2vec(1, 0, 1) = 7; o2tensor2vec(1, 1, 0) = 8; o2tensor2vec(2, 0, 0) = 9;

            /*o3vec2tensor << scalar(0), scalar(0), scalar(0),  
                scalar(0), scalar(0), scalar(1) / scalar(3), 
                scalar(0), scalar(0), scalar(2) / scalar(3), 
                scalar(0), scalar(0), scalar(1), 
                scalar(0), scalar(1) / scalar(3), scalar(0),
                scalar(0), scalar(1) / scalar(3), scalar(1) / scalar(3), 
                scalar(0), scalar(1) / scalar(3), scalar(2) / scalar(3), 
                scalar(0), scalar(2) / scalar(3), scalar(0),
                scalar(0), scalar(2) / scalar(3), scalar(1) / scalar(3),
                scalar(0), scalar(1), scalar(0),
                scalar(1) / scalar(3), scalar(0), scalar(0),
                scalar(1) / scalar(3), scalar(0), scalar(1) / scalar(3),
                scalar(1) / scalar(3), scalar(0), scalar(2) / scalar(3),
                scalar(1) / scalar(3), scalar(1) / scalar(3), scalar(0),
                scalar(1) / scalar(3), scalar(1) / scalar(3), scalar(1) / scalar(3),
                scalar(1) / scalar(3), scalar(2) / scalar(3), scalar(0), 
                scalar(2) / scalar(3), scalar(0), scalar(0),
                scalar(2) / scalar(3), scalar(0), scalar(1) / scalar(3),
                scalar(2) / scalar(3), scalar(1) / scalar(3), scalar(0), 
                scalar(1), scalar(0), scalar(0);*/

            o3tensor2vec = tensor3i(4, 4, 4);
            o3tensor2vec.setConstant(-1);
            o3tensor2vec(0, 0, 0) = 0; o3tensor2vec(0, 0, 1) = 1; o3tensor2vec(0, 0, 2) = 2; o3tensor2vec(0, 0, 3) = 3; o3tensor2vec(0, 1, 0) = 4;
            o3tensor2vec(0, 1, 1) = 5; o3tensor2vec(0, 1, 2) = 6; o3tensor2vec(0, 2, 0) = 7; o3tensor2vec(0, 2, 1) = 8; o3tensor2vec(0, 3, 0) = 9;
            o3tensor2vec(1, 0, 0) = 10; o3tensor2vec(1, 0, 1) = 11; o3tensor2vec(1, 0, 2) = 12; o3tensor2vec(1, 1, 0) = 13; o3tensor2vec(1, 1, 1) = 14;
            o3tensor2vec(1, 2, 0) = 15; o3tensor2vec(2, 0, 0) = 16; o3tensor2vec(2, 0, 1) = 17; o3tensor2vec(2, 1, 0) = 18; o3tensor2vec(3, 0, 0) = 19;

            time_transform.setConstant(0);
            /*time_transform << scalar(1), scalar(0), scalar(0), scalar(0),
                -scalar(11) / scalar(2), scalar(9), -scalar(9) / scalar(2), scalar(1),
                scalar(9), -scalar(45) / scalar(2), scalar(18), -scalar(9) / scalar(2),
                -scalar(9) / scalar(2), scalar(27) / scalar(2), -scalar(27) / scalar(2), scalar(9) / scalar(2);*/
            time_transform <<
                scalar(1), -scalar(11) / scalar(2), scalar(9), -scalar(9) / scalar(2),
                scalar(0), scalar(9), -scalar(45) / scalar(2), scalar(27) / scalar(2),
                scalar(0), -scalar(9) / scalar(2), scalar(18), -scalar(27) / scalar(2),
                scalar(0), scalar(1), -scalar(9) / scalar(2), scalar(9) / scalar(2);

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
        //mat3_10 o2vec2tensor;
        tensor3i o2tensor2vec;
        //mat3_20 o3vec2tensor;
        tensor3i o3tensor2vec;
        mat20_20 transform;
        mat4_4 time_transform;
        mat20_20 son_transform[8];
    };

    class subdivide_tree
    {
    public:
        subdivide_tree() { init(); }
        ~subdivide_tree(){}
    public:
        std::vector<std::vector<mat20_4>> tree_cof;
        void init()
        {
            for (int i = 0; i < 4; ++i)
            {
                std::vector<mat20_4> la;
                la.resize(pow(8, i));
                tree_cof.push_back(std::move(la));
            }
        }
    };
}

