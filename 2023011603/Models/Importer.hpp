/*************************************************************************
【文件名】 Importer.hpp
【功能模块和目的】 导入器类声明
【开发者及日期】 黄靖宸 2024/8/3
【更改记录】
*************************************************************************/

#ifndef Importer_hpp
#define Importer_hpp

//Model3D所属头文件
#include "Model3D.hpp"
//std::string所属头文件
#include <string>

/*************************************************************************
【类名】 Importer
【功能】 导入器类
【接口说明】
    默认构造函数
    虚析构函数（用作基类）
    设置文件名
    设置文件类型
    虚函数：读入模型（用作基类）
    读入文件类型
    获取文件名
    获取文件类型
【开发者及日期】 黄靖宸 2024/8/3
【更改记录】
*************************************************************************/
class Importer{
private:
    std::string  My_Name;
    std::string  My_Type;

protected:
    //默认构造函数
    Importer();
    //拷贝构造函数
    Importer(const Importer& Source) = delete;
    //赋值运算符overload
    Importer& operator=(const Importer& Source) = delete;
    //虚析构函数（用作基类）
    virtual ~Importer() = default;

public:
    //设置文件名
    unsigned int Copy_Name(std::string Name);
    //设置文件类型
    unsigned int Copy_Type(std::string Type);
    //虚函数：读入模型（用作基类）
    virtual std::pair<Model3D, unsigned int> Read_Model(std::ifstream& Stream) const = 0;
    //读入文件类型
    void Read_Type(const std::string& Filename);
    //获取文件名
    std::string Get_Name() const;
    //获取文件类型
    std::string Get_Type() const;
};

#endif /* Importer_hpp */