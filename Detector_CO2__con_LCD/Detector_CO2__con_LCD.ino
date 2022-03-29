/**
 *  Monitor de CO2 para interiores con sensor de (MH-Z19B)
 *  Monitoriza el nivel de CO2 en un espacio cerrado. Primero advierte y luego emite una alarma en caso de que el nivel de CO2 alcance un nivel no aceptable.
 *  La informacion se presenta en una de pantalla de 4 dígitos, una iluminación LED ademas un zumbador avisa al sobr`epasar un cierto nivel especifcio.
 *  Su alimentacion será mediante una fuente USB de 5V.
 */
#include <SoftwareSerial.h>                                
#include <MHZ19.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//Crear el objeto lcd  dirección  0x27 y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27,16,2);  

#define RX_PIN 10                                         // pin 10 al Rx pin sensor MHZ19
#define TX_PIN 11                                         // pin 11 al Tx pin sensor MHZ19
#define BAUDRATE 9600                                     // Velocidad en baudios para puerto serie del sensor MH-Z19 (no cambiar)
#define LED_Rojo_PIN 3                                    // Pin 5 conexión del LED RGB color Rojo
#define LED_Verde_PIN 7                                   // Pin 6 conexión del LED RGB color Verde
#define LED_Amarillo_PIN 5                                // Pin 3 conexión del LED RGB color Azul
#define BUZZER_PIN 4                                      // Pin 4 conexión del Buzzer
#define B_silencio_PIN 2                                  // Pin 2 interruptor de silencio para alarma  
#define T_lectura_sensor 2e3                              // MH-Z19 tiempo entre lecturas del sensor
//
//----------------------------------------------------------------------  inicializamos sensor y display -----------------------------------
MHZ19 myMHZ19;                                             
SoftwareSerial mySerial(RX_PIN, TX_PIN);                   
unsigned long Dato_tempo = 0;
int CO2 = 0;
enum LED_COLOR {LED_OFF, LED_Rojo, LED_Verde, LED_Amarillo};

///----------------------------------------------------------------------------------------- configuraciones -----------------------
void setup() {
    Serial.begin(9600);                                    
    mySerial.begin(BAUDRATE);                                
    myMHZ19.begin(mySerial);                             
   // myMHZ19.autoCalibration(false); 
    myMHZ19.autoCalibration(true); 
    lcd.init();
    lcd.backlight();
    pinMode(LED_Rojo_PIN, OUTPUT);
    pinMode(LED_Verde_PIN, OUTPUT);
    pinMode(LED_Amarillo_PIN, OUTPUT);
    setLED(LED_OFF); 
}
// ----------------------------------------------------- programa principal --------------------------------------------------------------
void loop() { 
  if (millis() - Dato_tempo >= T_lectura_sensor)
  {
//--- Obtener la medición de CO2 actual como ppm----------   
    CO2 = myMHZ19.getCO2();         // Solicitar CO2 (como ppm)
    Serial.print("CO2 (ppm): ");                      
    Serial.println(CO2); 
     // Cursor en la primera posición de la primera fila
    lcd.setCursor(0,0);
    lcd.print("Nivel CO2:  ");
    lcd.print(CO2);
    lcd.print("   "); 
    coloresled();  
    Dato_tempo = millis();
  }
}
