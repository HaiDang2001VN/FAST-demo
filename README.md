# Pose Estimation
### Installation

Code này chạy trên Visual Studio 2017 (vì em chưa viết CMake được nên chưa port lên Ubuntu được).

_**NOTE:**_ Lúc Run lần đầu thì được, sau khi em chuyển sang NuGet thì bị báo thiếu zlib1.dll. Nhưng nếu trên Ubuntu thì sẽ nhanh chóng hơn
(sudo apt-get install libopencv-dev là xong).
#### Requirements
##### OpenCV

OpenCV cài trên Ubuntu thì nhanh nhưng install trên Windows khó lắm, em install bằng prebuilt rồi link nó vào Project.
Nhưng sau đó em chuyển sang dùng prebuilt NuGet của Microsoft, package giống như apt bên Ubuntu (nhưng dĩ nhiên là ít hơn, cập nhật chậm hơn).

#### Zlib

Em vẫn chưa biết tại sao bị lỗi, để zlib1.dll (manually downloaded) vào cùng Tester.cpp thì báo lỗi khác (Uncorrectly start).
Vậy nên em để đó các anh nào biết thì giúp em ạ.

#### Build and Run

Dạ nếu dùng VS2017 thì F5 ạ, em không chắc máy khác có chạy được không.
Với Ubuntu thì em chưa biết viết CMake nên không thể
`cmake .. && make` được ạ.

#### Code components

Trong header Pose.hpp em cung cấp PoseEstimator namespace gồm các method dùng để estimate camera pose từ 2 frames. Ngoài ra Tester.cpp chứa code demo estimate pose trong folder data (0.png và 1.png).

##### getTransform()

Hàm này nhận 2 vector<KeyPoint> và camera matrix K làm input, trả về Transformation Matrix (dạng 3x4).

##### getPose()

Hàm này nhận 2 Mat là 2 ảnh đầu vào, và bộ fx, fy, cx, cy theo thông số camera (optional, default fx=500, fy=500, cx=Wid/2 (cast init hàm bằng NAN), cy=Hei/2 (cast init hàm bằng NAN)).
Sau khi xử lý, hàm trả về Transformation Matrix (dạng 3x4) do đã gọi `getTransform()`.
