/*************************************************************************
【文件名】 Exporter_obj.hpp
【功能模块和目的】 obj导出器声明
【开发者及日期】 黄靖宸 2024/8/4
【更改记录】
*************************************************************************/

#ifndef Exporter_obj_hpp
#define Exporter_obj_hpp

//Exporter所属头文件
#include "Exporter.hpp"
//Model3D所属头文件
#include "Model3D.hpp"
//std::ofstream所属头文件
#include <fstream>

/*************************************************************************
【类名】 Exporter_obj
【功能】 obj导出器类
【接口说明】
    默认构造函数
    虚析构函数（可能做基类）
    导出至文件
【开发者及日期】 黄靖宸 2024/8/4
【更改记录】
*************************************************************************/
class Exporter_obj : public Exporter{
public:
    //默认构造函数
    Exporter_obj();
    //无拷贝构造
    Exporter_obj(const Exporter_obj& Source) = delete;
    //无赋值运算符
    Exporter_obj& operator=(const Exporter_obj& Source) = delete;
    //虚析构函数（可能做基类）
    virtual ~Exporter_obj() = default;
    //导出至文件
    virtual void Write_File(std::ofstream& Stream, Model3D Model) const override;
};

#endif /* Exporter_obj_hpp */