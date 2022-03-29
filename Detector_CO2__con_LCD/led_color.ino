void setLED(LED_COLOR color) {

  analogWrite(LED_Rojo_PIN, 0);   // Reseteamos todos los colores a cero
  analogWrite(LED_Verde_PIN, 0);
  analogWrite(LED_Amarillo_PIN, 0);
  switch (color) {              // Activamos los diferentes colores
    case LED_Rojo:
      analogWrite(LED_Rojo_PIN, 255);
      break;
    case LED_Verde: 
      analogWrite(LED_Verde_PIN, 255);
      break;
    case LED_Amarillo: 
       analogWrite(LED_Amarillo_PIN, 255);
      break;
  }
}
