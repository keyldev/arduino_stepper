/*
            ##    ##    
           #  #  #      
           #  #   #     
           #  #    #    
           #  #     #   
            ##    ##   
*/
#define PIN_DIR 2 
#define PIN_STEP 3
#define PIN_LAMP 5 // LED заряда батареи
#define PIN_BUTTON_MOVE 13 // "движение"
#define PIN_BUTTON_SPEED A3 // ручка скорости
#define PIN_BUTTON_DIRECTION 12 // направление
#define PIN_ATD 6 // АЦП пин

const int N = 2; // ацп делитель
 
const int msType[5][3] = {
  {0,0,0}, // full
  {1,0,0}, // 1/2
  {0,1,0}, // 1/4
  {1,1,0}, // 1/8
  {1,1,1}, // 1/16
};
const int msPins[3] = {7, 8, 9}; // ms 1-3
void setup() {
  
  pinMode(PIN_BUTTON_MOVE, INPUT_PULLUP);
  pinMode(PIN_BUTTON_DIRECTION, INPUT_PULLUP);
  pinMode(PIN_LAMP, OUTPUT);
  pinMode(PIN_STEP, OUTPUT);
  pinMode(PIN_DIR, OUTPUT);
  
  for(int i = 0; i < 3; i++)
    pinMode(msPins[i], OUTPUT);
    
  //debug
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  
  //
  
}

void loop() {
  
  int stepMode = map(analogRead(PIN_BUTTON_SPEED), 0, 1023, 0, 5);
  int realVolt = analogRead(PIN_ATD)/N;
  //Buttons
  bool bMove = !digitalRead(PIN_BUTTON_MOVE);
  bool bDirection = !digitalRead(PIN_BUTTON_DIRECTION); // здесь был аналогРид, но в протеусе он не отрабатывал, магия
  //вопрос про вольтаж
  if(realVolt < 3) digitalWrite(PIN_LAMP, HIGH); // в теории, при недостаточном значении realVolt - лампочка должна загореться
  if(bMove == 1) // если клацнули на "движение"
  {
    //дебаг для протеуса
    digitalWrite(11, HIGH); // дебаг в осциллограф 
    //_____________
    
    if(bDirection == 1) {
      digitalWrite(PIN_DIR, HIGH); 
      digitalWrite(PIN_LAMP, HIGH); 
      digitalWrite(10, HIGH);
      } // если клацнули "направление"
    else {
      digitalWrite(PIN_DIR, LOW);
      digitalWrite(PIN_LAMP, LOW); 
      digitalWrite(10, LOW);
      }
    for(int i = 0; i < 3; i++)
    {
      digitalWrite(msPins[i], msType[stepMode][i]); // обрыв логики здесь. 
    }
    digitalWrite(PIN_STEP, HIGH);
  }
  else
  {
    digitalWrite(11, LOW);
  }
}
