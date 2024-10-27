import java.util.Random;

abstract public class Losowanie {
    public static int losuj(int dolna, int gorna){
        Random rand = new Random();
        assert dolna <= gorna : "Błąd: dolna granica musi być mniejsza lub równa górnej";
        return rand.nextInt(gorna - dolna + 1) + dolna;
    }
}
