public class koniecCzekania extends Zdarzenie{
    private Przystanek[] przystanki;

    public koniecCzekania() {
        this.godzina = new Godzina();
        godzina.setCzas(1440);
    };

    public void wykonaj(int dzien, Symulacja symulacja) {
        przystanki = symulacja.getPrzystanki();
        for (Przystanek przystanek : przystanki) {
            przystanek.koniecOczekiwania(dzien, godzina, symulacja);
        }
    }
}
