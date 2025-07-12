/*************************************************************************
【文件名】 Exporter.cpp
【功能模块和目的】 导出器类实现
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/

//自身所属头文件
#include "Controller.hpp"

/*************************************************************************
【函数名称】 Get_Instance
【函数功能】 静态：获取控制器实例指针
【参数】 无
【返回值】 控制器实例指针
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
std::shared_ptr<Controller> Controller::Get_Instance(){
    static std::shared_ptr<Controller> My_Instance = std::shared_ptr<Controller>(new Controller);
    return My_Instance;
}

/*************************************************************************
【函数名称】 Create_Model
【函数功能】 创建空模型，且设为当前模型
【参数】 无
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Create_Model(){
    My_Models.push_back(std::shared_ptr<Model3D> (new Model3D()));
    My_Model_Index = My_Models.size() - 1;
    return RES::Move_Success;
}

/*************************************************************************
【函数名称】 Set_Model
【函数功能】 设置指定模型为当前模型
【参数】 size_t Index
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Set_Model(size_t Index){
    if (Index > My_Models.size()) {
        return RES::Model_Index_Out_Of_Range;
    }
    else {
        My_Model_Index = Index;
        return RES::Move_Success;
    }
}

/*************************************************************************
【函数名称】 Import_Model_From_File
【函数功能】 从文件导入当前模型
【参数】 const std::string& FILENAME
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Import_Model_From_File(
    const std::string& FILENAME){
    unsigned int Position = FILENAME.rfind(".");
    std::string Type = FILENAME.substr(Position + 1);
    std::string Name = FILENAME.substr(0, Position);
    if (Type == "obj") {
        std::ifstream Stream;
        Stream.open(FILENAME);
        Importer_obj importer_obj(Name);
        std::pair Pair = importer_obj.Read_Model(Stream);
        Stream.close();
        if (Pair.second == 0) {
            (*My_Models[My_Model_Index]) = Pair.first;
        }
        return RES(Pair.second);
    }
    else {
        return RES::Type_Not_Supported_Now;
    }
}

/*************************************************************************
【函数名称】 Import_Model_From_File
【函数功能】 从文件导入指定模型
【参数】 const std::string& FILENAME, size_t Index
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Import_Model_From_File(
    const std::string& FILENAME, size_t Index){
    if (Index > My_Models.size()) {
        return RES::Model_Index_Out_Of_Range;
    }
    unsigned int Position = FILENAME.rfind(".");
    std::string Type = FILENAME.substr(Position + 1);
    std::string Name = FILENAME.substr(0, Position);
    if (Type == "obj") {
        std::ifstream Stream;
        Stream.open(FILENAME);
        Importer_obj importer_obj(Name);
        std::pair Pair = importer_obj.Read_Model(Stream);
        Stream.close();
        if (Pair.second == 0) {
            (*My_Models[Index]) = Pair.first;
        }
        return RES(Pair.second);
    }
    else {
        return RES::Type_Not_Supported_Now;
    }
}

/*************************************************************************
【函数名称】 Export_File_From_Model
【函数功能】 从当前模型导出文件
【参数】 std::string Filename
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Export_File_From_Model(std::string Filename){
    unsigned int Position = Filename.rfind(".");
    std::string Type = Filename.substr(Position + 1);
    if (Type == "obj") {
        std::ofstream File(Filename);
        Exporter_obj Exporter_obj;
        Exporter_obj.Write_File(File, (*My_Models[My_Model_Index]));
        File.close();
        return RES::Move_Success;
    }
    else {
        return RES::Type_Not_Supported_Now;
    }
}

/*************************************************************************
【函数名称】 Export_File_From_Model
【函数功能】 从指定模型导出文件
【参数】 size_t Index, std::string Filename
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Export_File_From_Model(
    size_t Index, std::string Filename){
    if (Index > My_Models.size()) {
        return RES::Model_Index_Out_Of_Range;
    }
    unsigned int Position = Filename.rfind(".");
    (*My_Models[Index]).My_Name = Filename.substr(0, Position);
    std::string Type = Filename.substr(Position + 1);
    if (Type == "obj") {
        std::ofstream File(Filename);
        Exporter_obj Exporter_obj;
        Exporter_obj.Write_File(File, (*My_Models[Index]));
        File.close();
        return RES::Move_Success;
    }
    else {
        return RES::Type_Not_Supported_Now;
    }
}

/*************************************************************************
【函数名称】 Delete_Line
【函数功能】 移除当前模型中的指定线，number指定线序号
【参数】 size_t Line_Number
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Delete_Line(size_t Line_Number){
    if (Line_Number > (*My_Models[My_Model_Index]).Line_Num() - 1) {
        return RES::Line_Number_Out_Of_Range;
    }
    else {
        std::vector<Line3D>& Line_list = 
        (*My_Models[My_Model_Index]).Get_Line_List();
        auto P_Line = Line_list.begin();
        P_Line += Line_Number;
        Line_list.erase(P_Line);
        return RES::Move_Success;
    }
}

/*************************************************************************
【函数名称】 Delete_Line
【函数功能】 移除指定模型中的指定线，number指定线序号
【参数】 size_t Index, size_t Line_Number
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Delete_Line(size_t Index, size_t Line_Number){
    if (Index > My_Models.size() - 1) {
        return RES::Model_Index_Out_Of_Range;
    }
    if (Line_Number > (*My_Models[Index]).Line_Num() - 1) {
        return RES::Line_Number_Out_Of_Range;
    }
    else {
        std::vector<Line3D>& Line_list = (*My_Models[Index]).Get_Line_List();
        auto P_Line = Line_list.begin();
        P_Line += Line_Number;
        Line_list.erase(P_Line);
        return RES::Move_Success;
    }
}

/*************************************************************************
【函数名称】 Delete_Face
【函数功能】 移除当前模型中的指定面，number指定面序号
【参数】 size_t Face_Number
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Delete_Face(size_t Face_Number){
    if (Face_Number > (*My_Models[My_Model_Index]).Face_Num() - 1) {
        return RES::Face_Number_Out_Of_Range;
    }
    else {
        std::vector<Face3D>& Face_list = 
        (*My_Models[My_Model_Index]).Get_Face_List();
        auto P_Face = Face_list.begin();
        P_Face += Face_Number;
        Face_list.erase(P_Face);
        return RES::Move_Success;
    }
}

/*************************************************************************
【函数名称】 Delete_Face
【函数功能】 移除指定模型中的指定面，number指定面序号
【参数】 size_t Index, size_t Face_Number
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Delete_Face(size_t Index, size_t Face_Number){
    if (Index > My_Models.size() - 1) {
        return RES::Model_Index_Out_Of_Range;
    }
    if (Face_Number > (*My_Models[Index]).Face_Num() - 1) {
        return RES::Face_Number_Out_Of_Range;
    }
    else {
        std::vector<Face3D>& Face_list = (*My_Models[Index]).Get_Face_List();
        auto P_Face = Face_list.begin();
        P_Face += Face_Number;
        Face_list.erase(P_Face);
        return RES::Move_Success;
    }
}

/*************************************************************************
【函数名称】 Insert_Line
【函数功能】 向当前模型添加指定线
【参数】 Line3D& Line
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Insert_Line(Line3D& Line){
    unsigned int Error = (*My_Models[My_Model_Index]).Insert_Line(Line);
    return RES(Error);
}

/*************************************************************************
【函数名称】 Insert_Line
【函数功能】 向指定模型添加指定线
【参数】 size_t Index, Line3D& Line
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Insert_Line(size_t Index, Line3D& Line){
    if (Index > My_Models.size()) {
        return RES::Model_Index_Out_Of_Range;
    }
    unsigned int Error = (*My_Models[Index]).Insert_Line(Line);
    return RES(Error);
}

/*************************************************************************
【函数名称】 Insert_Face
【函数功能】 向当前模型添加指定面
【参数】 Face3D& Face
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Insert_Face(Face3D& Face){
    unsigned int Error = (*My_Models[My_Model_Index]).Insert_Face(Face);
    return RES(Error);
}

/*************************************************************************
【函数名称】 Insert_Face
【函数功能】 向指定模型添加指定面
【参数】 size_t Index, Face3D& Face
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Insert_Face(size_t Index, Face3D& Face){
    if (Index > My_Models.size()) {
        return RES::Model_Index_Out_Of_Range;
    }
    unsigned int Error = (*My_Models[Index]).Insert_Face(Face);
    return RES(Error);
}

/*************************************************************************
【函数名称】 Change_Point_In_Line
【函数功能】 修改当前模型指定线中的指定点
【参数】 size_t Line_Number, double x, double y, double z, 
    unsigned int Point_Number
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Change_Point_In_Line(size_t Line_Number, 
    double x, double y, double z, unsigned int Point_Number){
    RES Res = Change_Point_In_Line(My_Model_Index, Line_Number, x, y, z, Point_Number);
    return Res;
}

/*************************************************************************
【函数名称】 Change_Point_In_Line
【函数功能】 修改指定模型指定线中的指定点
【参数】 size_t Index, size_t Line_Number, 
    double x, double y, double z, unsigned int Point_Number
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Change_Point_In_Line(size_t Index, 
    size_t Line_Number, double x, double y, double z, 
    unsigned int Point_Number){
    if (Index > My_Models.size()) {
        return RES::Model_Index_Out_Of_Range;
    }
    if (Line_Number > (*My_Models[Index]).Line_Num()) {
        return RES::Line_Number_Out_Of_Range;
    }
    else {
        unsigned int Error = 0;
        Line3D& Line = 
        (*My_Models[Index]).Get_Line_List()[Line_Number];
        double X_Original = 0;
        double Y_Original = 0;
        double Z_Original = 0;
        switch (Point_Number) {
        case 1 :
            X_Original = Line.Get_Point_1().Get_x();
            Y_Original = Line.Get_Point_1().Get_y();
            Z_Original = Line.Get_Point_1().Get_z();
            break;
        case 2 :
            X_Original = Line.Get_Point_2().Get_x();
            Y_Original = Line.Get_Point_2().Get_y();
            Z_Original = Line.Get_Point_2().Get_z();
            break; 
        default :
            break;
        }
        Error = Line.Change_Point_In_Line(x, y, z, Point_Number);
        if (Error == 0) {
            unsigned int Judge = 0;
            auto P_Line = (*My_Models[Index]).Get_Line_List().begin();
            while (P_Line != (*My_Models[Index]).Get_Line_List().end()) {
                if (Judge != Line_Number && Line == *P_Line) {
                    Error = 3;
                    Line.Change_Point_In_Line(X_Original, Y_Original, Z_Original, Point_Number);
                    return RES(Error);
                }
                P_Line++;
                Judge++;
            }
        }
        return RES(Error);
    }
}

/*************************************************************************
【函数名称】 Change_Point_In_Face
【函数功能】 修改当前模型指定面中的指定点
【参数】 size_t Face_Number, 
    double x, double y, double z, unsigned int Point_Number
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Change_Point_In_Face(size_t Face_Number, 
    double x, double y, double z, unsigned int Point_Number){
    RES Res = Change_Point_In_Face(My_Model_Index, Face_Number, 
    x, y, z, Point_Number);
    return Res;
}

/*************************************************************************
【函数名称】 Change_Point_In_Face
【函数功能】 修改指定模型指定面中的指定点
【参数】 size_t Index, size_t Face_Number, 
    double x, double y, double z, unsigned int Point_Number
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Change_Point_In_Face(size_t Index, 
    size_t Face_Number, double x, double y, double z, 
    unsigned int Point_Number){
    if (Index > My_Models.size()) {
        return RES::Model_Index_Out_Of_Range;
    }
    if (Face_Number > (*My_Models[Index]).Face_Num()) {
        return RES::Face_Number_Out_Of_Range;
    }
    else {
        unsigned int Error = 0;
        Face3D& Face = 
        (*My_Models[Index]).Get_Face_List()[Face_Number];
        double X_Original = 0;
        double Y_Original = 0;
        double Z_Original = 0;
        switch (Point_Number) {
        case 1 :
            X_Original = Face.Get_Point_1().Get_x();
            Y_Original = Face.Get_Point_1().Get_y();
            Z_Original = Face.Get_Point_1().Get_z();
            break;
        case 2 :
            X_Original = Face.Get_Point_2().Get_x();
            Y_Original = Face.Get_Point_2().Get_y();
            Z_Original = Face.Get_Point_2().Get_z();
            break; 
        case 3 :
            X_Original = Face.Get_Point_3().Get_x();
            Y_Original = Face.Get_Point_3().Get_y();
            Z_Original = Face.Get_Point_3().Get_z();
            break;
        default :
            break;
        }
        Error = Face.Change_Point_In_Face(x, y, z, Point_Number);
        if (Error == 0) {
            unsigned int Judge = 0;
            auto P_Face = (*My_Models[Index]).Get_Face_List().begin();
            while (P_Face != (*My_Models[Index]).Get_Face_List().end()) {
                if (Judge != Face_Number && Face == *P_Face) {
                    Error = 7;
                    Face.Change_Point_In_Face(X_Original, Y_Original, Z_Original, Point_Number);
                    return RES(Error);
                }
                P_Face++;
                Judge++;
            }
        }
        return RES(Error);
    }
}

/*************************************************************************
【函数名称】 Get_All_Line
【函数功能】 列出当前模型中所有线信息
【参数】 Line_Info_List& Info_List
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Get_All_Line(Line_Info_List& Info_List) const{
    const std::vector<Line3D>& LINE_LIST = 
    (*My_Models[My_Model_Index]).Get_Line_List();
    auto P_Line = LINE_LIST.begin();
    Info_List.clear();
    while (P_Line != LINE_LIST.end()) {
        LineInfo Temp_LineInfo;
        Temp_LineInfo.PointInfo[0].X = P_Line->Get_Point_1().Get_x();
        Temp_LineInfo.PointInfo[0].Y = P_Line->Get_Point_1().Get_x();
        Temp_LineInfo.PointInfo[0].Z = P_Line->Get_Point_1().Get_x();
        Temp_LineInfo.PointInfo[1].X = P_Line->Get_Point_2().Get_x();
        Temp_LineInfo.PointInfo[1].Y = P_Line->Get_Point_2().Get_y();
        Temp_LineInfo.PointInfo[1].Z = P_Line->Get_Point_2().Get_z();
        Info_List.push_back(Temp_LineInfo);
        P_Line++;
    }
    return RES::Move_Success;
}

/*************************************************************************
【函数名称】 Get_All_Line
【函数功能】 列出指定模型中所有线信息
【参数】 size_t Index, Line_Info_List& Info_List
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Get_All_Line(size_t Index, 
    Line_Info_List& Info_List) const{
    if (Index > My_Models.size()) {
        return RES::Model_Index_Out_Of_Range;
    }
    const std::vector<Line3D>& LINE_LIST = (*My_Models[Index]).Get_Line_List();
    auto P_Line = LINE_LIST.begin();
    Info_List.clear();
    while (P_Line != LINE_LIST.end()) {
        LineInfo Temp_LineInfo;
        Temp_LineInfo.PointInfo[0].X = P_Line->Get_Point_1().Get_x();
        Temp_LineInfo.PointInfo[0].Y = P_Line->Get_Point_1().Get_x();
        Temp_LineInfo.PointInfo[0].Z = P_Line->Get_Point_1().Get_x();
        Temp_LineInfo.PointInfo[1].X = P_Line->Get_Point_2().Get_x();
        Temp_LineInfo.PointInfo[1].Y = P_Line->Get_Point_2().Get_y();
        Temp_LineInfo.PointInfo[1].Z = P_Line->Get_Point_2().Get_z();
        Info_List.push_back(Temp_LineInfo);
        P_Line++;
    }
    return RES::Move_Success;
}

/*************************************************************************
【函数名称】 Get_All_Face
【函数功能】 列出当前模型中所有面信息
【参数】 Face_Info_List& Info_List
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Get_All_Face(Face_Info_List& Info_List) const{
    const std::vector<Face3D>& FACE_LIST = 
    (*My_Models[My_Model_Index]).Get_Face_List();
    auto P_Face = FACE_LIST.begin();
    Info_List.clear();
    while (P_Face != FACE_LIST.end()) {
        FaceInfo Temp_FaceInfo;
        Temp_FaceInfo.PointInfo[0].X = P_Face->Get_Point_1().Get_x();
        Temp_FaceInfo.PointInfo[0].Y = P_Face->Get_Point_1().Get_x();
        Temp_FaceInfo.PointInfo[0].Z = P_Face->Get_Point_1().Get_x();
        Temp_FaceInfo.PointInfo[1].X = P_Face->Get_Point_2().Get_x();
        Temp_FaceInfo.PointInfo[1].Y = P_Face->Get_Point_2().Get_y();
        Temp_FaceInfo.PointInfo[1].Z = P_Face->Get_Point_2().Get_z();
        Temp_FaceInfo.PointInfo[2].X = P_Face->Get_Point_3().Get_x();
        Temp_FaceInfo.PointInfo[2].Y = P_Face->Get_Point_3().Get_y();
        Temp_FaceInfo.PointInfo[2].Z = P_Face->Get_Point_3().Get_z();
        Info_List.push_back(Temp_FaceInfo);
        P_Face++;
    }
    return RES::Move_Success;
}

/*************************************************************************
【函数名称】 Get_All_Face
【函数功能】 列出指定模型中所有面信息
【参数】 size_t Index, Face_Info_List& Info_List
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Get_All_Face(size_t Index, 
    Face_Info_List& Info_List) const{
    if (Index > My_Models.size()) {
        return RES::Model_Index_Out_Of_Range;
    }
    const std::vector<Face3D>& FACE_LIST = (*My_Models[Index]).Get_Face_List();
    auto P_Face = FACE_LIST.begin();
    Info_List.clear();
    while (P_Face != FACE_LIST.end()) {
        FaceInfo Temp_FaceInfo;
        Temp_FaceInfo.PointInfo[0].X = P_Face->Get_Point_1().Get_x();
        Temp_FaceInfo.PointInfo[0].Y = P_Face->Get_Point_1().Get_x();
        Temp_FaceInfo.PointInfo[0].Z = P_Face->Get_Point_1().Get_x();
        Temp_FaceInfo.PointInfo[1].X = P_Face->Get_Point_2().Get_x();
        Temp_FaceInfo.PointInfo[1].Y = P_Face->Get_Point_2().Get_y();
        Temp_FaceInfo.PointInfo[1].Z = P_Face->Get_Point_2().Get_z();
        Temp_FaceInfo.PointInfo[2].X = P_Face->Get_Point_3().Get_x();
        Temp_FaceInfo.PointInfo[2].Y = P_Face->Get_Point_3().Get_y();
        Temp_FaceInfo.PointInfo[2].Z = P_Face->Get_Point_3().Get_z();
        Info_List.push_back(Temp_FaceInfo);
        P_Face++;
    }
    return RES::Move_Success;
}

/*************************************************************************
【函数名称】 Get_All_Point_In_Line
【函数功能】 列出当前模型指定线中所有点信息，number指定线序号
【参数】 Point_Info_List& Info_List, size_t Models_Number
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Get_All_Point_In_Line(
    Point_Info_List& Info_List, size_t Models_Number) const{
    if (Models_Number > (*My_Models[My_Model_Index]).Line_Num() - 1) {
        return RES::Line_Number_Out_Of_Range;
    }
    else {
        const Line3D& LINE = 
        (*My_Models[My_Model_Index]).Get_Line_List()[Models_Number];
        PointInfo Point_Temp_1;
        Point_Temp_1.X = LINE.Get_Point_1().Get_x();
        Point_Temp_1.Y = LINE.Get_Point_1().Get_y();
        Point_Temp_1.Z = LINE.Get_Point_1().Get_z();
        Info_List.push_back(Point_Temp_1);
        PointInfo Point_Temp_2;
        Point_Temp_2.X = LINE.Get_Point_2().Get_x();
        Point_Temp_2.Y = LINE.Get_Point_2().Get_y();
        Point_Temp_2.Z = LINE.Get_Point_2().Get_z();
        Info_List.push_back(Point_Temp_2);
        return RES::Move_Success;
    }
}

/*************************************************************************
【函数名称】 Get_All_Point_In_Line
【函数功能】 列出指定模型指定线中所有点信息，number指定线序号
【参数】 size_t Index, Point_Info_List& Info_List, size_t Line_Number
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Get_All_Point_In_Line(size_t Index, 
    Point_Info_List& Info_List, size_t Line_Number) const{
    if (Index > My_Models.size() - 1) {
        return RES::Model_Index_Out_Of_Range;
    }
    if (Line_Number > (*My_Models[Index]).Line_Num() - 1) {
        return RES::Line_Number_Out_Of_Range;
    }
    else {
        const Line3D& LINE = (*My_Models[Index]).Get_Line_List()[Line_Number - 1];
        PointInfo Point_Temp_1;
        Point_Temp_1.X = LINE.Get_Point_1().Get_x();
        Point_Temp_1.Y = LINE.Get_Point_1().Get_y();
        Point_Temp_1.Z = LINE.Get_Point_1().Get_z();
        Info_List.push_back(Point_Temp_1);
        PointInfo Point_Temp_2;
        Point_Temp_2.X = LINE.Get_Point_2().Get_x();
        Point_Temp_2.Y = LINE.Get_Point_2().Get_y();
        Point_Temp_2.Z = LINE.Get_Point_2().Get_z();
        Info_List.push_back(Point_Temp_2);
        return RES::Move_Success;
    }
}

/*************************************************************************
【函数名称】 Get_All_Point_In_Face
【函数功能】 列出当前模型指定线中所有点信息，number指定面序号
【参数】 Point_Info_List& Info_List, size_t Face_Number
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Get_All_Point_In_Face(
    Point_Info_List& Info_List, size_t Face_Number) const{
    if (Face_Number > (*My_Models[My_Model_Index]).Face_Num() - 1) {
        return RES::Face_Number_Out_Of_Range;
    }
    else {
        const Face3D& FACE = 
        (*My_Models[My_Model_Index]).Get_Face_List()[Face_Number];
        PointInfo Point_Temp_1;
        Point_Temp_1.X = FACE.Get_Point_1().Get_x();
        Point_Temp_1.Y = FACE.Get_Point_1().Get_y();
        Point_Temp_1.Z = FACE.Get_Point_1().Get_z();
        Info_List.push_back(Point_Temp_1);
        PointInfo Point_Temp_2;
        Point_Temp_2.X = FACE.Get_Point_2().Get_x();
        Point_Temp_2.Y = FACE.Get_Point_2().Get_y();
        Point_Temp_2.Z = FACE.Get_Point_2().Get_z();
        Info_List.push_back(Point_Temp_2);
        PointInfo Point_Temp_3;
        Point_Temp_3.X = FACE.Get_Point_3().Get_x();
        Point_Temp_3.Y = FACE.Get_Point_3().Get_y();
        Point_Temp_3.Z = FACE.Get_Point_3().Get_z();
        Info_List.push_back(Point_Temp_3);
        return RES::Move_Success;
    }
}

/*************************************************************************
【函数名称】 Get_All_Point_In_Face
【函数功能】 列出指定模型指定线中所有点信息，number指定面序号
【参数】 size_t Index, Point_Info_List& Info_List, size_t Face_Number
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Get_All_Point_In_Face(size_t Index, 
    Point_Info_List& Info_List, size_t Face_Number) const{
    if (Index > My_Models.size() - 1) {
        return RES::Model_Index_Out_Of_Range;
    }
    if (Face_Number > (*My_Models[Index]).Face_Num() - 1) {
        return RES::Face_Number_Out_Of_Range;
    }
    else {
        const Face3D& FACE = (*My_Models[Index]).Get_Face_List()[Face_Number - 1];
        PointInfo Point_Temp_1;
        Point_Temp_1.X = FACE.Get_Point_1().Get_x();
        Point_Temp_1.Y = FACE.Get_Point_1().Get_y();
        Point_Temp_1.Z = FACE.Get_Point_1().Get_z();
        Info_List.push_back(Point_Temp_1);
        PointInfo Point_Temp_2;
        Point_Temp_2.X = FACE.Get_Point_2().Get_x();
        Point_Temp_2.Y = FACE.Get_Point_2().Get_y();
        Point_Temp_2.Z = FACE.Get_Point_2().Get_z();
        Info_List.push_back(Point_Temp_2);
        PointInfo Point_Temp_3;
        Point_Temp_3.X = FACE.Get_Point_3().Get_x();
        Point_Temp_3.Y = FACE.Get_Point_3().Get_y();
        Point_Temp_3.Z = FACE.Get_Point_3().Get_z();
        Info_List.push_back(Point_Temp_3);
        return RES::Move_Success;
    }
}

/*************************************************************************
【函数名称】 Read_Statistics
【函数功能】 列出当前模型的统计信息
【参数】 无
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Read_Statistics(){
    ModelInfo Model_Info;
    Model_Info.Name         = (*My_Models[My_Model_Index]).My_Name;
    Model_Info.Point_Number = (*My_Models[My_Model_Index]).Point_Num();
    Model_Info.Line_Number  = (*My_Models[My_Model_Index]).Line_Num();
    Model_Info.Sum_Length   = (*My_Models[My_Model_Index]).Sum_Line_Lenth();
    Model_Info.Face_Number  = (*My_Models[My_Model_Index]).Face_Num();
    Model_Info.Sum_Area     = (*My_Models[My_Model_Index]).Sum_Face_Area();
    Model_Info.Cube_Length  = (*My_Models[My_Model_Index]).Cover_Cube();
    return RES::Move_Success;
}

/*************************************************************************
【函数名称】 Read_Statistics
【函数功能】 列出指定模型的统计信息
【参数】 size_t Index
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Read_Statistics(size_t Index){
    if (Index > My_Models.size()) {
        return RES::Model_Index_Out_Of_Range;
    }
    Model_Info.Name         = (*My_Models[Index]).My_Name;
    Model_Info.Point_Number = (*My_Models[Index]).Point_Num();
    Model_Info.Line_Number  = (*My_Models[Index]).Line_Num();
    Model_Info.Sum_Length   = (*My_Models[Index]).Sum_Line_Lenth();
    Model_Info.Face_Number  = (*My_Models[Index]).Face_Num();
    Model_Info.Sum_Area     = (*My_Models[Index]).Sum_Face_Area();
    Model_Info.Cube_Length  = (*My_Models[Index]).Cover_Cube();
    return RES::Move_Success;
}

/*************************************************************************
【函数名称】 Refresh_Model_Info_List
【函数功能】 更新所有模型信息
【参数】 Model_Info_List& Info_List
【返回值】 执行结果枚举值
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::RES Controller::Refresh_Model_Info_List(){
    Model_Info_List.clear();
    for (size_t i = 0; i < My_Models.size(); i++){
        ModelInfo Model_Temp;
        Model_Temp.Name         = (*My_Models[i]).My_Name;
        Model_Temp.Point_Number = (*My_Models[i]).Point_Num();
        Model_Temp.Line_Number  = (*My_Models[i]).Line_Num();
        Model_Temp.Sum_Length   = (*My_Models[i]).Sum_Line_Lenth();
        Model_Temp.Face_Number  = (*My_Models[i]).Face_Num();
        Model_Temp.Sum_Area     = (*My_Models[i]).Sum_Face_Area();
        Model_Temp.Cube_Length  = (*My_Models[i]).Cover_Cube();
        Model_Info_List.push_back(Model_Temp);
    }
    return RES::Move_Success;
}

/*************************************************************************
【函数名称】 Controller
【函数功能】 单例模式，私有默认构造函数
【参数】 无
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/5
【更改记录】
*************************************************************************/
Controller::Controller(){
    
}

//初始化Res_Str
const std::string Controller::Res_Str[21] = {
    "Move_Success"                     ,
    "Same_Point_When_Change_Line"      ,
    "Point_Error_When_Change_Line"     ,
    "Same_Line_When_Change_Line"       ,
    "Line_Number_Out_Of_Range"         ,
    "Same_Point_When_Change_Face"      ,
    "Point_Error_When_Change_Face"     ,
    "Same_Face_When_Change_Face"       ,
    "Face_Number_Out_Of_Range"         ,
    "Same_Point_When_Insert_Line"      ,
    "Line_Not_Found_When_Delete_Line"  ,
    "Same_Line_When_Insert_Line"       ,
    "Same_Point_When_Insert_Face"      ,
    "Face_Not_Found_When_Delete_Face"  ,
    "Same_Face_When_Insert_Face"       ,
    "Invalid_Name_When_Import"         ,
    "Invalid_Type_When_Import"         ,
    "Invalid_Tag_When_Import_OBJ_File" ,
    "Invalid_Type_When_Export"         ,
    "Type_Not_Supported_Now"           ,
    "Model_Index_Out_Of_Range"
};