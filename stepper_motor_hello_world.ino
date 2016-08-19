// pin definitions 
const byte motorDirPin = 2;
const byte motorStepPin = 3;
const byte MS1 = 4;
const byte MS2 = 5;
const byte MS3 = 6;

// stepper motor constants
long steps_per_revolution = 400;
int usteps_per_step[] = {1, 2, 4, 8, 16}; // microsteps per step
int step_table[] = {LOW,  LOW,  LOW,   // full step
                    HIGH, LOW,  LOW,   // half step 
                    LOW,  HIGH, LOW,   // quarter step
                    HIGH, HIGH, LOW,   // eighth step
                    HIGH, HIGH, HIGH}; // sixteenth step

// direction and speed
int dir = HIGH;
float rps = 0.5; // seconds per revolution
long delay_per_step; // delay per step, us

void rotate_stepper()
{
  for (int i=0; i<5; i++) {
    digitalWrite(MS1, step_table[i*3 + 0]);
    digitalWrite(MS2, step_table[i*3 + 1]);
    digitalWrite(MS3, step_table[i*3 + 2]);
    
    delay_per_step = (1e6/(rps * steps_per_revolution * usteps_per_step[i]));
    
    Serial.print("  MS1 = "); Serial.println(step_table[i*3 + 0]); 
    Serial.print("  MS2 = "); Serial.println(step_table[i*3 + 1]); 
    Serial.print("  MS3 = "); Serial.println(step_table[i*3 + 2]); 
    Serial.print("  Taking "); Serial.print(steps_per_revolution*usteps_per_step[i]); Serial.print(" steps at "); Serial.print(delay_per_step); Serial.println(" us per step.");
      
    for (long j=0; j<steps_per_revolution; j++) {
      for (int k=0; k<usteps_per_step[i]; k++) {
        digitalWrite(motorStepPin, HIGH);
        delayMicroseconds(delay_per_step/2);
        digitalWrite(motorStepPin, LOW);
        delayMicroseconds(delay_per_step/2);
      }
    }
    delay(1000);
  }
}

void setup(void)
{
  // stepper motor setup
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(MS3, LOW);
  
  pinMode(motorDirPin, OUTPUT);
  pinMode(motorStepPin, OUTPUT);

  digitalWrite(motorDirPin, dir);
  Serial.begin(9600);
  Serial.println("Opening serial connection at 9600");
}

void loop(void)
{
  rotate_stepper();
  // change direction
  if (dir == HIGH) { 
    dir = LOW; 
  } else { 
    dir = HIGH;
  }
  digitalWrite(motorDirPin, dir);
  delay(2000);
}
