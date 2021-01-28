#include "XuLyInp.h"

bool Tach_2_Doi_So(string str, string& str1, string& str2)
{
	int pos = str.find(' ');
	str1 = str.substr(0, pos);
	str2 = str.substr(pos + 1, str.length() - pos - 1);
	if (str1 != "" && str2 != "")
		return true;
	else return false;
}

// Ham tach lay doi so tu 1 chuoi
bool Tach_3_Doi_So(string str, string& str1, string& str2, string& str3)
{
	int index = 0, i = 0;		//luu gia tri khoi dau
	// lay doi so dau tien
	for (; i < str.length(); i++)
	{
		if (str[i] == ' ')
		{
			str1 = str.substr(index, i - index);
			index = i + 1;
			i++;
			break;
		}
	}
	// Lay doi so thu 2 hoac toan tu 1 ngoi
	for (; i < str.length(); i++)
	{
		if (str[i] == ' ')
		{
			str2 = str.substr(index, i - index);
			index = i + 1;
			break;
		}
	}
	// Lay doi so cuoi cung
	str3 = str.substr(index, str.length() - index);

	if (str1 != "" && str2 != "" && str3 != "")
		return true;
	else return false;
}

bool Tach_4_Doi_So(string str, string& str1, string& str2, string& str3, string& str4)
{
	int index = 0, i = 0;		//luu gia tri khoi dau
	for (; i < str.length(); i++)
	{
		if (str[i] == ' ')
		{
			str1 = str.substr(index, i - index);
			index = i + 1;
			i++;
			break;
		}
	}

	for (; i < str.length(); i++)
	{
		if (str[i] == ' ')
		{
			str2 = str.substr(index, i - index);
			index = i + 1;
			i++;
			break;
		}
	}
	for (; i < str.length(); i++)
	{
		if (str[i] == ' ')
		{
			str3 = str.substr(index, i - index);
			index = i + 1;
			i++;
			break;
		}
	}
	str4 = str.substr(index, str.length() - index);
	if (str1 != "" && str2 != "" && str3 != "" && str4 != "")
		return true;
	else return false;
}

int XulyInput(string str, string& doiso, int& coso)
{
	if (str == "") return KHONG_HOP_LE;
	//Xóa khoảng trắng đầu và cuối
	int i = 0, dem = 0;
	while (str[0] == ' ')
		str.erase(str.begin());
	while (str[str.length()] == ' ')
		str.erase(str.end());
	// Đếm khoảng trắng trong chuỗi
	for (i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ')
			dem++;
	}

	//Nếu có 2 khoảng trắng hoặc là đổi cơ số hoặc là xoay bit hoặc là phép NOT
	//Nếu có 3 khoảng trắng hoặc là toán tử 2 ngôi hoặc là dịch bit

	if (dem == 2)
	{
		string str1, str2, str3;

		Tach_3_Doi_So(str, str1, str2, str3);

		doiso = str3 ;

		coso = stoi(str1);
		if (str2.compare("~") == 0)
		{
			doiso = str3;
			return PHEP_NOT;
		}
		if (str2.compare("2") == 0 || str2.compare("10") == 0 || str2.compare("16") == 0)
		{
			doiso = str2 + ' ' + str3 ;
			return QUY_DOI;
		}
		if (str2.compare("ror") == 0)
			return PHEP_XOAY_PHAI;

		if (str2.compare("rol") == 0)
			return PHEP_XOAY_TRAI;

	}
	else if (dem == 3)
	{
		string str1, str2, str3, str4;
		Tach_4_Doi_So(str, str1, str2, str3, str4);

		doiso = str2 + ' ' + str4;

		coso = stoi(str1);
		if (str3.compare("*") == 0) return PHEP_NHAN;

		if (str3.compare("+") == 0) return PHEP_CONG;

		if (str3.compare("-") == 0) return PHEP_TRU;

		if (str3.compare("/") == 0) return PHEP_CHIA;

		if (str3.compare("<<") == 0) return PHEP_DICH_TRAI;

		if (str3.compare(">>") == 0) return PHEP_DICH_PHAI;

		if (str3.compare("&") == 0) return PHEP_AND;

		if (str3.compare("|") == 0) return PHEP_OR;

		if (str3.compare("^") == 0) return PHEP_XOR;
	}
	else
	{
		
		doiso ="0";
		throw new exception("Input khong dung");
	}
}

