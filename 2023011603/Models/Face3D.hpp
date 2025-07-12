/*************************************************************************
【文件名】 Face3D.hpp
【功能模块和目的】 三维面类声明
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/

#ifndef Face3D_hpp
#define Face3D_hpp

//Point3D类型所属头文件
#include "Point3D.hpp"

/*************************************************************************
【类名】 Face3D
【功能】 三维面类
【接口说明】
    默认构造函数
    带参构造函数
    拷贝构造函数
    赋值运算符overload
    虚析构函数（可能做基类）
    更改其中一个点的坐标
    判断与另一个面是否相同
    获取第1/2/3个点
    计算面积
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/

class Face3D{
private:
    Point3D My_Point_1;
    Point3D My_Point_2;
    Point3D My_Point_3;

public:
    //默认构造函数
    Face3D();
    //带参构造函数
    Face3D(const Point3D& Point_1, const Point3D& Point_2, const Point3D& Point_3);
    //拷贝构造函数
    Face3D(const Face3D& Source);
    //赋值运算符overload
    Face3D& operator=(const Face3D& Source);
    //虚析构函数（可能做基类）
    virtual ~Face3D() = default;
    //更改其中一个点的坐标
    unsigned int Change_Point_In_Face(double x, double y, double z, unsigned int n);
    //判断与另一个面是否相同
    bool operator==(const Face3D& Face_check);
    //获取第1个点
    const Point3D& Get_Point_1() const;
    //获取第2个点
    const Point3D& Get_Point_2() const;
    //获取第3个点
    const Point3D& Get_Point_3() const;
    //计算面积
    static double Get_Area(const Point3D& Point_1, const Point3D& Point_2, const Point3D& Point_3);
};

#endif /* Face3D_hpp */