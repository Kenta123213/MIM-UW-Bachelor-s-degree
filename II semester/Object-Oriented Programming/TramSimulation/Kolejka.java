public class Kolejka implements KolejkaZdarzen {
    private Zdarzenie[] zdarzenia; // Tablica przechowująca zdarzenia w kolejce
    private int maxZdarzen; // Maksymalna liczba zdarzeń, jakie mogą być przechowywane w kolejce
    private int iloscZdarzen; // Aktualna liczba zdarzeń w kolejce
    private Symulacja symulacja; // Referencja do obiektu klasy Symulacja

    // Konstruktor klasy Kolejka
    public Kolejka(Symulacja symulacja) {
        zdarzenia = new Zdarzenie[1];
        this.symulacja = symulacja; // Przypisanie referencji do obiektu klasy Symulacja
        maxZdarzen = 1; // Inicjalizacja maksymalnej liczby zdarzeń
        iloscZdarzen = 0; // Inicjalizacja liczby zdarzeń w kolejce
    }

    // Metoda startująca kolejkę zdarzeń na podanym dniu
    public void start(int dzien, Symulacja symulacja) {
        for (Zdarzenie zdarzenie : zdarzenia) {
            zdarzenie.wykonaj(dzien, symulacja); // Wykonanie każdego zdarzenia w kolejce
        }
    }

    // Metoda powiększająca tablicę zdarzeń
    private void powieksz() {
        maxZdarzen = maxZdarzen * 2; // Podwajanie maksymalnej liczby zdarzeń
        Zdarzenie[] temp = new Zdarzenie[maxZdarzen]; // Tworzenie nowej tablicy z podwójną wielkością
        for (int i = 0; i < maxZdarzen / 2; i++) {
            temp[i] = zdarzenia[i]; // Przeniesienie zdarzeń do nowej tablicy
        }
        zdarzenia = temp; // Aktualizacja referencji do tablicy zdarzeń
    }

    // Metoda dodająca zdarzenie do kolejki
    public void dodajZdarzenie(Zdarzenie zdarzenie) {
        if (iloscZdarzen == maxZdarzen) {
            powieksz(); // Powiększenie tablicy, jeśli jest zapełniona
        }
        zdarzenia[iloscZdarzen] = zdarzenie; // Dodanie zdarzenia do tablicy
        iloscZdarzen++; // Zwiększenie liczby zdarzeń w kolejce
    }

    // Metoda sortująca zdarzenia w kolejce po czasie
    public void sortuj() {
        dopasujTablice(); // Dopasowanie tablicy do liczby rzeczywistych zdarzeń
        int n = zdarzenia.length;
        boolean czyZamieniono;
        do {
            czyZamieniono = false;
            for (int i = 0; i < n - 1; i++) {
                if (zdarzenia[i].godzina.getCzas() > zdarzenia[i + 1].godzina.getCzas()) {
                    Zdarzenie temp = zdarzenia[i];
                    zdarzenia[i] = zdarzenia[i + 1];
                    zdarzenia[i + 1] = temp;
                    czyZamieniono = true;
                }
            }
            n--;
        } while (czyZamieniono);
    }

    // Metoda dopasowująca tablicę do liczby rzeczywistych zdarzeń
    private void dopasujTablice() {
        Zdarzenie[] temp = new Zdarzenie[iloscZdarzen];
        for (int i = 0; i < iloscZdarzen; i++) {
            temp[i] = zdarzenia[i]; // Przeniesienie zdarzeń do nowej tablicy
        }
        zdarzenia = temp; // Aktualizacja referencji do tablicy zdarzeń
    }

    // Metoda kończąca dzień - resetuje kolejkę zdarzeń
    public void koniecDnia() {
        zdarzenia = new Zdarzenie[1]; // Resetowanie tablicy zdarzeń
        maxZdarzen = 1; // Resetowanie maksymalnej liczby zdarzeń
        iloscZdarzen = 0; // Resetowanie liczby zdarzeń w kolejce
    }
}