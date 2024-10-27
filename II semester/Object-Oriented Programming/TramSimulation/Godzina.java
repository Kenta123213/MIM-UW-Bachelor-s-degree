public class Godzina {
    private int czas; //ilosc minut od polnocy
    public Godzina() {
        czas = 0;
    }

    public int getCzas() {
        return czas;
    }

    public String getGodzina() {
        if (czas % 60 < 10) return czas / 60 + ":0" + czas % 60;
        else return czas / 60 + ":" + czas % 60;
    }

    public void setCzas(int czas) {
        this.czas = czas;
    }

    public void dodajMinuty(int minuty) {
        czas += minuty;
    }

    public void wypiszCzas() {
        System.out.println(czas / 60 + ":" + czas % 60);
    }
}
