# HandMotionRecognition
"Sistem pengaturan nyala lampu berbasis gerakan tangan melalui wearable device dengan metode K-Nearest Neighbor"

Sistem ini berfungsi untuk mengenali gerakan tangan dan digunakan untuk melakukan pengaturan kondisi lampu meja.
Perangkat yang digunakan : 
1. Arduino Uno
2. Arduino Nano
3. Akselerometer GY-521
4. RF24
5. LED
6. PushButton

Dalam sistem ini terdapat 2 perangkat yaitu Wearable Device dan Lampu Meja.
Wearable device berfungsi untuk melakukan akuisisi data nilai x, y, dan z dari sensor akselerometer berdasarkan gerakan yang dilakukan oleh user dan nantinya akan dikirim menuju ke Lampu Meja. Pada wearable device ini terdapat pushbutton yang berfungsi untuk trigger wearable device mulai dan berhentinya proses akuisisi data.
Lampu Meja berfungsi untuk menerima dan mengolah data yang diterima dari wearable device sehingga dapat digunakan untuk menentukan kondisi lampu.
