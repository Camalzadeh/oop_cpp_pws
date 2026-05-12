public class Fraction {
    private int num;
    private int den;

    public Fraction() {
        this.num = 1;
        this.den = 1;
    }

    public Fraction(int num, int den) {
        this.num = num;
        this.den = (den == 0) ? 1 : den;
    }

    public Fraction(Fraction f) {
        this.num = f.num;
        this.den = f.den;
    }

    private int pgcd(int a, int b) {
        a = Math.abs(a);
        b = Math.abs(b);
        if (b == 0) return a;
        int r = a % b;
        if (r == 0) return b;
        else return pgcd(b, r);
    }

    public Fraction add(Fraction f) {
        return new Fraction(this.num * f.den + f.num * this.den, this.den * f.den);
    }

    public Fraction multiply(Fraction f) {
        return new Fraction(this.num * f.num, this.den * f.den);
    }

    public Fraction simplify() {
        if (num == 0) return new Fraction(0, 1);
        int common = pgcd(num, den);
        return new Fraction(num / common, den / common);
    }

    public void display() {
        System.out.println(num + "/" + den);
    }

    public static void main(String[] args) {
        System.out.println("--- Java Version ---");
        Fraction f1 = new Fraction(1, 2);
        Fraction f2 = new Fraction(3, 5);

        Fraction f3;
        f3 = f1.add(f2);
        System.out.print("f1 + f2: ");
        f3.display();

        Fraction f4;
        f4 = f1.multiply(f3);
        System.out.print("f1 * f3: ");
        f4.display();
        
        System.out.print("f4 simplified: ");
        f4.simplify().display();
    }
}
