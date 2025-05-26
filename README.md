# Hệ Thống Quản Lý Đào Tạo

## Mô tả
Hệ thống quản lý đào tạo trong nhà trường được viết bằng ngôn ngữ C, sử dụng cấu trúc dữ liệu danh sách liên kết để quản lý các thực thể: Sinh viên, Giảng viên, Môn học, Thời khóa biểu, Học phí, và Khoa.

## Cấu trúc Project
```
school_management_system/
├── school_management.h     # Header file chính
├── main.c                  # File chính chứa main() và menu
├── student.c               # Quản lý sinh viên
├── lecturer.c              # Quản lý giảng viên
├── course.c                # Quản lý môn học
├── schedule.c              # Quản lý thời khóa biểu
├── tuition.c               # Quản lý học phí
├── department.c            # Quản lý khoa
├── Makefile               # File biên dịch
└── README.md              # Hướng dẫn sử dụng
```

## Tính năng chính

### 1. Quản lý Sinh viên
- Thêm sinh viên mới
- Hiển thị danh sách sinh viên
- Tìm kiếm sinh viên theo mã
- Cập nhật thông tin sinh viên
- Xóa sinh viên

### 2. Quản lý Giảng viên
- Thêm giảng viên mới
- Hiển thị danh sách giảng viên
- Tìm kiếm giảng viên theo mã
- Cập nhật thông tin giảng viên
- Xóa giảng viên

### 3. Quản lý Môn học
- Thêm môn học mới
- Hiển thị danh sách môn học
- Tìm kiếm môn học theo mã
- Cập nhật thông tin môn học
- Xóa môn học

### 4. Quản lý Thời khóa biểu
- Thêm lịch học mới
- Hiển thị tất cả lịch học
- Xem lịch giảng dạy của giảng viên
- Xóa lịch học

### 5. Quản lý Học phí
- Thêm học phí mới
- Hiển thị tất cả học phí
- Cập nhật thanh toán học phí
- Xem học phí chưa thanh toán

### 6. Quản lý Khoa
- Thêm khoa mới
- Hiển thị danh sách khoa

### 7. Báo cáo
- Lịch giảng dạy của giảng viên
- Danh sách học phí chưa thanh toán
- Thống kê số lượng sinh viên theo khoa

### 8. Lưu trữ dữ liệu
- Lưu dữ liệu vào file text
- Tải dữ liệu từ file text
- Dữ liệu được lưu tự động khi thoát

## Cách chạy nhanh

### Windows
```bash
# Chạy file batch
run.bat

# Hoặc chạy trực tiếp
school_management.exe
```

### Sử dụng Makefile (Khuyến nghị)
```bash
# Biên dịch
make

# Chạy chương trình
make run

# Dọn dẹp file thực thi
make clean
```

### Biên dịch thủ công
```bash
gcc -Wall -Wextra -std=c99 -o school_management main.c student.c lecturer.c course.c schedule.c tuition.c department.c
```

### Chạy chương trình
```bash
./school_management
```

## Cấu trúc dữ liệu

### Student (Sinh viên)
- Mã sinh viên
- Họ tên
- Ngày sinh
- Giới tính
- Khoa
- Email
- Số điện thoại

### Lecturer (Giảng viên)
- Mã giảng viên
- Họ tên
- Khoa
- Chuyên ngành
- Email
- Số điện thoại

### Course (Môn học)
- Mã môn học
- Tên môn học
- Số tín chỉ
- Mã giảng viên phụ trách

### ClassSchedule (Thời khóa biểu)
- Mã lịch
- Mã môn học
- Thứ trong tuần (2-8)
- Giờ bắt đầu
- Giờ kết thúc
- Phòng học

### Tuition (Học phí)
- Mã học phí
- Mã sinh viên
- Học kỳ
- Tổng tiền
- Tiền đã nộp
- Hạn nộp
- Trạng thái (Paid/Unpaid/Partial)

### Department (Khoa)
- Mã khoa
- Tên khoa
- Mã trưởng khoa

## File dữ liệu
- `students.txt`: Dữ liệu sinh viên
- `lecturers.txt`: Dữ liệu giảng viên
- `courses.txt`: Dữ liệu môn học
- `students_sample.txt`: Dữ liệu mẫu sinh viên
- `lecturers_sample.txt`: Dữ liệu mẫu giảng viên
- `courses_sample.txt`: Dữ liệu mẫu môn học

## File chạy
- `run.bat`: File batch để chạy nhanh trên Windows
- `school_management.exe`: File thực thi chính

## Ghi chú
- Chương trình sử dụng menu text-based đơn giản
- Dữ liệu được lưu trữ dưới dạng file text với định dạng pipe-separated (|)
- Hỗ trợ tiếng Việt không dấu để tránh conflict với console
- Bộ nhớ được quản lý tự động (malloc/free)

## Hướng phát triển
- Thêm tính năng tìm kiếm nâng cao
- Hỗ trợ xuất báo cáo ra file
- Thêm validation dữ liệu đầu vào
- Hỗ trợ nhiều định dạng file (JSON, XML)
- Thêm giao diện đồ họa
