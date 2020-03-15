// 2 dimensional array af röðunum
const int row[8] = {
  2, 7, 19, 5, 13, 18, 12, 16
};

// 2 dimensional array of dálkunum:
const int col[8] = {
  6, 11, 10, 3, 17, 4, 8, 9
};

// 2-dimensional array af pixels:
int pixels[8][8];

// staðsetning punktsins.
int x = 5;
int y = 5;

// Takkinn á stýripinnanum
const int buttonPin = 1;
// Staðan á srýripinnanum, hvort hann sé ýttur eða ekki.
int buttonState = 0;

// Staðsetning stýripnnar
int vrx = A0; // Stýripinni X
int vry = A1; // Stýripinni Y

void setup() {
  // Virki takkann á stýripinnanum sem input.
  pinMode(buttonPin, INPUT);
  // Fer yfir alla pinnana og læt þá alla og virki þá með því að láta þá sem outputs.
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT);
    pinMode(row[thisPin], OUTPUT);
    // Passa að allar perurnar séu slokknar þegar ég fer yfir þær.
    digitalWrite(col[thisPin], LOW);
  }

  // Geri matrixið tilbúið með því að fara yfir allar raðirnar og allar perurnar í röðinni sem ég er að fara í gegnum og læt perurnar á LOW.
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = LOW;
    }
  }
}

void loop() {
  // Les hvort takkinn það sé verið að ýta á takkann á stýripninnanum.
  buttonState = digitalRead(buttonPin);

  // Les úr stýripinnanum.
  lesaSensora();

  // Uppfæri skjáinn.
  refreshScreen();

  // Slekk á ölum perunum sem voru kveiktar ef það var ýtt á takkann.
  if (buttonState == LOW) {
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        pixels[x][y] = LOW;
      }
    }
  }
}

void lesaSensora() {
   // Nota þetta fall til að lesa úr stýripinnanum með því að mappa x hreyfingar og y hreyfingar stýripinnan í tölur frá 0 - 7 og út frá þessum tölum nota ég variableinn pixels til að finna staðsetninguna sem að pixelinn á að kveikjast.
   pixels[x][y] == LOW;
   // read the sensors for X and Y values:
   x = 7 - map(analogRead(A0), 0, 1023, 0, 7);
   y = map(analogRead(A1), 0, 1023, 0, 7);
   // Hérna nota ég variableinn pixels til að kveikja á pixelinum á rétta staðnum:
   pixels[x][y] = HIGH;
}

void refreshScreen() {
  // Fer yfir allar perurnar í öllum röðunum
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // Læt pinnann á röðinni sem ég er að fara að fara í gegnum á low.
    digitalWrite(row[thisRow], LOW);
    // Fer síðan í gegnum allar perurnar á röðinni sem ég er að fara í gegnum.
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      // Finn stöðuna á pixelinum sem er á staðsetningu sem ég finn út frá hvaða röð og hvaða dálk ég er á.
      int thisPixel = pixels[thisRow][thisCol];
      // Þegar að röðin er á low og dálkurinn er á high þá kveikist á ljósinu þar sem að þau hittast.
      digitalWrite(col[thisCol], thisPixel);
      // Ég slekk síðan á ljósinu sem að er high:
      if (thisPixel == HIGH) {
        digitalWrite(col[thisCol], LOW);
      }
    }
    // Breyti pinnanum sem að er með röðina í low til að slökkva á röðinni.
    digitalWrite(row[thisRow], HIGH);
  }
}
