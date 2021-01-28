#include "QInt.h"
#include "XuLyInp.h"
#include <fstream>
using namespace std;

void UpperCase(string& str)
{
    for (int i = 0; i < str.length(); i++)
        if ((str[i] >= 'a' && str[i] <= 'z'))
            str[i] -= ('a' - 'A');
}
string chuan_hoa(string str)
{
    while (str[0] == '0')
        str.erase(str.begin());

    return str;
}
string Dao_bit(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = (1 - (str[i] - '0')) + '0';
    }
    return str;
}
string Quy_Doi(string str, int csCu, int csMoi)
{
    if (csCu == csMoi)
        return str;
    switch (csCu)
    {
    case  2:
    {
        if (csMoi == 10)
            return BinToDec(str);
        else
            if (csMoi == 16)
                return BinToHex(str);
            else return "Co so khong hop le";
        break;
    }
    case 10 :
    {
        if (csMoi == 2)
            return DecToBin(str);
        else if (csMoi == 16)
        {
            str = BinToHex(DecToBin(str));
            return str;
        }
        else
            return "Co so khong hop le";
        break;
    }
    case 16:
    {
        if (csMoi == 2)
        {
           
            return HexToBin(str);
        }
        else if (csMoi == 10)
        {
            str = BinToDec(HexToBin(str));
            return str;
        }
        else return "CO so khong hop le";
    }
    default:
        throw new exception("Khong the quy doi !!");
    }
}

int main(int argc, char** argv)
{
    ifstream inFile;
    ofstream outFile;

    if (argc < 3) {
        cout << "The format must be correct" << endl;
        cout << "Format : <name>.exe <input>.txt <output>.txt" << endl;
        return 0;
    }
    else {
        inFile.open(argv[1]);
        outFile.open(argv[2]);
    
    }
   
    
    // Kiểm tra mở tệp tin 
    if (!inFile.is_open()) {
        cout << "Khong tim thay file input hoac duong dan khong hop le" << endl;
        return 0;
    }
    if (!outFile.is_open()) {
        cout << "Khong the tao file ouput hoac duong dan khong hop le" << endl;
        return 0;
    }
    try {
        while (!inFile.eof())
        {
            string str, strx;                                               //strx là chuỗi lưu các đối số
            int fcoso = 10, key;
            getline(inFile, str);
            if (str == "") continue;
            UpperCase(str);
                key = XulyInput(str, strx, fcoso);
          
             if (key == KHONG_HOP_LE)
             {
                 outFile << "Khong hop le" << endl;
                 continue;
             }
            if (key == QUY_DOI)
            {
                string cosoMoi, So,res = "";
                Tach_2_Doi_So(strx, cosoMoi, So);
                res = Quy_Doi(So, fcoso,stoi( cosoMoi));
                outFile << chuan_hoa(res) << endl;
                continue;
            }
            switch (key)
            {
            case PHEP_CONG:
            {
                string soh1, soh2;
                Tach_2_Doi_So(strx, soh1, soh2);

                QInt A(soh1, fcoso), B(soh2, fcoso),res;            //Tạo 2 số hạng Qint 

                res = A + B;
                try
                {
                    outFile << res.toString(fcoso) << endl;
                }
                catch (exception* e)
                {
                    outFile << e->what() << endl;
                    delete e;
                    break;
                }
                break;
            }
            case PHEP_TRU:
            {
                string soh1, soh2;
                Tach_2_Doi_So(strx, soh1, soh2);

                QInt A(soh1, fcoso), B(soh2, fcoso),res;            //Tạo 2 số hạng Qint 

                res = A - B;
                try
                {
                    outFile << res.toString(fcoso) << endl;
                }
                catch (exception* e)
                {
                    outFile << e->what() << endl;
                    delete e;
                    break;
                }
                break;
            }
            case PHEP_NHAN:
            {
                string soh1, soh2;
                Tach_2_Doi_So(strx, soh1, soh2);

                QInt A(soh1, fcoso), B(soh2, fcoso),res;            //Tạo 2 số hạng Qint 

                res = A * B;
                try
                {
                    outFile << res.toString(fcoso) << endl;
                }
                catch (exception* e)
                {
                    outFile << e->what() << endl;
                    delete e;
                    break;
                }
                break;
            }
            case PHEP_CHIA:
            {
                string soh1, soh2;
                Tach_2_Doi_So(strx, soh1, soh2);

                QInt A(soh1, fcoso), B(soh2, fcoso),res;            //Tạo 2 số hạng Qint 

                //Exception handling
                try
                {
                    res = A / B;
                }
                catch (exception* e)
                {
                    outFile << e->what() << endl;
                    delete e;
                    break;
                }


                try
                {
                    outFile << res.toString(fcoso) << endl;
                }
                catch (exception* e)
                {
                    outFile << e->what() << endl;
                    delete e;
                    break;
                }
                break;
            }

            case PHEP_AND:
            {
                string soh1, soh2;
                Tach_2_Doi_So(strx, soh1, soh2);

                QInt A(soh1, fcoso), B(soh2, fcoso);            //Tạo 2 số hạng Qint 

                A = A & B;
                //Exception handling
                try
                {
                    outFile << A.toString(fcoso) << endl;
                }
                catch (exception* e)
                {
                    outFile << e->what() << endl;
                    delete e;
                    break;
                }
                break;
            }
            case PHEP_OR:
            {
                string soh1, soh2;
                Tach_2_Doi_So(strx, soh1, soh2);

                QInt A(soh1, fcoso), B(soh2, fcoso);            //Tạo 2 số hạng Qint 

                A = A | B;
                //Exception handling
                try
                {
                    outFile << A.toString(fcoso) << endl;
                }
                catch (exception* e)
                {
                    outFile << e->what() << endl;
                    delete e;
                    break;
                }
                break;
            }
            case PHEP_XOR:
            {
                string soh1, soh2;
                Tach_2_Doi_So(strx, soh1, soh2);

                QInt A(soh1, fcoso), B(soh2, fcoso);            //Tạo 2 số hạng Qint 

                A = A ^ B;
                //Exception handling
                try
                {
                    outFile << A.toString(fcoso) << endl;
                }
                catch (exception* e)
                {
                    outFile << e->what() << endl;
                    delete e;
                    break;
                }
                break;
            }
            case PHEP_NOT:
            {
                QInt A(strx, fcoso);
                QInt res = ~A;
                
                //Exception handling
                try
                {
                    outFile << chuan_hoa(res.toString(fcoso))<< endl;
                }
                catch (exception* e)
                {
                    outFile << e->what() << endl;
                    delete e;
                    break;
                }
                break;
            }
            case PHEP_DICH_TRAI:
            {
                string doiso, k = "1";

                Tach_2_Doi_So(strx, doiso, k);

                
                string res = "";
                res = Quy_Doi(strx, fcoso, 2);

                res = chuan_hoa(dich_trai(res, stoi(k)));

                res = Quy_Doi(res, 2, fcoso);
                outFile << chuan_hoa(res) << endl;
                break;
            }
            case PHEP_DICH_PHAI:
            {
                string doiso, k = "1";

                Tach_2_Doi_So(strx, doiso, k);
                string res = "";
                res = Quy_Doi(strx, fcoso, 2);

                res = chuan_hoa(dich_phai_so_hoc(res, stoi(k)));

                res = Quy_Doi(res, 2, fcoso);
                outFile << chuan_hoa(res) << endl;
                break;
            }
            case PHEP_XOAY_TRAI:
            {
                strx = Quy_Doi(strx, fcoso, 2);
                string res = xoay_trai(strx);

                res = Quy_Doi(res, 2, fcoso);
                outFile << chuan_hoa(res) << endl;
                break;
            }
            case PHEP_XOAY_PHAI:
            {
                strx = Quy_Doi(strx, fcoso, 2);
                string res = xoay_phai(strx);

                res = Quy_Doi(res, 2, fcoso);
                outFile << chuan_hoa(res) << endl;
                break;
            }
            default:
                outFile << "Input khong hop le!!!!!" << endl;
                break;
            }

        }
    }
    catch (exception* e)
    {
        outFile << e->what() << endl;
        delete e;
    }

    inFile.close();
    outFile.close();
    return 0;
}