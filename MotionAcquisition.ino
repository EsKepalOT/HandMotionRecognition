/*====== TRANSMITTER RAW DATA GY 521 ======*/
#include "I2Cdev.h"
#include "MPU6050.h"
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <RF24_config.h>
#include "Wire.h"

/*DEKLARASI PIN DAN ALAMAT*/
const int pushbutton = 2;
int buttonstate = 0;
RF24 radio(9,10);           //CE, CSN rf24
const uint64_t address = 0xE8E8F0F0E1LL; //alamat pipe atau tunnel
MPU6050 accelgyro;          // class default I2C address is 0x68

/*DEKLARASI VARIABEL*/
int16_t ax, ay, az;         // Variabel Accelerometer
int16_t gx, gy, gz;         // Variabel Gyroscope
int16_t antrian[50][3];     // array untuk menyimpan data accelerometer selama tombol ditekan
int16_t kirim[6][3];        // array untuk data yang dikirim ke perangkat penerima
int i = 0;

void setup() {
    Wire.begin();
    Serial.begin(115200);
    pinMode(pushbutton, INPUT);
    SPI.begin();
    radio.begin();
    radio.openWritingPipe(address); //setting alamat reciever
    accelgyro.initialize();  // initialize device    
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed"); // verify connection
    radio.stopListening(); //merubah modem ke mode transmisi
}

void loop() {
  buttonstate = digitalRead(pushbutton);
  while (buttonstate == 1)
  {
    delay(30);
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // read raw accel/gyro measurements from device
    antrian[i][0] = ax;
    antrian[i][1] = ay;
    antrian[i][2] = az;
    i++;
    buttonstate = digitalRead(pushbutton);
  }
  if (i != 0){
    Serial.print("jumlah data : "); Serial.println(i);
    for (int a = 0 ; a<i; a++){
      Serial.print(a); Serial.print("\t"); Serial.print(antrian[a][0]); Serial.print("\t");
      Serial.print(antrian[a][1]); Serial.print("\t");
      Serial.println(antrian[a][2]);
    }
    Serial.println(" ");

    Serial.println("3 data pertama : ");
    for (int b=0; b<3; b++)
    {
     kirim[b][0] = antrian[b][0];
     kirim[b][1] = antrian[b][1];
     kirim[b][2] = antrian[b][2];
      Serial.print(b); Serial.print("\t"); Serial.print(kirim[b][0]); Serial.print("\t");
      Serial.print(kirim[b][1]); Serial.print("\t");
      Serial.println(kirim[b][2]); 
    }
    
    Serial.println(" ");
    int e = i-3 ;
    Serial.println("2 data terakhir : ");
    for (e ; e<i ; e++)
    {
      if(e == i-2)
      {
        kirim[3][0] = antrian[e][0]; kirim[3][1] = antrian[e][1]; kirim[3][2] = antrian[e][2];
        Serial.print(e); Serial.print("\t"); Serial.print(kirim[3][0]); Serial.print("\t");
        Serial.print(kirim[3][1]); Serial.print("\t");
        Serial.println(kirim[3][2]);
      } else if(e == i-1)
      {
        kirim[4][0] = antrian[e][0]; kirim[4][1] = antrian[e][1]; kirim[4][2] = antrian[e][2];
        Serial.print(e); Serial.print("\t"); Serial.print(kirim[4][0]); Serial.print("\t");
        Serial.print(kirim[4][1]); Serial.print("\t");
        Serial.println(kirim[4][2]);
      } 
    }
    delay(100);
    radio.write(&kirim , sizeof(kirim)); //paket data yang dikirim 
    Serial.println(" "); 
    Serial.print("besar paket : "); Serial.println(sizeof(kirim));
    Serial.println("Paket yang Dikirim : ");
    for(int z = 0; z<5 ; z++)
    {
      Serial.print(z+1); Serial.print("\t");
      Serial.print(kirim[z][0]); Serial.print("\t");
      Serial.print(kirim[z][1]); Serial.print("\t");
      Serial.println(kirim[z][2]);
    }
  }
 /*RESET NILAI VARIABEL*/
  i = 0;
}

