// MatrixClassPrepare.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

/***********
*   头文件命名解释：
*   LJZ+M+功能——Matrix的定义和相关函数的实现
*   LJZ+V+功能——Vector的定义和相关函数的实现
*   TimeStruct——各种时间格式的定义和函数
*   CoordinateStruct——坐标定义和坐标转换相关函数
/***********/

#include <iostream>
#include<vector>

//有关矩阵的定义和实现
#include"LJZMatrix.h"
#include"LJZMCalculator.h"
#include"LJZMConstructor.h"
#include"LJZMOperators.h"
#include"LJZMToolKits.h"

//有关向量的定义和实现
#include"LJZVector.h"
#include"LJZVConstructor.h"
#include"LJZVToolKits.h"
#include"LJZVOperators.h"

//时间系统和坐标系统的定义和实现
#include "TimeStruct.h"
#include "CoordinateStruct.h"





int main()
{
    /*矩阵功能测试*/
    //double* testData = new double[9];
    //for (int i = 0; i <9; i++)
    //{
    //    testData[i] = 5;
    //}
    //LJZMatrix<double> matrix1(3, 3, testData);
    //
    ////matrix1.PrintMatrix();

    //LJZMatrix<double> matrix2(matrix1);

    //matrix2.PrintMatrix();
    
    //cout << matrix1.GetElementAt(2, 2) << endl;
    /*matrix1.SetElementAt(2, 2, 10);
    matrix1.PrintMatrix();*/

    /*int addValue = 6;
    LJZMatrix<double> matrix3;
    matrix3 = matrix1 - 6.0;
    /// <summary>
    /// 测试反馈，这里和矩阵相加的数得是至少浮点数？得和矩阵元素的数据类型相同
    /// </summary>
    /// <returns></returns>


    matrix3.PrintMatrix();*/

    //double m1Data[4] = { 1.0,2.0,3,4};
    //double m2Data[9] = { 1.0,5.0,2.0,6.0,2.0,4.0,3.0,2.0,1.0 };
    /*LJZMatrix<double> m1(2, 2, m1Data);
    LJZMatrix<double> m2(3, 3, m2Data);*/
    //LJZMatrix<double>result = m1 * m2;
    //result.PrintMatrix();
    //m2 = m2.Transpose();
    /*LJZMatrix<double> identity(3, 3);
    identity.SetToIdentity();*/
    //identity.PrintMatrix();
    //m2.CombineOtherMatrix(identity);


    //m2.PrintMatrix();


    /*int seprate[8] = { 1,2,3,4,5,6,7,8 };
    LJZMatrix<int> m_sep(2, 4, seprate);
    LJZMatrix<int> l;
    LJZMatrix<int> r;
    l.Resize(2, 2);
    r.Resize(2, 2);
    m_sep.Seperate(l, r, 2);
    l.PrintMatrix();*/

    ///*向量测试*/
    //vector<double> v1_data = { 1,0,0 };
    //LJZVector<double> v1(v1_data);

    //vector<double> v2_data = {0,1,0 };
    //LJZVector<double> v2(v2_data);

    //LJZVector<double> v3;

    ////std::cout<< LJZVector<double>::dot(v1, v2);

    ////v3 = v1.Normalized();

    //v3 = LJZVector<double>::cross(v2, v1);

    ////std::cout << v1.GetMold();

    //v3.PrintVector();

    
    //时间测试
    //1.MJD and Com
    /*CommonTime com = CommonTime(2021, 11, 14, 7, 21, 12.0);

    MJDTime mjd = Com2MJD(com);

    com.PrintCom();
    mjd.PrintMJD();

    CommonTime com2 = MJD2Com(mjd);

    com2.PrintCom();*/

    //2.GPS and MJD
    /*CommonTime com = CommonTime(2022, 9, 17, 8, 44, 40.25);
    MJDTime mjd = Com2MJD(com);

    com.PrintCom();
    mjd.PrintMJD();

    GPSTime gps = MJD2GPST(mjd);
    gps.PrintGPST();

    MJDTime mjd2 = GPST2MJD(gps);
    mjd2.PrintMJD();*/

    //3.Com and GPST
    CommonTime com = CommonTime(2021, 11, 14, 7, 21, 12.0);
    GPSTime gps = Com2GPST(com);
    gps.PrintGPST();

    CommonTime com2 = GPST2Com(gps);
    com2.PrintCom();

    //4.Doy and GPST
    /*CommonTime com = CommonTime(2022, 9, 17, 8, 44, 40.25);
    GPSTime gps = Com2GPST(com);
    gps.PrintGPST();

    cout << GPST2DOY(gps) << endl;

    GPSTime gps2 = DOY2GPST(260, 2022);

    gps2.PrintGPST();

    CommonTime com2 = GPST2Com(gps2);

    com2.PrintCom();*///在这里的通用时精确不到时分秒，因为当计算DOY时只精确到天，用260天（DOY）
                    //作为参数转换到GPS时的时候，对应这当日开始时的周秒（可以从通用时的形式看出来0时0分0秒）


    //坐标转换测试
    //参考坐标经纬度: (东经 113.5°，北纬 29.5°，地面高 40000m
    /*BLH blh = BLH(29.5 * D2R, 113.5 * D2R, 40000);
    XYZ xyz = BLH2XYZ(blh, R_WGS84, F_WGS84);
    xyz.PrintXYZ();

    BLH blh2 = XYZ2BLH(xyz, R_WGS84, F_WGS84);
    blh2.PrintBLH();*/

    cin.get();
}

