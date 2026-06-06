// Pins for Sensor 1
const int S0_1 = 2;
const int S1_1 = 3;
const int S2_1 = 4;
const int S3_1 = 5;
const int OUT_1 = 6;

// Pins for Sensor 2
const int S0_2 = 7;
const int S1_2 = 8;
const int S2_2 = 9;
const int S3_2 = 10;
const int OUT_2 = 11;

void setup() {
  Serial.begin(9600);

  // Setup sensor 1 pins
  pinMode(S0_1, OUTPUT); pinMode(S1_1, OUTPUT);
  pinMode(S2_1, OUTPUT); pinMode(S3_1, OUTPUT);
  pinMode(OUT_1, INPUT);
  
  // Setup sensor 2 pins
  pinMode(S0_2, OUTPUT); pinMode(S1_2, OUTPUT);
  pinMode(S2_2, OUTPUT); pinMode(S3_2, OUTPUT);
  pinMode(OUT_2, INPUT);
  
  // Set frequency scaling to 20%
  digitalWrite(S0_1, HIGH); digitalWrite(S1_1, LOW);
  digitalWrite(S0_2, HIGH); digitalWrite(S1_2, LOW);
}

int readColor(int S2, int S3, int OUT) {
  digitalWrite(S2, LOW); digitalWrite(S3, LOW);
  int red = pulseIn(OUT, LOW);
  
  digitalWrite(S2, HIGH); digitalWrite(S3, HIGH);
  int green = pulseIn(OUT, LOW);
  
  digitalWrite(S2, LOW); digitalWrite(S3, HIGH);
  int blue = pulseIn(OUT, LOW);

  // Simple color decision (tweak thresholds as needed)
  if (red < green && red < blue) return 1;    // Red
  else if (green < red && green < blue) return 2; // Green
  else return 3; // Blue
}

void loop() {
  int color1 = readColor(S2_1, S3_1, OUT_1);
  int color2 = readColor(S2_2, S3_2, OUT_2);

  Serial.print("Sensor 1: ");
  printColor(color1);
  Serial.print(" | Sensor 2: ");
  printColor(color2);
  Serial.println();

  delay(1000);  // Adjust delay as needed
}

void printColor(int color) {
  if (color == 1) Serial.print("Red");
  else if (color == 2) Serial.print("Green");
  else Serial.print("Blue");
}
