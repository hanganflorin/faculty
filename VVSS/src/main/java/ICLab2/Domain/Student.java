package ICLab2.Domain;

public class Student implements HasId<String> {
    private  String id;
    private  String nume;
    private int grupa;
    private String email;
    private String indrumator;
    public Student(String id,String nume,int grupa, String email, String indrumator){
        this.setId(id);
        this.setNume(nume);
        this.setGrupa(grupa);
        this.setEmail(email);
        this.setIndrumator(indrumator);
    }
    @Override
    public String getId() {
        return id;
    }
    @Override
    public void setId(String id) {
        this.id = id;
    }
    public String getNume() {
        return nume;
    }
    public void setNume(String nume) {
        this.nume = nume;
    }
    public int getGrupa() {
        return grupa;
    }
    public void setGrupa(int grupa) {
        this.grupa = grupa;
    }
    public String getEmail() {
        return email;
    }
    public void setEmail(String email) {
        this.email = email;
    }
    public String getIndrumator() {
        return indrumator;
    }
    public void setIndrumator(String indrumator) {
        this.indrumator = indrumator;
    }
    @Override
    public String toString(){
        return this.id+"#"+this.nume+"#"+this.grupa+"#"+this.email+"#"+this.indrumator;
    }
}
