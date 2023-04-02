#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

// Setting up LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

const int ROWS = 4;
const int COLUMNS = 4;

const int reley_pin = 0;

const int BUZZER = 8;

const int GREEN_LED = 6;
const int RED_LED = 7;

char keys[ROWS][COLUMNS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROWS] = {A2, A1, A0, A3};
byte pin_columns[COLUMNS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_columns, ROWS, COLUMNS);

char key;
int n = 0;

char c;

char password[4] = "123A";
char inKeys[4];

bool pass_change = false;

void setup() {
  SPI.begin();
  mfrc522.PCD_Init();
  delay(5);
  mfrc522.PCD_DumpVersionToSerial();
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
  if (! mfrc522.PICC_IsNewCardPresent() && ! mfrc522.PICC_ReadCardSerial()) {
    if (key) {
      if (!pass_change) {
          if (key == 'C') update_display();
          else if (key == '#') {
            pass_change = true;
            n = 0;
            lcd.clear();
            lcd.setCursor(n, 0);
            lcd.print("Change password:");
          } else {
            enter_pass(key);
          } 
          check_pass();  
      } else {
        change_password(key);
      }
    }
  } else {
    //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
    unsigned long uid = getID();
    if(uid == 4294964518) unlock();
    else lock();
  }
}

unsigned long getID(){
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
    return 0;
  }
  unsigned long hex_num;
  hex_num =  mfrc522.uid.uidByte[0] << 24;
  hex_num += mfrc522.uid.uidByte[1] << 16;
  hex_num += mfrc522.uid.uidByte[2] <<  8;
  hex_num += mfrc522.uid.uidByte[3];
  mfrc522.PICC_HaltA(); // Stop reading
  return hex_num;
}

void enter_pass(char k) {
  lcd.setCursor(n, 1);
  inKeys[n] = key;
  lcd.print("*"); // This is for printing * instead of keys 
  n++;
}

void update_display() {
  n = 0;
  lcd.setCursor(n, 1);
  lcd.clear();
  lcd.print("Enter password: ");
  lcd.setCursor(0, 1);
}

void change_password(char k) {
  if (key && n < 4) {
    lcd.setCursor(n, 1);
    password[n] = key;
    lcd.print(password[n]);
    n++;
  }
  else {
    pass_change = false;
    update_display();
  }
}

void unlock() {
      //Serial.println("Pass");
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
}

void lock() {
  //Serial.println("Lock");
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

void check_pass() {
  if (n == 4) {
    if (inKeys[0] == password[0] && inKeys[1] == password[1] && inKeys[2] == password[2] && inKeys[3] == password[3]) {
      unlock();
    } else {
      lock();
    }
  } else return;
}
