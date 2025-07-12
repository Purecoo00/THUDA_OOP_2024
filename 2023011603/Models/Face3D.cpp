/*************************************************************************
【文件名】 Face3D.cpp
【功能模块和目的】 三维面类实现
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/

//自身所属头文件
#include "Face3D.hpp"
//sqrt所属头文件
#include <math.h>
//std::vector所属头文件
#include <vector>

/*************************************************************************
【函数名称】 Face3D
【函数功能】
    默认构造函数
    第一个点为(1.0, 0.0, 0.0)
    第二个点为(0.0, 1.0, 0.0)
    第三个点为(0.0, 0.0, 1.0)
【参数】 无
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
Face3D::Face3D() : Face3D(Point3D(1.0, 0.0, 0.0),
                          Point3D(0.0, 1.0, 0.0),
                          Point3D(0.0, 0.0, 1.0)){

}

/*************************************************************************
【函数名称】 Face3D
【函数功能】 带参构造函数，三个点分别设置为给定点，同时计算面积
【参数】 const Point3D& Point_1, 
        const Point3D& Point_2, 
        const Point3D& Point_3
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
Face3D::Face3D(const Point3D& Point_1, 
               const Point3D& Point_2, 
               const Point3D& Point_3){
    My_Point_1 = Point_1;
    My_Point_2 = Point_2;
    My_Point_3 = Point_3;
}

/*************************************************************************
【函数名称】 Face3D
【函数功能】 拷贝构造函数
【参数】 const Face3D& Source
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
Face3D::Face3D(const Face3D& Source){
    My_Point_1 = Source.Get_Point_1();
    My_Point_2 = Source.Get_Point_2();
    My_Point_3 = Source.Get_Point_3();
}

/*************************************************************************
【函数名称】 operator=
【函数功能】 赋值运算符overload
【参数】 const Face3D& Source
【返回值】 三维面自身的引用
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
Face3D& Face3D::operator=(const Face3D& Source){
    My_Point_1 = Source.Get_Point_1();
    My_Point_2 = Source.Get_Point_2();
    My_Point_3 = Source.Get_Point_3();
    return *this;
}

/*************************************************************************
【函数名称】 Change_Point_In_Face
【函数功能】
    更改其中一个点的坐标，n=1修改第一个点，以此类推至n=3
    如有非法操作，返回对应的错误码
【参数】 double x, double y, double z, unsigned int Point_Number
【返回值】 错误码
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
unsigned int Face3D::Change_Point_In_Face(double x, double y, double z, 
    unsigned int Point_Number){
    Point3D Point_Temp = Point3D(x, y, z);
    if (Point_Number >= 1 && Point_Number <= 3) {
        if (Point_Number == 1 && 
            Point_Temp != My_Point_2 && 
            Point_Temp != My_Point_3) {
            My_Point_1.Change_Point(x, y, z);
            return 0;
        }
        else if (Point_Number == 2 && 
                 Point_Temp != My_Point_1 && 
                 Point_Temp != My_Point_3) {
            My_Point_2.Change_Point(x, y, z);
            return 0;
        }
        else if (Point_Number == 3 && 
                 Point_Temp != My_Point_1 && 
                 Point_Temp != My_Point_2) {
            My_Point_3.Change_Point(x, y, z);
            return 0;
        }
        else {
            /*ERROR: Same_Point_When_Change_Face*/
            return 5;
        }
    }
    else {
        /*ERROR: Point_Error_When_Change_Face*/
        return 6;
    }
}

/*************************************************************************
【函数名称】 operator==
【函数功能】 判断与另一个面是否相同
【参数】 const Face3D& Face_check
【返回值】 bool变量，true相同，false不同
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
bool Face3D::operator==(const Face3D& Face_check){
    Point3D Point1_check = Face_check.My_Point_1;
    Point3D Point2_check = Face_check.My_Point_2;
    Point3D Point3_check = Face_check.My_Point_3;
    std::vector<Point3D> My_Points{My_Point_1, My_Point_2, My_Point_3};
    std::vector<Point3D> Check_Points{Point1_check, Point2_check, Point3_check};
    bool Flag = false;
    for (size_t i = 0; i < 3; i++) {
        if (My_Points[0] == Check_Points[i] && 
            My_Points[1] == Check_Points[(i + 1) % 3] &&
            My_Points[2] == Check_Points[(i + 2) % 3]) {
            Flag = true;
            break;
        }
        if (My_Points[0] == Check_Points[i] && 
            My_Points[1] == Check_Points[(i + 2) % 3] &&
            My_Points[2] == Check_Points[(i + 1) % 3]) {
            Flag = true;
            break;
        }
    }
    return Flag;
}

/*************************************************************************
【函数名称】 Get_Point_1
【函数功能】 获取第1个点
【参数】 无
【返回值】 const Point3D&类型，第1个点
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
const Point3D& Face3D::Get_Point_1() const{
    return My_Point_1;
}

/*************************************************************************
【函数名称】 Get_Point_2
【函数功能】 获取第2个点
【参数】 无
【返回值】 const Point3D&类型，第2个点
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
const Point3D& Face3D::Get_Point_2() const{
    return My_Point_2;
}

/*************************************************************************
【函数名称】 Get_Point_3
【函数功能】 获取第3个点
【参数】 无
【返回值】 const Point3D&类型，第3个点
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
const Point3D& Face3D::Get_Point_3() const{
    return My_Point_3;
}

/*************************************************************************
【函数名称】 Get_Area
【函数功能】 获取面积
【参数】 const Point3D& Point_1, 
    const Point3D& Point_2, const Point3D& Point_3
【返回值】 double类型，面积
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
double Face3D::Get_Area(const Point3D& Point_1, 
    const Point3D& Point_2, const Point3D& Point_3){
    double Len1 = Point3D::Distance(Point_1, Point_2);
    double Len2 = Point3D::Distance(Point_2, Point_3);
    double Len3 = Point3D::Distance(Point_3, Point_1);
    double Half_C = (Len1 + Len2 + Len3) / 2;
    double Area = sqrt(Half_C * (Half_C - Len1) * 
    (Half_C - Len2) * (Half_C - Len3));
    return Area;
}