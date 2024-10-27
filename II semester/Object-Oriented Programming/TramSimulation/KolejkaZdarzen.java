public interface KolejkaZdarzen {
    public void start(int dzien, Symulacja symulacja);
    public void dodajZdarzenie(Zdarzenie zdarzenie);
    public void sortuj();
    public void koniecDnia();
}
