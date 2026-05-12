public class Voiture extends Vehicule {
    private int doors;

    public Voiture(String brand, String model, int doors, double price) {
        super(brand, model, price);
        this.doors = doors;
        System.out.println("-> Car " + brand + " " + model + " created");
    }

    @Override
    public void afficher() {
        System.out.println("[Car] brand:" + brand + ", model:" + model + " (daily price: " + price + " Eur)  (" + doors + " doors)");
    }
}
