#include "ScannerS/Models/CPVDM.hpp"
#include "catch.hpp"

#include <Eigen/Core>
#include <array>
#include <cmath>
#include <vector>

namespace {

const std::vector<ScannerS::Models::CPVDM::AngleInput> testpoints{
    {110.49, 692.92, 565.6, 64.06, 0.91, -0.41, 0.02, 2.68, 2.43, -4.58,
     217238., 279689., 246.08},
    {154.25, 351.42, 822.88, 307.61, 0.98, 0.84, 0.07, 3.47, 9.42, 15.87,
     161453., 929693., 304.43},
    {990.09, 215.21, 232.75, 893.66, 0.58, -1.55, -0.04, 4.79, 14.24, 20.69,
     611383., 702599., 687.87},
    {171.12, 578.57, 817.77, 122.12, -1.01, 0.78, -1.43, 6.45, 9.89, 18.19,
     525864., 259241., 104.41},
    {344.38, 706.88, 382.01, 858.26, -0.59, -0.58, -0.4, 4.05, 14.48, 20.91,
     449311., 647112., 54.},
    {910.07, 434.8, 622.76, 187.03, 0.58, 1.55, 0.27, 8.37, 12.73, 1.46,
     113837., 212934., 69.85},
    {652.77, 976.21, 571.95, 523.63, -1.4, -0.44, -1.3, 4.96, 13.7, -2.13,
     75402.4, 824665., 190.06},
    {436.17, 238.69, 327.91, 982.09, -0.67, 0.91, 0.54, 2.36, 15.77, 20.27,
     72182., 115322., 364.67},
    {982.43, 784.39, 597.13, 272.7, 0.3, 1.05, 0.26, 7.56, 0.89, 9.05, 617086.,
     194674., 440.45},
    {589.64, 648.49, 586.01, 418.5, -0.37, -1.46, 0.82, 2.85, 9.29, -24.48,
     -7087.2, 141280., 948.05},
    {408.18, 863.95, 670.87, 157.8, 0.02, 0.21, -1.44, 4.55, 16.14, -15.83,
     437587., 630691., 671.23},
    {385.59, 462.69, 964.6, 287.73, 1.04, 0.78, 0.7, 3.61, 13.99, 14.95,
     947521., 656427., 548.63},
    {416.56, 387.86, 141.11, 726.07, 0.91, 0.88, -0.8, 8.31, 5.94, -8.54,
     468653., 756391., 197.75},
    {704.42, 434.08, 56.54, 130.28, 0.46, -0.85, -0.7, 4.22, 9.45, -4.9,
     214529., 835192., 520.45},
    {944.71, 663.23, 428.32, 852.54, -0.07, 0.24, -0.09, 6.97, 7.88, 5.44,
     601463., 993517., 263.37},
    {725.68, 197.02, 186.45, 809.57, -0.94, -0.85, -0.07, 0.01, 8.95, -7.27,
     364592., 585931., 308.65},
    {471.58, 896.16, 78.35, 188.11, 1.54, 1.56, -1.45, 6.31, 10.03, 20.81,
     915646., 871012., 647.22},
    {195.24, 725.02, 661.46, 279.36, -0.09, -1.5, -1.22, 7.19, 13.08, 21.45,
     515075., 32944.7, 460.7},
    {547.8, 547.53, 904.38, 660.27, 0.54, 0.33, 1.39, 4.01, 16.78, -5.02,
     30253.2, 932093., 986.74},
    {167.43, 308.52, 827.47, 824.05, 0.57, 0.77, -1.4, 6.52, 15.78, -13.08,
     636804., 409285., 823.15},
    {103.58, 116.22, 489.45, 110.22, -0.93, 1.53, 0.45, 3.95, 11.42, -14.87,
     493574., 321975., 121.64},
    {302.04, 547.96, 826.88, 290.17, 0.29, 0.98, -0.98, 3.41, 2.46, -6.69,
     94511., 814028., 584.15},
    {256.74, 197.91, 596.39, 593.78, 0.08, 0.43, -1.53, 5.86, 10.37, 17.1,
     218303., 106861., 277.19},
    {435.83, 608.4, 800.39, 864.55, 0.97, 0.12, -0.34, 6.59, 15.45, 3.89,
     732902., 605125., 774.1},
    {966.95, 744.3, 991.09, 987.96, -0.24, 1.46, -1.28, 2.34, 0.64, 13.14,
     340278., 375799., 334.},
    {851.41, 909.67, 935.8, 452.11, -0.66, -0.05, 1.1, 1.89, 12.46, 22.62,
     98936.4, 159319., 352.89},
    {482.68, 882.63, 734.94, 583.25, 0.26, -0.73, 0.01, 3.05, 6.77, 8.46,
     403185., 703031., 702.4},
    {178.18, 107.5, 754.87, 372.33, 0.84, -1.32, -0.03, 2.94, 14.04, -5.55,
     316436., 9539.34, 124.49},
    {887.95, 816.37, 469.11, 479.85, -1.31, 0.36, 0.94, 0.84, 15.63, -7.28,
     438160., 424526., 127.85},
    {464.86, 136.78, 772.98, 567.7, 1.18, -1.17, 0.3, 1.14, 2.29, 16.47,
     265281., 897534., 67.69},
    {248.96, 986.02, 717.61, 140.09, 1.4, 1.21, 0.42, 6.09, 14.95, -21.07,
     932788., 993192., 308.51},
    {377.36, 311.35, 914.91, 636.02, 0.04, -1.25, 1.54, 8.34, 14.34, 19.73,
     736989., 564307., 531.21},
    {990.57, 70.88, 935.44, 678., -0.8, 1.39, -0.04, 1.46, 0.69, -6.34, 610799.,
     522727., 915.71},
    {777.81, 270.21, 515.17, 920.67, -0.27, 0.35, 0.17, 1.72, 3.3, 11.53,
     938295., 923032., 158.91},
    {803.65, 848.99, 486.41, 90.46, 1.34, 0.66, 1.06, 0.37, 13.46, -25.81,
     619159., 315309., 409.37},
    {375.76, 587.33, 621.74, 326.56, 1.47, -0.69, -0.21, 2.66, 12.23, -17.81,
     308474., 732355., 438.14},
    {825.52, 909.64, 964., 284., 1.22, 1.26, -0.28, 0.97, 8.43, -6.18, 269144.,
     585570., 256.05},
    {930.91, 480.93, 915.75, 906.41, -0.13, 0.55, 0.74, 3.96, 14.17, -11.76,
     540180., 697205., 692.36},
    {556.99, 391.47, 189.8, 543.61, 1.41, 0.92, -1.2, 3.03, 15.37, 9.22,
     892458., 445071., 43.69},
    {978.43, 782.08, 932.13, 625.58, 1.33, 0., 0.67, 5.89, 3.47, -2.78, 916995.,
     676833., 924.35},
    {179.54, 928., 925.58, 440.1, -1.15, -0.68, 0.96, 2.21, 7.01, 21.37,
     637369., 143792., 384.55},
    {779.91, 539.53, 362.06, 523.69, 1.5, -0.21, -1.01, 4.42, 13.41, -23.57,
     638324., 726406., 39.56},
    {503.72, 442.14, 391.24, 364.18, 0.8, 1.48, 1.1, 6.72, 13.68, -21.94,
     -2926.87, 281618., 895.76},
    {149.51, 501.61, 568.89, 387.71, -0.86, -1.39, 1.29, 0.33, 12.27, -5.93,
     474686., 890904., 813.85},
    {792.96, 159.05, 460.55, 213.64, -1.18, 0.84, -0.25, 6.43, 12.03, 6.81,
     603268., 273481., 818.21},
    {426.28, 479.76, 274.25, 236.12, 1.33, -0.36, 0.42, 5.88, 3.16, -4.76,
     426334., 215839., 97.29},
    {894.4, 564.3, 863.93, 628.57, 0.34, 1.28, 0.18, 3.74, 9.39, 18.02, 530837.,
     477007., 990.66},
    {41.21, 258.51, 784.63, 393.11, 0.72, -1.2, 0.98, 6.9, 6.02, -6.42, 916815.,
     41342.9, 595.42},
    {862.15, 54.06, 681.28, 988.03, -0.39, -0.61, 1.44, 4.86, 9.98, 11.28,
     105444., 730876., 978.61},
    {178.89, 828.27, 246.34, 266.87, -0.13, 1.04, -0.12, 0.89, 16.99, 18.25,
     843898., 245727., 940.23}};
}

using namespace ScannerS;

TEST_CASE("Generate CPVDM", "[unit][CPVDM][gen]") {
  for (const auto &i : testpoints) {
    Models::CPVDM::ParameterPoint p{i};
    if (Models::CPVDM::Valid(p)) {
      REQUIRE(p.mHi[0] < p.mHi[1]);
      REQUIRE(p.mHi[1] < p.mHi[2]);

      REQUIRE(Approx(p.mHi[2] * p.mHi[2]) ==
              -(std::pow(p.mHi[0], 2) * p.R(0, 0) * p.R(0, 1) +
                std::pow(p.mHi[1], 2) * p.R(1, 0) * p.R(1, 1)) /
                  (p.R(2, 0) * p.R(2, 1)));
    }
  }
}
