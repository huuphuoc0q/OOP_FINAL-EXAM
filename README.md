# Đồ án OOP: Sát thương nhân vật — Console 2D

## YÊU CẦU
- 3 điểm báo cáo Word: dự án có cấu trúc lớp, mô tả quy luật, phân công, giải thích code và hướng dẫn demo; nhóm cần hoàn thiện thông tin thành viên và ảnh minh chứng.
- 2 điểm thiết kế lớp cơ bản: lớp `VuKhi` có constructor mặc định/có tham số, getter/setter và nạp xuất `>>`, `<<`. Các lớp dẫn xuất cũng có constructor, getter/setter và ghi đè nhập xuất.
- 1 điểm kế thừa: `Sung`, `Kiem`, `PhepThuat` kế thừa `VuKhi`.
- 2 điểm đa hình: `TanCong()`, `SatThuong(int t)`, `getLoai()` là hàm ảo; lớp con override. Chương trình gọi qua `VuKhi*` và chọn hành vi bằng kiểu thực tế.
- 2 điểm Console 2D: dùng khung ASCII, nhân vật/boss, thanh máu, màu console và `iomanip`.

## Cấu trúc
- `include/`: khai báo lớp.
- `src/`: định nghĩa phương thức và chương trình.
- `CMakeLists.txt`: cấu hình biên dịch không cần SFML.
- 'docs/': Chứa tất cả nội dung đề tài, yêu cầu đề tài, file báo cáo.
## Build
```bash
cmake -S . -B build
cmake --build build
```
Windows có thể mở thư mục bằng Visual Studio CMake hoặc biên dịch các file `.cpp` và thêm `include` vào đường dẫn header.
Linux:
```bash
g++ -std=c++17 -Iinclude src/*.cpp -o SatThuongNhanVat
./SatThuongNhanVat
```

## Điều khiển
Nhấn phím trực tiếp, không cần Enter: 1/2/3 chọn vũ khí; 4 hoặc Space tấn công; 5 bắt đầu thay băng; 6 xem trạng thái; 7 hồi mana; 8 chơi lại; 0 hoặc Esc thoát.

## Quy luật chiến đấu
- Nhân vật có 160 HP, Boss có 160 HP.
- Mỗi lượt đánh, vũ khí gây sát thương theo `SatThuong(1)`; Boss còn sống sẽ phản công 35HP khi dùng súng, 15 khi dùng kiếm, 20 khi dùng phép.
- Súng dùng một viên đạn/lượt; kiếm giảm độ bền 20 mỗi lần đánh; phép thuật tiêu hao mana theo số giây tấn công.
- Sau mỗi đòn đánh thành công, súng hồi chiêu 1 giây, kiếm 2 giây và phép thuật 4 giây. Mỗi vũ khí có thời gian hồi chiêu riêng.
- Thay băng mất thời gian theo `Sung::getTocDoThayBang()` (mặc định 2 giây). Trong lúc thay băng không thể bắn; thời gian hồi chiêu và thay băng vẫn chạy khi người chơi không nhấn phím.
- Chơi lại phục hồi HP, đạn, mana và độ bền.
- Boss chỉ phản công sau đòn đánh thành công; thay băng và chờ hồi chiêu không khiến Boss tấn công.

## Lưu ý
- Màu console dùng Windows Console API trên Windows; trên Linux/macOS mã màu chưa được triển khai (các lệnh game vẫn chạy).
- Cần chạy trong terminal tương tác để chương trình đọc phím trực tiếp.
- Nếu terminal không hỗ trợ UTF-8 hoặc các ký tự khung, dùng terminal hỗ trợ Unicode. Nội dung mặc định không dấu để tránh lỗi font.
