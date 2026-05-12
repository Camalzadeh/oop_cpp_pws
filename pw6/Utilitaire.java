public class Utilitaire extends Vehicule {
    private double volume;

    public Utilitaire(String brand, String model, double volume, double price) {
        super(brand, model, price);
        this.volume = volume;
        System.out.println("-> Utility vehicle " + brand + " " + model + " created");
    }

    @Override
    public void afficher() {
        System.out.println("[Utility vehicle] brand:" + brand + ", model:" + model + " (daily price: " + price + " Eur)  (" + volume + " m3)");
    }
}
