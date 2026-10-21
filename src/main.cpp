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

void mauChu(int mau) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mau);
#else
    (void)mau;
#endif
}
void xoaManHinh() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void thanhMau(const string& ten,int hp,int maxHP,int rong=24) {
    int day=maxHP>0?hp*rong/maxHP:0;
    cout<<ten<<" [";
    mauChu(10); for(int i=0;i<day;++i)cout<<"#";
    mauChu(8); for(int i=day;i<rong;++i)cout<<"-";
    mauChu(7); cout<<"] "<<hp<<"/"<<maxHP<<"\n";
}
void khungDauTruong(const NhanVat& nv,int bossHP,int bossMax) {
    cout<<"+--------------------------------------------------------------+\n";
    cout<<"|                       DAU TRUONG 2D                          |\n";
    cout<<"+--------------------------------------------------------------+\n";
    cout<<"|       NHAN VAT "<<left<<setw(16)<<nv.getTen()<<"       BOSS THU LINH       |\n";
    cout<<"|             O                           .-====-.             |\n";
    cout<<"|            /|\\                         /  X  X  \\            |\n";
    cout<<"|            / \\                         |   __   |            |\n";
    cout<<"|                                         \\______/             |\n";
    thanhMau("HP nhan vat",nv.getMau(),nv.getMauToiDa(),20);
    thanhMau("HP Boss",bossHP,bossMax,20);
    cout<<"+--------------------------------------------------------------+\n";
}
void menu() {
    cout<<"\n+---------------------- MENU ----------------------+\n";
    cout<<"| 1. Chon sung Eclipse                             |\n";
    cout<<"| 2. Chon kiem Phan Quang                          |\n";
    cout<<"| 3. Chon phep thuat Loi Quang                     |\n";
    cout<<"| 4. Tan cong Boss                                 |\n";
    cout<<"| 5. Nap dan                                       |\n";
    cout<<"| 6. Xem trang thai va thong tin vu khi            |\n";
    cout<<"| 7. Hoi mana                                      |\n";
    cout<<"| 8. Choi lai                                      |\n";
    cout<<"| 0. Thoat                                         |\n";
    cout<<"+--------------------------------------------------+\n";
}
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    NhanVat nv("Hac Si", 160);
    nv.themVuKhi(make_unique<Sung>("Eclipse",30,1.0,5,2.0));
    nv.themVuKhi(make_unique<Kiem>("Phan Quang",20,1.0,100));
    nv.themVuKhi(make_unique<PhepThuat>("Loi Quang",25,1.0,"Loi",30));//sat thuong 25, mana 30
    int bossHP=160,bossMax=160,diem=0,luot=1,chon=0;
    bool ketThuc=false;
    string dongNhatKy="Chao mung den dau truong!";
    while(true) {
        xoaManHinh();
        mauChu(11); cout<<"================ SAT THUONG NHAN VAT ================\n"; mauChu(7);
        cout<<"Do an OOP C++ | Console 2D | Color + iomanip\n";
        khungDauTruong(nv,bossHP,bossMax);
        cout<<"\nVU KHI CUA BAN:\n";
        for(int i=0;i<nv.soVuKhi();++i) {
            VuKhi* v=nv.getVuKhi(i);
            cout<<" "<<i+1<<". "<<left<<setw(14)<<v->getTen()
                <<" | "<<setw(12)<<v->getLoai()
                <<" | sat thuong "<<setw(2)<<v->getSatThuongCoBan()
                <<" | toc do "<<v->getTocDoRaDon()<<" don/giay";
            if(auto* s=dynamic_cast<Sung*>(v))cout<<" | dan "<<s->getSoDan()<<"/5";
            if(auto* p=dynamic_cast<PhepThuat*>(v))cout<<" | mana "<<p->getManaHienTai()<<"/30";
            if(auto* k=dynamic_cast<Kiem*>(v))cout<<" | do ben "<<k->getDoBen()<<"/100";
            cout<<"\n";
        }
        cout<<"\nVu khi dang chon: "<<(chon>=0&&chon<nv.soVuKhi()?nv.getVuKhi(chon)->getTen():"Chua chon")<<"\n";
        cout<<"Diem sat thuong: "<<diem<<" | Luot: "<<luot<<"\n";
        mauChu(14); cout<<"Nhat ky: "<<dongNhatKy<<"\n"; mauChu(7);
        if(ketThuc) {
            mauChu(bossHP==0?10:12);
            cout<<(bossHP==0?"*** CHIEN THANG! BOSS DA BI HA GUC ***":"*** THAT BAI! NHAN VAT DA HET MAU ***")<<"\n"; mauChu(7);
        }
        menu();
        cout<<"Nhap lua chon: ";
        int luaChon;
        if(!(cin>>luaChon)){cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n');dongNhatKy="Du lieu khong hop le.";continue;}
        if(luaChon==0)break;
        if(luaChon==8) {
            bossHP=bossMax;nv.hoiMau();diem=0;luot=1;chon=0;ketThuc=false;
            if(auto*s=dynamic_cast<Sung*>(nv.getVuKhi(0)))s->NapDan();
            if(auto*p=dynamic_cast<PhepThuat*>(nv.getVuKhi(2)))p->HoiMana();
            if(auto*k=dynamic_cast<Kiem*>(nv.getVuKhi(1)))k->setDoBen(100);
            dongNhatKy="Tran dau da duoc dat lai.";continue;
        }
        if(luaChon>=1&&luaChon<=3){chon=luaChon-1;dongNhatKy="Da chon "+nv.getVuKhi(chon)->getTen()+".";continue;}
        if(luaChon==6){nv.hienThiTrangThai();cout<<"\nNhan Enter de tiep tuc...";cin.ignore(numeric_limits<streamsize>::max(),'\n');cin.get();continue;}
        if(luaChon==5) {
            if(auto*s=dynamic_cast<Sung*>(nv.getVuKhi(0))){s->NapDan();dongNhatKy="Sung Eclipse da nap day dan.";}
            else dongNhatKy="Khong tim thay sung.";
            continue;
        }
        if(luaChon==7) {
            if(auto*p=dynamic_cast<PhepThuat*>(nv.getVuKhi(2))){p->HoiMana();dongNhatKy="Mana da hoi day.";}
            continue;
        }
        if(luaChon==4) {
            if(ketThuc){dongNhatKy="Tran dau da ket thuc. Hay choi lai.";continue;}
            VuKhi* v=nv.getVuKhi(chon);int satThuong=0;bool hopLe=true;
            if(auto*s=dynamic_cast<Sung*>(v)){if(!s->ConDan()){dongNhatKy="Het dan! Hay chon Nap dan.";hopLe=false;}else{s->TanCong();satThuong=s->SatThuong(1);s->SuDungDan();}}
            else if(auto*k=dynamic_cast<Kiem*>(v)){if(k->getDoBen()<20){dongNhatKy="Kiem khong du do ben de tan cong.";hopLe=false;}else{k->TanCong();satThuong=k->SatThuong(1);k->setDoBen(k->getDoBen()-20);}}
            else if(auto*p=dynamic_cast<PhepThuat*>(v)){
                if(!p->DuMana(8)){
                    dongNhatKy="Khong du mana de su dung phep.";
                    hopLe=false;
                }else{
                    p->TanCong();
                    satThuong=p->SatThuong(1);
                    p->SuDungMana(8);
                }
            }
            if(hopLe) {
                bossHP=max(0,bossHP-satThuong);diem+=satThuong;
                dongNhatKy=nv.getTen()+" dung "+v->getTen()+", gay "+to_string(satThuong)+" sat thuong.";
                if(bossHP==0){ketThuc=true;dongNhatKy="Chien thang! Boss da bi ha guc.";}
                else {
                    int phanCong=0;
                    if(dynamic_cast<Sung*>(v)!=nullptr){
                        phanCong=35;
                    }
                    else if (dynamic_cast<Kiem*>(v)!=nullptr){
                        phanCong=15;
                    }
                    else if(dynamic_cast<PhepThuat*>(v)!=nullptr){
                        phanCong=20;
                    }
                    nv.nhanSatThuong(phanCong);
                    dongNhatKy+="Boss phan cong "+to_string(phanCong)+" sat thuong.";
                    if(nv.getMau()==0){
                        ketThuc=true;
                        dongNhatKy="That bai! Nhan vat da het mau.";
                    }
                }
                ++luot;
            }
            continue;
        }
        dongNhatKy="Lua chon khong hop le.";
    }
    mauChu(7);cout<<"Cam on ban da choi!\n";return 0;
}
