public class Tramwaj extends Pojazd {

    private Linia linia;
    private Przystanek przystanek;
    private boolean doPrzodu;
    private Przystanek[] przystanki;
    private int[] czasDojazdu;
    private Pasazer[] pasazerowie;

    public Tramwaj(int numerBoczny, int pojemnosc, Linia linia, boolean doPrzodu){
        this.numerBoczny = numerBoczny;
        this.pojemnosc = pojemnosc;
        this.linia = linia;
        if (doPrzodu) {przystanek = linia.petla1();}
        else {przystanek = linia.petla2();}
        this.doPrzodu = doPrzodu;
        this.przystanki = linia.getPrzystanki();
        this.czasDojazdu = linia.getCzasDojazdu();
        this.zapelnienie = 0;
        this.pasazerowie = new Pasazer[pojemnosc];
    }

    public boolean wolneMiejsca() {
        return zapelnienie < pojemnosc;
    }

    public boolean pusty() {
        return zapelnienie == 0;
    }

    public int getNumerBoczny() {
        return numerBoczny;
    }

    public Linia getLinia() {
        return linia;
    }

    public Przystanek getPrzystanek() {
        return przystanek;
    }

    public Przystanek[] pozostale(Przystanek przystanekAktualny, boolean doPrzoduAktualne) {
        Przystanek[] pozostale;
        int i = 0;
        while (przystanki[i] != przystanekAktualny) i++;
        if (i == 0)
        {
            pozostale = new Przystanek[przystanki.length - 1];
            for (int j = 0; j < przystanki.length - 1; j++)
            {
                pozostale[j] = przystanki[j + 1];
            }
        }
        else if (i == przystanki.length - 1) {
            pozostale = new Przystanek[przystanki.length - 1];
            for (int j = 0; j < przystanki.length - 1; j++) {
                pozostale[j] = przystanki[j];
            }
        }
        else {
            if (doPrzoduAktualne){
                int k = 0;
                pozostale = new Przystanek[przystanki.length - i - 1];
                for (int j = i + 1; j < przystanki.length; j++) {
                    pozostale[k] = przystanki[j];
                    k++;
                }
            }
            else {
                pozostale = new Przystanek[i];
                for (int j = 0; j < i; j++) {
                    pozostale[j] = przystanki[j];
                }
            }
        }
        return pozostale;
    }

    public void pasazerowieWysiadaja(int dzien, Przystanek przystanek, Godzina godzina) {
        for (Pasazer pasazer : pasazerowie) {
            if (pasazer != null && przystanek.wolneMiejsca()) {
                pasazer.wysiadzZTramwaju(this, dzien, przystanek, godzina);
            }
        }
    }

    public void pasazerWsiada(Pasazer pasazer) {
        int i = 0;
        while (pasazerowie[i] != null) i++;
        pasazerowie[i] = pasazer;
        zapelnienie++;
    }

    public void pasazerWysiada(Pasazer pasazer){
        int i = 0;
        while (pasazerowie[i] != pasazer) i++;
        pasazerowie[i] = null;
        zapelnienie--;
    }

    public void wypuscNaTrase(Godzina czas, KolejkaZdarzen kolejka) {
        while (czas.getCzas() <= 1380) przejedzTrase(czas, kolejka);
    }

    public void przejedzTrase(Godzina czas, KolejkaZdarzen kolejka) {
        kolejka.dodajZdarzenie(new StartTrasy(przystanek, czas, this, doPrzodu));
        czas.dodajMinuty(czasNaNastepny());
        nastepnyPrzystanek();
        for (int i = 0; i < 2 * (przystanki.length - 1) - 1; i++){
            if (czyPetla()) kolejka.dodajZdarzenie(new KoniecTrasy(przystanek, czas, this, doPrzodu));
            else kolejka.dodajZdarzenie(new PostojTramwaju(przystanek, czas, this, doPrzodu));
            if (czyPetla()) {
                postojNaPetli(czas);
                kolejka.dodajZdarzenie(new StartTrasy(przystanek, czas, this, doPrzodu));
            }
            czas.dodajMinuty(czasNaNastepny());
            przejedzNaNastepny();
        }
        kolejka.dodajZdarzenie(new KoniecTrasy(przystanek, czas, this, doPrzodu));
        postojNaPetli(czas);
        zmienKierunek();
    }

    public void zmienKierunek() {
        doPrzodu = !doPrzodu;
    }

    public void postojNaPetli(Godzina czas) {
        czas.dodajMinuty(czasDojazdu[czasDojazdu.length - 1]);
    }

    private int czasNaNastepny() {
        int i = 0;
        while (przystanek != przystanki[i]) i++;
        if (doPrzodu) {
            if (i != przystanki.length - 1) return czasDojazdu[i];
            else return czasDojazdu[czasDojazdu.length - 2];
        }
        else {
            if (i != 0) return czasDojazdu[i - 1];
            else return czasDojazdu[0];
        }
    }

    public void nastepnyPrzystanek() {
        int i = 0;
        while (przystanek != przystanki[i]) i++;
        if (doPrzodu) {
            if (i != przystanki.length - 1) przystanek = przystanki[i + 1];
            else przystanek = przystanki[przystanki.length - 2];
        }
        else {
            if (i != 0) przystanek = przystanki[i - 1];
            else przystanek = przystanki[1];
        }
    }

    public boolean czyPetla() {
        int i = 0;
        while (przystanek != przystanki[i]) i++;
        return i == przystanki.length - 1 || i == 0;
    }

    public void przejedzNaNastepny() {
        boolean temp = czyPetla();
        nastepnyPrzystanek();
        if (temp) zmienKierunek();
    }

    public void koniecDnia() {
        this.zapelnienie = 0;
        this.pasazerowie = new Pasazer[pojemnosc];
    }
}
