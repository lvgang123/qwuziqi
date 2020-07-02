/**
 * 纯C++头文件 整理:lvgang 2020-6-30
 */
#include <iostream>
#include <memory>
#include <math.h>
#include "help/typedef.h"

using namespace std;

const double PI = atan(1.)*4.;
const float EPSINON = 0.0000001;
const int Product = 1;
const int Zoom = 2;

struct CPoint
{
    int x;
    int y;
};
