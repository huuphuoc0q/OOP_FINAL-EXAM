#include <iostream>
#include <iomanip>
#include <memory>
#include <limits>
#include <sstream>
#include <string>
#include "NhanVat.h"
#include "Sung.h"
#include "Kiem.h"
#include "PhepThuat.h"
using namespace std;

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void mauChu(int mau){
    #ifdef _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mau);
    #else
        (void)mau;
    #endif
}

void xoaManHinh(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

const int CHIEU_RONG_DAU_TRUONG = 140;
const string MAU_SUNG      = "\033[93m";   
const string MAU_KIEM      = "\033[96m";   
const string MAU_PHEP      = "\033[95m";   
const string MAU_HERO      = "\033[38;5;190m"; 
const string MAU_BOSS      = "\033[1;91m"; 
const string MAU_RESET     = "\033[0m";    
const string MAU_KHUNG_DAU_TRUONG = "\033[38;5;166m";
const string MAU_TENBOSS = "\033[1;91m";
const string MAU_TENHERO = "\033[38;5;190m";
const string MAU_KVK = "\033[38;5;154m";
const string MAU_NHATKY = "\033[38;5;189m";
const string MAU_WIN = "\033[38;5;118m";
// const string mautext = "\033[38;5;m";

unsigned int docMaUnicode(const string &chuoi, size_t viTri, size_t &soByte)
{
    const unsigned char dau = static_cast<unsigned char>(chuoi[viTri]);
    if (dau < 0x80) {
        soByte = 1;
        return dau;
    }

    size_t doDai = dau >= 0xF0 ? 4 : dau >= 0xE0 ? 3 : dau >= 0xC2 ? 2 : 1;
    if (viTri + doDai > chuoi.length()) {
        soByte = 1;
        return dau;
    }

    unsigned int ma = dau & (doDai == 2 ? 0x1F : doDai == 3 ? 0x0F :
        doDai == 4 ? 0x07 : 0xFF);
    for (size_t i = 1; i < doDai; ++i) {
        const unsigned char tiep =
            static_cast<unsigned char>(chuoi[viTri + i]);
        if ((tiep & 0xC0) != 0x80) {
            soByte = 1;
            return dau;
        }
        ma = (ma << 6) | (tiep & 0x3F);
    }

    soByte = doDai;
    return ma;
}

int doRongKyTu(unsigned int ma)
{
    if (ma == 0x200D || (ma >= 0x0300 && ma <= 0x036F) ||
        (ma >= 0x1AB0 && ma <= 0x1AFF) ||
        (ma >= 0x1DC0 && ma <= 0x1DFF) ||
        (ma >= 0x20D0 && ma <= 0x20FF) ||
        (ma >= 0xFE00 && ma <= 0xFE0F) ||
        (ma >= 0xFE20 && ma <= 0xFE2F) ||
        (ma >= 0xE0100 && ma <= 0xE01EF))
        return 0;

    if (ma < 0x20 || (ma >= 0x7F && ma < 0xA0))
        return 0;

    if (ma >= 0x1100 && (ma <= 0x115F || ma == 0x2329 || ma == 0x232A ||
        (ma >= 0x2E80 && ma <= 0xA4CF && ma != 0x303F) ||
        (ma >= 0xAC00 && ma <= 0xD7A3) ||
        (ma >= 0xF900 && ma <= 0xFAFF) ||
        (ma >= 0xFE10 && ma <= 0xFE19) ||
        (ma >= 0xFE30 && ma <= 0xFE6F) ||
        (ma >= 0xFF00 && ma <= 0xFF60) ||
        (ma >= 0xFFE0 && ma <= 0xFFE6) ||
        (ma >= 0x1F300 && ma <= 0x1FAFF) ||
        (ma >= 0x20000 && ma <= 0x3FFFD)))
        return 2;

    return 1;
}

int doRongHienThi(const string &chuoi)
{
    int tong = 0;
    for (size_t i = 0; i < chuoi.length();) {
        size_t soByte;
        tong += doRongKyTu(docMaUnicode(chuoi, i, soByte));
        i += soByte;
    }
    return tong;
}

string catTheoDoRong(const string &chuoi, int chieuRong)
{
    string ketQua;
    int tong = 0;
    for (size_t i = 0; i < chuoi.length();) {
        size_t soByte;
        unsigned int ma = docMaUnicode(chuoi, i, soByte);
        int rongKyTu = doRongKyTu(ma);
        if (tong + rongKyTu > chieuRong)
            break;
        ketQua.append(chuoi, i, soByte);
        tong += rongKyTu;
        i += soByte;
    }
    return ketQua;
}

string canGiua(const string &noiDung, int chieuRong)
{
    int rongNoiDung = doRongHienThi(noiDung);
    if (rongNoiDung >= chieuRong)
        return noiDung;

    int benTrai = (chieuRong - rongNoiDung) / 2;
    return string(benTrai, ' ') + noiDung +
           string(chieuRong - benTrai - rongNoiDung, ' ');
}


string thanhMau(const string &ten, int hp, int maxHP, int rong = 20)
{
    int day = 0;
    if (maxHP > 0 && hp > 0)
        day = hp >= maxHP ? rong : static_cast<int>(
            static_cast<long long>(hp) * rong / maxHP);

    string tenHienThi = catTheoDoRong(ten, 15);
    tenHienThi += string(15 - doRongHienThi(tenHienThi), ' ');

    int doDaiThuc = 15 + 1 + rong + 2 
                  + static_cast<int>(to_string(hp).length()) + 1 
                  + static_cast<int>(to_string(maxHP).length());

    int khungRong = CHIEU_RONG_DAU_TRUONG / 2; 
    int lechTrai = max(0, (khungRong - doDaiThuc) / 2);
    int lechPhai = max(0, khungRong - doDaiThuc - lechTrai);
    
    int marginTrai = max(0, (CHIEU_RONG_DAU_TRUONG - (khungRong + 4)) / 2); 

    string noiDung = string(lechTrai, ' ')
                   + "\033[97m" + tenHienThi + "["
                   + "\033[92m" + string(day, '#')
                   + "\033[90m" + string(rong - day, '-')
                   + "\033[97m] " + to_string(hp) + "/" + to_string(maxHP)
                   + string(lechPhai, ' ');

    string ketQua = string(marginTrai, ' ')
                  + MAU_KHUNG_DAU_TRUONG + "||" + MAU_RESET
                  + noiDung
                  + MAU_KHUNG_DAU_TRUONG + "||" + MAU_RESET + "\n";

    return ketQua;
}
void khungDauTruong(const NhanVat& nv, int bossHP, int bossMax) {
    cout<<MAU_KHUNG_DAU_TRUONG; 
    cout<<string(33, ' ') << "++======================================================================++"<<endl;
    cout<<string(33, ' ') << "||                              DAU TRUONG                              ||"<<endl;
    cout<<string(33, ' ') << "++======================================================================++"<<endl;
    cout<<string(33, ' ') << "||              " << MAU_TENHERO <<"HAC SI" <<MAU_TENBOSS<<"                             GENGAR               "<<MAU_KHUNG_DAU_TRUONG<<"||"<<endl;
    cout<<string(33, ' ') << "||             "<<MAU_TENHERO<<"💪(◣_◢)👍                            "<<MAU_TENBOSS<<"/\\_/\\               "<<MAU_KHUNG_DAU_TRUONG<<"||"<<endl;
    cout<<string(33, ' ') << "||              "<<MAU_TENHERO<<"| [][]|                            "<<MAU_TENBOSS<<"(◣.◢ )               "<<MAU_KHUNG_DAU_TRUONG<<"||"<<endl;
    cout<<string(33, ' ') << "||              "<<MAU_TENHERO<<"| [][]|                            "<<MAU_TENBOSS<<"(  \"  )              "<<MAU_KHUNG_DAU_TRUONG<<"||" <<endl;
    cout<<string(33, ' ') << "||              "<<MAU_TENHERO<<"=======                           "<<MAU_TENBOSS<<"/|     |\\             "<<MAU_KHUNG_DAU_TRUONG<<"||" <<endl;
    cout<<string(33, ' ') << "||              "<<MAU_TENHERO<<"//  \\\\                           "<<MAU_TENBOSS<<"(_________)            "<<MAU_KHUNG_DAU_TRUONG<<"||" <<endl;
    cout<<string(33, ' ') << "||                                                                      ||" <<endl;
    cout<<(thanhMau("HP HAC SI", nv.getMau(), nv.getMauToiDa(), 20));
    cout<<(thanhMau("HP Gengar", bossHP, bossMax, 20)); 
    cout<<string(33, ' ')<<MAU_KHUNG_DAU_TRUONG << "++======================================================================++"<<endl;
}
void dongKe(char kiTu,string text, int size_){
    int left = max(0, (size_ - doRongHienThi(text))/2);
    for(int i = 0; i<left; i++)
        cout<<kiTu;
    cout<<text; 
    for(int i = left + doRongHienThi(text); i<size_; i++)
        cout<<kiTu; 
    cout<<endl;
}

void inLine(std::string kiTu, int size_, std::string backGround, std::string text, std::string align = "center", int valueColor = 7){
    std::cout<<backGround; 
    if(align == "left"){
        for(int i = 0; i<5; i++) std::cout<<kiTu; 
        std::cout<<text; 
        for(int i = 0; i<size_ - text.length() - 5; i++) std::cout<<kiTu; 
        cout<<MAU_RESET;
        return; 
    }
    int left = (size_/2 - (text.length()/2));
    for(int i = 0; i<left; i++) 
        std::cout<<kiTu; 
    for(int i = 0; i<text.length(); i++)
        {
            mauChu(valueColor); 
            std::cout<<text[i]; 
        }
    std::cout<<backGround; 
    
    for(int i = left + text.length(); i<size_; i++) 
        std::cout<<kiTu; 
    cout<<MAU_RESET;
    
}
void printTitle(std::string title, string color_Khung){
    cout<<string(33, ' '); 
    inLine("=", CHIEU_RONG_DAU_TRUONG/2 + 3, color_Khung, "", "center", 14); std::cout<<std::endl;
    cout<<color_Khung; 
    cout<<string(33, ' ');
    std::cout<<"|";
    inLine(" ", CHIEU_RONG_DAU_TRUONG/2 + 1, color_Khung, title,"center", 14); 
    cout<<color_Khung;
    std::cout<<"|";
    std::cout<<std::endl;
    cout<<string(33, ' ');
    inLine("=", CHIEU_RONG_DAU_TRUONG/2 + 3, color_Khung, ""); std::cout<<std::endl;
    cout<<MAU_RESET;
} 

void printOption(std::string title, std::vector<std::string>& option, string color_Khung, string color_Opt){
    string tmp_color = color_Opt;
    printTitle(title, color_Khung);
    for(int i = 0; i<option.size(); i++){
        std::cout<<color_Khung;
        cout<<string(33, ' ');
        int tmp = i; if (tmp==(option.size() - 1)) tmp = -1;
        std::cout<<"|";
        switch(i) {
            case 0:
                color_Opt = MAU_SUNG; 
                break;
            case 1: 
                color_Opt = MAU_KIEM;
                break;
            case 2: 
                color_Opt = MAU_PHEP;
                break;
            case 8: 
                color_Opt = MAU_BOSS; 
                break;
            case 9: 
                color_Opt = MAU_BOSS;
                break;
            default: 
                color_Opt = tmp_color;
                break;
        }
        inLine(" ", CHIEU_RONG_DAU_TRUONG/2 + 1, color_Opt, std::to_string(tmp + 1) + ". " + option[i], "left"); 
        cout<<color_Khung;
        std::cout<<"|"<<"\n";
    } 
    cout<<string(33, ' ');
    inLine("=", CHIEU_RONG_DAU_TRUONG/2 + 3, color_Khung, "");
    std::cout << "\033[0m";
    std::cout<<"\n";
}

void menu()
{
    vector<string> opt = {
        "Chon sung Eclipse", 
        "Chon kiem Phan Quang", 
        "Chon phep thuat Loi Quang", 
        "Tan cong Boss trong t giay", 
        "Tan cong Boss", 
        "Nap dan", 
        "Xem trang thai va thong tin vu khi", 
        "Hoi mana",
        "Choi lai",
        "Thoat"
    };
    printOption("MENU", opt, MAU_KVK, MAU_NHATKY); cout<<endl;
}

void printHeader() {
    mauChu(11);
    dongKe('=',"", 140); 
    cout<<"      ██████╗  █████╗ ████████╗████████╗██╗     ███████╗    ███████╗██╗███╗   ███╗██╗   ██╗██╗      █████╗ ████████╗ ██████╗ ██████╗"<<endl;
    cout<<"      ██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║     ██╔════╝    ██╔════╝██║████╗ ████║██║   ██║██║     ██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗"<<endl;
    cout<<"      ██████╔╝███████║   ██║      ██║   ██║     █████╗      ███████╗██║██╔████╔██║██║   ██║██║     ███████║   ██║   ██║   ██║██████╔╝"<<endl;
    cout<<"      ██╔══██╗██╔══██║   ██║      ██║   ██║     ██╔══╝      ╚════██║██║██║╚██╔╝██║██║   ██║██║     ██╔══██║   ██║   ██║   ██║██╔══██╗"<<endl;
    cout<<"      ██████╔╝██║  ██║   ██║      ██║   ███████╗███████╗    ███████║██║██║ ╚═╝ ██║╚██████╔╝███████╗██║  ██║   ██║   ╚██████╔╝██║  ██║"<<endl;
    cout<<"      ╚═════╝ ╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚══════╝╚══════╝    ╚══════╝╚═╝╚═╝     ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝"<<endl;
    dongKe('=',"CODEPATH", 140); 
    mauChu(7);
}
void printKhoVuKhi(NhanVat& nv) {
    cout<<MAU_KVK;
    string v1 = "+" + (string( CHIEU_RONG_DAU_TRUONG/4 + 3, '=') + " KHO VU KHI " + string( CHIEU_RONG_DAU_TRUONG/4 + 3, '=')) + "+";
    cout<<canGiua(v1, CHIEU_RONG_DAU_TRUONG)<<endl; 

    // v1 = "|" + nv.getVuKhi(0)->getTen() + " |"
    for(int i = 0 ;i<3; i++ ){ 
        cout << string(25, ' ');  
        string color_; 
        switch(i) {
            case 0: 
                color_ = MAU_SUNG; 
                break;
            case 1: 
                color_ = MAU_KIEM;
                break;
            case 2: 
                color_ = MAU_PHEP;
                break;
            default: 
                break;
        }
        cout<<MAU_KVK;
        cout<<"|" <<color_<< to_string(i + 1) + ". " << left <<setw(17) << nv.getVuKhi(i)->getTen();
        cout<<MAU_KVK; 
        cout<<"| "<<color_ << left << setw(16) << nv.getVuKhi(i)->getLoai();
        cout<<MAU_KVK;
        cout<<"| "<<color_ <<"Sat thuong " << left << setw(3) << nv.getVuKhi(i)->getSatThuongCoBan();
        cout<<MAU_KVK;
        cout<<"| "<< color_<<"Toc do " << left << setw(3) << nv.getVuKhi(i)->getTocDoRaDon() <<" s/don";
        cout<<MAU_KVK;
        VuKhi *v = nv.getVuKhi(i);
        if (auto *s = dynamic_cast<Sung *>(v))
            cout<<"| "<< color_ <<"Dan " << s->getSoDan() <<"/5" << string (7, ' ') <<MAU_KVK<< "|";
        if (auto *p = dynamic_cast<PhepThuat *>(v)){
            if (p->getManaHienTai() < 10) 
                cout<<"| "<< color_<<"Mana 0" <<p->getManaHienTai() <<"/30" << string(4, ' ') <<MAU_KVK<< "|";
            else   
                cout<<"| "<< color_<<"Mana " <<p->getManaHienTai() <<"/30" << string(4, ' ') <<MAU_KVK<< "|";
        }
        if (auto *k = dynamic_cast<Kiem *>(v))
            if (k->getDoBen() < 100 && k->getDoBen() >= 10) {
                cout<<"| "<< color_<<"Do ben  " <<k->getDoBen() <<"/100"<<MAU_KVK<<"|";
            }
            else if (k->getDoBen() == 100) {
                cout<<"| "<< color_<<"Do ben " <<k->getDoBen() <<"/100"<<MAU_KVK<<"|";
            }
            else 
                cout<<"| "<< color_<<"Do ben   " <<k->getDoBen() <<"/100"<<MAU_KVK<<"|";
        cout << right <<endl;
    }
    cout<<MAU_KVK;
    v1 = "+" + (string( CHIEU_RONG_DAU_TRUONG/4 + 3, '=') + "============" + string( CHIEU_RONG_DAU_TRUONG/4 + 3, '=')) + "+";
    cout<<canGiua(v1, CHIEU_RONG_DAU_TRUONG)<<endl; 
}


void printNhatKy(int chon, NhanVat& nv, int diem, int luot, string dongNhatKy, bool ketThuc, int bossHP) {
    VuKhi* v = nv.getVuKhi(chon);
    string color_VK; 
    if (auto *s = dynamic_cast<Sung *>(v))
        color_VK = MAU_SUNG;
    if (auto *k = dynamic_cast<Kiem *>(v))
        color_VK = MAU_KIEM;
    if (auto *p = dynamic_cast<PhepThuat *> (v))
        color_VK = MAU_PHEP;
    cout <<string(33, ' ') 
    << MAU_NHATKY << "Vu khi dang chon: " 
    << color_VK << (chon >= 0 && chon < nv.soVuKhi() ? nv.getVuKhi(chon)->getTen() : "Chua chon") << "\n";
    cout <<string(33, ' ') 
    << MAU_NHATKY << "Diem sat thuong: " 
    << MAU_RESET << diem << " | " << MAU_NHATKY << "Luot: " <<MAU_RESET<< luot << "\n";
    mauChu(14);
    cout <<string(33, ' ') 
    << MAU_NHATKY << "Nhat ky: " 
    << MAU_SUNG << dongNhatKy << "\n";
    mauChu(7);
    if (ketThuc)
    {
        mauChu(bossHP == 0 ? 10 : 12);
        cout << MAU_WIN << (bossHP == 0 ? "*** CHIEN THANG! BOSS DA BI HA GUC ***" : "*** THAT BAI! NHAN VAT DA HET MAU ***") << "\n";
        mauChu(7);
    }
    cout<<MAU_RESET; 
    cout<<"\n";
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    NhanVat nv("HAC SI", 160);
    nv.themVuKhi(make_unique<Sung>("Eclipse", 15, 0.5, 5, 2.0));
    nv.themVuKhi(make_unique<Kiem>("Phan Quang", 20, 1.0, 100, 20));
    nv.themVuKhi(make_unique<PhepThuat>("Loi Quang", 25, 1.0, "Loi", 30)); 

   
    int bossHP = 200, bossMax = 200, diem = 0, luot = 1, chon = 0;
    bool ketThuc = false;
    string dongNhatKy = "Chao mung den dau truong!";

    while (true)
    {
        xoaManHinh();
        printHeader(); cout<<endl;
        khungDauTruong(nv, bossHP, bossMax);
        printKhoVuKhi(nv);
        // printInfo(nv);
        printNhatKy(chon, nv, diem, luot, dongNhatKy, ketThuc, bossHP); 
        menu();
        
        cout << string(33, ' ') << "\033[1;96m▶ Nhap lua chon: \033[0m";
        int luaChon;
        if (!(cin >> luaChon))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            dongNhatKy = "Du lieu khong hop le.";
            continue;
        }

        if (luaChon == 0)
            break;
        if (luaChon == 9)
        {
            bossHP = bossMax;
            nv.hoiMau();
            diem = 0;
            luot = 1;
            chon = 0;
            ketThuc = false;
            if (auto *s = dynamic_cast<Sung *>(nv.getVuKhi(0)))
                s->napDan();
            if (auto *p = dynamic_cast<PhepThuat *>(nv.getVuKhi(2)))
                p->hoiMana();
            if (auto *k = dynamic_cast<Kiem *>(nv.getVuKhi(1)))
                k->setDoBen(100);
            dongNhatKy = "Tran dau da duoc dat lai.";
            continue;
        }
        if (luaChon >= 1 && luaChon <= 3)
        {
            chon = luaChon - 1;
            dongNhatKy = "Da chon " + nv.getVuKhi(chon)->getTen() + ".";
            continue;
        }
        if (luaChon == 7)
        {
            nv.hienThiTrangThai();
            cout << "\nNhan Enter de tiep tuc...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            continue;
        }
        if (luaChon == 6)
        {
            if (auto *s = dynamic_cast<Sung *>(nv.getVuKhi(0)))
            {
                s->napDan();
                dongNhatKy = "Sung Eclipse da nap day dan.";
            }
            else
                dongNhatKy = "Khong tim thay sung.";
            continue;
        }
        if (luaChon == 8)
        {
            if (auto *p = dynamic_cast<PhepThuat *>(nv.getVuKhi(2)))
            {
                p->hoiMana();
                dongNhatKy = "Mana da hoi day.";
            }
            continue;
        } 
        if (luaChon == 4 || luaChon == 5)
        {
            if (ketThuc)
            {
                dongNhatKy = "Tran dau da ket thuc. Hay choi lai.";
                continue;
            }

            VuKhi *v = nv.getVuKhi(chon);
            int satThuong = 0;
            bool hopLe = true;
            int thoiGian = 1; 

            if (luaChon == 4)
            {
                cout<<"Nhap thoi gian danh boss trong vong t giay: ";
                cin>>thoiGian; 
            }
            if (auto *s = dynamic_cast<Sung *>(v))
            {
                if (!s->conDan())
                {
                    dongNhatKy = "Het dan! Hay chon Nap dan.";
                    hopLe = false;
                }
                if (s->soDanCanDung(thoiGian) > s->getSoDan()) {
                    dongNhatKy = "Khong the tan cong, vi khong du dan";
                    hopLe = false; 
                }
                else
                {
                    s->tanCong();
                    Sleep(2000); 
                    satThuong = s->satThuong(thoiGian);
                    s->suDungDan(thoiGian);
                }
            }
            else if (auto *k = dynamic_cast<Kiem *>(v))
            {
                
                if (k->getDoBen() < 20)
                {
                    dongNhatKy = "Kiem khong du do ben de tan cong.";
                    hopLe = false;
                }
                if (k->doBenCanDung(thoiGian) > k->getDoBen()) {
                    dongNhatKy = "Khong the tan cong, vi khong du do ben";
                    hopLe = false; 
                }
                else
                {
                    k->tanCong();
                    Sleep(2000); 
                    satThuong = k->satThuong(thoiGian);
                    k->setDoBen(k->getDoBen() - k->doBenCanDung(thoiGian));
                }
            }
            else if (auto *p = dynamic_cast<PhepThuat *>(v))
            {
                if (p->soManaCanDung(thoiGian) > p->getManaHienTai()) {
                    dongNhatKy = "Khong the tan cong, vi khong du mana";
                    hopLe = false; 
                }
                else
                {
                    p->tanCong();
                    Sleep(2000);
                    satThuong = p->satThuong(thoiGian);
                    p->suDungMana(8*thoiGian);
                }
            }
            if (hopLe)
            {
                bossHP = max(0, bossHP - satThuong);
                diem += satThuong;
                dongNhatKy = nv.getTen() + " dung " + v->getTen() + ", gay " + to_string(satThuong) + " sat thuong.";
                if (bossHP == 0)
                {
                    ketThuc = true;
                    dongNhatKy = "Chien thang! Boss da bi ha guc.";
                }
                else
                {
                    int phanCong = 0;
                    if (dynamic_cast<Sung *>(v) != nullptr)
                    {
                        phanCong = 35*(static_cast<int>((thoiGian*1.0)/v->getTocDoRaDon()));
                    }
                    else if (dynamic_cast<Kiem *>(v) != nullptr)
                    {
                        phanCong = 15*(static_cast<int>((thoiGian*1.0)/v->getTocDoRaDon()));
                    }
                    else if (dynamic_cast<PhepThuat *>(v) != nullptr)
                    {
                        phanCong = 20*(static_cast<int>((thoiGian*1.0)/v->getTocDoRaDon()));
                    }
                    nv.nhanSatThuong(phanCong);
                    dongNhatKy += " Boss phan cong " + to_string(phanCong) + " sat thuong.";
                    if (nv.getMau() == 0)
                    {
                        ketThuc = true;
                        dongNhatKy = "That bai! Nhan vat da het mau.";
                    }
                }
                ++luot;
            }
            continue;
        }
        dongNhatKy = "Lua chon khong hop le.";
    }
    mauChu(7);
    cout << "Cam on ban da choi!\n";
    return 0;
}


//Tốc độ ra đòn phải là giây / đòn 