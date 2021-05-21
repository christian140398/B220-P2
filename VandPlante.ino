
//Styrer hvor lang tid hver plante skal vandes, på baggrund af fugtigheds niveau
void VandPlante(int Fugt) {
  
  if (Fugt < PlanteFugt) {
    digitalWrite(PumpePin, HIGH);

    double VT = VandTid();
    int vt = VT * 1000;

    delay(vt);

    digitalWrite(PumpePin, LOW);
    delay(10000);
  }
}

int VandTid() {
  //Mål på produkt
  int Hoej = 3;
  int Bred = 55;
  int Dyb = 20;
  int AntalBakker = 2;
  int Str = (Hoej * Bred * Dyb) * AntalBakker;
  int Fugt = TjekFugt();
  double maxVand = Str * 0.8;

  double VandingTid = ((((PlanteFugt - Fugt) * 0.01) * maxVand) * 0.04542563823) + 1.337467066;

  return VandingTid;  
}
