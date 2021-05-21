
//Anvendes til test af forskellige funktioner (bare print).
void Print() {
  Serial.print("Plante: ");
  Serial.println(Besked);

  float Temp = TjekTemp();
  Serial.print("Temperatur: ");
  Serial.println(Temp);

  Serial.print("Ønskede temperatur: ");
  Serial.println(SetPoint);

  int Fugt = TjekFugt();
  Serial.print("Fugtighed: ");
  Serial.println(Fugt);

  Serial.print("Ønskede fugtighed: ");
  Serial.println(PlanteFugt);

  int VT = VandTid() * 1000;
  Serial.print("Vandingstid: ");
  Serial.println(VT);

  Serial.print("VarmeTid: ");
  Serial.println(VarmeTid);

  Serial.print("Klokken: ");
  Serial.println(Ur);

  Serial.print("StartTid: ");
  Serial.println(StartTid);
  
  Serial.print("StopTid: ");
  Serial.println(StopTid);

  Serial.println("");
}
