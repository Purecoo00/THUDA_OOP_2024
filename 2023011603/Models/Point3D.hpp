/*************************************************************************
【文件名】 Point3D.hpp
【功能模块和目的】 三维点类声明
【开发者及日期】 黄靖宸 2024/8/1
【更改记录】
*************************************************************************/

#ifndef Point3D_hpp
#define Point3D_hpp

//std::string所属头文件
#include <string>

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
    获取x/y/z坐标
    获取坐标字符串
    判断与另一个点是否不同
    判断与另一个点是否相同
    与另一个点按照xyz顺序比较坐标大小
    获得两点之间的距离
    获取本点与另一个点之间的距离
【开发者及日期】 黄靖宸 2024/8/1
【更改记录】
*************************************************************************/

class Point3D{
private:
    double My_x;
    double My_y;
    double My_z;

public:
    //默认构造函数
    Point3D();
    //带参构造函数
    Point3D(double x, double y, double z);
    //拷贝构造函数
    Point3D(const Point3D& Source);
    //赋值运算符overload
    Point3D& operator=(const Point3D Source);
    //虚析构函数（可能做基类）
    virtual ~Point3D() = default;
    //更改其中一个点的坐标
    void Change_Point(double x, double y, double z);
    //获取x坐标
    double Get_x() const;
    //获取y坐标
    double Get_y() const;
    //获取z坐标
    double Get_z() const;
    //获取坐标字符串
    std::string Get_xyz_vector() const;
    //判断与另一个点是否不同
    bool operator!=(const Point3D& point_check);
    //判断与另一个点是否相同
    bool operator==(const Point3D& point_check);
    //与另一个点按照xyz顺序比较坐标大小
    bool operator<(const Point3D& point_check);
    //获得两点之间的距离
    static double Distance(const Point3D& point_1, const Point3D& point_2);
    //获取本点与另一个点之间的距离
    double To_Distance(const Point3D& point);
};

#endif /* Point3D_hpp */