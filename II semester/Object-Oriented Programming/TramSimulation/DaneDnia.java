public class DaneDnia {
    private int dzien;
    private int iloscPrzejazdow;
    private int lacznyCzasOczekiwania;

    public DaneDnia(int dzien) {
        iloscPrzejazdow = 0;
        lacznyCzasOczekiwania = 0;
        this.dzien = dzien;
    }

    public void dodajPrzejazd() {
        iloscPrzejazdow++;
    }

    public void dodajCzasOczekiwania(int minuty) {
        lacznyCzasOczekiwania += minuty;
    }

    public int getiloscPrzejazdow() {
        return iloscPrzejazdow;
    }

    public int getLacznyCzasOczekiwania() {
        return lacznyCzasOczekiwania;
    }

    public void wypisz() {
        System.out.println("Dnia: " + dzien + " łączna liczba przejazdów pasażerów to: " + iloscPrzejazdow +
                " łączny czas oczekiwania wyniósł: " + lacznyCzasOczekiwania);
    }
}
