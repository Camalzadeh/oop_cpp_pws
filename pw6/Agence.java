import java.util.ArrayList;
import java.util.List;

public class Agence {
    private String name;
    private List<Vehicule> fleet;

    public Agence(String name) {
        this.name = name;
        this.fleet = new ArrayList<>();
    }

    public void ajouterFlotte(Vehicule v) {
        fleet.add(v);
    }

    public void afficherFlotte() {
        for (Vehicule v : fleet) {
            v.afficher();
        }
    }

    public void close() {
        System.out.println(" -> The agency " + name + " closes its doors.");
    }
}
