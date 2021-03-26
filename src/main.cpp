#include <Arduino.h>


// Bardzo prosty kod oparty na zmiennych globalnych (dla prostoty i lepszego zrozumienia)




#define DISPLAY_INTERVAL      500     // Co ile odświeżamy wyświetlacz (ms)
#define BUTTON_INTERVAL       100     // Co ile sprawdzamy wciśnięcie przycisku (ms), dostosować pod własną wygodę
#define MEASUREMENT_INTERVAL  500     // Co ile mierzymy temperaturę (ms)
#define PAGES                 2       // Ile ekranów do wyswietlania
#define BUTTON                10      // Tu wstaw nr pinu pod który podepniesz przycisk.
                                      // Przycisk wepnij między pinem a masą!


// Tu wrzuc potrzebny kod (include itp.)




// Zmienne globalne

unsigned long actualTime = 0;           // Przechowuje aktualny czas
unsigned long displayUpdateTime = 0;    // Ostatni czas update wyświetlacza
unsigned long buttonCheckTime = 0;      // Ostatni czas sprawdzania przycisku
unsigned long readSensorsTime = 0;      // Ostatni czas odczytu sensorów

int pageNo = 1;                         // Przechowuje która strona jest aktualnie aktywna

// Dodaj pozostałe potrzebne zmienne

// Funkcje

void ReadSensors()  // Funkcja pomiaru temperatury
{
  // Miejsce na kod odpowiedzialny za pomiary temperatury

  Serial.println("Odczyt temperatur");
}

void CheckButtons()  // Funkcja odczytu przycisku
{
  if(digitalRead(BUTTON) == LOW)
  {
    delay(10); // konieczny żeby wyeliminować drgania zestyków

    if(digitalRead(BUTTON) == LOW)  // Jesli po tym czasie przycisk jes nadal wciśnięty
    {
      Serial.println("Sprawdzenie przycisku");

      pageNo++; // Zwiększ nr wyświetlanej strony

      if(pageNo > PAGES)  // Jeśli nr wyświetlanej strony jest większy niż max liczba stron
      {
        pageNo = 1; // Wróć do pierwszej strony
      }

      Serial.print("Aktualna strona: ");
      Serial.println(pageNo);
    }
  }
}

void DisplayPage()  // Funkcja odczytu przycisku
{
  Serial.println("Wyświetlanie strony");

  switch(pageNo)  // Wybór strony do wyświetlania
  {
    case 1:   // Strona nr 1
    {

      // Tu kod odpowiedzialny za to co ma być wyświetlone na stronie 1, dodać clear na początku!

      break;
    }
    case 2:   // Strona nr 2
    {

      // Tu kod odpowiedzialny za to co ma być wyświetlone na stronie 2, dodać clear na początku!

      break;
    }
    //case 3: // Strona nr 3 (jeśli potrzebna)
    //{
    //  break;
    //}
  }
}


// Program główny

void setup() 
{
Serial.begin(9600);

pinMode(BUTTON, INPUT_PULLUP);    // definicja pinu jako wejście

// Reszta kodu



}

void loop() 
{
  actualTime = millis();    // millis() zwraca czas od włączenia Arduino, sprawdzamy aktualny czas

  // Pomiary z czujników
  // Jeśli od ostatniego pomiaru upłynął czas większy niż interwał
  if(actualTime - readSensorsTime > MEASUREMENT_INTERVAL)
  {
    ReadSensors();
    readSensorsTime = actualTime;   // ostatni czas pomiaru = aktualny czas
  }

  // Odczyt stanu przycisku
  // Jeśli od ostatniego pomiaru upłynął czas większy niż interwał
  if(actualTime - buttonCheckTime > BUTTON_INTERVAL)
  {
    CheckButtons();
    buttonCheckTime = actualTime;   // ostatni czas sprawdzania przycisku = aktualny czas
  }

  // Wyświetlanie strony
  // Jeśli od ostatniego pomiaru upłynął czas większy niż interwał
  if(actualTime - displayUpdateTime > DISPLAY_INTERVAL)
  {
    DisplayPage();
    displayUpdateTime = actualTime;   // ostatni czas wyświetlania strony = aktualny czas
  }
}