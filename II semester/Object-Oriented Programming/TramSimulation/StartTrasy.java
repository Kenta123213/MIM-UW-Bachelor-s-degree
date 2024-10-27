public class StartTrasy extends Zdarzenie{
    private Tramwaj tramwaj;
    private boolean doPrzodu;

    public StartTrasy(Przystanek przystanek, Godzina godzina, Tramwaj tramwaj, boolean doPrzodu) {
        this.przystanek = przystanek;
        this.godzina = new Godzina();
        this.godzina.setCzas(godzina.getCzas());
        this.tramwaj = tramwaj;
        this.doPrzodu = doPrzodu;
    }

    public void wykonaj(int dzien, Symulacja symulacja) {
        System.out.println(dzien + ", " + godzina.getGodzina() + " tramwaj lini " + tramwaj.getLinia().getNumerLinii() +
                " (o nr bocz." + tramwaj.getNumerBoczny() + ") zatrzymał się na przystanku " + przystanek.getNazwa());
        przystanek.pasazerowieWsiadaja(tramwaj, dzien, godzina, symulacja, doPrzodu);
    }
}

