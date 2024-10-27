import java.util.Scanner;

public class Symulacja {
    private int liczbaDniSym;
    private int dzien;
    private int liczbaPrzystankow;
    private Przystanek[] przystanki;
    private int liczbaPasazerow;
    private Pasazer[] pasazerowie;
    private Linia[] linie;
    private int liczbaLinii;
    private int numerBoczny;
    private KolejkaZdarzen kolejka;
    private DaneDnia[] daneDnia;

    public Symulacja () {
        numerBoczny = 0;
        dzien = 0;
        Scanner sc = new Scanner(System.in);
        liczbaDniSym = sc.nextInt();
        int pojemnoscPrzystanku = sc.nextInt();
        liczbaPrzystankow = sc.nextInt();
        przystanki = new Przystanek[liczbaPrzystankow];
        for (int i = 0; i < liczbaPrzystankow; i++) {
            przystanki[i] = new Przystanek(pojemnoscPrzystanku, sc.next());
        }
        liczbaPasazerow = sc.nextInt();
        generujPasazerow();
        int pojemnoscTramwaju = sc.nextInt();
        liczbaLinii = sc.nextInt();
        wygenerujLinie(pojemnoscTramwaju);
        daneDnia = new DaneDnia[liczbaDniSym];
        kolejka = new Kolejka(this);
    }

    public void dodajPrzejazd(int dzien) {
        daneDnia[dzien].dodajPrzejazd();
    }

    public Przystanek[] getPrzystanki() {
        return przystanki;
    }

    public void dodajCzasOczekiwania(int dzien, int minuty) {
        daneDnia[dzien].dodajCzasOczekiwania(minuty);
    }

    private void wygenerujLinie(int pojemnoscTramwaju){
        Scanner sc = new Scanner(System.in);
        int liczbaTramwajowLinii;
        int dlugoscTrasy;
        linie = new Linia[liczbaLinii];
        for (int i = 0; i < liczbaLinii; i++){
            liczbaTramwajowLinii = sc.nextInt();
            dlugoscTrasy = sc.nextInt();
            linie[i] = new Linia(i, liczbaTramwajowLinii, dlugoscTrasy);
            for (int j = 0; j < dlugoscTrasy; j++){
                String temp = sc.next();
                Przystanek p = null;
                for (Przystanek przystanek : przystanki) {
                    if (przystanek.getNazwa().equals(temp)){p = przystanek;}
                }
                linie[i].dodajPrzystanek(p, sc.nextInt());
            }
            for (int j = 0; j < liczbaTramwajowLinii; j++){
                linie[i].dodajTramwaj(numerBoczny, pojemnoscTramwaju, j % 2 == 0);
                numerBoczny++;
            }
        }
    }

    private void generujPasazerow() {
        pasazerowie = new Pasazer[liczbaPasazerow];
        for (int i = 0; i < liczbaPasazerow; i++) {
            pasazerowie[i] = new Pasazer(przystanki, i);
        }
    }

    public void startSymulacji() {
        for (int i = 0; i < liczbaDniSym; i++) {
            daneDnia[i] = new DaneDnia(i);
            startDnia();
            koniecDnia();
            dzien++;
        }
    }

    public void startDnia() {
        for (Pasazer pasazer : pasazerowie) {
            pasazer.idzNaPrzystanek(kolejka);
        }
        for (Linia linia : linie) {
            linia.generujRozkladJazdy(new Godzina(), kolejka);
        }
        kolejka.dodajZdarzenie(new koniecCzekania());
        kolejka.sortuj();
        kolejka.start(dzien, this);
    }

    public void koniecDnia() {
        for (Linia linia : linie ) linia.koniecDnia();
        for (Przystanek przystanek : przystanki) przystanek.koniecDnia();
        kolejka.koniecDnia();
    }

    public void wypiszDane() {
        int lacznaLiczbaPrzejazdow = 0;
        float lacznyCzasOczekiwania = 0;
        for (DaneDnia dane: daneDnia) {
            lacznaLiczbaPrzejazdow += dane.getiloscPrzejazdow();
            lacznyCzasOczekiwania += dane.getLacznyCzasOczekiwania();
            dane.wypisz();
        }
        if (liczbaDniSym != 0) System.out.println("W całej symulacji łączna ilość przejazdów to: "
                + lacznaLiczbaPrzejazdow + " a średni czas oczekiwania wyniósł: "
                + String.format("%.2f", lacznyCzasOczekiwania/lacznaLiczbaPrzejazdow) + " minut.");
        else System.out.println("W całej symulacji łączna ilość przejazdów to: "
                + lacznaLiczbaPrzejazdow + " a średni czas oczekiwania wyniósł: brak danych ");
    }
}
