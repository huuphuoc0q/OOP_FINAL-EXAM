#ifndef NHANVAT_H
#define NHANVAT_H

#include <iostream>
#include <string>
#include <windows.h>
#include "NhanVat.h"
#include <iomanip>
using namespace std;

namespace MauSac {
    constexpr int chu = 15;
    constexpr int khung = 11;
    constexpr int nhanVat = 10;
    constexpr int boss = 13;
    constexpr int hpTrong = 8;
    constexpr int menu = 11;
    constexpr int canhBao = 12;
    constexpr int tieuDe = 14;
    constexpr int chienThang = 10;
    constexpr int thatBai = 12;
}

namespace UI_Menu {

    void mauChu(int mau){
        #ifdef _WIN32
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mau);
        #else
            (void)mau;
        #endif
    }
    void dongKe(char kiTu,string text, int size_){
        int left = (size_ - text.length())/2;
        for(int i = 0; i<left; i++)
            cout<<kiTu;
        cout<<text; 
        for(int i = left + text.length(); i<size_; i++)
            cout<<kiTu; 
        cout<<endl;
    }

    void printHeader() {
        dongKe('=',"", 125); 
        cout<<"██████╗  █████╗ ████████╗████████╗██╗     ███████╗    ███████╗██╗███╗   ███╗██╗   ██╗██╗      █████╗ ████████╗ ██████╗ ██████╗"<<endl;
        cout<<"██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║     ██╔════╝    ██╔════╝██║████╗ ████║██║   ██║██║     ██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗"<<endl;
        cout<<"██████╔╝███████║   ██║      ██║   ██║     █████╗      ███████╗██║██╔████╔██║██║   ██║██║     ███████║   ██║   ██║   ██║██████╔╝"<<endl;
        cout<<"██╔══██╗██╔══██║   ██║      ██║   ██║     ██╔══╝      ╚════██║██║██║╚██╔╝██║██║   ██║██║     ██╔══██║   ██║   ██║   ██║██╔══██╗"<<endl;
        cout<<"██████╔╝██║  ██║   ██║      ██║   ███████╗███████╗    ███████║██║██║ ╚═╝ ██║╚██████╔╝███████╗██║  ██║   ██║   ╚██████╔╝██║  ██║"<<endl;
        cout<<"╚═════╝ ╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚══════╝╚══════╝    ╚══════╝╚═╝╚═╝     ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝"<<endl;
        dongKe('=',"CODEPATH", 125); 
    }

    void printMenu()
    {
        mauChu(MauSac::menu);
        cout << "\n++====================== MENU ======================++\n";
        cout << "|| 1. Chon sung Eclipse                             ||\n";
        cout << "|| 2. Chon kiem Phan Quang                          ||\n";
        cout << "|| 3. Chon phep thuat Loi Quang                     ||\n";
        cout << "|| 4. Tan cong Boss trong t giay                    ||\n";
        cout << "|| 5. Tan cong Boss                                 ||\n";
        cout << "|| 6. Nap dan                                       ||\n";
        cout << "|| 7. Xem trang thai va thong tin vu khi            ||\n";
        cout << "|| 8. Hoi mana                                      ||\n";
        cout << "|| ";
        mauChu(MauSac::canhBao);
        cout<<"9. Choi lai                                      ";
        mauChu(MauSac::menu);
        cout<<"||\n";
        mauChu(MauSac::menu);
        cout << "|| ";
        mauChu(MauSac::canhBao);
        cout<<"0. Thoat                                         ";
        mauChu(MauSac::menu);
        cout<<"||\n";
        mauChu(MauSac::menu);
        cout << "++==================================================++\n";
    }

    void thanhMau(const string &ten, int hp, int maxHP, int rong = 24, int mauDay = MauSac::nhanVat)
    {
        int day = maxHP > 0 ? hp * rong / maxHP : 0;
        //---- = 64
        mauChu(MauSac::khung);
        cout <<"|| ";
        mauChu(MauSac::chu);
        cout<< ten;
        for(int i = 0; i<15 - ten.length(); i++) cout<<" ";
        cout<<"[";
        mauChu(mauDay);
        for (int i = 0; i < day; ++i)
            cout << "#";
        mauChu(MauSac::hpTrong);
        for (int i = day; i < rong; ++i)
            cout << "-";
        mauChu(MauSac::chu);
        cout << "] " << hp << "/" << maxHP;
    }

    void khungDauTruong(const NhanVat& nv, int bossHP, int bossMax)
    {
        mauChu(MauSac::khung);
        cout << "++==============================================================++\n";
        cout << "||                       DAU TRUONG 2D                          ||\n";
        cout << "++==============================================================++\n";
        cout << "||";
        mauChu(MauSac::nhanVat);
        cout<<"           " << left << setw(16) << nv.getTen();
        mauChu(MauSac::boss);
        cout<<"                GENGAR             ";
        mauChu(MauSac::khung);
        cout<<"||\n";
        auto veHangDauTruong = [](const string &nhanVat, const string &boss) {
            cout << "||";
            mauChu(MauSac::nhanVat);
            cout << left << setw(24) << ("    " + nhanVat) << string(17, ' ');
            mauChu(MauSac::boss);
            cout << left << setw(10) << boss;
            mauChu(MauSac::khung);
            cout << string(11, ' ') << "||\n";
        };
        veHangDauTruong("*       /\\", ".-====-.");
        veHangDauTruong("|      /  \\", "/  X  X  \\");
        veHangDauTruong("|     /____\\", "|   __   |");
        veHangDauTruong("|     (o  o)", "\\______/");
        veHangDauTruong("|      \\__/", "");
        veHangDauTruong("|     __| |__", "");
        veHangDauTruong("|    /  | |  \\", "");
        veHangDauTruong("|___/___|_|___\\", "");
        mauChu(MauSac::chu);
        thanhMau("HP nhan vat", nv.getMau(), nv.getMauToiDa(), 20, MauSac::nhanVat);
        mauChu(MauSac::khung);
        cout<<"                ||"<<"\n";
        thanhMau("HP Boss", bossHP, bossMax, 20, MauSac::boss);
        mauChu(MauSac::khung);
        cout<<"                ||"<<"\n";
        mauChu(MauSac::khung);
        cout << "++==============================================================++\n";
        mauChu(MauSac::chu);
    }
}

#endif