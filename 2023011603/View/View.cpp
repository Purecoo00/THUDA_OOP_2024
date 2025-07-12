/*************************************************************************
【文件名】 View.cpp
【功能模块和目的】 界面类实现
【开发者及日期】 黄靖宸 2024/8/6
【更改记录】
*************************************************************************/

//自身所属头文件
#include "View.hpp"
//std::iostream所属头文件
#include <iostream>
//std::string所属头文件
#include <string>
//std::shared_ptr所属头文件
#include <memory>
//控制器类所属头文件
#include "../Controller/Controller.hpp"

using namespace std;

//简化类型名称
using RES              = Controller::RES;
using PointInfo        = Controller::PointInfo;
using LineInfo         = Controller::LineInfo;
using FaceInfo         = Controller::FaceInfo;
using ModelInfo        = Controller::ModelInfo;
using Point_Info_List  = Controller::Point_Info_List;
using Line_Info_List   = Controller::Line_Info_List;
using Face_Info_List   = Controller::Face_Info_List;

/*************************************************************************
【函数名称】 View
【函数功能】 默认构造函数
【参数】 无
【返回值】 无
【开发者及日期】 黄靖宸 2024/8/6
【更改记录】
*************************************************************************/
View::View(){
    cout << Main_Menu() << endl;
}

/*************************************************************************
【函数名称】 Main_Menu
【函数功能】 显示主菜单
【参数】 无
【返回值】 std::string，开发信息
【开发者及日期】 黄靖宸 2024/8/6
【更改记录】
*************************************************************************/
std::string View::Main_Menu() const{
    //获取控制器实例指针
    shared_ptr<Controller> Ctr_ptr = Controller::Get_Instance();
    //准备获取模型统计信息
    ModelInfo InfoList;
    //用户键入的选择
    string Selection;
    //非预期选择，循环显示菜单，要求用户再次键入选择
    while (Selection != "1" && 
           Selection != "2" && 
           Selection != "3" && 
           Selection != "4" && 
           Selection != "5" && 
           Selection != "6" && 
           Selection != "7") {
        cout << "---Menu---" << endl;
        cout << "1. Models"  << endl;
        cout << "2. Create"  << endl;
        cout << "3. Import"  << endl;
        cout << "4. Export"  << endl;
        cout << "5. Select"  << endl;
        cout << "6. Modify"  << endl;
        cout << "7. Exit"    << endl 
        << "Please Select(1/2/3/4/5/6/7): ";

        getline(cin, Selection);

        //根据选择触发下一级菜单显示
        if (Selection == "1") {
            cout << List_Model_Menu()   << endl;
        }
        else if (Selection == "2") {
            cout << Create_Model_Menu() << endl;
        }
        else if (Selection == "3") {
            cout << Import_Model_Menu() << endl;
        }
        else if (Selection == "4") {
            cout << Export_Model_Menu() << endl;
        }
        else if (Selection == "5") {
            cout << Select_Model_Menu() << endl;
        }
        else if (Selection == "6") {
            cout << Modify_Model_Menu() << endl;
        }
        else if (Selection == "7") {
            break;
        }
        Selection.clear();
    }
    //返回开发信息
    return "huang-jc23@mails.tsinghua.edu.cn 2024/8/1";
}

/*************************************************************************
【函数名称】 Create_Model_Menu
【函数功能】 显示创建模型菜单
【参数】 无
【返回值】 std::string，空字符串
【开发者及日期】 黄靖宸 2024/8/6
【更改记录】
*************************************************************************/
std::string View::Create_Model_Menu() const{
    //获取控制器实例指针
    shared_ptr<Controller> Ctr_Ptr = Controller::Get_Instance();
    //用户键入选择
    string Selection;
    //非预期选择，循环显示菜单，要求用户再次键入选择
    while (Selection != "Y" && Selection != "y") {
        cout << endl << "---Create Empty Model---" << endl;
        Ctr_Ptr->Create_Model();
        cout << "1 Empty Model Created Successfully" << endl;
        cout << "Current Model Index Is: "
        << Ctr_Ptr->Current_Model_Index << endl;
        Selection.clear();
        while (Selection != "Y" && Selection != "N" 
            && Selection != "y" && Selection != "n") {
            cout << endl <<  "Return To Main Menu?" << endl 
            << "(Y/N? N For Create Another Empty Model): ";
            getline(cin, Selection);
        }
    }
    return "";
}

/*************************************************************************
【函数名称】 Import_Model_Menu
【函数功能】 显示导入模型菜单
【参数】 无
【返回值】 std::string，空字符串
【开发者及日期】 黄靖宸 2024/8/6
【更改记录】
*************************************************************************/
std::string View::Import_Model_Menu() const{
    //获取控制器实例指针
    shared_ptr<Controller> Ctr_Ptr = Controller::Get_Instance();
    //用户键入选择
    string Selection;
    //获取模型信息列表
    std::vector<ModelInfo>& Info_List = Ctr_Ptr->Model_Info_List;
    //非预期选择，循环显示菜单，要求用户再次键入选择
    while (Selection != "Y" && Selection != "y") {
        //更新模型信息列表
        Ctr_Ptr->Refresh_Model_Info_List();
        cout << endl << "---Import Model From File---" << endl;
        if (Info_List.size() == 0) {
            cout 
            << "No Model Is Available Now, Please Create One" << endl;
            return "";
        }
        cout << "File Name: ";
        string Filename;
        getline(cin, Filename);
        cout << "Current Model Index Is: " 
        << Ctr_Ptr->Current_Model_Index << endl;
        cout << "Model Index Range: (0~ " << Info_List.size() - 1 << ")";
        size_t Index;
        cin >> Index;
        cin.get();
        RES Res = Ctr_Ptr->Import_Model_From_File(Filename, Index);
        if (Res != RES::Move_Success) {
            cout << Ctr_Ptr->Res_Str[static_cast<int>(Res)] << endl;
        }
        else {
            cout << "\"" << Filename << "\" Has Been Imported To Model No."
            << Index << endl;
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "N" 
            && Selection != "y" && Selection != "n") {
            cout << endl <<  "Return To Main Menu?" << endl
                 << "(Y/N? N For Import Another File):";
            getline(cin, Selection);
        }
    }
    return "";
}

/*************************************************************************
【函数名称】 Export_Model_Menu
【函数功能】 显示导出模型菜单
【参数】 无
【返回值】 std::string，空字符串
【开发者及日期】 黄靖宸 2024/8/6
【更改记录】
*************************************************************************/
std::string View::Export_Model_Menu() const{
    //获取控制器实例指针
    shared_ptr<Controller> Ctr_Ptr = Controller::Get_Instance();
    //用户键入选择
    string Selection;
    //获取模型信息列表
    std::vector<ModelInfo>& Info_List = Ctr_Ptr->Model_Info_List;
    //非预期选择，循环显示菜单，要求用户再次键入选择
    while (Selection != "Y" && Selection != "y") {
        //更新模型信息列表
        Ctr_Ptr->Refresh_Model_Info_List();
        cout << endl << "---Save Model To File---" << endl;
        if (Info_List.size() == 0) {
            cout 
            << "No Model Is Available Now, Please Create One" << endl;
            return "";
        }
        cout << "Please Input File Name: ";
        string Filename;
        getline(cin, Filename);
        cout << "Current Model Index Is: " 
        << Ctr_Ptr->Current_Model_Index << endl;
        cout << "Model Index Range: (0~ " << Info_List.size() - 1 << ")";
        size_t Index;
        cin >> Index;
        cin.get();
        RES Res = Ctr_Ptr->Export_File_From_Model(Index, Filename);
        if (Res != RES::Move_Success) {
            cout << Ctr_Ptr->Res_Str[static_cast<int>(Res)] << endl;
        }
        else {
            cout << "\"" << Filename 
            << "\" Has Been Exported From Model No." << Index << endl;
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "N" 
            && Selection != "y" && Selection != "n") {
            cout << endl <<  "Return To Main Menu?" << endl
                 << "(Y/N? N For Export Another File):";
            getline(cin, Selection);
        }
    }
    return "";
}

/*************************************************************************
【函数名称】 Select_Model_Menu
【函数功能】 显示选择模型菜单
【参数】 无
【返回值】 std::string，空字符串
【开发者及日期】 黄靖宸 2024/8/7
【更改记录】
*************************************************************************/
std::string View::Select_Model_Menu() const{
    //获取控制器实例指针
    shared_ptr<Controller> Ctr_Ptr = Controller::Get_Instance();
    //用户键入选择
    string Selection;
    //获取模型信息列表
    std::vector<ModelInfo>& Info_List = Ctr_Ptr->Model_Info_List;
    while (Selection != "Y" && Selection != "y") {
        //更新模型信息列表
        Ctr_Ptr->Refresh_Model_Info_List();
        cout << endl << "---Select Current Model---" << endl;
        if (Ctr_Ptr->Current_Model_Index == SIZE_MAX) {
            cout << "No Model Is Selected Now" << endl;
        }
        else {
            cout << "Current Model Index Is: " 
            << Ctr_Ptr->Current_Model_Index << endl;
        }
        if (Info_List.size() == 0) {
            cout << "No Model Is Available Now" << endl;
        }
        else {
            cout << "Model Index Range: (0~ " << Info_List.size() - 1 << ")";
            size_t Index;
            cin >> Index;
            cin.get();
            RES Res = Ctr_Ptr->Set_Model(Index);
            if (Res != RES::Move_Success) {
                cout << Ctr_Ptr->Res_Str[static_cast<int>(Res)] << endl;
            }
            else {
                cout << "Model No." << Index << " Is Selected Now";
            }
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "N" 
            && Selection != "y" && Selection != "n") {
            cout << endl << "Return To Main Menu? (Y/N):";
            getline(cin, Selection);
        }
    }
    return "";
}

/*************************************************************************
【函数名称】 Modify_Model_Menu
【函数功能】 显示编辑模型菜单
【参数】 无
【返回值】 std::string，空字符串
【开发者及日期】 黄靖宸 2024/8/7
【更改记录】
*************************************************************************/
std::string View::Modify_Model_Menu() const{
    //获取控制器实例指针
    shared_ptr<Controller> Ctr_Ptr = Controller::Get_Instance();
    //用户键入选择
    string Selection;
    //非预期选择，循环显示菜单，要求用户再次键入选择
    while (Selection != "1" && 
           Selection != "2" && 
           Selection != "3" && 
           Selection != "4" && 
           Selection != "5" && 
           Selection != "6" && 
           Selection != "7") {
        cout << "---Modify Current Model---" << endl;
        if (Ctr_Ptr->Current_Model_Index == SIZE_MAX) {
            cout << "No Model Is Selected Now" << endl;
            return "";
        }
        cout << "1. Model Information" << endl;
        cout << "2. Insert Line"           << endl;
        cout << "3. Delete Line"           << endl;
        cout << "4. Modify Points In Line" << endl;
        cout << "5. Insert Face"           << endl;
        cout << "6. Delete Face"           << endl;
        cout << "7. Modify Points In Face" << endl;
        cout << "8. Return To Main Menu"   << endl 
        << "Please Select(1/2/3/4/5/6/7/8): ";
        getline(cin, Selection);
        if (Selection == "1") {
            cout << List_Model_Menu()        << endl;
        }
        else if (Selection == "2") {
            cout << Insert_Line_Menu()       << endl;
        }
        else if (Selection == "3") {
            cout << Delete_Line_Menu()       << endl;
        }
        else if (Selection == "4") {
            cout << Modify_Line_Point_Menu() << endl;
        }
        else if (Selection == "5") {
            cout << Insert_Face_Menu()       << endl;
        }
        else if (Selection == "6") {
            cout << Delete_Face_Menu()       << endl;
        }
        else if (Selection == "7") {
            cout << Modify_Face_Point_Menu() << endl;
        }
        else if (Selection == "8") {
            break;
        }
        Selection.clear();
    }
    return "";
}

/*************************************************************************
【函数名称】 List_Model_Menu
【函数功能】 显示列出模型菜单
【参数】 无
【返回值】 std::string，空字符串
【开发者及日期】 黄靖宸 2024/8/7
【更改记录】
*************************************************************************/
std::string View::List_Model_Menu() const{
    //获取控制器实例指针
    shared_ptr<Controller> Ctr_Ptr = Controller::Get_Instance();
    //用户键入选择
    string Selection;
    //获取模型信息列表
    std::vector<ModelInfo>& Info_List = Ctr_Ptr->Model_Info_List;
    while (Selection != "Y" && Selection != "y") {
        //更新模型信息列表
        Ctr_Ptr->Refresh_Model_Info_List();
        cout << endl << "---List All Models---" << endl;
        cout << "Total:" << Info_List.size() << "Model(s)" << endl;
        //显示所有模型信息
        for (size_t i = 0; i < Info_List.size(); i++){
            ModelInfo Model_Info = Info_List[i];
            cout << "Index:        " << i                       << endl;
            cout << "Point Number: " << Model_Info.Point_Number << endl;
            cout << "Line Number:  " << Model_Info.Line_Number  << endl;
            cout << "Total Length: " << Model_Info.Sum_Length   << endl;
            cout << "Face Number:  " << Model_Info.Face_Number  << endl;
            cout << "Total Area:   " << Model_Info.Sum_Area     << endl;
            cout << "Cover Cube:   " << Model_Info.Cube_Length  << endl;
            cout << endl;
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "N"
            && Selection != "y" && Selection != "n") {
            cout << endl << "Return To Main Menu? (Y/N): ";
            getline(cin, Selection);
        }
    }
    return "";
}

/*************************************************************************
【函数名称】 Insert_Line_Menu
【函数功能】 显示添加线菜单
【参数】 无
【返回值】 std::string，空字符串
【开发者及日期】 黄靖宸 2024/8/7
【更改记录】
*************************************************************************/
std::string View::Insert_Line_Menu() const{
    //获取控制器实例指针
    shared_ptr<Controller> Ctr_Ptr = Controller::Get_Instance();
    //用户键入选择
    string Selection;
    //非预期选择，循环显示菜单，要求用户再次键入选择
    while (Selection != "Y" && Selection != "y") {
        cout << "---Insert Line---" << endl;
        if (Ctr_Ptr->Current_Model_Index == SIZE_MAX) {
            cout << "No Model Is Selected Now" << endl;
            return "";
        }
        double Point_1_x;
        double Point_1_y;
        double Point_1_z;
        double Point_2_x;
        double Point_2_y;
        double Point_2_z;
        cout << "Please Input Point_1_x: ";
        cin >> Point_1_x;
        cout << "Please Input Point_1_y: ";
        cin >> Point_1_y;
        cout << "Please Input Point_1_z: ";
        cin >> Point_1_z;
        cout << "Please Input Point_2_x: ";
        cin >> Point_2_x;
        cout << "Please Input Point_2_y: ";
        cin >> Point_2_y;
        cout << "Please Input Point_2_z: ";
        cin >> Point_2_z;
        cin.get();
        Line3D temp_line = Line3D(
            Point3D(Point_1_x, Point_1_y, Point_1_z), 
            Point3D(Point_2_x, Point_2_y, Point_2_z));
        RES Res = Ctr_Ptr->Insert_Line(temp_line);
        if (Res != RES::Move_Success) {
            cout << Ctr_Ptr->Res_Str[static_cast<int>(Res)] << endl;
        }
        else {
            cout << "Line Inserted Successfully" << endl;
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "N" 
            && Selection != "y" && Selection != "n") {
            cout << endl << "Return To Main Menu?" << endl 
            << "(Y/N? N For Insert Another Line): ";
            getline(cin, Selection);
        }
    }
    return "";
}

/*************************************************************************
【函数名称】 Delete_Line_Menu
【函数功能】 显示删除线菜单
【参数】 无
【返回值】 std::string，空字符串
【开发者及日期】 黄靖宸 2024/8/7
【更改记录】
*************************************************************************/
std::string View::Delete_Line_Menu() const{
    //获取控制器实例指针
    shared_ptr<Controller> Ctr_Ptr = Controller::Get_Instance();
    //用户键入选择
    string Selection;
    while (Selection != "Y" && Selection != "y") {
        cout << "---Delete Line---" << endl;
        if (Ctr_Ptr->Current_Model_Index == SIZE_MAX) {
            cout << "No Model Is Selected Now" << endl;
            return "";
        }
        size_t Index;
        Line_Info_List Info_List;
        //获取模型中所有线信息
        Ctr_Ptr->Get_All_Line(Info_List);
        if (Info_List.size() == 0) {
            cout << "No Line Found In This Model" << endl;
            return "";
        }
        cout << "Line Index Range: (0~ " << Info_List.size() - 1 << ")";
        cin >> Index;
        cin.get();
        if (Index < 0) {
            cout << Ctr_Ptr->Res_Str[static_cast<int>(4)] << endl;
        }
        else {
            RES Res = Ctr_Ptr->Delete_Line(Index - 1);
            if (Res != RES::Move_Success) {
                cout << Ctr_Ptr->Res_Str[static_cast<int>(Res)] << endl;
            }
            else {
                cout << "Line Deleted Successfully" << endl;
            }
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "N" 
            && Selection != "y" && Selection != "n") {
            cout << endl << "Return To Main Menu?" << endl 
            << "(Y/N? N For Delete Another Line): ";
            getline(cin, Selection);
        }
    }
    return "";
}

/*************************************************************************
【函数名称】 Modify_Line_Point_Menu
【函数功能】 显示编辑线上点菜单
【参数】 无
【返回值】 std::string，空字符串
【开发者及日期】 黄靖宸 2024/8/7
【更改记录】
*************************************************************************/
std::string View::Modify_Line_Point_Menu() const{
    //获取控制器实例指针
    shared_ptr<Controller> Ctr_Ptr = Controller::Get_Instance();
    //用户键入选择
    string Selection;
    while (Selection != "Y" && Selection != "y" ){
        cout << "---Modify Point In Line---" << endl;
        if (Ctr_Ptr->Current_Model_Index == SIZE_MAX) {
            cout << "No Model Is Selected Now" << endl;
            return "";
        }
        size_t Line_Number;
        Line_Info_List Info_List;
        //获取模型中所有线信息
        Ctr_Ptr->Get_All_Line(Info_List);
        if (Info_List.size() == 0) {
            cout << "No Line Found In This Model" << endl;
            return "";
        }
        cout << "Line Index Range: (0~ " << Info_List.size() - 1 << ")";
        cin >> Line_Number;
        cin.get();
        Point_Info_List P_Info_List;
        RES Res = Ctr_Ptr->Get_All_Point_In_Line(P_Info_List, Line_Number);
        if (Res != RES::Move_Success) {
            cout << Ctr_Ptr->Res_Str[static_cast<int>(Res)] << endl;
        }
        else {
            //展示选中线信息
            cout << "Line No." << Line_Number << " Is Selected Now" << endl;
            cout << "Point_1: " << "(" << P_Info_List[0].X 
            << ", " << P_Info_List[0].Y
            << ", " << P_Info_List[0].Z << ")" << endl;
            cout << "Point_2: " << "(" << P_Info_List[1].X 
            << ", " << P_Info_List[1].Y
            << ", " << P_Info_List[1].Z << ")" << endl;
            unsigned int Point_Index;
            cout << "Point Index(1~2): ";
            cin >> Point_Index;
            double x;
            double y;
            double z;
            cout << "X: ";
            cin >> x;
            cout << "Y: ";
            cin >> y;
            cout << "Z: ";
            cin >> z;
            cin.get();
            Res = Ctr_Ptr->Change_Point_In_Line(
                Line_Number, x, y, z, Point_Index);
            if (Res != RES::Move_Success) {
                cout << Ctr_Ptr->Res_Str[static_cast<int>(Res)] << endl;
            }
            else {
                cout << "Line Modified Successfully" << endl;
            }
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "N" 
            && Selection != "y" && Selection != "n") {
            cout << endl << "Return To Main Menu?" << endl 
            << "(Y/N? N For Another Line Modify): ";
            getline(cin, Selection);
        }
    }
    return "";
}

/*************************************************************************
【函数名称】 Insert_Face_Menu
【函数功能】 显示添加面菜单
【参数】 无
【返回值】 std::string，空字符串
【开发者及日期】 黄靖宸 2024/8/7
【更改记录】
*************************************************************************/
std::string View::Insert_Face_Menu() const{
    //获取控制器实例指针
    shared_ptr<Controller> Ctr_Ptr = Controller::Get_Instance();
    //用户键入选择
    string Selection;
    while (Selection != "Y" && Selection != "y") {
        cout << "---Insert Face---" << endl;
        if (Ctr_Ptr->Current_Model_Index == SIZE_MAX) {
            cout << "No Model Is Selected Now" << endl;
            return "";
        }
        double Point_1_x;
        double Point_1_y;
        double Point_1_z;
        double Point_2_x;
        double Point_2_y;
        double Point_2_z;
        double Point_3_x;
        double Point_3_y;
        double Point_3_z;
        cout << "Please Input Point_1_x: ";
        cin >> Point_1_x;
        cout << "Please Input Point_1_y: ";
        cin >> Point_1_y;
        cout << "Please Input Point_1_z: ";
        cin >> Point_1_z;
        cout << "Please Input Point_2_x: ";
        cin >> Point_2_x;
        cout << "Please Input Point_2_y: ";
        cin >> Point_2_y;
        cout << "Please Input Point_2_z: ";
        cin >> Point_2_z;
        cout << "Please Input Point_3_x: ";
        cin >> Point_3_x;
        cout << "Please Input Point_3_y: ";
        cin >> Point_3_y;
        cout << "Please Input Point_3_z: ";
        cin >> Point_3_z;
        cin.get();
        Face3D Temp_Face = Face3D(
            Point3D(Point_1_x, Point_1_y, Point_1_z), 
            Point3D(Point_2_x, Point_2_y, Point_2_z), 
            Point3D(Point_3_x, Point_3_y, Point_3_z));
        RES Res = Ctr_Ptr->Insert_Face(Temp_Face);
        if (Res != RES::Move_Success) {
            cout << Ctr_Ptr->Res_Str[static_cast<int>(Res)] << endl;
        }
        else {
            cout << "Face Inserted Successfully" << endl;
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "N" 
            && Selection != "y" && Selection != "n") {
            cout << endl << "Return To Main Menu?" << endl 
            << "(Y/N? N For Insert Another Face): ";
            getline(cin, Selection);
        }
    }
    return "";
}

/*************************************************************************
【函数名称】 Delete_Face_Menu
【函数功能】 显示删除面菜单
【参数】 无
【返回值】 std::string，空字符串
【开发者及日期】 黄靖宸 2024/8/7
【更改记录】
*************************************************************************/
std::string View::Delete_Face_Menu() const{
    //获取控制器实例指针
    shared_ptr<Controller> Ctr_Ptr = Controller::Get_Instance();
    //用户键入选择
    string Selection;
    while (Selection != "Y" && Selection != "y") {
        cout << "---Delete Face---" << endl;
        if (Ctr_Ptr->Current_Model_Index == SIZE_MAX) {
            cout << "No Model Is Selected Now" << endl;
            return "";
        }
        size_t Index;
        Face_Info_List Info_List;
        //获取模型中所有面信息
        Ctr_Ptr->Get_All_Face(Info_List);
        if (Info_List.size() == 0) {
            cout << "No Face Found In This Model" << endl;
            return "";
        }
        cout << "Face Index Range: (0~ " << Info_List.size() - 1 << ")";
        cin >> Index;
        cin.get();
        if (Index < 0) {
            cout << Ctr_Ptr->Res_Str[static_cast<int>(8)] << endl;
        }
        else {
            RES Res = Ctr_Ptr->Delete_Face(Index);
            if (Res != RES::Move_Success) {
                cout << Ctr_Ptr->Res_Str[static_cast<int>(Res)] << endl;
            }
            else {
                cout << "Face Deleted Successfully" << endl;
            }
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "N" 
            && Selection != "y" && Selection != "n") {
            cout << endl << "Return To Main Menu?" << endl 
            << "(Y/N? N For Delete Another Face): ";
            getline(cin, Selection);
        }
    }
    return "";
}

/*************************************************************************
【函数名称】 Modify_Face_Point_Menu
【函数功能】 显示编辑面上点菜单
【参数】 无
【返回值】 std::string，空字符串
【开发者及日期】 黄靖宸 2024/8/7
【更改记录】
*************************************************************************/
std::string View::Modify_Face_Point_Menu() const{
    //获取控制器实例指针
    shared_ptr<Controller> Ctr_Ptr = Controller::Get_Instance();
    //用户键入选择
    string Selection;
    while (Selection != "Y" && Selection != "y" ){
        cout << "---Modify Point In Face---" << endl;
        if (Ctr_Ptr->Current_Model_Index == SIZE_MAX) {
            cout << "No Model Is Selected Now" << endl;
            return "";
        }
        size_t Face_Number;
        Face_Info_List Info_List;
        //获取模型中所有面信息
        Ctr_Ptr->Get_All_Face(Info_List);
        if (Info_List.size() == 0) {
            cout << "No Face Found In This Model" << endl;
            return "";
        }
        cout << "Face Index Range: (0~ " << Info_List.size() - 1 << ")";
        cin >> Face_Number;
        cin.get();
        Point_Info_List P_Info_List;
        RES Res = Ctr_Ptr->Get_All_Point_In_Face(P_Info_List, Face_Number);
        if (Res != RES::Move_Success) {
            cout << Ctr_Ptr->Res_Str[static_cast<int>(Res)] << endl;
        }
        else {
            //展示选中面信息
            cout << "Face No." << Face_Number << " Is Selected Now" << endl;
            cout << "Point_1: " << "(" << P_Info_List[0].X 
            << ", " << P_Info_List[0].Y
            << ", " << P_Info_List[0].Z << ")" << endl;
            cout << "Point_2: " << "(" << P_Info_List[1].X 
            << ", " << P_Info_List[1].Y
            << ", " << P_Info_List[1].Z << ")" << endl;
            cout << "Point_3: " << "(" << P_Info_List[2].X 
            << ", " << P_Info_List[2].Y
            << ", " << P_Info_List[2].Z << ")" << endl;
            unsigned int Point_Index;
            cout << "Point Index(1~3): ";
            cin >> Point_Index;
            double x;
            double y;
            double z;
            cout << "X: ";
            cin >> x;
            cout << "Y: ";
            cin >> y;
            cout << "Z: ";
            cin >> z;
            cin.get();
            Res = Ctr_Ptr->Change_Point_In_Face(
                Face_Number, x, y, z, Point_Index);
            if (Res != RES::Move_Success) {
                cout << Ctr_Ptr->Res_Str[static_cast<int>(Res)] << endl;
            }
            else {
                cout << "Face Modified Successfully" << endl;
            }
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "N" 
            && Selection != "y" && Selection != "n") {
            cout << endl << "Return To Main Menu?" << endl 
            << "(Y/N? N For Another Face Modify): ";
            getline(cin, Selection);
        }
    }
    return "";
}