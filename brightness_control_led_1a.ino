/*
 * measure time for activate two independent pushbutton (masurare timp apasare 2 butoane)
 * program adapt by Nicu FLORICA (niq_ro) - http://nicuflorica.blogspot.com/
 * original ideea from Andy DOZ's blog - https://andydoz.blogspot.com
 * ver.1.0 - control a led with2 buttons (on/off/decrease and increase the brithness)
 * ver.1.a - clear the unuseful data
 */

#define buton1 3  // buton 1 fara retine la masa
#define buton2 2  // buton 2 fara retine la masa
#define led 11    // led + rezistenta 220..470 ohmi la masa

int apasarebuton1 = 0; // stare buton (apasat/neapasat)
int duratamare1 = 1000; // valoare timp apaaare lunga, in ms
int durataapasare1 = 0; // durata apasare buton
int tpaparare1 = 0;// memorare timp apasare
int tpeliberare1 = 0;// memorare timp eliberare
int durata1 = 0;  // durata apasare, in timp real
boolean stare1 = false; // stare de cronometrare

int apasarebuton2 = 0; // stare buton (apasat/neapasat)
int duratamare2 = 1000; // valoare timp apaaare lunga, in ms
int durataapasare2 = 0; // durata apasare buton
int tpaparare2 = 0;// memorare timp apasare
int tpeliberare2 = 0;// memorare timp eliberare
int durata2 = 0;  // durata apasare, in timp real
boolean stare2 = false; // stare de cronometrare

int nivel= 5;  // initial brightness
int pas = 2;   // step for brightness
int nivelmin = 5;   // lower level of brightness
int nivelmax = 255; // higher level of brightness
byte aprins = 0; // 0 - led off, 1 - led on
byte scurt1 = 0; // 1  - short push
byte lung1 = 0;  // 1 - long push
byte scurt2 = 0;
byte lung2 = 0;
byte micropauza = 5;

void setup() {
  Serial.begin(9600);
  pinMode(buton1,INPUT);//
  digitalWrite(buton1,HIGH); // pull-up activ
  pinMode(buton2,INPUT);//
  digitalWrite(buton2,HIGH); // pull-up activ
  pinMode(led,OUTPUT);//
  analogWrite(led, 0);  // led stins
}

void loop() { 
    durataapasare1 = aflareduratapasare1();
    durataapasare2 = aflareduratapasare2();
    delay (micropauza);
    
if (aprins == 0)
{        
  analogWrite(led, 0);  // led stins
}
else
{
  analogWrite(led, nivel);  // led aprins
}
 
} // end main loop


int aflareduratapasare1() 
   {
   apasarebuton1 = digitalRead(buton1);    // citiree stare buton 1
   if(apasarebuton1 == LOW && stare1 == false) {   // daca butonul 1 e apasat, dar nu mai fusese apasat
   tpaparare1 = millis();
   stare1 = true;
   };
          
 if (apasarebuton1 == HIGH && stare1 == true) 
   {  // daca butonul 1 este neapasat si tocmai a fost eliberat
    tpeliberare1 = millis ();
    durataapasare1 = tpeliberare1 - tpaparare1;
    stare1 = false;
    if ((scurt1 == 1) and (lung1 == 0)) aprins = 0;  // just short push
    scurt1 = 0;
    lung1 = 0;
    };

 if(apasarebuton1 == LOW && stare1 == true) 
   {  // daca butonul 1 este inca apasat
   durata1 = millis() - tpaparare1;
   scurt1 = 1;
   if (durata1 > duratamare1) 
      {   // aprinde led daca s-a depasit timpul minim
      nivel = nivel - pas;
      if (nivel < nivelmin) nivel = nivelmin;
      delay(micropauza);
      lung1 = 1;
      }  
  }       
   return durataapasare1;  // iesire din subrutina si memorare timp
}

int aflareduratapasare2() 
   {
   apasarebuton2 = digitalRead(buton2);    // citiree stare buton 1
   if(apasarebuton2 == LOW && stare2 == false) {   // daca butonul 1 e apasat, dar nu mai fusese apasat
   tpaparare2 = millis();
   stare2 = true;
   };
          
 if (apasarebuton2 == HIGH && stare2 == true) {  // daca butonul 2 este neapasat si tocmai a fost eliberat
    tpeliberare2 = millis ();
    durataapasare2 = tpeliberare2 - tpaparare2;
    stare2 = false;
    if ((scurt2 == 1) and (lung2 == 0)) aprins = 1;  // short push
    scurt2 = 0;
    lung2 = 0;
    };

 if(apasarebuton2 == LOW && stare2 == true) 
   {  // daca butonul 2 este inca apasat
   durata2 = millis() - tpaparare2;
   scurt2 = 1;
   if (durata2 > duratamare2) 
      {   // aprinde led daca s-a depasit timpul minim
      nivel = nivel + pas;
      if (nivel > nivelmax) nivel = nivelmax;
      delay(micropauza);
      lung2 = 1;
      }
  }       
   return durataapasare2;  // iesire din subrutina si memorare timp
}
