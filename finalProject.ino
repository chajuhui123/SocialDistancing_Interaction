//사회적거리두기제안하는캠페인의자
#include "pitches.h" 

int ledArrRed[3][3] = {{22,28,34},{31,37,43},{40,46,49}}; //R LED 배열
int ledArrGreen[3][3] = {{24,30,36},{33,39,45},{42,48,51}}; //G LED 배열 
int ledArrBlue[3][3] = {{26,32,38},{35,41,47},{44,50,53}}; //B LED 배열
int seatArr[3][3] = {{A0, A1, A2},{ A3, A4, A5},{A6, A7, A8}}; //압력센서 배열
int notes[] = {NOTE_A4, NOTE_C3, NOTE_E4}; //도미솔 음
int count = 0 ;
int originSeat[]= {}; // originSeat값 저장 예시

int col = 3; // 배열 세로
int row = 3; // 배열 가로
int ocol; //newSeat 외 압력값이 존재하는 자리 하나의 세로값
int orow; //newSeat 외 압력값이 존재하는 자리 하나의 가로값
int originRow = sizeof(originSeat) / sizeof(originSeat[0]);
int speaker = 8;


void setup(){
  for (int i = 0 ; i < col ;  i ++ ){
    for(int j = 0 ; j < row ; j ++){
      pinMode(ledArrRed[i][j], OUTPUT);}
      };
  for (int i = 0 ; i < col ;  i ++ ){
    for(int j = 0 ; j < row ; j ++){
      pinMode(ledArrGreen[i][j], OUTPUT);}
      };
  for (int i = 0 ; i < col ;  i ++ ){
    for(int j = 0 ; j < row ; j ++){
      pinMode(ledArrBlue[i][j], OUTPUT);}
      };
      Serial.begin(9600);
  pinMode(speaker,OUTPUT);
  }

//이차원배열버전 : newSeat 저장하기
void loop(){
  for (int thisSensorC = 0 ; thisSensorC < col ; thisSensorC++){
    for (int thisSensorR = 0 ; thisSensorR < row; thisSensorR ++){
      int sensorValue = analogRead(seatArr[thisSensorC][thisSensorR]); //sensorValue값받기
      Serial.println("SensorValue: " + String(sensorValue));
      delay(500);
      
      if (sensorValue >= 500){ //sensorValue가 500이 넘을 경우 (사물의 압력 값과 차별화)
        Serial.println("thisSensorC: " + String(thisSensorC));
        Serial.println("thisSensorR: "+ String(thisSensorR));
        int newSeat = (seatArr[thisSensorC][thisSensorR]); //현재 센서위치를 newSeat 변수에 할당
        Serial.println("newSeat: "+ String(newSeat)); // A0:54 A1:55 A2:56 A3:57 A4:58 A5:59
        delay(500);

        //newSeat 외 자리의 col과 row 구하기
        for(int i=0; i<3; i++){       
          for(int j=0; j<3; j++){
            int OriginValue = analogRead(seatArr[i][j]);
          
            Serial.println("OriginValue: " + String(OriginValue));
 
            if((seatArr[i][j] != newSeat) && (OriginValue > 500)){ // OriginValue가 500이 넘는 것끼리만 비교가능
              ocol = i;
              orow = j;
              Serial.println("ocol: " + String(ocol));
              Serial.println("orow: " + String(orow));

              delay(500);
              
              if(thisSensorC == ocol){ // col이 같은 경우
                if (abs(orow-thisSensorR)==1){ // row가 하나 차이남
                digitalWrite(ledArrRed[thisSensorC][thisSensorR], LOW);
                digitalWrite(ledArrRed[ocol][orow], LOW);
                digitalWrite(ledArrBlue[thisSensorC][thisSensorR], HIGH);
                digitalWrite(ledArrBlue[ocol][orow], HIGH);
                digitalWrite(ledArrGreen[thisSensorC][thisSensorR], HIGH);
                digitalWrite(ledArrGreen[ocol][orow], HIGH);
                delay(2000);
                digitalWrite(ledArrBlue[thisSensorC][thisSensorR], LOW);
                digitalWrite(ledArrBlue[ocol][orow], LOW);
                digitalWrite(ledArrRed[thisSensorC][thisSensorR], LOW);
                digitalWrite(ledArrRed[ocol][orow], LOW);
                digitalWrite(ledArrGreen[thisSensorC][thisSensorR], LOW);
                digitalWrite(ledArrGreen[ocol][orow], LOW);
                Serial.println("col이 같고 row가 1차이. 거리유지 실패");
                
                }else{
                  digitalWrite(ledArrRed[thisSensorC][thisSensorR], HIGH);
                  digitalWrite(ledArrRed[ocol][orow], HIGH);
                  digitalWrite(ledArrBlue[thisSensorC][thisSensorR], LOW);
                  digitalWrite(ledArrBlue[ocol][orow], LOW);
                  digitalWrite(ledArrGreen[thisSensorC][thisSensorR], HIGH);
                  digitalWrite(ledArrGreen[ocol][orow], HIGH);
                  delay(2000);
                  digitalWrite(ledArrBlue[thisSensorC][thisSensorR], LOW);
                  digitalWrite(ledArrBlue[ocol][orow], LOW);
                  digitalWrite(ledArrRed[thisSensorC][thisSensorR], LOW);
                  digitalWrite(ledArrRed[ocol][orow], LOW);
                  digitalWrite(ledArrGreen[thisSensorC][thisSensorR], LOW);
                  digitalWrite(ledArrGreen[ocol][orow], LOW);
                  tone(speaker,notes[0],250);  // 스피커
                  delay(300);
                  tone(speaker,notes[1],250);  // 스피커
                  delay(300);
                  tone(speaker,notes[2],250);  // 스피커
                  delay(300);
                  Serial.println("col이 같고 row가 차이가 남. 거리유지 성공");
        
                 }
              }else{ // col이 다름
                if (abs(ocol - thisSensorC)==2){
                  digitalWrite(ledArrRed[thisSensorC][thisSensorR], HIGH);
                  digitalWrite(ledArrRed[ocol][orow], HIGH);
                  digitalWrite(ledArrBlue[thisSensorC][thisSensorR], LOW);
                  digitalWrite(ledArrBlue[ocol][orow], LOW);
                  digitalWrite(ledArrGreen[thisSensorC][thisSensorR], HIGH);
                  digitalWrite(ledArrGreen[ocol][orow], HIGH);
                  delay(2000);
                  digitalWrite(ledArrBlue[thisSensorC][thisSensorR], LOW);
                  digitalWrite(ledArrBlue[ocol][orow], LOW);
                  digitalWrite(ledArrRed[thisSensorC][thisSensorR], LOW);
                  digitalWrite(ledArrRed[ocol][orow], LOW);
                  digitalWrite(ledArrGreen[thisSensorC][thisSensorR], LOW);
                  digitalWrite(ledArrGreen[ocol][orow], LOW);
                  tone(speaker,notes[0],250);  // 스피커
                  delay(300);
                  tone(speaker,notes[1],250);  // 스피커
                  delay(300);
                  tone(speaker,notes[2],250);  // 스피커
                  delay(300);
                  Serial.println("col 다르며 2차이. 거리유지 성공");
                 } else {
                  if(orow == thisSensorR){
                    digitalWrite(ledArrRed[thisSensorC][thisSensorR], LOW);
                    digitalWrite(ledArrRed[ocol][orow], LOW);
                    digitalWrite(ledArrBlue[thisSensorC][thisSensorR], HIGH);
                    digitalWrite(ledArrBlue[ocol][orow], HIGH);
                    digitalWrite(ledArrGreen[thisSensorC][thisSensorR], HIGH);
                    digitalWrite(ledArrGreen[ocol][orow], HIGH);
                    delay(2000);
                    digitalWrite(ledArrBlue[thisSensorC][thisSensorR], LOW);
                    digitalWrite(ledArrBlue[ocol][orow], LOW);
                    digitalWrite(ledArrRed[thisSensorC][thisSensorR], LOW);
                    digitalWrite(ledArrRed[ocol][orow], LOW);
                    digitalWrite(ledArrGreen[thisSensorC][thisSensorR], LOW);
                    digitalWrite(ledArrGreen[ocol][orow], LOW);
                    Serial.println("col 다르고 row 같음. 거리유지 실패");
                  } else {
                    digitalWrite(ledArrRed[thisSensorC][thisSensorR], HIGH);
                    digitalWrite(ledArrRed[ocol][orow], HIGH);
                    digitalWrite(ledArrBlue[thisSensorC][thisSensorR], LOW);
                    digitalWrite(ledArrBlue[ocol][orow], LOW);
                    digitalWrite(ledArrGreen[thisSensorC][thisSensorR], HIGH);
                    digitalWrite(ledArrGreen[ocol][orow], HIGH);
                    delay(2000);
                    digitalWrite(ledArrBlue[thisSensorC][thisSensorR], LOW);
                    digitalWrite(ledArrBlue[ocol][orow], LOW);
                    digitalWrite(ledArrRed[thisSensorC][thisSensorR], LOW);
                    digitalWrite(ledArrRed[ocol][orow], LOW);
                    digitalWrite(ledArrGreen[thisSensorC][thisSensorR], LOW);
                    digitalWrite(ledArrGreen[ocol][orow], LOW);
                    tone(speaker,notes[0],250);  // 스피커
                    delay(300);
                    tone(speaker,notes[1],250);  // 스피커
                    delay(300);
                    tone(speaker,notes[2],250);  // 스피커
                    delay(300);
                    Serial.println("col 다르고 row 다름. 거리유지 성공");}
                  }
                }  
              }
        
              }
            }
          }    
    }
  }
}
