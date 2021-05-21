
//Tjekker den nuværende temperatur i VF, to forskellige steder i VF
float TjekTemp() {
  float Temp;
  float TempDHT1;
  float TempDHT2;

  float Temp1 = 0;
  TempDHT1 = 0;

  float Temp2 = 0;
  TempDHT2 = 0;

  for (int i = 0; i < 100; i++) {
    Temp1 = dht1.readTemperature();
    TempDHT1 = Temp1 + TempDHT1;
  }

  for (int i = 0; i < 100; i++) {
    Temp2 = dht2.readTemperature();
    TempDHT2 = Temp2 + TempDHT2;
  }

  TempDHT1 = (TempDHT1 / 100) + 0.5;
  TempDHT2 = (TempDHT2 / 100) + 0.5;

  Temp = (TempDHT1 + TempDHT2) / 2;
  return Temp;
}
