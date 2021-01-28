#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

#define PHEP_CONG	0
#define PHEP_TRU	1
#define PHEP_NHAN	2
#define PHEP_CHIA	3

#define PHEP_AND	4
#define PHEP_OR		5
#define PHEP_XOR	6
#define PHEP_NOT	7

#define PHEP_DICH_TRAI	8
#define PHEP_DICH_PHAI	9
#define PHEP_XOAY_TRAI 13
#define PHEP_XOAY_PHAI 14

#define KHONG_HOP_LE	10
#define QUY_DOI			11
#define TINH_TOAN		12

using namespace std;


//Tach hai doi so tu 1 chuoi
bool Tach_2_Doi_So(string str, string& str1, string& str2);
// Ham tach lay doi so tu 1 chuoi
bool Tach_3_Doi_So(string str, string& str1, string& str2, string& str3);
//Ham tach 4 doi so tu string
bool Tach_4_Doi_So(string str, string& str1, string& str2, string& str3, string& str4);
//Xử lý dòng Input nhập vào
int XulyInput(string str, string& doiso, int& coso);


