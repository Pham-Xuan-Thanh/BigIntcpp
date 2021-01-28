#include "QInt.h"
#include "XuLyInp.h"

QInt::QInt()
{
	memset(body, 0, 16);
	coso = 10;
}

QInt::QInt(string str, int base)
{
	int length = str.length();
	coso = base;
	memset(body, 0, 16*sizeof(body[0]));				//khởi tạo giá trị tất cả byte trong body = 0
	
	bool isNeg = false;
	switch (base)
	{
	case 10:
	{
		
		if (str[0] == '-')
		{
			isNeg = true;
			str.erase(str.begin());
		}

		// Convert sang trường hợp Nhị phân giải quyết
		str = DecToBin(str);
		length = str.length();
		base = 2;
	}
	case 2:
	{
		int block = 0;
		if (str[0] == '1') isNeg = true;
		for (int pos = length - 1; pos >= 0 && length - pos <= 128 && block < 16; pos-=8)
		{
			string temp;
			if (pos < 7)
			{
				temp.resize(7 - pos, '0');
				temp += str.substr(0, pos + 1);

			}
			else
			{
				temp = str.substr(pos - 7, 8);					//Lấy 8 ký tự tương ứng với 8 bit trong chuỗi
			}
			bitset<8> foo(temp);			//Sử dụng hàm khởi tao một chuỗi 8 bit từ chuỗi

			body[block] = (unsigned char)foo.to_ulong();
			
			block++;
		}
		// Xử lý trường hợp số âm
		if (isNeg)
		{
			unsigned char pos = 0, sodu = 1;
			//Đảo bit
			for (int i = 0; i < 16; i++)
				body[i] ^= 0xFF;
			
			while (sodu == 1 && pos < 15)
			{
				if (body[pos] == 0xFF)
				{
					body[pos] = 0x00;
					sodu = 1;
				}
				else
				{
					body[pos] += sodu;
					sodu = 0;
				}
			}

		}
		break;
	}

	case 16:
	{
		for (int pos = length - 2, block = 0; pos >= -1 && length - pos <= 33 && block < 16; pos -= 2, block++)
		{
			int pos1, pos2;
			if (pos !=-1)
			{
				 pos1 = Hexa.find(str[pos + 1]),pos2= Hexa.find(str[pos]);
			}
			else
			{
				 pos1 = Hexa.find(str[pos + 1]), pos2 = Hexa.find('0');
			}
			bitset<4> foo(pos1);					//đọc bit từ ký tự đầu
			bitset<4> bar(pos2);
			bitset<8> total;									//Biến lưu tổng khi gộp bit
			//Tiến hành gộp bit
			for (int i = 0; i < 4; i++)
			{
				total[i] = foo[i];
				total[i + 4] = bar[i];
			}
			
			body[block] = (unsigned char)total.to_ulong();

		}
		break;
	}
	default:
		throw new exception("Co so ko hop le");
	}


}

QInt QInt::operator+(const QInt&M) const
{
	QInt res;
	char sodu = 0;
	for (int i = 0; i < 16; i++)
	{
		unsigned short temp = this->body[i] + M.body[i] + sodu;
		res.body[i] = temp % 256;
		sodu = temp / 256;	
	}
	return res;
}

QInt QInt::operator-(const QInt&m) const
{
	return  *this + m.Negative();
}

QInt QInt::operator*(const QInt&M) const
{
	QInt res;
	int temp = 0,
		sonho = 0;
	for (int i = 0; i < 16; i++)
	{
		temp = 0;
		for (int j = 0; j <= i; j++)
			temp += this->body[j] * M.body[i - j]; 

		temp += sonho; 

		res.body[i] = temp % 256;
		sonho = temp / 256;
	}
	return res;
}

QInt QInt::operator/(const QInt& m) const
{
	if (this->half[0] == 0 && this->half[1] == 0)
		return *this;
	if (m.half[0] == 0 && m.half[1] == 0) 
	{
		throw new exception("Loi chia cho 0");
		return m;
	}

	QInt Q = *this;
	QInt A("0");
	QInt M = m;

	bool oneIsNegative = 0;//false

	if (Q.body[15] & 0x80) {
		Q = Q.Negative();
		oneIsNegative = 1 - oneIsNegative;// Bật tắt true/false
	}
	if (M.body[15] & 0x80) {
		M = M.Negative();
		oneIsNegative = 1 - oneIsNegative;// Bật tắt true/false
	}

	for (int i = 0; i < 128; ++i) {
		A = (A << 1);						
		if (Q.body[15] & 0x80) {									//Nếu Q < 0 thì A  set = n bit 1
			A.body[0] |= 1;
		}
		else {
			A.body[0] &= 254;								
		}
		Q = Q << 1;

		A = A - M;
		if (A.body[15] & 0x80) {
			A = A + M;
			Q.body[0] = Q.body[0] & 254;
		}
		else {
			Q.body[0] = Q.body[0] | 1; // 0000 0001
		}
	}
	QInt soDu;
	if (oneIsNegative) {
		if (m.body[15] & 128)
			soDu = m + A;
		else
			soDu = m - A;
		return Q.Negative();
	}
	else {
		soDu = A;
		return Q;
	}

}

QInt QInt::operator&(const QInt&m) const
{
	QInt res;
	for (int i = 0; i < 16; i++)
		res.body[i] = body[i] & m.body[i];
	return res;
}

QInt QInt::operator|(const QInt&m) const
{
	QInt res;
	for (int i = 0; i < 16; i++)
		res.body[i] = body[i] | m.body[i];
	return res;
}

QInt QInt::operator^(const QInt&m) const
{
	QInt res;
	for (int i = 0; i < 16; i++)
		res.body[i] = body[i] ^ m.body[i];
	return res;
}




string QInt::toString(int cosoMoi)
{
	string res("");
	bool isNeg = 0;

	if (body[15] & 0x80)				// Kiểm tra bit đầu tiên có bằng 1 -> số âm
		isNeg = true;
	

	int blockID = 15;

	while (body[blockID] == 0 && blockID >=0)			//Kiểm tra các bit đầu có bằng 0
	{
		blockID--;
	}

	if (blockID < 0)		return "0";

	//Chuyển đổi các byte trong body về cơ số 2
	//Sau đó sẽ sử dụng các hàm chuyển đổi sang các hệ cơ số khác
	


	switch (cosoMoi)
	{
	case 2:
	{
		while (blockID >= 0)
		{

			bitset<8> temp(body[blockID]);				//Lưu các bit vào temp dưới dạng bitset

			res += temp.to_string();
			blockID--;
		}
		//chuẩn hóa lại chuỗi kết quả
		while (res[0] == '0') res.erase(res.begin());
		break;
	}
	case 10:
	{
		unsigned char* block = new unsigned char[16];
		// day bit tam de chuyen ve thap phan
		memcpy(block, body, 16);

		if (isNeg) {
			int so_du = 1;
			int block_pos = 0;
			for (int i = 0; i < 16; ++i) {
				block[i] ^= 0xFF;
			}
			while (so_du != 0 && block_pos < 16) {
				if (block[block_pos] == 0xFF) {
					block[block_pos] = 0;
					so_du = 1;
				}
				else {
					block[block_pos] += so_du;
					so_du = 0;
				}
			}
		}

		res = "0";
		int pos = (blockID + 1) * 8 - 1;// bo di bit cao nhat

		while (pos >= 0) {
			int vitri_trong_bit = pos % 8;
			int vitri_block = pos / 8;

			char bit = (block[vitri_block] & (1 << vitri_trong_bit));
			int add_bit = bit ? 1 : 0;

			res = nhanChuoiCho2(res, add_bit);
			--pos;
		}
		while (res[0] == '0') res.erase(res.begin());
		if (isNeg) res.insert(0, "-");
		
		delete[]block;
		break;
	}
	
		
	
	case 16:
	{
		while (blockID >= 0)
		{

			bitset<8> temp(body[blockID]);				//Lưu các bit vào temp dưới dạng bitset

			res += temp.to_string();
			blockID--;
		}
		res = BinToHex(res);
		//chuẩn hóa lại chuỗi kết quả
		while (res[0] == '0') res.erase(res.begin());
		break;
	}
	default:
		throw new exception("Co So khong hop le!");
		break;
	}
	return res;
}

QInt QInt::operator<<(int soBit) const
{
	if (soBit <= 0) throw new exception("shift left error");

	QInt result = (*this);

	char isNegative = result.body[15] & 128;
	if (isNegative) {
		result = ~result;
	}

	int soBitDich = soBit % 8;
	int soByteDich = soBit / 8;

	if (soByteDich > 0) {
		for (int i = 15; i >= soByteDich; --i) {
			result.body[i] = result.body[i - soByteDich];
		}
		memset(result.body, 0, soByteDich);
	}
	if (soBitDich == 0) return result;

	//when soBitDich > 0
	unsigned char nho_old = result.body[0] >> (8 - soBitDich),
		nho_new = 0;
	result.body[0] = (unsigned char)(result.body[0] << soBitDich);

	for (int i = 1; i < 16; ++i) {
		nho_new = result.body[i] >> (8 - soBitDich);
		unsigned char saukhiDich = (result.body[i] << soBitDich);
		result.body[i] = saukhiDich | nho_old;
		nho_old = nho_new;
		nho_new = 0;
	}

	if (isNegative) {
		result = ~result;
	}

	return result;
}

QInt QInt::Negative() const
{
	if (this->half[0] == 0 && half[1] == 0)
		return *this;

	QInt res = ~(*this);
	unsigned char pos = 0, sodu = 1;
	while (sodu == 1 && pos < 15)
	{
		if (res.body[pos] == 0xFF)
		{
			res.body[pos] = 0x00;
			sodu = 1;
		}
		else
		{
			res.body[pos] += sodu;
			sodu = 0;
		}
	}
	return res;
}

QInt operator~(const QInt& m)
{
	QInt res;
	for (int i = 0; i < 16; i++)
		res.body[i] = m.body[i] ^ 0xFF;
	return res;
	
}
string NhanChuoiCho8(string str, int a)
{
	string kq = "";

	int soNho = a;
	int pos = str.length() - 1;

	while (pos >= 0)
	{
		int soNhan = (str[pos] - '0') * 8 + soNho;
		soNho = soNhan / 10;
		soNhan = soNhan % 10;

		kq.insert(0, to_string(soNhan));
		pos--;
	}

	if (soNho)
	{
		kq.insert(0, "1");
	}

	return kq;
}
string ChiaChuoiCho16(string str, int& soDu)
{
	if (str == "0")
		return "0";
	string KQ;
	unsigned char pos = 0;
	soDu = 0;
	// chia chuoi cho 16, chia tu trai sang phai
	while (pos < str.length())
	{

		int sochia = ((str[pos] - '0') + soDu * 10) / 16;
		KQ.push_back(sochia + '0');
		soDu = ((str[pos] - '0') + soDu * 10) - 16 * sochia;
		pos++;
	}

	while (KQ.front() == '0' && KQ.length() > 1)
		KQ.erase(0, 1);

	return KQ;
}





int canBangChuoi(string& str1, string& str2)
{
	int len1 = str1.length();
	int len2 = str2.length();
	int len = 0;

	if (len2 > len1)
	{
		for (int i = 0; i < len2 - len1; i++)
			str1.insert(0, "0");

		len = len2;
	}

	else
	{
		for (int i = 0; i < len1 - len2; i++)
			str2.insert(0, "0");
		len = len1;
	}

	return len;
}
string cong_chuoi_he_10(string str1, string str2)
{
	string kq = "";

	int len = canBangChuoi(str1, str2);
	int bienNho = 0;

	for (int i = len - 1; i >= 0; i--)
	{
		int str1Bit = str1[i] - '0';
		int str2Bit = str2[i] - '0';

		int sum = (str1Bit + str2Bit + bienNho);

		kq.insert(0, to_string(sum % 10));

		bienNho = sum / 10;

	}

	if (bienNho == 1) //tran so
		kq.insert(0, "1");
	return kq;
}
string cong_chuoi(string str1, string str2)
{
	string kq = "";

	int len = canBangChuoi(str1, str2);

	int bienNho = 0;

	for (int i = len - 1; i >= 0; i--)
	{
		int str1Bit = str1[i] - '0';
		int str2Bit = str2[i] - '0';

		int sum = (str1Bit ^ str2Bit ^ bienNho);
		kq.insert(0, to_string(sum));

		bienNho = (str1Bit & str2Bit) | (str2Bit & bienNho) | (str1Bit & bienNho);
	}

	if (bienNho == 1) //tran so
		kq.insert(0, "1");
	return kq;
}
string tru_chuoi(string str1, string str2)
{
	string kq = "";
	int len = canBangChuoi(str1, str2);
	for (int i = 0; i < len; ++i)
	{
		if (str2[i] == '0')
			str2[i] = '1';
		else if (str2[i] == '1')
			str2[i] = '0';
	}

	str2 = cong_chuoi(str2, "1");
	kq = cong_chuoi(str1, str2);
	kq.erase(0, 1);
	return kq;
}
string NhanChuoiCho2(string str)
{
	string kq = "";

	int soNho = 0;
	int pos = str.length() - 1;

	while (pos >= 0)
	{
		int soNhan = (str[pos] - '0') * 2 + soNho;
		soNho = soNhan / 10;
		soNhan = soNhan % 10;

		kq.insert(0, to_string(soNhan));
		pos--;
	}

	if (soNho)
	{
		kq.insert(0, "1");
	}

	return kq;
}
string nhanChuoiCho2(string dec, int add_value)
{
	{
		string kq = "";

		int overflow_prev = add_value;
		int pos = dec.length() - 1;

		while (pos >= 0) {
			int donvi_nhan = (dec[pos] - '0') * 2 + overflow_prev;
			overflow_prev = donvi_nhan / 10;
			donvi_nhan = donvi_nhan % 10;

			kq.push_back(donvi_nhan + '0');
			pos--;
		}
		if (overflow_prev) {
			kq.push_back('1');
		}
		reverse(kq.begin(), kq.end());

		return kq;
	}

}
string ChiaChuoiCho2(string str, int& soDu)
{
	if (str == "0") return "0";
	string KQ;
	unsigned char pos = 0;
	soDu = 0;

	// chia chuoi cho 2, chia tu trai sang phai
	while (pos < str.length())
	{
		int sochia = ((str[pos] - '0') + soDu * 10) / 2;

		KQ.push_back(sochia + '0');

		soDu = (str[pos] - '0') % 2;

		pos++;
	}

	while (KQ.front() == '0' && KQ.length() > 1)
		KQ.erase(0, 1);

	return KQ;
}
string DecToBin(string str)
{
	if (str == "") return "";
	if (str == "0") return "0";

	string ChuoiTraVe = "";
	int soTanCung = 0;

	int temp = 0;
	if (str[0] == '-') // Khong phai so am
	{
		temp = 1;
	}

	if (temp == 0)
	{
		while (str != "0")
		{
			int len = str.length();
			soTanCung = (str[len - 1] - '0');
			int bin = soTanCung % 2;
			ChuoiTraVe.insert(0, to_string(bin));
			int soDu = 0;
			str = ChiaChuoiCho2(str, soDu);
		}

	}

	// la so am, chuyen ve bu 2
	else if (temp == 1)
	{
		str.erase(0, 1); // xoa dau -

		while (str != "0")
		{
			int len = str.length();
			soTanCung = (str[len - 1] - '0');
			int bin = soTanCung % 2;

			// dao bit
			if (bin == 1)
				bin = 0;
			else if (bin == 0)
				bin = 1;

			ChuoiTraVe.insert(0, to_string(bin));
			int soDu = 0;
			str = ChiaChuoiCho2(str, soDu);
		}
		ChuoiTraVe = cong_chuoi(ChuoiTraVe, "1");

	}

	int len = ChuoiTraVe.length();

	for (int i = 0; i < 8 * (len / 8 + 1) - len; i++)
	{
		if (temp == 1)
			ChuoiTraVe.insert(0, "1");
	}

	return ChuoiTraVe;
}
string BinToDec(string str)
{
	if (str == "") return "";
	if (str == "") return "0";

	string SoTraVe = "";
	string bienNho = "1";

	int len = str.length();

	if (str[0] == '0' || len % 8 != 0)
	{
		int pos = len - 1;

		while (pos >= 0)
		{
			int soTanCung = (str[pos] - '0');

			if (soTanCung == 1)
				SoTraVe = cong_chuoi_he_10(SoTraVe, bienNho);

			bienNho = NhanChuoiCho2(bienNho);
			pos--;
		}
	}

	else if (str[0] == '1' && len % 8 == 0)
	{
		str = tru_chuoi(str, "1");
		int pos = len - 1;

		while (pos >= 0)
		{
			int soTanCung = (str[pos] - '0');

			if (soTanCung == 0)
				SoTraVe = cong_chuoi_he_10(SoTraVe, bienNho);

			bienNho = NhanChuoiCho2(bienNho);
			pos--;
		}

		SoTraVe.insert(0, "-");
	}
	return SoTraVe;
}





string DecToHex(string str)
{
	if (str == "") return "";
	if (str == "0") return "0";

	string ChuoiTraVe = "";
	int temp = 0;

	if (str[0] == '-')
	{
		temp = 1;
		str.erase(0, 1); // xoa dau -
	}

	while (str != "0")
	{
		int soDu = 0;
		str = ChiaChuoiCho16(str, soDu);
		if (soDu < 10)
			ChuoiTraVe.insert(0, to_string(soDu));
		else
			ChuoiTraVe.insert(0, 1, soDu + '7');
	}

	if (temp == 1)
	{
		ChuoiTraVe.insert(0, "-");
	}

	return ChuoiTraVe;
}

string HexToDec(string str)
{
	string SoTraVe = "";
	int viTri = 0;
	string soNho = "1";
	int temp = 0;

	if (str[0] == '-')
	{
		temp = 1;
		str.erase(0, 1); // xoa dau '-'
	}

	for (int i = str.length() - 1; i >= 0; i--)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			// thieu phep nhan	int soNhan = (str[i] - 48) * soNho;
			//thieu phep cong	SoTraVe = SoTraVe + soNhan;

			soNho = nhanChuoiCho2(NhanChuoiCho8(soNho, 0), 0);
		}


		else if (str[i] >= 'A' && str[i] <= 'F')
		{
			// thieu phep nhan	int soNhan = (str[i] - 55) * soNho;
			// thieu phep cong	SoTraVe = SoTraVe + soNhan;

			soNho = nhanChuoiCho2(NhanChuoiCho8(soNho, 0), 0);
		}
	}


	if (temp == 1)
	{
		SoTraVe.insert(0, "-");
	}


	return SoTraVe;
}

string BinToHex(string str)
{
	if (str == "") return "0";
	int len , id = 0;
	string res = "";
	while (str.length() % 4)
	{
		str.insert(str.begin(), '0');
	}

	len = str.length();
	while (len - id >=4 && id <= 128)
	{
		
		string tmp = str.substr(id,4);
		bitset<4> foo(tmp);

		res += Hexa[foo.to_ulong()];
		id += 4;
	}
	if (len - id != 0)
	{
		string tmp = str.substr(0, id);
		bitset<4> foo(tmp);

		res += Hexa[foo.to_ulong()];
	}
	return res;

}

string HexToBin(string str)
{
	if (str == "") return "";
	if (str == "0") return "0";
	
	string res="";
	for (int i = 0; i < str.length(); i++)
	{
		bitset<4> foo(Hexa.find_first_of(str[i]));

		res += foo.to_string();
	}
	while (res[0] == '0') res.erase(res.begin());

	return res;
}


string dich_trai(string str, int n )
{
	string KQ("");
	int len = str.length();
	if (n > len)
		n = len;

	// them 0 vao cuoi chuoi
	for (int i = 0; i < n; i++)
		KQ.insert(0, "0");


	//shift
	while (len > n)
	{
		KQ.insert(KQ.begin(), str[len - 1]);
		len--;
	}

	return KQ;
}

string dich_phai_so_hoc(string str, int n)
{
	string KQ("");
	int len = str.length();

	for (int i = 0; i < n; i++)
	{
		if (len % 8 != 0)
		{
			KQ.insert(0, "0");
		}
		else
		{
			if (str[0] == '1')
				KQ.insert(0, "1");
			else
				KQ.insert(0, "0");

		}
	}
	for (int i = 0; i < len - n; i++)
	{
		KQ.insert(KQ.end(), str[i]);
	}


	return KQ;
}

string xoay_trai(string str)
{
	string res("0");
	char bit_nho = str[0];
	res = dich_trai(str,1);
	res[res.length() - 1] = bit_nho;
	return res;
}

string xoay_phai(string str)
{
	 string res("0");
	 int len = str.length();
	 char bit_nho = str[len - 1];
	 res = dich_phai_so_hoc(str, 1);
	 res[0] = bit_nho;

	 return res;
}
