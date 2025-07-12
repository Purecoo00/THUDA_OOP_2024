/*************************************************************************
【文件名】 Model3D.hpp
【功能模块和目的】 三维模型类声明
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/

#ifndef Model3D_hpp
#define Model3D_hpp

//std::vector所属头文件
#include <vector>
//std::string所属头文件
#include <string>
//Point3D类型所属头文件
#include "Point3D.hpp"
//Line3D类型所属头文件
#include "Line3D.hpp"
//Face3D类型所属头文件
#include "Face3D.hpp"

/*************************************************************************
【类名】 Model3D
【功能】 三维模型类
【接口说明】
    默认构造函数
    带参构造函数
    拷贝构造函数
    赋值运算符overload
    虚析构函数（可能做基类）
    以多种参数方式添加三维线
    以多种参数方式添加三维面
    添加注释
    设置模型名
    以多种参数形式删除三维线
    以多种参数形式删除三维面
    修改指定三维线的一个点
    修改指定三维面的一个点
    获取三维线集合
    获取三维面集合
    获取注释
    获取三维线数量
    获取三维线总长度
    获取三维面数量
    获取三维面总面积
    获取三维点数量
    获取囊括所有元素正方体的最小边长
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
class Model3D{
private:
    std::vector<Line3D>       My_Line_List;
    std::vector<Face3D>       My_Face_List;
    std::vector<std::string>  Annotation;

public:
    std::string My_Name;
    //默认构造函数
    Model3D();
    //带参构造函数
    Model3D(const std::vector<Line3D>& Line_List, 
            const std::vector<Face3D>& Face_List);
    //拷贝构造函数
    Model3D(const Model3D& Source);
    //赋值运算符overload
    Model3D& operator=(const Model3D& Source);
    //虚析构函数（可能做基类），无动态构造成员，默认实现
    virtual ~Model3D() = default;
    //添加三维线
    unsigned int Insert_Line(Point3D& Point1, Point3D& Point2);
    //添加三维线
    unsigned int Insert_Line(Line3D& Line);
    //添加三维面
    unsigned int Insert_Face(Point3D& Point1, Point3D& Point2, Point3D& Point3);
    //添加三维面
    unsigned int Insert_Face(Face3D& Face);
    //添加注释
    void Append_Annotaion(std::string Annotation);
    //设置模型名
    void Set_Name(std::string Name);
    //删除三维线
    unsigned int Delete_Line(Point3D& Point1, Point3D& Point2);
    //删除三维线
    unsigned int Delete_Line(Line3D& Line);
    //删除三维面
    unsigned int Delete_Face(Point3D& Point1, Point3D& Point2, Point3D& Point3);
    //删除三维面
    unsigned int Delete_Face(Face3D& Face);
    //修改指定三维线的一个点
    unsigned int Change_Line(unsigned int Line_Number, double x, double y, double z, unsigned int Point_Number);
    //修改指定三维面的一个点
    unsigned int Change_Face(unsigned int Face_Number, double x, double y, double z, unsigned int Point_Number);
    //获取三维线集合
    std::vector<Line3D>&            Get_Line_List();
    //获取三维面集合
    std::vector<Face3D>&            Get_Face_List();
    //获取注释
    std::vector<std::string>&       Get_Annotation();
    //获取三维线数量
    unsigned int Line_Num()       const;
    //获取三维线总长度
    double       Sum_Line_Lenth() const;
    //获取三维面数量
    unsigned int Face_Num()       const;
    //获取三维面总面积
    double       Sum_Face_Area()  const;
    //获取三维点数量
    unsigned int Point_Num()      const;
    //获取囊括所有元素正方体的最小边长
    double       Cover_Cube()     const;
};

#endif /* Model3D_hpp */