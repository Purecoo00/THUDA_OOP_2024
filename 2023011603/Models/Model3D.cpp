/*************************************************************************
【文件名】 Model3D.cpp
【功能模块和目的】 三维模型类实现
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/

//自身所属头文件
#include "Model3D.hpp"
//max_element, min_element所属头文件
#include <algorithm>
//std::string所属头文件
#include <string>

/*************************************************************************
【函数名称】 Model3D
【函数功能】 默认构造函数
【参数】 无
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
Model3D::Model3D(){

}

/*************************************************************************
【函数名称】 Model3D
【函数功能】 带参构造函数
【参数】 const std::vector<Line3D>& Line_List, 
        const std::vector<Face3D>& Face_List
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
Model3D::Model3D(const std::vector<Line3D>& Line_List, 
                 const std::vector<Face3D>& Face_List){
    auto P_Line = Line_List.begin();
    auto P_Face = Face_List.begin();
    while (P_Line != Line_List.end()) {
        My_Line_List.push_back(*P_Line);
        P_Line++;
    }
    while (P_Face != Face_List.end()) {
        My_Face_List.push_back(*P_Face);
        P_Face++;
    }
}

/*************************************************************************
【函数名称】 Model3D
【函数功能】 拷贝构造函数
【参数】 const Model3D& Source
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
Model3D::Model3D(const Model3D& Source){
    My_Line_List  = Source.My_Line_List;
    My_Face_List  = Source.My_Face_List;
    Annotation    = Source.Annotation;
    My_Name          = Source.My_Name;
}

/*************************************************************************
【函数名称】 operator=
【函数功能】 赋值运算符overload
【参数】 const Model3D& Source
【返回值】 三维模型自身的引用
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
Model3D& Model3D::operator=(const Model3D& Source){
    if (this != &Source) {
        My_Line_List  = Source.My_Line_List;
        My_Face_List  = Source.My_Face_List;
        Annotation    = Source.Annotation;
        My_Name          = Source.My_Name;
    }
    return *this;
}

/*************************************************************************
【函数名称】 Insert_Line
【函数功能】 以两点为参数添加三维线，如有非法操作则返回对应错误码
【参数】 Point3D& Point1, Point3D& Point2
【返回值】 错误码
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/

unsigned int Model3D::Insert_Line(Point3D& Point1, Point3D& Point2){
    if (Point1 == Point2) {
        return 9; /* Same Point When Insert Line */
    }
    else if (Point1 < Point2) {
        Line3D Temp_Line(Point1, Point2);
        return Insert_Line(Temp_Line);
    }
    else {
        Line3D Temp_Line(Point2, Point1);
        return Insert_Line(Temp_Line);
    }
}

/*************************************************************************
【函数名称】 Insert_Line
【函数功能】 以三维线为参数添加三维线，如有非法操作则返回对应错误码
【参数】 Line3D& Line
【返回值】 错误码
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
unsigned int Model3D::Insert_Line(Line3D& Line){
    auto P_Line = My_Line_List.begin();
    while (P_Line != My_Line_List.end()) {
        if (Line == *P_Line) {
            return 11; /* Same Line When Insert Line */
        }
        P_Line++;
    }
    My_Line_List.push_back(Line);
    return 0;
}

/*************************************************************************
【函数名称】 Insert_Face
【函数功能】 以三点为参数添加三维面，如有非法操作则返回对应错误码
【参数】 Point3D& Point1, Point3D& Point2, Point3D& Point3
【返回值】 错误码
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
unsigned int Model3D::Insert_Face(Point3D& Point1, Point3D& Point2, Point3D& Point3){
    if (Point1 == Point2 || Point2 == Point3 || Point3 == Point1) {
        return 12; /* Same Point When Insert Face */
    }
    else if (Point1 < Point2 && Point1 < Point3) {
        if (Point2 < Point3) {
            Face3D temp_face(Point1, Point2, Point3);
            return Insert_Face(temp_face);
        }
        else {
            Face3D temp_face(Point1, Point3, Point2);
            return Insert_Face(temp_face);
        }
    }
    else if (Point2 < Point3 && Point2 < Point1) {
        if (Point1 < Point3) {
            Face3D temp_face(Point2, Point1, Point3);
            return Insert_Face(temp_face);
        }
        else {
            Face3D temp_face(Point2, Point3, Point1);
            return Insert_Face(temp_face);
        }
    }
    else if (Point3 < Point1 && Point3 < Point2) {
        if (Point1 < Point2) {
            Face3D temp_face(Point3, Point1, Point2);
            return Insert_Face(temp_face);
        }
        else {
            Face3D temp_face(Point3, Point2, Point1);
            return Insert_Face(temp_face);
        }
    }
    return 0;
}

/*************************************************************************
【函数名称】 Insert_Face
【函数功能】 以三维面添加三维面，如有非法操作则返回对应错误码
【参数】 Face3D& Face
【返回值】 错误码
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
unsigned int Model3D::Insert_Face(Face3D& Face){
    auto P_Face = My_Face_List.begin();
    while (P_Face != My_Face_List.end()) {
        if (Face == *P_Face) {
            return 14; /* Same Face When Insert Face */
        }
        P_Face++;
    }
    My_Face_List.push_back(Face);
    return 0;
}

/*************************************************************************
【函数名称】 Append_Annotaion
【函数功能】 添加注释
【参数】 std::string annotation
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
void Model3D::Append_Annotaion(std::string annotation){
    Annotation.push_back(annotation);
}

/*************************************************************************
【函数名称】 Set_Name
【函数功能】 设置模型名
【参数】 std::string Name
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
void Model3D::Set_Name(std::string Name){
    My_Name = Name;
}

/*************************************************************************
【函数名称】 Delete_Line
【函数功能】 以两点为参数删除三维线，如有非法操作则返回错误码
【参数】 Point3D& Point1, Point3D& Point2
【返回值】 错误码
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
unsigned int Model3D::Delete_Line(Point3D& Point1, Point3D& Point2){
    unsigned int Error = 10; /* Line Not Found */
    auto P_Line = My_Line_List.begin();
    while (P_Line != My_Line_List.end()) {
        if (Point1 == P_Line->Get_Point_1() && Point2 == P_Line->Get_Point_2()) {
            My_Line_List.erase(P_Line);
            Error = 0;
            break;
        }
        P_Line++;
    }
    return Error;
}

/*************************************************************************
【函数名称】 Delete_Line
【函数功能】 以三维线为参数删除三维线，如有非法操作则返回错误码
【参数】 Line3D& Line
【返回值】 错误码
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
unsigned int Model3D::Delete_Line(Line3D& Line){
    unsigned int Error = 10; /* Line Not Found */
    auto P_Line = My_Line_List.begin();
    while (P_Line != My_Line_List.end()) {
        if (Line == *P_Line) {
            My_Line_List.erase(P_Line);
            Error = 0;
            break;
        }
        P_Line++;
    }
    return Error;
}

/*************************************************************************
【函数名称】 Delete_Face
【函数功能】 以三点为参数删除三维面，如有非法操作则返回错误码
【参数】 Point3D& Point1, Point3D& Point2, Point3D& Point3
【返回值】 错误码
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
unsigned int Model3D::Delete_Face(Point3D& Point1, 
    Point3D& Point2, Point3D& Point3){
    unsigned int Error = 13; /* Face Not Found */
    auto P_Face = My_Face_List.begin();
    while (P_Face != My_Face_List.end()) {
        if (Point1 == P_Face->Get_Point_1() && 
            Point2 == P_Face->Get_Point_2() && 
            Point3 == P_Face->Get_Point_3()) {
            My_Face_List.erase(P_Face);
            Error = 0;
            break;
        }
        P_Face++;
    }
    return Error;
}

/*************************************************************************
【函数名称】 Delete_Face
【函数功能】 以三维面为参数删除三维面，如有非法操作则返回错误码
【参数】 Face3D& Face
【返回值】 错误码
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
unsigned int Model3D::Delete_Face(Face3D& Face){
    unsigned int Error = 13; /* Face Not Found */
    auto P_Face = My_Face_List.begin();
    while (P_Face != My_Face_List.end()) {
        if (Face == *P_Face) {
            My_Face_List.erase(P_Face);
            Error = 0;
            break;
        }
        P_Face++;
    }
    return Error;
}

/*************************************************************************
【函数名称】 Change_Line
【函数功能】 修改指定三维线的一个点，如有非法操作则返回错误码
【参数】 unsigned int Line_Number, double x, double y, double z, 
    unsigned int Point_Number
【返回值】 错误码
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
unsigned int Model3D::Change_Line(unsigned int Line_Number, 
    double x, double y, double z, unsigned int Point_Number){
    auto P_Line = My_Line_List.begin();
    unsigned int Error = 0;
    P_Line += (Line_Number - 1);
    Line3D Temp_Line = *P_Line;
    Error = Temp_Line.Change_Point_In_Line(x, y, z, Point_Number);
    if (Error != 0) {
        return Error;
    }
    else {
        P_Line = My_Line_List.begin();
        while (P_Line != My_Line_List.end()) {
            if (Temp_Line == *P_Line) {
                Error = 3;
                return Error;
            }
            P_Line++;
        }
    }
    return Error;
}

/*************************************************************************
【函数名称】 Change_Face
【函数功能】 修改指定三维面的一个点，如有非法操作则返回错误码
【参数】 unsigned int Face_Number, double x, double y, double z, 
    unsigned int Point_Number
【返回值】 错误码
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
unsigned int Model3D::Change_Face(unsigned int Face_Number, 
    double x, double y, double z, unsigned int Point_Number){
    auto P_Face = My_Face_List.begin();
    unsigned int Error = 0;
    P_Face += (Face_Number - 1);
    Face3D temp_face = *P_Face;
    Error = temp_face.Change_Point_In_Face(x, y, z, Point_Number);
    if (Error != 0) {
        return Error;
    }
    else {
        P_Face = My_Face_List.begin();
        while (P_Face != My_Face_List.end()) {
            if (temp_face == *P_Face) {
                Error = 7;
                return Error;
            }
            P_Face++;
        }
    }
    return Error;
}

/*************************************************************************
【函数名称】 Line_Num
【函数功能】 获取三维线数量
【参数】 无
【返回值】 三维线数量
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
unsigned int Model3D::Line_Num() const{
    return My_Line_List.size();
}

/*************************************************************************
【函数名称】 Sum_Line_Lenth
【函数功能】 获取三维线总长度
【参数】 无
【返回值】 三维线总长度
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
double Model3D::Sum_Line_Lenth() const{
    double Sum_Lenth = 0;
    auto P_Line = My_Line_List.begin();
    Line3D Line_Temp;
    while (P_Line != My_Line_List.end()) {
        Line_Temp = *P_Line;
        Sum_Lenth += Point3D::Distance(Line_Temp.Get_Point_1(), 
        Line_Temp.Get_Point_2());
        P_Line++;
    }
    return Sum_Lenth;
}

/*************************************************************************
【函数名称】 Face_Num
【函数功能】 获取三维面数量
【参数】 无
【返回值】 三维面数量
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
unsigned int Model3D::Face_Num() const{
    return My_Face_List.size();
}

/*************************************************************************
【函数名称】 Sum_Face_Area
【函数功能】 获取三维面总面积
【参数】 无
【返回值】 三维面总面积
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
double Model3D::Sum_Face_Area() const{
    double Sum_Area = 0;
    auto P_Face = My_Face_List.begin();
    Face3D Face_Temp;
    while (P_Face != My_Face_List.end()) {
        Face_Temp = *P_Face;
        Sum_Area += Face3D::Get_Area(
            Face_Temp.Get_Point_1(), 
            Face_Temp.Get_Point_2(), 
            Face_Temp.Get_Point_3());
        P_Face++;
    }
    return Sum_Area;
}

/*************************************************************************
【函数名称】 Point_Num
【函数功能】 获取三维点数量
【参数】 无
【返回值】 三维点数量
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
unsigned int Model3D::Point_Num() const{
    return 2 * My_Line_List.size() + 3 * My_Face_List.size();
}

/*************************************************************************
【函数名称】 Cover_Cube
【函数功能】 获取囊括所有元素正方体的最小边长
【参数】 无
【返回值】 囊括所有元素正方体的最小边长
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
double Model3D::Cover_Cube() const{
    if (My_Line_List.size() == 0 && My_Face_List.size() == 0) {
        return 0;
    }
    double X_Gap = 0;
    double Y_Gap = 0;
    double Z_Gap = 0;
    std::vector<double> X_List;
    std::vector<double> Y_List;
    std::vector<double> Z_List;
    auto P_Line = My_Line_List.begin();
    auto P_Face = My_Face_List.begin();
    while (P_Line != My_Line_List.end()) {
        X_List.push_back(P_Line->Get_Point_1().Get_x());
        X_List.push_back(P_Line->Get_Point_2().Get_x());
        Y_List.push_back(P_Line->Get_Point_1().Get_y());
        Y_List.push_back(P_Line->Get_Point_2().Get_y());
        Z_List.push_back(P_Line->Get_Point_1().Get_z());
        Z_List.push_back(P_Line->Get_Point_2().Get_z()); 
        P_Line++;
    }
    while (P_Face != My_Face_List.end()) {
        X_List.push_back(P_Face->Get_Point_1().Get_x());
        X_List.push_back(P_Face->Get_Point_2().Get_x());
        X_List.push_back(P_Face->Get_Point_3().Get_x());
        Y_List.push_back(P_Face->Get_Point_1().Get_y());
        Y_List.push_back(P_Face->Get_Point_2().Get_y());
        Y_List.push_back(P_Face->Get_Point_3().Get_y());
        Z_List.push_back(P_Face->Get_Point_1().Get_z());
        Z_List.push_back(P_Face->Get_Point_2().Get_z());
        Z_List.push_back(P_Face->Get_Point_3().Get_z()); 
        P_Face++;
    }
    auto P_X_Max = max_element(X_List.begin(), X_List.end());
    auto P_Y_Max = max_element(Y_List.begin(), Y_List.end());
    auto P_Z_Max = max_element(Z_List.begin(), Z_List.end());
    auto P_X_Min = min_element(X_List.begin(), X_List.end());
    auto P_Y_Min = min_element(Y_List.begin(), Y_List.end());
    auto P_Z_Min = min_element(Z_List.begin(), Z_List.end());
    X_Gap = *P_X_Max - *P_X_Min;
    Y_Gap = *P_Y_Max - *P_Y_Min;
    Z_Gap = *P_Z_Max - *P_Z_Min;
    std::vector<double> MAX = {X_Gap, Y_Gap, Z_Gap};
    auto P_Max = max_element(MAX.begin(), MAX.end());
    return *P_Max;
}

/*************************************************************************
【函数名称】 Get_Line_List
【函数功能】 获取三维线集合
【参数】 无
【返回值】 std::vector<Line3D>&，三维线集合
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
std::vector<Line3D>& Model3D::Get_Line_List(){
    return My_Line_List;
}

/*************************************************************************
【函数名称】 Get_Face_List
【函数功能】 获取三维面集合
【参数】 无
【返回值】 std::vector<Face3D>&，三维面集合
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
std::vector<Face3D>& Model3D::Get_Face_List(){
    return My_Face_List;
}

/*************************************************************************
【函数名称】 Get_Annotation
【函数功能】 获取注释
【参数】 无
【返回值】 std::vector<std::string>&，注释
【开发者及日期】 黄靖宸 2024/8/2
【更改记录】
*************************************************************************/
std::vector<std::string>& Model3D::Get_Annotation(){
    return Annotation;
}