public class PasazerNaPrzystanek extends Zdarzenie{
    private Pasazer pasazer;

    public PasazerNaPrzystanek(Przystanek przystanek, Godzina godzina, Pasazer pasazer) {
        this.przystanek = przystanek;
        this.godzina = godzina;
        this.pasazer = pasazer;
    }

    public void wypisz() {
        System.out.println("Pasazer " + pasazer.getId() + " przystanek " + przystanek.getNazwa() +
                " o godzinie " + godzina.getGodzina());
    }

    public void wykonaj(int dzien, Symulacja symulacja) {
        if (przystanek.wolneMiejsca())
        {
            przystanek.dodajPasazera(pasazer);
            System.out.println(dzien + ", " + godzina.getGodzina() + " pasazer " + pasazer.getId() +
                    " przyszedł na przystanek " + przystanek.getNazwa());
        }
        else {
            System.out.println(dzien + ", " + godzina.getGodzina() + " pasazer " + pasazer.getId() +
                    " przyedł na przystanek " + przystanek.getNazwa() +
                    " ale z powodu braku wolnych miejsc wrócił do domu");
        }
    }
}
