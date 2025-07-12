/*************************************************************************
【文件名】 View_hpp
【功能模块和目的】 界面类声明
【开发者及日期】 黄靖宸 2024/8/6
【更改记录】
*************************************************************************/

#ifndef View_hpp
#define View_hpp

//std::string所属头文件
#include <string>

/*************************************************************************
【类名】 View
【功能】 界面类
【接口说明】
    默认构造函数
    虚析构函数（可能做基类）
    显示主菜单
    显示创建模型菜单
    显示导入模型菜单
    显示导出模型菜单
    显示选择模型菜单
    显示编辑模型菜单
    显示列出模型菜单
    显示添加线菜单
    显示删除线菜单
    显示编辑线上点菜单
    显示添加面菜单
    显示删除面菜单
    显示编辑面上点菜单
【开发者及日期】 黄靖宸 2024/8/6
【更改记录】
*************************************************************************/
class View{
public:
    //默认构造函数
    View();
    //虚析构函数（可能做基类），无动态构造成员，默认实现
    virtual ~View() = default;

protected:
    //显示主菜单
    virtual std::string Main_Menu()              const;
    //显示创建模型菜单
    virtual std::string Create_Model_Menu()      const;
    //显示导入模型菜单
    virtual std::string Import_Model_Menu()      const;
    //显示导出模型菜单
    virtual std::string Export_Model_Menu()      const;
    //显示选择模型菜单
    virtual std::string Select_Model_Menu()      const;
    //显示编辑模型菜单
    virtual std::string Modify_Model_Menu()      const;
    //显示列出模型菜单
    virtual std::string List_Model_Menu()        const;
    //显示添加线菜单
    virtual std::string Insert_Line_Menu()       const;
    //显示删除线菜单
    virtual std::string Delete_Line_Menu()       const;
    //显示编辑线上点菜单
    virtual std::string Modify_Line_Point_Menu() const;
    //显示添加面菜单
    virtual std::string Insert_Face_Menu()       const;
    //显示删除面菜单
    virtual std::string Delete_Face_Menu()       const;
    //显示编辑面上点菜单
    virtual std::string Modify_Face_Point_Menu() const;
};

#endif /* View_hpp */