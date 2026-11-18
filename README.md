# Low-Voltage-Detection-and-Monitoring-System-Using-Arduino
# &#x20;

## 1. Project Overview

This project is designed to detect and monitor low-level DC input voltages using an Arduino microcontroller. It measures the input voltage through an analog input pin (A0), displays the measured voltage and signal level on a 16×2 I2C LCD, and activates an LED connected to digital pin D2 when the detected voltage reaches the configured threshold.

The system uses a resistor voltage divider to scale the input voltage before feeding it to the Arduino ADC.

### Key Features

- Low-voltage input monitoring.
- Analog voltage measurement using Arduino ADC.
- 10 mV programmed LED detection threshold.
- LED indication through digital pin D2.
- Real-time voltage display in millivolts.
- Signal-level indication (0–10).
- 16×2 LCD with I2C communication.
- ADC averaging to reduce measurement noise.

## 2. Hardware Requirements

| Component          |    Quantity |
| ------------------ | ----------: |
| Arduino UNO / Nano |           1 |
| 16×2 I2C LCD       |           1 |
| LED                |           1 |
| 100 kΩ resistor    |           1 |
| 10 kΩ resistor     |           1 |
| 220 Ω resistor     |           1 |
| Breadboard         |           1 |
| Jumper wires       | As required |
| DC voltage source  |           1 |

## 3. Pin Configuration

### Arduino Connections

| Component            | Arduino Pin       |
| -------------------- | ----------------- |
| LCD SDA              | A4 (UNO)          |
| LCD SCL              | A5 (UNO)          |
| LCD VCC              | 5V                |
| LCD GND              | GND               |
| Analog voltage input | A0                |
| LED positive         | D2                |
| LED negative         | GND through 220 Ω |

### Voltage Divider Configuration

The voltage divider consists of:

- R1 = 100 kΩ
- R2 = 10 kΩ

Connection:

```text
       DC Input (+)
            |
         R1 100kΩ
            |
            +---------- Arduino A0
            |
         R2 10kΩ
            |
           GND
```

The voltage divider reduces the input voltage before it reaches the Arduino ADC.

Voltage divider equation:

Vout = Vin × (R2 / (R1 + R2))

For the selected resistor values:

Vout = Vin / 11

Therefore:

Vin = Vout × 11

## 4. Working Principle

The system operates through the following steps:

1. The external DC voltage is applied to the resistor voltage divider.
2. The voltage divider scales the input voltage to a suitable ADC level.
3. Arduino reads the analog voltage through A0.
4. Multiple ADC readings are averaged to reduce noise.
5. The ADC reading is converted into millivolts.
6. The original input voltage is calculated using the voltage divider ratio.
7. The measured voltage is displayed on the I2C LCD.
8. The signal level is calculated on a scale of 0–10.
9. When the calculated input voltage reaches the programmed 10 mV threshold, the LED connected to D2 turns ON.

## 5. LCD Display

The LCD displays two parameters:

**First Row:**

- V: Measured input voltage in millivolts.
- S: Signal level from 0 to 10.

**Second Row:**

- A 16-character bar graph representing the signal level.

Example:

```text
V:128mV S:1
███
```

The displayed values depend on the actual input voltage.

## 6. Software Requirements

- Arduino IDE
- Wire.h library
- LiquidCrystal_I2C library

### Arduino Configuration

The project uses:

| Parameter       | Configuration            |
| --------------- | ------------------------ |
| Analog input    | A0                       |
| LED output      | D2                       |
| LCD address     | 0x27                     |
| LCD size        | 16×2                     |
| ADC reference   | Internal 1.1V (UNO/Nano) |
| ADC resolution  | 10-bit                   |
| Voltage divider | 100kΩ / 10kΩ             |
| LED threshold   | 10 mV                    |
| Signal scale    | 0–10                     |

## 7. Voltage Measurement Calculation

The Arduino ADC converts the analog input into a digital value between 0 and 1023.

ADC voltage:

Vadc = (ADC Reading × Vref) / 1023

Actual input voltage:

Vin = Vadc × 11

For an ADC reference of 1.1V:

Vadc = (ADC Reading × 1100) / 1023 mV

Vin = Vadc × 11

## 8. LED Detection Logic

The LED is controlled using a voltage threshold comparison.

```cpp
const float led_threshold_mv = 10.0;

if (input_voltage_mv >= led_threshold_mv)
{
    digitalWrite(pin_led, HIGH);
}
else
{
    digitalWrite(pin_led, LOW);
}
```

- Input voltage below 10 mV: LED OFF.
- Input voltage at or above 10 mV: LED ON.

**Note:** The 10 mV value is the programmed threshold, not a guaranteed physical detection sensitivity. With the 100kΩ/10kΩ divider and nominal 1.1V reference, one ADC count corresponds to approximately 11.8 mV at the original input. Reliable detection at 10 mV requires a suitable low-noise amplifier or comparator.

## 9. Applications

Potential applications include:

- Low-voltage DC monitoring.
- Electronic circuit voltage indication.
- Sensor output monitoring.
- Battery voltage monitoring (within the designed input range).
- Basic analog signal detection.
- Educational ADC and embedded-system experiments.

## 10. Limitations and Future Improvements

### Current Limitations

- ADC resolution limits very-low-voltage detection.
- Internal ADC reference requires calibration for accurate measurements.
- The present circuit is intended for DC input measurement.
- Noise can affect measurements at very low input levels.

### Future Improvements

- Add an operational amplifier for low-voltage signal amplification.
- Use an external high-resolution ADC.
- Implement automatic voltage calibration.
- Add adjustable detection thresholds.
- Introduce data logging and serial monitoring.
- Improve noise filtering and measurement stability.

## 11. Safety Precautions

- Do not exceed the Arduino ADC input voltage limit.
- With a nominal 1.1V reference and 100kΩ/10kΩ divider, keep the original input below approximately 12.1V.
- Use a common ground between the input circuit and Arduino.
- Do not connect AC mains directly to the Arduino.
- Verify the voltage divider connections before powering the circuit.

## 12. Conclusion

This project demonstrates a basic low-voltage monitoring and detection system using Arduino. It combines analog voltage measurement, ADC processing, resistor-based voltage scaling, LCD visualization, and digital LED indication.

The system provides a foundation for developing more advanced low-voltage sensing and monitoring applications.

---

**Project Category:** Embedded Systems / Analog Voltage Monitoring

**Controller:** Arduino UNO / Nano

**Display:** 16×2 I2C LCD

**Input:** Analog A0

**Output:** Digital D2 LED

**Programmed Detection Threshold:** 10 mV
