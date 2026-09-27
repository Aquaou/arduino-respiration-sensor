# Arduino Respiration Sensor

Arduino sketch for collecting voltage data from a conductive rubber cord stretch sensor. Stretching the cord changes its resistance; the sketch records the sensor voltage over time for later analysis.

## Files

- `resp/resp.ino` — Arduino sketch.

## Hardware and circuit assumptions

The sketch assumes an Arduino Uno with a 10-bit ADC, a 5 V analog reference, and a bridge/divider circuit using 8.2 kΩ fixed resistors.

| Connection | Purpose |
| --- | --- |
| A0 | Sensor divider midpoint |
| A1 | Reference divider midpoint |
| GND | Common circuit ground |
| 5 V | Divider excitation assumed by the calculations |

The resistance equation in the code assumes an 8.2 kΩ resistor between 5 V and A0, with the conductive cord between A0 and ground. An equal-resistor reference divider places A1 near half the supply voltage. Confirm your actual wiring and resistor values match these assumptions.

## Getting started

1. Download or clone this repository.
2. Open `resp/resp.ino` in the Arduino IDE, keeping it inside the `resp` folder.
3. Select your Arduino Uno and its connected port.
4. Adjust the sampling and duration settings if needed.
5. Upload the sketch and open the Serial Monitor at **9600 baud**.
6. Reset the board to start a fresh capture. The sketch stops after the configured duration; reset it again to repeat.

No additional Arduino libraries are required.

## Configuration

| Variable | Default | Meaning |
| --- | --- | --- |
| `sampleFreqHz` | `80.0` | Requested sampling rate in Hz |
| `runTimeMs` | `60000` | Capture duration in milliseconds (60 seconds) |
| `V_IN` | `5.0` | Assumed supply and ADC reference voltage |
| `R3` | `8200.0` | Fixed sensor divider resistor in ohms |

`R1` and `R2` are declared as 8.2 kΩ but are not used in the current calculations.

## Serial output

The sketch prints `Starting....`, followed by comma-separated data rows, then `Done.`.

Each data row contains:

```text
elapsed_time_ms,A0_voltage_V
```

For example, an illustrative row is:

```text
120,2.5024
```

Remove the opening and closing status lines before importing the capture as a purely numeric CSV. The sketch does not print a column header.

A1 voltage, bridge voltage difference, and cord resistance are also calculated, but their serial print statements are currently commented out.

## Calculations

With a 10-bit ADC:

```text
V_A0 = raw_a0 × V_IN / 1023
V_A1 = raw_a1 × V_IN / 1023
V_OUT = V_A0 - V_A1
R_CORD = R3 × V_A0 / (V_IN - V_A0)
```

The cord resistance equation applies to the divider orientation described above. It becomes undefined when `V_A0` equals `V_IN`; the current sketch does not guard against that case.

## Current limitations

- **Sampling is approximate.** At 80 Hz, the ideal interval is 12.5 ms, but the integer conversion truncates it to 12 ms (about 83.3 Hz before other delays). Use the recorded timestamps when analyzing the data.
- **Serial output can limit the sample rate.** At 9600 baud, printing can delay the loop, especially if more output columns are enabled.
- Voltage conversion assumes an exact 5 V reference; actual reference voltage affects the results.
- The sketch records a raw sensor signal. It does not calculate breathing rate, filter the data, or calibrate voltage to chest expansion or respiratory volume.
