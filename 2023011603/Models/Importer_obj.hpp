/*************************************************************************
【文件名】 Importer_obj.hpp
【功能模块和目的】 obj导入器类声明
【开发者及日期】 黄靖宸 2024/8/3
【更改记录】
*************************************************************************/

#ifndef Importer_obj_hpp
#define Importer_obj_hpp

//Importer所属头文件
#include "Importer.hpp"

/*************************************************************************
【类名】 Importer_obj
【功能】 obj导入器类
【接口说明】
    默认构造函数
    带参构造函数
    虚析构函数（可能做基类）
    从文件读入模型
    读取模型
【开发者及日期】 黄靖宸 2024/8/3
【更改记录】
*************************************************************************/
class Importer_obj : public Importer{
public:
    //默认构造函数
    Importer_obj();
    //带参构造函数
    Importer_obj(std::string Name);
    //无拷贝构造
    Importer_obj(const Importer_obj&) = delete;
    //无赋值运算符
    Importer_obj& operator=(const Importer_obj&) = delete;
    //虚析构函数（可能做基类）
    virtual ~Importer_obj() = default;
    //从文件读入模型
    std::pair<Model3D, unsigned int> Read_Model(std::ifstream& Stream) const;
};

#endif /* Importer_obj_hpp */