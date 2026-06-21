interface Animal {
    void sound();
}

class Dog implements Animal {
    @Override
    public void sound() {
        System.out.println("Dog says: Woof!");
    }
}

class Cat implements Animal {
    @Override
    public void sound() {
        System.out.println("Cat says: Meow!");
    }
}

class Cow implements Animal {
    @Override
    public void sound() {
        System.out.println("Cow says: Moo!");
    }
}

class Lion implements Animal {
    @Override
    public void sound() {
        System.out.println("Lion says: Roar!");
    }
}

public class p10 {
    public static void main(String[] args) {
        Animal a1 = new Dog();
        Animal a2 = new Cat();
        Animal a3 = new Cow();
        Animal a4 = new Lion();

        a1.sound();
        a2.sound();
        a3.sound();
        a4.sound();
    }
}
