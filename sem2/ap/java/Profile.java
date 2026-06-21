import java.io.Serializable;

class Profile implements Serializable {
    private static final long serialVersionUID = 1L;

    private String name;
    private int age;
    private double avgMarks;

    public Profile(String name, int age, double avgMarks) {
        this.name = name;
        this.age = age;
        this.avgMarks = avgMarks;
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    public double getAvgMarks() {
        return avgMarks;
    }

    @Override
    public String toString() {
        return "Name: " + name + ", Age: " + age + ", Average Marks: " + avgMarks;
    }
}
