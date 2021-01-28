#pragma once
#include <iostream>
#include <cmath>
#include <bitset>
#include <algorithm>
using namespace std;

const string Hexa = "0123456789ABCDEF";

class QInt
{
private:
	union
	{
		long long half[2];
		unsigned char	body[16];
	};
	unsigned char coso;				//lưu cơ số đang xử lý
public:

	// -------------------------- HÀM KHỞI TẠO -------------------------- 

	QInt(); // Mặc định là 0 ở cơ số 10
	QInt(int m_coso) { coso = m_coso; }
	QInt(string str, int coso = 10); // Chuỗi số ở cơ số của nó mặc định cơ số 10
	
	//--------------------------- OPERATOR -------------------------------
	QInt operator+(const QInt&)const;
	QInt operator-(const QInt&)const;
	QInt operator*(const QInt&)const;
	QInt operator/(const QInt&)const;
	QInt operator&(const QInt&)const;
	QInt operator|(const QInt&)const; 
	QInt operator^(const QInt&)const; 

	friend QInt operator~(const QInt&); // phep NOT, chi tac dung len chinh minh

	QInt operator<<(int soBit)const; //dich trai
	QInt operator>>(int soBit)const; //dich phai
	QInt Negative() const;
	// -------------------------- HÀM TRẢ VỀ CHUỖI --------------------------
	string toString(int coso);
	void Xuat() { for (int i = 0; i < 16; i++) cout << (int)body[i] << " | "; }
	
};
string ChiaChuoiCho2(string str, int& );
string NhanChuoiCho2(string str);
string nhanChuoiCho2(string dec, int);

string ChiaChuoiCho16(string str, int& soDu);
// -------------------------- CÁC HÀM CHUYỂN ĐỔI -------------------------
string DecToBin(string str);
string BinToDec(string bit);
string DecToHex(string str);
string HexToDec(string str);
string BinToHex(string str);
string HexToBin(string str);
string dich_trai(string,int);
string dich_phai_so_hoc(string,int);
string xoay_trai(string);
string xoay_phai(string);