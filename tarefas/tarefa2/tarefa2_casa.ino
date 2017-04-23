typedef struct Bt{//struct destinada ao botão
	int pin;
	unsigned long lastClick;
	const unsigned long debouncing=200;//tempo de debouncing obtido experimentalmente na aula
	int state;//estado atual do botão, pode ser 0==desligado, 1==click, 2==apertado 
	
	void start(int p){//faz o set do pin e ajusta as variaveis auxiliares
		pin=p;
		pinMode(pin, INPUT);
		state = !digitalRead(pin);
		lastClick=millis();
	}
	int getState(){//obtem o state atual
		int tmp = !digitalRead(pin);//le o pino
		if(!tmp && lastClick+debouncing<=millis()){//se soltar o botão por mais que [debouncing]ms, considera desligado
			state=0;
		}
		else if(state ==0 && tmp){//se eu acabei de apertar o botão
			state =1;
			lastClick=millis();
		}
		else if(state==1 && tmp){//se eu já estava com o botão pressionado
			state=2;
		}
		return state;
	}
	unsigned long getLastClick(){
		return lastClick;
	}
};
typedef struct Led{//struct destinada ao led
	int pin;
	int state;//estado atual do led
	const unsigned long minDelay=100;//tempo minimo para o led no modo blink (este valor foi encontrado experimentalmente durante a aula, e visa melhorar o efeito visual)
	unsigned long lastBlink;
	unsigned long blinkDelay;//tempo do blink
	void start(int p){//faz o set do pin e ajusta as variáveis auxiliares
		pin = p;
		pinMode(pin, OUTPUT);
		state=0;
	}
	void setBlink(unsigned long delay){//faz as configurações para o modo blink
		blinkDelay=delay;
		lastBlink=millis();
	}
	void ajustBlink(long ajust){//ajusta o delay do blink
		blinkDelay = max(minDelay,blinkDelay+ajust);
	}
	
	void setState(int s){		
		state=s;
		digitalWrite(pin,state);
	}
	void blink(){
		if(lastBlink+blinkDelay<=millis()){
			setState(!state);
			lastBlink=millis();
		}
	}
};
Led l1;
Bt bt1,bt2;    
int b1,b2;

void setup() {
  l1.start(13);
  l1.setBlink(1000);
  
  bt1.start(2);
  bt2.start(3);
  
  Serial.begin(9600); 
}

void loop() {
	b1 = bt1.getState();
	b2 = bt2.getState();
	if(b1==2&&b2==2 && max(bt1.getLastClick(), bt2.getLastClick())+500<=millis()){//os dois apertados ao mesmo tempo 
        Serial.print("Parou tudo\n");
        while(1);
	}else if(b1==1){
		l1.ajustBlink(-100);
		Serial.print("UP\n");
	}else if(b2 ==1){
		Serial.print("DOWN\n");
		l1.ajustBlink(+100);
	}
	l1.blink();
}