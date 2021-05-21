
//Styrer temperatur regulering i VF
void StyrTemp() {

  float m = 0.55 * 1.225; //Masse
  float c = 1012.0; //Varmekapacitet
  float Temp = TjekTemp(); //Nuværende temp i VF 
  float Pind = 1.3; //Effekt varmeelement
  float Pud = 1.0; //Effekt tab

  DeltaT = SetPoint - Temp; //Forskellen i temp
  VarmeTid = ((m * c * DeltaT) / (Pind - Pud));

  pinMode(VarmePin, HIGH);
  t1 = millis();
  HL = true;

}

void slukTemp(int tempDelay){
    pinMode(VarmePin, LOW);
    HL = false;
    delay(tempDelay);
}
