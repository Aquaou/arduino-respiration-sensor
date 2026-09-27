const int PIN_0 = A0;
const int PIN_1 = A1;
const float V_IN = 5.0;
const float R3 = 8200.0;
const float R1 = 8200.0;
const float R2 = 8200.0;

float sampleFreqHz = 80.0; // <-- set sampling rate (Hz)
unsigned long sampleIntervalMs = (unsigned long)(1000.0 / sampleFreqHz);

unsigned long runTimeMs = 60000; // <-- set total run time (ms), 60000 = 60s

unsigned long lastSampleTime = 0;
unsigned long startTime = 0;
bool finished = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting....");
  startTime = millis();
}

void loop() {
  if (finished) return;

  unsigned long now = millis();

  if (now - startTime >= runTimeMs) {
    finished = true;
    Serial.println("Done.");
    return;
  }

  if (now - lastSampleTime >= sampleIntervalMs) {
    lastSampleTime = now;

    int raw_a0 = analogRead(PIN_0);
    int raw_a1 = analogRead(PIN_1);

    float V_A0 = raw_a0 * (V_IN / 1023.0);
    float V_A1 = raw_a1 * (V_IN / 1023.0);
    float V_OUT = V_A0 - V_A1;
    float R_CORD = R3 * V_A0 / (V_IN - V_A0);

    //Serial.print("t=");
    Serial.print(now - startTime);
    Serial.print(",");
    //Serial.print("ms  V_A0: ");
    Serial.println(V_A0, 4);
    //Serial.print("  V_A1(ref): ");
    //Serial.print(V_A1, 4);
    //Serial.print("  V_OUT(diff): ");
    //Serial.print(V_OUT, 4);
    //Serial.print("  R_CORD: ");
    //Serial.println(R_CORD, 1);
  }
}
