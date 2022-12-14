#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>          // library for LCD with I2C
#include <virtuabotixRTC.h>
virtuabotixRTC myRTC(8, 9, 10); // CLK, DAT, RST

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pompa = 12;
const int pbplus = 4;
const int pbmin = 5;
const int pbSubMode = 3;
const int pbMode = 6;
const int buzzer = 2;
int alarmHour=0;
int alarmMinutes=0;
boolean alarmOn=0;
int M = 12;
int D = 31;
int Y = 2020;
int day = 7;
int h = 23;
int m = 59;
int mode = 1;
int submode = 1;

void setup()  {
  pinMode(pompa, OUTPUT);
  pinMode(pbmin, INPUT_PULLUP);
  pinMode(pbplus, INPUT_PULLUP);
  pinMode(pbSubMode, INPUT_PULLUP);
  pinMode(pbMode, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  //myRTC.setDS1302Time(00, 32, 13, 2, 21, 12, 2020);
  lcd.init();         // initialize the LCD
  lcd.backlight();    // Turn on the blacklight
}


void loop()  {
  if (digitalRead(pbMode) == LOW) {
    mode++;
    if (mode == 4) {
      mode = 1;
    }
    submode = 0;
    lcd.clear();
    delay(200);
  }
  if (mode==1){
    clockDisplay();
  }
  if (mode==2){
    gantitgl();
  }
  if (mode==3){
    aktifalarm();
  }
  if (mode==0){
    alarmOn=1;
    alarm();
  }
  if (alarmOn==1 && myRTC.hours==alarmHour && myRTC.minutes==alarmMinutes) {
      alarmOn=0;
      mode=0;  
  }
}      

void alarm(){
  clockDisplay();
  digitalWrite(pompa, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(300);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(pompa, LOW);
  digitalWrite(buzzer, HIGH);
  delay(300);
  digitalWrite(buzzer, LOW);
  delay(200);
}

void clockDisplay(){
  myRTC.updateTime();
  //  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.setCursor(0, 1);
  if (myRTC.dayofmonth < 10) {
    lcd.print("0");
    lcd.print(myRTC.dayofmonth);
  }
  else{
    lcd.print(myRTC.dayofmonth);
  }
  lcd.print("/");
  lcd.setCursor(3,1);
  switch (myRTC.month) {
    case 1: lcd.print("Jan"); break;
    case 2: lcd.print("Feb"); break;
    case 3: lcd.print("Mar"); break;
    case 4: lcd.print("Apr"); break;
    case 5: lcd.print("Mei"); break;
    case 6: lcd.print("Jun"); break;
    case 7: lcd.print("Jul"); break;
    case 8: lcd.print("Ags"); break;
    case 9: lcd.print("Sep"); break;
    case 10: lcd.print("Okt"); break;
    case 11: lcd.print("Nov"); break;
    case 12: lcd.print("Des"); break;
  }
  lcd.print("/");
  lcd.print(myRTC.year);

  lcd.setCursor(13, 1);
  switch (myRTC.dayofweek) {
    case 1: lcd.print("Min"); break;
    case 2: lcd.print("Sen"); break;
    case 3: lcd.print("Sel"); break;
    case 4: lcd.print("Rab"); break;
    case 5: lcd.print("Kam"); break;
    case 6: lcd.print("Jum"); break;
    case 7: lcd.print("Sab"); break;
  }
  lcd.setCursor(4, 0);
    if (myRTC.hours < 10) {
    lcd.print("0");
  }
  lcd.print(myRTC.hours);
  lcd.print(":");
  if (myRTC.minutes < 10) {
    lcd.print("0");
  }
  lcd.print(myRTC.minutes);
  lcd.print(":");
  if (myRTC.seconds < 10) {
    lcd.print("0");
  }
  lcd.print(myRTC.seconds);
  lcd.print("   ");
}

void gantitgl(){
  lcd.setCursor(0, 0);
  if (digitalRead(pbSubMode) == LOW) {
    submode++;
    if (submode > 7) {
      submode = 0;
    }
    delay(200);
    lcd.clear();
  }
  if (submode == 0) {
    lcd.setCursor(0, 0);
    lcd.print("iki ngatur tgl");
  }
  if (submode == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Ganti Bulan bos");
    lcd.setCursor(0, 1);
    lcd.print("--> ");
    if (digitalRead(pbplus) == LOW) {
      M++;
      if (M == 13) {
        M = 1;
      }
      delay(200);
    }
    if (digitalRead(pbmin) == LOW) {
      M--;
      if (M == 0) {
        M = 12;
      }
      delay(200);
    }
    switch (M) {
      case 1: lcd.print("Januari     ");
        break;
      case 2: lcd.print("Februari    ");
        break;
      case 3: lcd.print("Maret       ");
        break;
      case 4: lcd.print("April       ");
        break;
      case 5: lcd.print("Mei         ");
        break;
      case 6: lcd.print("Juni        ");
        break;
      case 7: lcd.print("Juli        ");
        break;
      case 8: lcd.print("Agustus     ");
        break;
      case 9: lcd.print("September   ");
        break;
      case 10: lcd.print("Oktober     ");
        break;
      case 11: lcd.print("November    ");
        break;
      case 12: lcd.print("Desember    ");
        break;
    }
  }
  if (submode == 2) {
    lcd.setCursor(0, 0);
    lcd.print("Ganti tgl bos");
    lcd.setCursor(0, 1);
    lcd.print("--> ");
    if (digitalRead(pbplus) == LOW) {
      D++;
      if (D == 32) {
        D = 1;
      }
      delay(200);
    }
    if (digitalRead(pbmin) == LOW) {
      D--;
      if (D == 0) {
        D = 31;
      }
      delay(200);
    }
    lcd.print(D);
    lcd.print(" ");
  }
  if (submode == 3) {
    lcd.setCursor(0, 0);
    lcd.print("Ganti tahun bos");
    lcd.setCursor(0, 1);
    lcd.print("--> ");
    if (digitalRead(pbplus) == LOW) {
      Y++;
      delay(200);
    }
    if (digitalRead(pbmin) == LOW) {
      Y--;
      delay(200);
    }
    lcd.print(Y);
  }
  if (submode == 4) {
    lcd.setCursor(0, 0);
    lcd.print("Ganti dina bos");
    lcd.setCursor(0, 1);
    lcd.print("--> ");
    if (digitalRead(pbplus) == LOW) {
      day++;
      if (day == 8) {
        day = 1;
      }
      delay(200);
    }
    if (digitalRead(pbmin) == LOW) {
      day--;
      if (day == 0) {
        day = 7;
      }
      delay(200);
    }
    switch (day) {
      case 1: lcd.print("Minggu      ");
        break;
      case 2: lcd.print("Senin       ");
        break;
      case 3: lcd.print("Selasa      ");
        break;
      case 4: lcd.print("Rabu        ");
        break;
      case 5: lcd.print("Kamis       ");
        break;
      case 6: lcd.print("Jumat       ");
        break;
      case 7: lcd.print("Sabtu       ");
        break;
    }
  }
  if (submode == 5) {
    lcd.setCursor(0, 0);
    lcd.print("Ganti jam bos");
    lcd.setCursor(0, 1);
    lcd.print("--> ");
    if (digitalRead(pbplus) == LOW) {
      h++;
      if (h == 24) {
        h = 00;
      }
      delay(200);
    }
    if (digitalRead(pbmin) == LOW) {
      h--;
      if (h == -1) {
        h =23;
      }
      delay(200);
    }
    if (h<10){
      lcd.print("0");
    }
    lcd.print(h);
  }
    if (submode == 6) {
    lcd.setCursor(0, 0);
    lcd.print("Ganti menit bos");
    lcd.setCursor(0, 1);
    lcd.print("--> ");
    if (digitalRead(pbplus) == LOW) {
      m++;
      if (m == 60) {
        m = 0;
      }
      delay(200);
    }
    if (digitalRead(pbmin) == LOW) {
      m--;
      if (m == -1) {
        m = 59;
      }
      delay(200);
    }
    if (m<10){
      lcd.print("0");
    }
    lcd.print(m);
  }
  if (submode == 7) {
    lcd.setCursor(0, 0);
    lcd.print("Lagi ganti tgl");
    lcd.setCursor(0, 1);
    lcd.print("Sabar nggih");
    delay(200);
    lcd.print(".");
    delay(200);
    lcd.print(".");
    delay(200);
    lcd.print(".");
    delay(200);
    lcd.print(".");
    delay(200);
    lcd.print(".");
    delay(200);
    myRTC.setDS1302Time(00, m, h, day, D, M, Y);
    delay(200);
    lcd.clear();
    mode = 1;
  }
}
void aktifalarm(){
  lcd.setCursor(0,0);
 if (digitalRead(pbSubMode) == LOW) {
    submode++;
    if (submode > 4) {
      submode = 0;
    }
    delay(200);
    lcd.clear();
  }  
  if (submode == 0) {
    lcd.print("Nek iki alarm");
   }
if(submode==1){
    lcd.setCursor(0, 0);
    lcd.print("Arep tangi jam?");
    if (digitalRead(pbplus) == LOW) {
      alarmHour++;
      if (alarmHour == 24) {
        alarmHour = 00;
      }
      delay(200);
    }
    if (digitalRead(pbmin) == LOW) {
      alarmHour--;
      if (alarmHour == -1) {
        alarmHour =23;
      }
      delay(200);
    }
    lcd.setCursor(0, 1);
    if (alarmHour < 10) {
      lcd.print("0");
      lcd.setCursor(1, 1);
    }
    lcd.print(alarmHour);
    lcd.setCursor(2, 1);
    lcd.print(":");
    lcd.setCursor(3, 1);
    if (alarmMinutes < 10) {
      lcd.print("0");
      lcd.setCursor(4, 1);
    }
    lcd.print(alarmMinutes);
    lcd.setCursor(13,1);
    if (alarmOn==1){lcd.print("ON ");}
    else {lcd.print("OFF");}
  }  
  if (submode==2){
    lcd.setCursor(0, 0);  
    lcd.print("Arep tangi jam?");
    lcd.setCursor(0, 1);
    if (alarmHour < 10) {
      lcd.print("0");
      lcd.setCursor(1, 1);
    }
    lcd.print(alarmHour);
    lcd.setCursor(2, 1);
    lcd.print(":");
    lcd.setCursor(3, 1);
    if(digitalRead(pbplus)==LOW){
      alarmMinutes++;
      if (alarmMinutes == 60) {
        alarmMinutes = 00;
      }
      delay(200);
    }
    if (digitalRead(pbmin) == LOW) {
      alarmMinutes--;
      if (alarmMinutes == -1) {
        alarmMinutes = 59;
      }
      delay(200);
  }
      if (alarmMinutes < 10) {
      lcd.print("0");
      lcd.setCursor(4, 1);
    }
    lcd.print(alarmMinutes);
    lcd.setCursor(13,1);
    if (alarmOn==1){lcd.print("ON ");}
    else {lcd.print("OFF");}
  }
  if (submode==3){
    lcd.setCursor(0, 0);
    lcd.print("Arep tangi jam?");
    lcd.setCursor(0, 1);
    if (alarmHour < 10) {
      lcd.print("0");
      lcd.setCursor(1, 1);
    }
    lcd.print(alarmHour);
    lcd.setCursor(2, 1);
    lcd.print(":");
    lcd.setCursor(3, 1);
    if (alarmMinutes < 10) {
      lcd.print("0");
      lcd.setCursor(4, 1);
    }
    lcd.print(alarmMinutes);
    if (digitalRead(pbplus) == LOW) {
      alarmOn = !alarmOn;
      delay(200);
  }
  lcd.setCursor(13,1);
    if (alarmOn==1){lcd.print("ON ");}
    else {lcd.print("OFF");}
  }  
  if (submode==4 && alarmOn==1){
    lcd.clear();
    lcd.print("Nyimpen alarm");
    lcd.setCursor(0, 1);
    lcd.print("Sabar nggih");
    delay(200);
    lcd.print(".");
    delay(200);
    lcd.print(".");
    delay(200);
    lcd.print(".");
    delay(200);
    lcd.print(".");
    delay(200);
    lcd.print(".");
    delay(200);
    submode = 0;
    mode = 1;
    lcd.clear();
    }
  if (submode==4 && alarmOn==0){
      lcd.clear();
      lcd.print("Alarm e mati bos");
      submode = 0;
      mode = 1;
      delay(2000);
      lcd.clear();
    }
}
