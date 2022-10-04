#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// Setting up LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int ROWS = 4;
const int COLUMNS = 4;

const int reley_pin = 6;

const int BUZZER = 11;

const int GREEN_LED = 12;
const int RED_LED = 13;

char keys[ROWS][COLUMNS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROWS] = {10, 9, 8, 7};
byte pin_columns[COLUMNS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_columns, ROWS, COLUMNS);

char key;
int n = 0;

char c;

char password[4] = "123A";
char inKeys[4];

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter password: ");
  lcd.setCursor(0, 1);
  pinMode(reley_pin, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(reley_pin, HIGH);
  noTone(BUZZER);
}

void loop() {
  key = keypad.getKey();
  if (key != 'C' && key) {
    lcd.setCursor(n, 1);
    inKeys[n] = key;
    lcd.print(inKeys[n]);
    n++;
  } else if (key == 'C') {
    update_display();
  } else return;

  check_pass();
}

void update_display() {
  n = 0;
  lcd.setCursor(n, 1);
  lcd.clear();
  lcd.print("Enter password: ");
  lcd.setCursor(0, 1);
}

void check_pass() {
  if (n == 4) {
    if (inKeys[0] == password[0] && inKeys[1] == password[1] && inKeys[2] == password[2] && inKeys[3] == password[3]) {
      Serial.println("Pass");
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("Pass");
      tone(BUZZER, 700);
      digitalWrite(GREEN_LED, HIGH);
      delay(700);
      noTone(BUZZER);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(reley_pin, LOW); // Turns reley on (unlock door)
      delay(3000);
      Serial.println("Lock");
      digitalWrite(reley_pin, HIGH); // Turns reley off (lock door)
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("Lock");
      delay(1000);
      update_display();
      return;
    } else {
      Serial.println("Lock");
      tone(BUZZER, 900);
      digitalWrite(RED_LED, HIGH);
      delay(700);
      noTone(BUZZER);
      digitalWrite(RED_LED, LOW);
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("Lock");
      delay(2000);
      update_display();
    }
  } else return;
}
