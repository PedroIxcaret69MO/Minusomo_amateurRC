#include <Ps3Controller.h>

//motores
const int ENA = 13;
const int IN1 = 12;
const int IN2 = 14;
const int IN3 = 27;
const int IN4 = 26;
const int ENB = 25;
const int freq = 15000;
const int pwmchanel = 4;
const int pwmchanel2 = 1;
const int resolution = 8;
int duty_cycle = 0;
int dato = 0;
//Indicar la conexión
int led = 2;

void setup() 
{
    Serial.begin(115200);
    //PWM
    ledcSetup(pwmchanel,freq,resolution);
    ledcSetup(pwmchanel2,freq,resolution);
    
    ledcAttachPin(ENA,pwmchanel);
    ledcAttachPin(ENB,pwmchanel2);
    Ps3.begin("8c:7c:b5:b2:d7:a7");
    //f0:f0:02:4c:ac:3b negro
    //14:5a:fc:3a:65:8e ROJO
    //Ps3.begin("8c:7c:b5:b2:d7:a7");
    Ps3.attachOnConnect(Conectar);
    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
    pinMode(IN3,OUTPUT);
    pinMode(IN4,OUTPUT);
    pinMode(ENA,OUTPUT);
    pinMode(ENB,OUTPUT);
    pinMode(led,OUTPUT);
}

void loop() 
{
    dato = Ps3.data.analog.button.r1;
    while(dato < 50)
    {
      Condiciones();
      dato = Ps3.data.analog.button.r1;
      if(dato > 50);
      {
        break;
      }
    }
    while(dato > 50)
    {
      dato = Ps3.data.analog.button.r1;
      Condiciones2();
      if(dato < 50);
      {
        break;
      }
    }
}


void Condiciones()
{
    if(Ps3.data.analog.stick.ly < -10)
    {
        duty_cycle = Ps3.data.analog.button.r2;
          if(duty_cycle > 200)
     {
        duty_cycle = 200;
     }
        Adelante(duty_cycle);
    }else if(Ps3.data.analog.stick.ly > 10)
    {
        duty_cycle = Ps3.data.analog.button.r2;
        if(duty_cycle > 200)
     {
        duty_cycle = 200;
     }
        Atras(duty_cycle);
    }else if(Ps3.data.analog.stick.rx < -10)
    {
        duty_cycle = Ps3.data.analog.button.r2;
        if(duty_cycle > 200)
     {
        duty_cycle = 200;
     }
        Izquierda(duty_cycle);
    }else if(Ps3.data.analog.stick.rx > 10)
    {
        duty_cycle = Ps3.data.analog.button.r2;
        if(duty_cycle > 200)
     {
        duty_cycle = 200;
     }
        Derecha(duty_cycle);
    }else
    {
        Alto(0);
    }
}

void Condiciones2()
{
   if(Ps3.data.analog.stick.ly < -10)
    {
        duty_cycle = Ps3.data.analog.button.r2;
    
        Adelante(duty_cycle);
    }else if(Ps3.data.analog.stick.ly > 10)
    {
        duty_cycle = Ps3.data.analog.button.r2;
 
        Atras(duty_cycle);
    }else if(Ps3.data.analog.stick.rx < -10)
    {
        duty_cycle = Ps3.data.analog.button.r2;
  
        Izquierda(duty_cycle);
    }else if(Ps3.data.analog.stick.rx > 10)
    {
        duty_cycle = Ps3.data.analog.button.r2;
   
        Derecha(duty_cycle);
    }else
    {
        Alto(0);
    }
}

void Conectar()
{
    digitalWrite(led,HIGH);
}

int Izquierda(int velocidad)
{
    Serial.println(velocidad);
    Serial.println("Derecha");
    ledcWrite(pwmchanel,velocidad);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);    
    ledcWrite(pwmchanel2,velocidad);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    return velocidad;
}
int Derecha(int velocidad)
{
    Serial.println(velocidad);
    Serial.println("Izquierda");
    ledcWrite(pwmchanel,velocidad);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);    
    ledcWrite(pwmchanel2,velocidad);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    return velocidad;
}
int Adelante(int velocidad)
{
    Serial.println(velocidad);
    Serial.println("Atras");
    ledcWrite(pwmchanel,velocidad);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);    
    ledcWrite(pwmchanel2,velocidad);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    return velocidad;
}
int Atras(int velocidad)
{
    Serial.println(velocidad);
    Serial.println("Adelante");
    ledcWrite(pwmchanel,velocidad);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);    
    ledcWrite(pwmchanel2,velocidad);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH); 
    return velocidad;
}
int Alto(int velocidad)
{
    Serial.println(velocidad);
    Serial.println("Alto");
    ledcWrite(pwmchanel,0);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);    
    ledcWrite(pwmchanel2,0);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW); 
    return velocidad;
}
