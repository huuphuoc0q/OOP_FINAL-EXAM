#include <iostream>
#include <iomanip>
#include <memory>
#include <limits>
#include <string>
#include "NhanVat.h"
#include "Sung.h"
#include "Kiem.h"
#include "PhepThuat.h"
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void mauChu(int mau)
{
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mau);
#else
    (void)mau;
#endif
}
void xoaManHinh()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void thanhMau(const string &ten, int hp, int maxHP, int rong = 24)
{
    int day = maxHP > 0 ? hp * rong / maxHP : 0;
    cout << ten << " [";
    mauChu(10);
    for (int i = 0; i < day; ++i)
        cout << "#";
    mauChu(8);
    for (int i = day; i < rong; ++i)
        cout << "-";
    mauChu(7);
    cout << "] " << hp << "/" << maxHP << "\n";
}

void khungDauTruong(const NhanVat &nv, int bossHP, int bossMax)
{
    cout << "+--------------------------------------------------------------+\n";
    cout << "|                       DAU TRUONG 2D                          |\n";
    cout << "+--------------------------------------------------------------+\n";
    cout << "|           " << left << setw(16) << nv.getTen() << "                GENGAR             |\n";
    cout << "|             O                           .-====-.             |\n";
    cout << "|            /|\\                         /  X  X  \\            |\n";
    cout << "|            / \\                         |   __   |            |\n";
    cout << "|                                         \\______/             |\n";
    thanhMau("HP nhan vat", nv.getMau(), nv.getMauToiDa(), 20);
    thanhMau("HP Boss", bossHP, bossMax, 20);
    cout << "+--------------------------------------------------------------+\n";
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

void menu()
{
    mauChu(10); 
    cout << "\n+---------------------- MENU ----------------------+\n";
    cout << "| 1. Chon sung Eclipse                             |\n";
    cout << "| 2. Chon kiem Phan Quang                          |\n";
    cout << "| 3. Chon phep thuat Loi Quang                     |\n";
    cout << "| 4. Tan cong Boss trong t giay                    |\n";
    cout << "| 5. Tan cong Boss                                 |\n";
    cout << "| 6. Nap dan                                       |\n";
    cout << "| 7. Xem trang thai va thong tin vu khi            |\n";
    cout << "| 8. Hoi mana                                      |\n";

    cout << "| ";
    mauChu(4); 
    cout<<"9. Choi lai                                      ";
    mauChu(10); 
    cout<<"|\n";
    mauChu(10);
    cout << "| ";
    mauChu(4);
    cout<<"0. Thoat                                         ";
    mauChu(10);
    cout<<"|\n";
    mauChu(10);
    cout << "+--------------------------------------------------+\n";
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    NhanVat nv("Hac Si", 160);
    nv.themVuKhi(make_unique<Sung>("Eclipse", 30, 2.0, 5, 2.0));
    nv.themVuKhi(make_unique<Kiem>("Phan Quang", 20, 0.5, 100, 20));
    nv.themVuKhi(make_unique<PhepThuat>("Loi Quang", 25, 1.0, "Loi", 30)); 

   
    int bossHP = 160, bossMax = 160, diem = 0, luot = 1, chon = 0;
    bool ketThuc = false;
    string dongNhatKy = "Chao mung den dau truong!";

    while (true)
    {
        xoaManHinh();
        mauChu(11);
        dongKe('=',"", 125); 
        cout<<"██████╗  █████╗ ████████╗████████╗██╗     ███████╗    ███████╗██╗███╗   ███╗██╗   ██╗██╗      █████╗ ████████╗ ██████╗ ██████╗"<<endl;
        cout<<"██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║     ██╔════╝    ██╔════╝██║████╗ ████║██║   ██║██║     ██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗"<<endl;
        cout<<"██████╔╝███████║   ██║      ██║   ██║     █████╗      ███████╗██║██╔████╔██║██║   ██║██║     ███████║   ██║   ██║   ██║██████╔╝"<<endl;
        cout<<"██╔══██╗██╔══██║   ██║      ██║   ██║     ██╔══╝      ╚════██║██║██║╚██╔╝██║██║   ██║██║     ██╔══██║   ██║   ██║   ██║██╔══██╗"<<endl;
        cout<<"██████╔╝██║  ██║   ██║      ██║   ███████╗███████╗    ███████║██║██║ ╚═╝ ██║╚██████╔╝███████╗██║  ██║   ██║   ╚██████╔╝██║  ██║"<<endl;
        cout<<"╚═════╝ ╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚══════╝╚══════╝    ╚══════╝╚═╝╚═╝     ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝"<<endl;
        dongKe('=',"CODEPATH", 125); 

        mauChu(7);
        khungDauTruong(nv, bossHP, bossMax);

        mauChu(6);
        cout << "\nVU KHI CUA BAN:\n";
        for (int i = 0; i < nv.soVuKhi(); ++i)
        {
            VuKhi *v = nv.getVuKhi(i);
            cout << " " << i + 1 << ". " << left << setw(14) << v->getTen()
                 << " | " << setw(12) << v->getLoai()
                 << " | sat thuong " << setw(2) << v->getSatThuongCoBan()
                 << " | toc do " << v->getTocDoRaDon() << " don/giay";
            if (auto *s = dynamic_cast<Sung *>(v))
                cout << " | dan: " << s->getSoDan() << "/5";
            if (auto *p = dynamic_cast<PhepThuat *>(v))
                cout << " | mana: " << p->getManaHienTai() << "/30";
            if (auto *k = dynamic_cast<Kiem *>(v))
                cout << " | do ben: " << k->getDoBen() << "/100";
            cout << "\n";
        }
        mauChu(7); 
        cout << "\nVu khi dang chon: " << (chon >= 0 && chon < nv.soVuKhi() ? nv.getVuKhi(chon)->getTen() : "Chua chon") << "\n";
        cout << "Diem sat thuong: " << diem << " | Luot: " << luot << "\n";
        mauChu(14);
        cout << "Nhat ky: " << dongNhatKy << "\n";
        mauChu(7);
        if (ketThuc)
        {
            mauChu(bossHP == 0 ? 10 : 12);
            cout << (bossHP == 0 ? "*** CHIEN THANG! BOSS DA BI HA GUC ***" : "*** THAT BAI! NHAN VAT DA HET MAU ***") << "\n";
            mauChu(7);
        }

        menu();
        cout << "Nhap lua chon: ";
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
                s->NapDan();
            if (auto *p = dynamic_cast<PhepThuat *>(nv.getVuKhi(2)))
                p->HoiMana();
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
                s->NapDan();
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
                p->HoiMana();
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
                cout << "Thoi gian can su dung (giay > 0): ";
                while (!(cin >> thoiGian) || thoiGian <= 0)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Loi! Thoi gian phai la so nguyen duong (> 0). Vui long nhap lai: ";
                }
            }
            if (auto *s = dynamic_cast<Sung *>(v))
            {
                if (!s->ConDan())
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
                    satThuong = s->satThuong(thoiGian);
                    s->SuDungDan(thoiGian);
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
                    satThuong = p->satThuong(thoiGian);
                    p->SuDungMana(8*thoiGian);
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
                        phanCong = 35;
                    }
                    else if (dynamic_cast<Kiem *>(v) != nullptr)
                    {
                        phanCong = 15;
                    }
                    else if (dynamic_cast<PhepThuat *>(v) != nullptr)
                    {
                        phanCong = 20;
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
