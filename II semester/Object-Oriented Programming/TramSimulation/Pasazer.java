public class Pasazer {
    private int id;
    private Przystanek przystanek;
    private Przystanek przystanekDocelowy;
    private Godzina godzinaStartuOczekiwania;

    public Pasazer(Przystanek[] przystanki, int id) {
        this.przystanek = przystanki[Losowanie.losuj(0, przystanki.length - 1)];
        this.id = id;
        this.godzinaStartuOczekiwania = new Godzina();
    }

    public void losujGodzine() {
        this.godzinaStartuOczekiwania.setCzas(Losowanie.losuj(360, 720));
    }

    public void koniecOczekiwania(int dzien, Godzina godzina, Symulacja symulacja) {
        symulacja.dodajCzasOczekiwania(dzien, godzina.getCzas() - godzinaStartuOczekiwania.getCzas());
    }

    public void wypiszPasazera() {
        System.out.println("Przystanek: " + przystanek.getNazwa());
    }

    public void idzNaPrzystanek (KolejkaZdarzen kolejka) {
        losujGodzine();
        kolejka.dodajZdarzenie(new PasazerNaPrzystanek(przystanek, godzinaStartuOczekiwania, this));
    }

    public void wsiadzDoTramwaju(Tramwaj tramwaj, int dzien, Godzina godzina, Symulacja symulacja, boolean doPrzodu) {
        losujPrzystanek(tramwaj, doPrzodu);
        tramwaj.pasazerWsiada(this);
        przystanek.usunPasazera();
        System.out.println(dzien + ", " + godzina.getGodzina() + ": Pasazer " + id + " wsiadł do tramwaju linii "
                + tramwaj.getLinia().getNumerLinii() + " (nr bocz." + tramwaj.getNumerBoczny() + ") na przystanku "
                + przystanek.getNazwa() + " z zamiarem dojechania do " + przystanekDocelowy.getNazwa());
        symulacja.dodajPrzejazd(dzien);
        symulacja.dodajCzasOczekiwania(dzien, godzina.getCzas() - godzinaStartuOczekiwania.getCzas());
    }

    public void wysiadzZTramwaju(Tramwaj tramwaj, int dzien, Przystanek przystanekTramwaju, Godzina godzina) {
        if (przystanekTramwaju == przystanekDocelowy) {
            tramwaj.pasazerWysiada(this);
            przystanek = przystanekTramwaju;
            przystanekTramwaju.dodajPasazera(this);
            System.out.println(dzien + ", " + godzina.getGodzina() + ": Pasazer " + id + " wysiadł z tramwaju linii "
                    + tramwaj.getLinia().getNumerLinii() + " (nr bocz." + tramwaj.getNumerBoczny() + ") na przystanku "
                    + przystanekDocelowy.getNazwa());
        }
        godzinaStartuOczekiwania.setCzas(godzina.getCzas());
    }

    public void losujPrzystanek(Tramwaj tramwaj, boolean doPrzodu) {
        Przystanek[] przystanki = tramwaj.pozostale(przystanek, doPrzodu);
        int i = Losowanie.losuj(0, przystanki.length - 1);
        przystanekDocelowy = przystanki[i];
    }

    public int getId() {
        return id;
    }
}
