public class Przystanek {
    private int pojemnosc;
    private int zapelnienie;
    private String nazwa;
    private Pasazer[] pasazerowie;

    public Przystanek(int pojemnosc, String nazwa) {
        this.pojemnosc = pojemnosc;
        this.nazwa = nazwa;
        this.pasazerowie = new Pasazer[pojemnosc];
        this.zapelnienie = 0;
    }

    public void koniecOczekiwania(int dzien, Godzina czas, Symulacja symulacja) {
        for (int i = 0; i < zapelnienie; i++) {
            pasazerowie[i].koniecOczekiwania(dzien,czas,symulacja);
        }
    }

    public void dodajPasazera(Pasazer pasazer) {
        pasazerowie[zapelnienie] = pasazer;
        zapelnienie++;
    }

    public void usunPasazera() {
        zapelnienie--;
        pasazerowie[zapelnienie] = null;
    }

    public void pasazerowieWsiadaja(Tramwaj tramwaj, int dzien, Godzina godzina, Symulacja symulacja, boolean doPrzodu) {
        for (int i = zapelnienie - 1; i >= 0; i--) {
            if (tramwaj.wolneMiejsca()) pasazerowie[i].wsiadzDoTramwaju(tramwaj, dzien, godzina, symulacja, doPrzodu);
        }
    }

    public boolean pusty() {
        return zapelnienie == 0;
    }

    public boolean wolneMiejsca() {
        return zapelnienie < pojemnosc;
    }

    public String getNazwa() {
        return nazwa;
    }

    public void koniecDnia() {
        zapelnienie = 0;
        pasazerowie = new Pasazer[pojemnosc];
    }
}
