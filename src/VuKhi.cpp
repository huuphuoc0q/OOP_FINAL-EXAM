#include "VuKhi.h"
#include <limits>
VuKhi::VuKhi() : 
    tenVuKhi_(""), 
    satThuong_(0), //Mac dinh sat thuong = 0 vì chưa có đối tượng vũ khí
    tocDo_(0) {} //Mac định tốc độ hồi chiêu = 0

VuKhi::VuKhi(const std::string& tenVuKhi, int satThuong, double tocDo) : 
    tenVuKhi_(tenVuKhi), 
    satThuong_(satThuong), 
    tocDo_(tocDo) {}

std::string VuKhi::getTen() const { 
    return tenVuKhi_; 
}

int VuKhi::getSatThuongCoBan() const { 
    return satThuong_; 
}

double VuKhi::getTocDoRaDon() const { 
    return tocDo_; 
}

void VuKhi::setTen(const std::string& newTenVuKhi){
    if (!newTenVuKhi.empty()) 
        tenVuKhi_ = newTenVuKhi;  
}

void VuKhi::setSatThuongCoBan(int satThuong) {
    if (satThuong>=0) 
        satThuong_ = satThuong; 
}

void VuKhi::setTocDoRaDon(double tocDo) {
    if (tocDo>0) 
        tocDo_ = tocDo; 
}

void VuKhi::xuat(std::ostream& os) const { 
    os << "Ten vu khi: " << tenVuKhi_ << "\nSat thuong co ban: " << satThuong_
       << "\nToc do ra don: " << tocDo_ << " don/giay\n";
}

void VuKhi::nhap(std::istream& is) {
    std::string tenVuKhi; int satThuong; double tocDo;
    std::cout << "Ten vu khi: "; std::getline(is >> std::ws,tenVuKhi);
    std::cout << "Sat thuong co ban: "; is >> satThuong;
    std::cout << "Toc do ra don (don/giay): "; is >> tocDo;
    if (is && !tenVuKhi.empty() && satThuong>0 && tocDo>0) { 
        tenVuKhi_ = tenVuKhi; 
        satThuong_ = satThuong; 
        tocDo_ = tocDo; 
    }
    else { 
        is.clear(); // Đặt luồng nhập về bình thường khi người dùng nhập saikiểu dữ liệu
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        //Dọn bộ đệm đã nhập sai
    }
}

std::ostream& operator<<(std::ostream& os, const VuKhi& vuKhi) { 
    vuKhi.xuat(os); 
    return os; 
}

std::istream& operator>>(std::istream& is, VuKhi& vuKhi) { 
    vuKhi.nhap(is); 
    return is; 
}
