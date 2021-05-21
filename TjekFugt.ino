
//Tjekker fugt niveau, mellem to fugtighedsmålere og finder gennemsnit
int TjekFugt() {
   int Fugt1 = 0;
  int Fugt2 = 0;
  unsigned int AnalogFugt1;
  unsigned int AnalogFugt2;

  delay(100);
  for (int i = 0; i < 1000; i++) {
    AnalogFugt1 = analogRead(AnalogFugtPin1);
    Fugt1 = AnalogFugt1 + Fugt1;

    AnalogFugt2 = analogRead(AnalogFugtPin2);
    Fugt2 = AnalogFugt2 + Fugt2;
  }

  Fugt1 = Fugt1 / 1000;
  Fugt2 = Fugt2 / 1000;


  int Fugt36Procent = (-96.7754034 * (log(0.0002297952524 * Fugt1)));
  int Fugt39Procent = (-88.38794608 * (log(0.0002097183483 * Fugt2)));

  if (Fugt36Procent > 100) {
    Fugt36Procent = 100;
  }
  if (Fugt36Procent < 0) {
    Fugt36Procent = 0;
  }
  if (Fugt39Procent > 100) {
    Fugt39Procent = 100;
  }
  if (Fugt39Procent < 0) {
    Fugt36Procent = 0;
  }

  int Fugt = (Fugt36Procent + Fugt39Procent) / 2;
  
  return Fugt;
}
