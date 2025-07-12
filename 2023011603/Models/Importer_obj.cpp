/*************************************************************************
【文件名】 Importer_obj.cpp
【功能模块和目的】 obj导入器类实现
【开发者及日期】 黄靖宸 2024/8/3
【更改记录】
*************************************************************************/

//自身所属头文件
#include "Importer_obj.hpp"
//std::ifstream所属头文件
#include <fstream>

/*************************************************************************
【函数名称】 Importer_obj
【函数功能】 默认构造函数，设置类型为“obj”
【参数】 无
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
Importer_obj::Importer_obj(){
    Copy_Type("obj");
}

/*************************************************************************
【函数名称】 Importer_obj
【函数功能】 带参构造函数，默认类型为“obj”
【参数】 std::string Name
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
Importer_obj::Importer_obj(std::string Name){
    Copy_Name(Name);
    Copy_Type("obj");
}

/*************************************************************************
【函数名称】 Read_Model
【函数功能】 读入模型
【参数】 std::ifstream& Stream
【返回值】 std::pair<Model3D, unsigned int>，三维模型和错误码
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
std::pair<Model3D, unsigned int> Importer_obj::Read_Model(std::ifstream& Stream) const{
    Model3D Model;
    std::vector<Point3D> Points;
    std::vector<Line3D>  Lines;
    std::vector<Face3D>  Faces;
    char Tag;
    unsigned int Index1{0};
    unsigned int Index2{0};
    unsigned int Index3{0};
    std::string Annotation;
    double X_Temp{0};
    double Y_Temp{0};
    double Z_Temp{0};
    unsigned int Error = 0;
    while (!Stream.eof() && Error == 0) {
        Tag = 0;
        Stream >> Tag;
        Stream.get();
        switch (Tag) {
        case '#' :
            getline(Stream, Annotation);
            Model.Append_Annotaion(Annotation);
            break;
        case 'g' :
            getline(Stream, Model.My_Name);
            break;
        case 'v' :
            Stream >> X_Temp >> Y_Temp >> Z_Temp;
            Stream.get();
            Points.push_back(Point3D(X_Temp, Y_Temp, Z_Temp));
            break;
        case 'l' :
            Stream >> Index1 >> Index2;
            Stream.get();
            Error = Model.Insert_Line(Points[Index1 - 1], 
                                      Points[Index2 - 1]);
            break;
        case 'f' :
            Stream >> Index1 >> Index2 >> Index3;
            Stream.get();
            Error = Model.Insert_Face(Points[Index1 - 1], 
                                      Points[Index2 - 1], 
                                      Points[Index3 - 1]);
            break;
        default :
            break;
        }
    }
    return std::pair<Model3D, unsigned int> (Model, Error);
}