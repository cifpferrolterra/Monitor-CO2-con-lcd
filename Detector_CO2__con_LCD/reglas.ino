void coloresled() {
  if (CO2 < 700) {
    setLED(LED_Verde);
    Serial.println("Se activara el led Verde ");
    return;
  } 
  if (CO2 < 1200) {
    Serial.println("Se activara el led en Amarillo");
    setLED(LED_Amarillo);
    return;
  }
  setLED(LED_Rojo);
  Serial.println("Se activara el led en Rojo");
}
