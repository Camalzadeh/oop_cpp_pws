public class Main {
    public static void main(String[] args) {
        Agence malocation = new Agence("MaLocation");

        malocation.ajouterFlotte(new Utilitaire("Mercedes", "Vito", 9.0, 50.0));
        malocation.ajouterFlotte(new Utilitaire("Peugeot", "Master", 9.0, 45.0));
        malocation.ajouterFlotte(new Utilitaire("Renault", "Kangoo", 4.0, 35.0));

        malocation.ajouterFlotte(new Voiture("Peugeot", "207", 5, 25.0));
        malocation.ajouterFlotte(new Voiture("Renault", "Clio", 3, 25.0));

        malocation.afficherFlotte();

        malocation.close();
    }
}
