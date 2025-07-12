/*************************************************************************
【文件名】 Point3D.cpp
【功能模块和目的】 三维点类实现
【开发者及日期】 黄靖宸 2024/8/1
【更改记录】
*************************************************************************/

//自身所属头文件
#include "Point3D.hpp"
//sqrt所属头文件
#include <math.h>

/*************************************************************************
【函数名称】 Point3D
【函数功能】 默认构造函数，默认为坐标原点
【参数】 无
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/1
【更改记录】
*************************************************************************/
Point3D::Point3D() : Point3D(0.0, 0.0, 0.0){

}

/*************************************************************************
【函数名称】 Point3D
【函数功能】 带参构造函数，构造指定坐标点
【参数】 double x, double y, double z
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/1
【更改记录】
*************************************************************************/
Point3D::Point3D(double x, double y, double z){
    My_x = x;
    My_y = y;
    My_z = z;
}

/*************************************************************************
【函数名称】 Point3D
【函数功能】 拷贝构造函数，拷贝构造指定点
【参数】 const Point3D& Source
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/1
【更改记录】
*************************************************************************/
Point3D::Point3D(const Point3D& Source){
    My_x = Source.Get_x();
    My_y = Source.Get_y();
    My_z = Source.Get_z();
}

/*************************************************************************
【函数名称】 operator=
【函数功能】 赋值运算符overload
【参数】 const Point3D Source
【返回值】 三维点自身的引用
【开发者及日期】 黄靖宸 2024/8/1
【更改记录】
*************************************************************************/
Point3D& Point3D::operator=(const Point3D Source){
    My_x = Source.Get_x();
    My_y = Source.Get_y();
    My_z = Source.Get_z();
    return *this;
}

/*************************************************************************
【函数名称】 Change_Point
【函数功能】 更改其中一个点的坐标为(x, y, z)
【参数】 double x, double y, double z
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/1
【更改记录】
*************************************************************************/
void Point3D::Change_Point(double x, double y, double z){
    My_x = x;
    My_y = y;
    My_z = z;
}

/*************************************************************************
【函数名称】 Get_x
【函数功能】 获取x坐标
【参数】 无
【返回值】 点的x坐标
【开发者及日期】 黄靖宸 2024/8/1
【更改记录】
*************************************************************************/
double Point3D::Get_x() const{
    return My_x;
}

/*************************************************************************
【函数名称】 Get_y
【函数功能】 获取y坐标
【参数】 无
【返回值】 点的y坐标
【开发者及日期】 黄靖宸 2024/8/1
【更改记录】
*************************************************************************/
double Point3D::Get_y() const{
    return My_y;
}

/*************************************************************************
【函数名称】 Get_z
【函数功能】 获取z坐标
【参数】 无
【返回值】 点的z坐标
【开发者及日期】 黄靖宸 2024/8/1
【更改记录】
*************************************************************************/
double Point3D::Get_z() const{
    return My_z;
}

/*************************************************************************
【函数名称】 Get_xyz_vector
【函数功能】 获取坐标字符串
【参数】 无
【返回值】 值为"x y z"的string
【开发者及日期】 黄靖宸 2024/8/1
【更改记录】
*************************************************************************/
std::string Point3D::Get_xyz_vector() const{
    std::string x = std::to_string(My_x);
    std::string y = std::to_string(My_y);
    std::string z = std::to_string(My_z);
    std::string Result = x + " " + y + " " + z;
    return Result;
}

/*************************************************************************
【函数名称】 operator!=
【函数功能】 判断与另一个点是否不同
【参数】 const Point3D& Point_check
【返回值】 bool变量，true代表不同，false代表相同
【开发者及日期】 黄靖宸 2024/8/1
【更改记录】
*************************************************************************/
bool Point3D::operator!=(const Point3D& Point_check){
    double X_Check = Point_check.My_x;
    double Y_Check = Point_check.My_y;
    double Z_Check = Point_check.My_z;
    const double EPS = 1e-8;
    if (abs(X_Check - My_x) > EPS || 
        abs(Y_Check - My_y) > EPS || 
        abs(Z_Check - My_z) > EPS) {
        return true;
    }
    else {
        return false;
    }
}

/*************************************************************************
【函数名称】 operator==
【函数功能】 判断与另一个点是否相同
【参数】 const Point3D& Point_check
【返回值】 bool变量，true代表相同，false代表不同
【开发者及日期】 黄靖宸 2024/8/1
【更改记录】
*************************************************************************/
bool Point3D::operator==(const Point3D& Point_check){
    double X_Check = Point_check.My_x;
    double Y_Check = Point_check.My_y;
    double Z_Check = Point_check.My_z;
    const double EPS = 1e-8;
    if (abs(X_Check - My_x) < EPS && 
        abs(Y_Check - My_y) < EPS && 
        abs(Z_Check - My_z) < EPS) {
        return true;
    }
    else {
        return false;
    }
}

/*************************************************************************
【函数名称】 operator<
【函数功能】 与另一个点按照xyz顺序比较坐标大小
【参数】 const Point3D& Point_check
【返回值】 bool变量，true代表本点坐标更小，false代表point_check坐标更小
【开发者及日期】 黄靖宸 2024/8/1
【更改记录】
*************************************************************************/
bool Point3D::operator<(const Point3D& Point_check){
    double X_Check = Point_check.My_x;
    double Y_Check = Point_check.My_y;
    double Z_Check = Point_check.My_z;
    if (My_x < X_Check) {
        return true;
    }
    else if (My_x > X_Check) {
        return false;
    }
    if (My_y < Y_Check) {
        return true;
    }
    else if (My_y > Y_Check) {
        return false;
    }
    if (My_z < Z_Check) {
        return true;
    }
    else if (My_z > Z_Check) {
        return false;
    }
    return false;
}

/*************************************************************************
【函数名称】 Distance
【函数功能】 获得两点之间的距离
【参数】 const Point3D& Point_1, const Point3D& Point_2
【返回值】 两点间距离
【开发者及日期】 黄靖宸 2024/8/1
【更改记录】
*************************************************************************/
double Point3D::Distance(const Point3D& Point_1, const Point3D& Point_2){
    double X_Delta = Point_1.My_x - Point_2.My_x;
    double Y_Delta = Point_1.My_y - Point_2.My_y;
    double Z_Delta = Point_1.My_z - Point_2.My_z;
    double Distance_Points = sqrt(X_Delta * X_Delta + 
    Y_Delta * Y_Delta + Z_Delta * Z_Delta);
    return Distance_Points;
}

/*************************************************************************
【函数名称】 To_Distance
【函数功能】 获取本点与另一个点之间的距离
【参数】 const Point3D& Point
【返回值】 两点间距离
【开发者及日期】 黄靖宸 2024/8/1
【更改记录】
*************************************************************************/
double Point3D::To_Distance(const Point3D& Point){
    double X_Delta = Point.My_x - My_x;
    double Y_Delta = Point.My_y - My_y;
    double Z_Delta = Point.My_z - My_z;
    double Distance_Points = sqrt(X_Delta * X_Delta + 
    Y_Delta * Y_Delta + Z_Delta * Z_Delta);
    return Distance_Points;
}