
//Funktion der styrer uret
void Klok() {
  timeClient.update();
  Ur = timeClient.getFormattedTime();

  int starttid = StartTid[3] + StartTid[4] * 60 + StartTid[1] * 60 * 60 + StartTid[0] * 60 * 60 * 60;
  int tid = Ur[4] + Ur[2] * 60 + Ur[1] * 60 * 60 + Ur[0] * 60 * 60 * 60;
  int stoptid = StopTid[4] + StopTid[2] * 60 + StopTid[1] * 60 * 60 + StopTid[0] * 60 * 60 * 60;

  if (starttid <= tid && tid <= stoptid) {
    digitalWrite(LedPin, HIGH);
  } else {
    digitalWrite(LedPin, LOW);
  }


  delay(100);
}
