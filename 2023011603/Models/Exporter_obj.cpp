/*************************************************************************
【文件名】 Exporter_obj.cpp
【功能模块和目的】 obj导出器类实现
【开发者及日期】 黄靖宸 2024/8/4
【更改记录】
*************************************************************************/

//自身所属头文件
#include "Exporter_obj.hpp"

/*************************************************************************
【函数名称】 Exporter_obj
【函数功能】 默认构造函数，设置文件类型为“obj”
【参数】 无
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/4
【更改记录】
*************************************************************************/
Exporter_obj::Exporter_obj(){
    Exporter::Set_Type("obj");
}

/*************************************************************************
【函数名称】 Write_File
【函数功能】 导出至文件，将数据写入Stream
【参数】 std::ofstream& Stream, Model3D Model
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/4
【更改记录】
*************************************************************************/
void Exporter_obj::Write_File(
    std::ofstream& Stream, Model3D Model) const{
    std::vector<std::string> anno = Model.Get_Annotation();
    std::vector<Line3D>   li_list = Model.Get_Line_List();
    std::vector<Face3D>   fa_list = Model.Get_Face_List();
    auto P_Anno = anno.begin();
    while (P_Anno != anno.end()) {
        Stream << "# " << *P_Anno << std::endl;
        P_Anno++;
    }
    Stream << "g " << Model.My_Name << std::endl;

    auto P_Line = li_list.begin();
    while (P_Line != li_list.end()) {
        Point3D point_line_1 = P_Line->Get_Point_1();
        Point3D point_line_2 = P_Line->Get_Point_2();
        Stream << "v " << point_line_1.Get_xyz_vector() << std::endl;
        Stream << "v " << point_line_2.Get_xyz_vector() << std::endl;
        P_Line++;
    }
    auto P_Face = fa_list.begin();
    while (P_Face != fa_list.end()) {
        Point3D point_face_1 = P_Face->Get_Point_1();
        Point3D point_face_2 = P_Face->Get_Point_2();
        Point3D point_face_3 = P_Face->Get_Point_3();
        Stream << "v " << point_face_1.Get_xyz_vector() << std::endl;
        Stream << "v " << point_face_2.Get_xyz_vector() << std::endl;
        Stream << "v " << point_face_3.Get_xyz_vector() << std::endl;
        P_Face++; 
    }

    P_Line = li_list.begin();
    unsigned int count = 1;
    while (P_Line != li_list.end()) {
        Stream << "l " <<  count      << ' ' 
                       << (count + 1) << std::endl;
        P_Line++;
        count += 2;
    }

    P_Face = fa_list.begin();
    while (P_Face != fa_list.end()) {
        Stream << "f " <<  count      << ' ' 
                       << (count + 1) << ' '
                       << (count + 2) << std::endl;
        P_Face++;
        count += 3;
    }
}