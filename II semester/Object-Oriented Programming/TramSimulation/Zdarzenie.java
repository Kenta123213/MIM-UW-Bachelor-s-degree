abstract public class Zdarzenie {
    protected Przystanek przystanek;
    protected Godzina godzina;

    public Godzina getGodzina() {
        return godzina;
    }

    abstract public void wykonaj(int dzien, Symulacja symulacja);
}
