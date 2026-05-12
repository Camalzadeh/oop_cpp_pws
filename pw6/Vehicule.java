public abstract class Vehicule {
    protected String brand;
    protected String model;
    protected double price;

    public Vehicule(String brand, String model, double price) {
        this.brand = brand;
        this.model = model;
        this.price = price;
    }

    public void afficher() {
        System.out.println("[Vehicle] brand:" + brand + ", model:" + model + " (daily price:" + price + " Eur)");
    }
}
