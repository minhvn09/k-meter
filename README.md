# k-meter
**Dự án phát triển công tơ điện tử wifi đo điện 1 pha , 3 pha, mặt trời**

-Tải app Blynk cho Android: <a href='https://play.google.com/store/apps/details?id=cc.blynk&hl=vi&gl=VI'>Vào tải</a><p>
-Tải app Blynk cho Iphone: <a href='https://apps.apple.com/vn/app/blynk-iot-for-arduino-esp32/id808760481?l=vi'>Vào tải</a><p>
**-Các lệnh cài đặt (có thể nhập trên ô nhập lệnh app Blynk, hoặc trên web ô nhập lệnh trong setup)**

 - Đổi pass wifi(xx là pass nhà bạn): ssid:xx 
 - Đổi mật khẩu wifi (xx là mật khẩu nhà bạn): pass:xx 
 - Đổi token blynk (token blynk lấy trên app blynk): blynk:xx 
 - Đổi server blynk (ví dụ server:iot.htpro.vn): server:xx 
 - Đổi ngày chốt điện (ví dụ chot:15): chot:xx 
 - Đổi giá bán điện (ví dụ: gia:1943): gia:xx 
 - Chỉnh sai số (ví dụ sai số thực tế <5% nhập là 1.05, >5% nhập 0.95): saiso:xx 
 - Reset biểu đồ điện trên web: resetbieudo 
 - Khởi động lại công tơ: resetcongto  

 - Đổi kwh hôm nay (ví dụ homnay:10): homnay:xx 
 - Đổi kwh hôm qua: homqua:xx 
 - Đổi kwh tháng này:thangnay:xx 
 - Đổi kwh tháng trước: thangtruoc:xx 
 - Đổi tổng kwh: tongkwh:xx 
 - Xóa số ngày hôm nay, hôm qua: resetngay 
 - Xóa số tháng này, tháng trướd: resetthang 
 - Xóa mọi thông số, khôi phục cài đặt: resetall  

**Cấu hình chân trên App Blynk**(h2)
 - V40 - - Volt pha A 
 - V41 - Ampe pha A 
 - V42 - Công suất W pha A 
 - V43 - KWh pha A 
 - V44 - Cosphi pha A 
 - V45 - Tần số pha A  
  
 - V50 - - Volt pha B 
 - V51 - Ampe pha B 
 - V52 - Công suất W pha B 
 - V53 - KWh pha B 
 - V54 - Cosphi pha B 
 - V55 - Tần số pha B  

 - V60 - - Volt pha C 
 - V61 - Ampe pha C 
 - V62 - Công suất W pha C 
 - V63 - KWh pha C 
 - V64 - Cosphi pha C 
 - V65 - Tần số pha C  

 - V70 - Tổng Ampe 3 pha 
 - V71 - Tổng công suất 3 pha W 
 - V72 - Tổng điện năng 3 pha KWh 
 - V73 - Tổng điện năng pzem KWh  
    
 - V7 Thời gian chạy từ lúc cắm điện(s) 
 - V11 Số hôm nay KWh 
 - V12 Số hôm qua KWh 
 - V13 Số tháng này KWh 
 - V14 Số tháng trước KWh 
 - V15 Tiền tháng này - Vnđ 
 - V16 Tiền tháng trước - Vnđ 
 - V25 Cường độ wifi (mạnh nhất là 100%) 
 - V10 Ô nhập lệnh cài đặt, đổi thông số 
 - V30 Địa chỉ IP, ID chip <p>
 **Giao diện Blynk 3 pha**<p>
![k-meter-3pha-280221](https://user-images.githubusercontent.com/56754677/109424892-63f90500-7a18-11eb-980f-623c147b746c.PNG)

 **Giao diện 1 pha 1 chiều điện sinh hoạt**<p>
![k-meter-220221](https://user-images.githubusercontent.com/56754677/109425512-25b11500-7a1b-11eb-8b9f-7898425f0786.jpg)

**Giao diện solar 2 chiều**<p>
![k-solar-220221](https://user-images.githubusercontent.com/56754677/109425696-17172d80-7a1c-11eb-9b09-18c743d2424a.jpg)
