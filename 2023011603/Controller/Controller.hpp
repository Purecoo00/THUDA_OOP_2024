/*************************************************************************
【文件名】 Controller_hpp
【功能模块和目的】 控制器类声明
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/

#ifndef Controller_hpp
#define Controller_hpp

//size_t所属头文件
#include <cstddef>
//Point3D类所属头文件
#include "../Models/Point3D.hpp"
//Line3D类所属头文件
#include "../Models/Line3D.hpp"
//Face3D类所属头文件
#include "../Models/Face3D.hpp"
//Model3D类所属头文件
#include "../Models/Model3D.hpp"
//Importer类所属头文件
#include "../Models/Importer.hpp"
//Exporter类所属头文件
#include "../Models/Exporter.hpp"
//Importer_obj类所属头文件
#include "../Models/Importer_obj.hpp"
//Exporter_obj类所属头文件
#include "../Models/Exporter_obj.hpp"
//std::vector所属头文件
#include <vector>
//std::shared_ptr所属头文件
#include <memory>
//std::string所属头文件
#include <string>

/*************************************************************************
【类名】 Controller
【功能】 控制器类
【接口说明】
    静态：获取控制器实例指针
    虚析构函数（可能做基类）
    创建空模型并设为当前模型
    设置指定模型为当前模型
    从文件导入指定模型
    从指定模型导出文件
    移除指定模型中的指定线
    移除指定模型中的指定面
    向指定模型添加指定线
    向指定模型添加指定面
    修改指定模型指定线中的指定点
    修改指定模型指定面中的指定点
    列出指定模型中所有线信息
    列出指定模型中所有面信息
    列出指定模型指定线中所有点信息
    列出指定模型指定面中所有点信息
    列出指定模型的统计信息
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
class Controller{
public:
    enum class RES : int{
        Move_Success                     = 0,
        Same_Point_When_Change_Line      = 1,
        Point_Error_When_Change_Line     = 2,
        Same_Line_When_Change_Line       = 3,
        Line_Number_Out_Of_Range         = 4,
        Same_Point_When_Change_Face      = 5,
        Point_Error_When_Change_Face     = 6,
        Same_Face_When_Change_Face       = 7,
        Face_Number_Out_Of_Range         = 8,
        Same_Point_When_Insert_Line      = 9,
        Line_Not_Found_When_Delete_Line  = 10,
        Same_Line_When_Insert_Line       = 11,
        Same_Point_When_Insert_Face      = 12,
        Face_Not_Found_When_Delete_Face  = 13,
        Same_Face_When_Insert_Face       = 14,
        Invalid_Name_When_Import         = 15,
        Invalid_Type_When_Import         = 16,
        Invalid_Tag_When_Import_OBJ_File = 17,
        Invalid_Type_When_Export         = 18,
        Type_Not_Supported_Now           = 19,
        Model_Index_Out_Of_Range         = 20
    };

    //模型信息
    class ModelInfo{
    public:
        std::string Name;
        size_t Face_Number;
        double Sum_Area;
        size_t Line_Number;
        double Sum_Length;
        size_t Point_Number;
        double Cube_Length;
    };

    //点信息
    class PointInfo{
    public:
        double X;
        double Y;
        double Z;
    };

    //线信息
    class LineInfo{
    public:
        PointInfo PointInfo[2];
        double Length;
    };

    //面信息
    class FaceInfo{
    public:
        PointInfo PointInfo[3];
        double Area;
    };

    //点信息列表
    using Point_Info_List = std::vector<PointInfo>;
    
    //线信息列表
    using Line_Info_List  = std::vector<LineInfo>;
    
    //面信息列表
    using Face_Info_List  = std::vector<FaceInfo>;

    std::vector<ModelInfo> Model_Info_List;

    ModelInfo Model_Info;

    //静态：获取控制器实例指针
    static std::shared_ptr<Controller> Get_Instance();
    //单例模式，不允许拷贝
    Controller(const Controller& Source) = delete;
    //单例模式，不允许赋值
    Controller& operator=(const Controller Source) = delete;
    //虚析构函数（可能做基类），无动态构造成员，默认实现
    virtual ~Controller() = default;
    //创建空模型，且设为当前模型
    RES Create_Model();
    //设置指定模型为当前模型
    RES Set_Model(size_t index);
    //从文件导入当前模型
    RES Import_Model_From_File(const std::string& filename);
    //从文件导入指定模型
    RES Import_Model_From_File(const std::string& filename, size_t index);
    //从当前模型导出文件
    RES Export_File_From_Model(std::string filename);
    //从指定模型导出文件
    RES Export_File_From_Model(size_t index, std::string filename);
    //移除当前模型中的指定线
    RES Delete_Line(size_t number);
    //移除指定模型中的指定线
    RES Delete_Line(size_t index, size_t number);
    //移除当前模型中的指定面
    RES Delete_Face(size_t number);
    //移除指定模型中的指定面
    RES Delete_Face(size_t index, size_t number);
    //向当前模型添加指定线
    RES Insert_Line(Line3D& line);
    //向指定模型添加指定线
    RES Insert_Line(size_t index, Line3D& line);
    //向当前模型添加指定面
    RES Insert_Face(Face3D& face);
    //向指定模型添加指定面
    RES Insert_Face(size_t index, Face3D& face);
    //修改当前模型指定线中的指定点
    RES Change_Point_In_Line(size_t number, double x, double y, double z, unsigned int n);
    //修改指定模型指定线中的指定点
    RES Change_Point_In_Line(size_t index, size_t number, double x, double y, double z, unsigned int n);
    //修改当前模型指定面中的指定点
    RES Change_Point_In_Face(size_t number, double x, double y, double z, unsigned int n);
    //修改指定模型指定面中的指定点
    RES Change_Point_In_Face(size_t index, size_t number, double x, double y, double z, unsigned int n);
    //列出当前模型中所有线信息
    RES Get_All_Line(Line_Info_List& Info_List) const;
    //列出指定模型中所有线信息
    RES Get_All_Line(size_t index, Line_Info_List& Info_List) const;
    //列出当前模型中所有面信息
    RES Get_All_Face(Face_Info_List& Info_List) const;
    //列出指定模型中所有面信息
    RES Get_All_Face(size_t index, Face_Info_List& Info_List) const;
    //列出当前模型指定线中所有点信息
    RES Get_All_Point_In_Line(Point_Info_List& Info_List, size_t number) const;
    //列出指定模型指定线中所有点信息
    RES Get_All_Point_In_Line(size_t index, Point_Info_List& Info_List, size_t number) const;
    //列出当前模型指定面中所有点信息
    RES Get_All_Point_In_Face(Point_Info_List& Info_List, size_t number) const;
    //列出指定模型指定面中所有点信息
    RES Get_All_Point_In_Face(size_t index, Point_Info_List& Info_List, size_t number) const;
    //列出当前模型的统计信息
    RES Read_Statistics();
    //列出指定模型的统计信息
    RES Read_Statistics(size_t index);
    //更新所有模型信息
    RES Refresh_Model_Info_List();
    const size_t& Current_Model_Index{My_Model_Index};
    static const std::string Res_Str[21];

private:
    std::string My_Type;
    //当前模型索引
    size_t My_Model_Index{SIZE_MAX};
    //所有模型实例指针列表
    std::vector<std::shared_ptr<Model3D>> My_Models{};
    //单例模式，私有默认构造函数
    Controller();
};

#endif /* Controller_hpp */