
double AnalogFugt1, AnalogFugt2;
double Fugt, Fugt1, Fugt2;

int FugtPin1;
int FugtPin2;

void setup() {
  Serial.begin(115200);
}

void loop() {

  for ( int i = 0; i < 1000; i++) {
    AnalogFugt1 = analogRead(FugtPin1);
    AnalogFugt2 = analogRead(FugtPin2);

    Fugt1 = map(AnalogFugt1, maxFugt, minFugt, 0, 100);
    Fugt2 = map(AnalogFugt2, maxFugt, minFugt, 0, 100);

  }

  FugtProcent = (Fugt1 + Fugt2) / 1000;



}
