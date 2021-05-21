
//Funktion der styrer uret
void Klok() {
  timeClient.update();
  Ur = timeClient.getFormattedTime();

  if (Tilstand != 0) {
    if ((Ur[0] >= StartTid[0]) && (Ur[1] >= StartTid[1]) && (Ur[3] >= StartTid[3]) && (Ur[4] >= StartTid[4])) {
      digitalWrite(LedPin, HIGH);
    }
    else if ((Ur[0] >= StopTid[0]) && (Ur[1] >= StopTid[1]) && (Ur[3] >= StopTid[3]) && (Ur[4] >= StopTid[4])) {
      digitalWrite(LedPin, LOW);
    }
  }


  delay(100);
}
