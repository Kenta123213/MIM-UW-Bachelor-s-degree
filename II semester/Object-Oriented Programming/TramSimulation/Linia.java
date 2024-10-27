public class Linia {
    private int numerLinii;
    private int liczbaTramwajow;
    private int dlugoscTrasy;
    private Przystanek[] przystanki;
    private int[] czasDojazdu;
    private int dodanePrzystanki;
    private Tramwaj[] tramwaje;
    private int dodaneTramwaje;
    private int odstepWyjazdu;

    // Konstruktor klasy Linia
    public Linia(int numerLinii, int liczbaTramwajow, int dlugoscTrasy) {
        this.numerLinii = numerLinii;
        this.liczbaTramwajow = liczbaTramwajow;
        this.dlugoscTrasy = dlugoscTrasy;
        this.tramwaje = new Tramwaj[liczbaTramwajow];
        this.przystanki = new Przystanek[dlugoscTrasy];
        this.czasDojazdu = new int[dlugoscTrasy];
        this.dodanePrzystanki = 0;
        this.dodaneTramwaje = 0;
    }

    // Metoda dodająca przystanek do trasy linii wraz z czasem dojazdu
    public void dodajPrzystanek(Przystanek przystanek, int czasDojazdu) {
        przystanki[dodanePrzystanki] = przystanek; // Dodanie przystanku do tablicy
        this.czasDojazdu[dodanePrzystanki] = czasDojazdu; // Przypisanie czasu dojazdu do przystanku
        dodanePrzystanki++; // Zwiększenie licznika dodanych przystanków
    }

    // Metoda zwracająca numer linii
    public int getNumerLinii() {
        return numerLinii;
    }

    // Metoda zwracająca tablicę przystanków
    public Przystanek[] getPrzystanki() {
        return przystanki;
    }

    // Metoda zwracająca tablicę czasów dojazdu
    public int[] getCzasDojazdu() {
        return czasDojazdu;
    }

    // Metoda dodająca tramwaj na trasę linii
    public void dodajTramwaj(int numerBoczny, int pojemnosc, boolean zPierwKonca) {
        tramwaje[dodaneTramwaje] = new Tramwaj(numerBoczny, pojemnosc, this, zPierwKonca);
        dodaneTramwaje++;
    }

    // Metoda zwracająca pierwszy przystanek na trasie linii
    public Przystanek petla1() {
        return przystanki[0];
    }

    // Metoda zwracająca ostatni przystanek na trasie linii
    public Przystanek petla2() {
        return przystanki[dlugoscTrasy - 1];
    }

    // Metoda generująca rozkład jazdy tramwajów na podstawie podanego czasu
    public void generujRozkladJazdy(Godzina czas, KolejkaZdarzen kolejka) {
        for (int czasDojazdu : czasDojazdu) {
            odstepWyjazdu += 2 * czasDojazdu;
        }
        odstepWyjazdu = odstepWyjazdu / liczbaTramwajow;
        for (int i = 0; i < liczbaTramwajow; i++) {
            czas.setCzas(360 + i / 2  * odstepWyjazdu);
            tramwaje[i].wypuscNaTrase(czas, kolejka);
        }
    }

    // Metoda kończąca dzień - resetuje ustawienia tramwajów na linii
    public void koniecDnia() {
        for (Tramwaj tramwaj : tramwaje) tramwaj.koniecDnia();
    }
}
