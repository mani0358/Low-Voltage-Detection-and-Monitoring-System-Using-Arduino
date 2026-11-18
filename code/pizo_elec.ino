


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------------- CONFIGURATION ----------------

// LCD configuration
const int lcd_i2c_addr = 0x27;
LiquidCrystal_I2C lcd(lcd_i2c_addr, 16, 2);

// Input and LED pins
const int pin_a0 = A0;
const int pin_led = 2;

// Resistor divider values
const float r_top = 100000.0;
const float r_bot = 10000.0;

const float div_factor = (r_top + r_bot) / r_bot;

// ADC reference
const float adc_ref_mv = 1100.0;
const int adc_max = 1023;

// Signal display configuration
const int max_signal = 10;
const float full_scale_mv = 1000.0;

// LED threshold
const float led_threshold_mv = 100.0;

// ---------------- SETUP ----------------

void setup() {

  pinMode(pin_led, OUTPUT);
  pinMode(pin_a0, INPUT);

  analogReference(INTERNAL);

  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Voltage Monitor");

  lcd.setCursor(0, 1);
  lcd.print("Initializing...");

  delay(1500);

  lcd.clear();
}

// ---------------- MAIN LOOP ----------------

void loop() {

  // Read ADC
  int adc_value = analogRead(pin_a0);

  // Convert ADC reading into voltage (mV)
  float adc_voltage_mv =
      ((float)adc_value * adc_ref_mv) / adc_max;

  // Calculate actual input voltage
  float input_voltage_mv =
      adc_voltage_mv * div_factor;

  // Calculate signal strength (0-10)
  int signal = map(
      (long)input_voltage_mv,
      0,
      (long)full_scale_mv,
      0,
      max_signal
  );

  signal = constrain(signal, 0, max_signal);

  // LED indication
  if (input_voltage_mv >= led_threshold_mv) {
    digitalWrite(pin_led, HIGH);
  }
  else {
    digitalWrite(pin_led, LOW);
  }

  // ---------------- LCD DISPLAY ----------------

  // First row: Voltage and signal
  lcd.setCursor(0, 0);

  lcd.print("V:");
  lcd.print((int)input_voltage_mv);
  lcd.print("mV ");

  lcd.print("S:");
  lcd.print(signal);
  lcd.print("  ");

  // Second row: Bar graph
  lcd.setCursor(0, 1);

  int bars = map(signal, 0, max_signal, 0, 16);

  for (int i = 0; i < 16; i++) {

    if (i < bars) {
      lcd.write(byte(255));
    }
    else {
      lcd.print(" ");
    }
  }

  delay(200);
}
