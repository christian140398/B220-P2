
//SwitchCase styrre de forskellige værdier for hver valgt besked.
void SwitchCase() {
  int Fugt = TjekFugt();

  switch (Case) {
    case 't':
      digitalWrite(PumpePin, HIGH);
      digitalWrite(LedPin, HIGH);
      Tilstand = 0;
      break;

    case 's':
      digitalWrite(PumpePin, LOW);
      digitalWrite(LedPin, LOW);
      Tilstand = 0;
      break;

    case 'm':
      PlanteFugt = MynteFugt;
      VandPlante(Fugt);
      Tilstand = 1;

      break;

    case 'k':
      PlanteFugt = KarseFugt;
      VandPlante(Fugt);
      Tilstand = 1;
      break;

    default:
      break;
  }
}
