/*************************************************************************
【文件名】 Line3D.cpp
【功能模块和目的】 三维线类实现
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/

//自身所属头文件
#include "Line3D.hpp"
//std::vector所属头文件
#include <vector>

/*************************************************************************
【函数名称】 Line3D
【函数功能】 
    默认构造函数
    第一个点设置为(1.0, 0.0, 0.0)
    第二个点设置为(0.0, 1.0, 0.0)
【参数】 无
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
Line3D::Line3D() : Line3D(Point3D(1.0, 0.0, 0.0), 
                          Point3D(0.0, 1.0, 0.0)) {

}

/*************************************************************************
【函数名称】 Line3D
【函数功能】 带参构造函数，给定两个点进行构造，同时算出线长度赋值
【参数】 const Point3D& Point_1, const Point3D& Point_2
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
Line3D::Line3D(const Point3D& Point_1, 
               const Point3D& Point_2){
    My_Point_1 = Point_1;
    My_Point_2 = Point_2;
}

/*************************************************************************
【函数名称】 Line3D
【函数功能】 拷贝构造函数
【参数】 const Line3D& Source
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
Line3D::Line3D(const Line3D& Source) {
    My_Point_1 = Source.Get_Point_1();
    My_Point_2 = Source.Get_Point_2();
}

/*************************************************************************
【函数名称】 operator=
【函数功能】 赋值运算符overload
【参数】 const Line3D Source
【返回值】 三维线自身的引用
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
Line3D& Line3D::operator=(const Line3D& Source) {
    My_Point_1 = Source.Get_Point_1();
    My_Point_2 = Source.Get_Point_2();
    return *this;
}

/*************************************************************************
【函数名称】 Change_Point_In_Line
【函数功能】
    更改其中一个点的坐标为给定值，n=1改变第一个点，n=2改变第二个点
    如有非法操作则返回对应的错误码
【参数】 double x, double y, double z, unsigned int Point_Number
【返回值】 错误码
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
unsigned int Line3D::Change_Point_In_Line(
    double x, double y, double z, unsigned int Point_Number){
    Point3D Point_Temp = Point3D(x, y, z);
    if (Point_Number == 1 || Point_Number == 2) {
        if (Point_Number == 1 && Point_Temp != My_Point_2) {
            My_Point_1.Change_Point(x, y, z);
            return 0;
        }
        else if (Point_Number == 2 && Point_Temp != My_Point_1) {
            My_Point_2.Change_Point(x, y, z);
            return 0;
        }
        else {
            /*ERROR: Same_Point_When_Change_Line*/
            return 1;
        }
    }
    else {
        /*ERROR: Point_Error_When_Change_Line*/
        return 2;
    }
}

/*************************************************************************
【函数名称】 operator==
【函数功能】 判断与另一条线是否相同
【参数】 const Line3D& Line_Check
【返回值】 bool变量，true相同，false不同
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
bool Line3D::operator==(const Line3D& Line_Check){
    Point3D Point1_check = Line_Check.My_Point_1;
    Point3D Point2_check = Line_Check.My_Point_2;
    std::vector<Point3D> My_Points{My_Point_1, My_Point_2};
    std::vector<Point3D> Check_Points{Point1_check, Point2_check};
    bool Flag = false;
    for (size_t i = 0; i < 2; i++) {
        if (My_Points[0] == Check_Points[i] && 
            My_Points[1] == Check_Points[1-i]) {
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
const Point3D& Line3D::Get_Point_1() const{
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
const Point3D& Line3D::Get_Point_2() const{
    return My_Point_2;
}