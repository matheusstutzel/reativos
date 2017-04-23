const int bt1 = 2;
const int bt2 = 3;
const int ledPin =  13;

int buttonState = 0;

unsigned long t1,tApertou,b1PT,b2PT;
int apertou;
int b1,b2;
int b1P,b2P;
int d1;
int state;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(bt1, INPUT);
  pinMode(bt2, INPUT);
  
  t1=millis();
  b1PT=millis();
  b2PT=millis();
  apertou=0;
  d1=1000;
  state=1;
  b1P=0;
  b2P=0;

  Serial.begin(9600); 
}

void loop() {
  b1 = !digitalRead(bt1);
  b2 = !digitalRead(bt2);

  //se soltar o b1 limpa o b1P
  if(!b1 && b1PT+200<=millis()){
    b1P=0;
  }
  //se soltar o b2 limpa o b2P
  if(!b2&& b2PT+200<=millis()){
    b2P=0;
  }

  //os dois apertados ao mesmo tempo
  if(b1&&b2){
    if(!apertou){
      tApertou=millis();
      apertou = !apertou;
    }else{
      //se ele segurou os dois botões por mais de 500 ms 
      if(tApertou+500<=millis()){
        //para tudo
        Serial.print("Parou tudo\n");
        while(1);
      }
    }
  }else{
	apertou=0;
	if(b1&& !b1P){
		b1P=!b1P;
		b1PT=millis();
		d1-=100;
		Serial.print("UP\n");
		if(d1<100)d1=100;
	}else if(b2 && !b2P){
		b2P=!b2P;
		b2PT=millis();
		Serial.print("DOWN\n");
		d1+=100;
	}
  }

  
  if(t1+d1<=millis()){
    state=!state;
    t1=millis();
    digitalWrite(ledPin,state);
  }
}