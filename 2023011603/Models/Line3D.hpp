/*************************************************************************
【文件名】 Line3D.hpp
【功能模块和目的】 三维线类声明
【开发者及日期】 黄靖宸 2024/8/1
【更改记录】
*************************************************************************/

#ifndef Line3D_hpp
#define Line3D_hpp

//Point3D类型所属头文件
#include "Point3D.hpp"

/*************************************************************************
【类名】 Point3D
【功能】 三维点类
【接口说明】
    默认构造函数
    带参构造函数
    拷贝构造函数
    赋值运算符overload
    虚析构函数（可能做基类）
    更改其中一个点的坐标
    判断与另一条线是否相同
    获取第1/2个点
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/

class Line3D{
private:
    Point3D My_Point_1;
    Point3D My_Point_2;

public:
    //默认构造函数
    Line3D();
    //带参构造函数
    Line3D(const Point3D& Point_1, const Point3D& Point_2);
    //拷贝构造函数
    Line3D(const Line3D& Source);
    //赋值运算符overload
    Line3D& operator=(const Line3D& Source);
    //虚析构函数（可能做基类
    virtual ~Line3D() = default;
    //更改其中一个点的坐标
    unsigned int Change_Point_In_Line(double x, double y, double z, unsigned int Point_Number);
    //判断与另一条线是否相同
    bool operator==(const Line3D& Line_check);
    //获取第1个点
    const Point3D& Get_Point_1() const;
    //获取第2个点
    const Point3D& Get_Point_2() const;
};

#endif /* Line3D_hpp */