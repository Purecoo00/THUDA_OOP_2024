/*************************************************************************
【文件名】 Exporter.hpp
【功能模块和目的】 导出器类声明
【开发者及日期】 黄靖宸 2024/8/4
【更改记录】
*************************************************************************/

#ifndef Exporter_hpp
#define Exporter_hpp

//std::string所属头文件
#include <string>
//std::ofstream所属头文件
#include <fstream>
//Model3D所属头文件
#include "Model3D.hpp"

/*************************************************************************
【类名】 Exporter
【功能】 导出器类
【接口说明】
    默认构造函数
    虚析构函数（用作基类）
    获取文件类型
    设置文件类型
    虚函数：导出至文件（用作基类）
【开发者及日期】 黄靖宸 2024/8/4
【更改记录】
*************************************************************************/
class Exporter{
private:
    std::string My_Type;

protected:
    //默认构造函数
    Exporter();
    //拷贝构造函数
    Exporter(const Exporter& Source) = delete;
    //赋值运算符overload
    Exporter& operator=(const Exporter& Source) = delete;
    //虚析构函数（用作基类）
    virtual ~Exporter() = default;

public:
    //设置文件类型
    unsigned int Set_Type(std::string Type);
    //获取文件类型
    std::string Get_Type() const;
    //虚函数：导出至文件（用作基类）
    virtual void Write_File(std::ofstream& Stream, Model3D Model) const = 0;
};

#endif /* Exporter_hpp */