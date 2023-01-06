/*---------------------- Tutorial Menggunakan Servo ------------------------*/
/*----------------------- CopyRight By ACM Channel -------------------------*/
/*---------- COPYRIGHT https://tipsandtricklengkap.blogspot.com/ -----------*/
/*--------- Jika Bermanfaat Jangan Lupa Subcribe, Like dan Komen :) --------*/

#include <Servo.h> //library Servo 

Servo acmServo; 
int i=0; //inisialisasi variabel i untuk perulangan

void setup() {
  acmServo.attach(9); //Pemberian pin data servo ke pin 9 arduino

}

void loop() {

  /*cara 1*/
  acmServo.write(0); //Mengarahkan servo ke sudut 0 derajat
  delay(100);

  acmServo.write(90); //Mengarahkan servo ke sudut 90 derajat
  delay(100);

  acmServo.write(180); //Mengarahkan servo ke sudut 180 derajat
  delay(100);

  /*Cara 2*/
  for(i=0; i<180; i++){ //For akan menghitung +1 secara berulang dari 0 sampai 90
    acmServo.write(i); //.write berfungsi untuk menuliskan/memberikan sudut ke servo dengan memanggil objek acmServo.write(i);
    delay(50); //Waktu perulangan / pergerakan servo berputar selama 50 ms
  }
  for(i=180; i>=0; i--){ //Servo akan bergerak dari sudut 180 ke 0 karena perulangan -1
    acmServo.write(i); //.write berfungsi untuk menuliskan/memberikan sudut ke servo dengan memanggil objek acmServo.write(i);
    delay(50); //Waktu perulangan / pergerakan servo berputar selama 50 ms
  }

}

/*------------------- YT CHANNEL  :  ACM Channel ---------------------- */
/*----------- https://tipsandtricklengkap.blogspot.com/ --------------- */
