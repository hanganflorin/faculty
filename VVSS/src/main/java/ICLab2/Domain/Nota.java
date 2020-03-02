package ICLab2.Domain;

import java.time.LocalDateTime;

public class Nota implements HasId<Integer> {

    //private Pair<String,Integer> idNota;
    private Integer idNota;
    private String studentId;
    private Integer temaLabId;
    private double valoare;
    private LocalDateTime ldt;

    public  Nota(Integer idNota,String studentId,Integer temaLabId,double valoare,LocalDateTime ldt){
        this.idNota=idNota;
        this.studentId=studentId;
        this.temaLabId=temaLabId;
        this.valoare=valoare;
        this.ldt=ldt;
    }

    @Override
    public Integer getId() {
        return idNota;
    }

    @Override
    public void setId(Integer id) {
        this.idNota=id;
    }

    public String getStudentId() {
        return studentId;
    }

    public void setStudentId(String studentId) {
        this.studentId = studentId;
    }

    public Integer getTemaLabId() {
        return temaLabId;
    }

    public void setTemaLabId(Integer temaLabId) {
        this.temaLabId = temaLabId;
    }

    public double getValoare() {
        return valoare;
    }

    public void setValoare(double valoare) {
        this.valoare = valoare;
    }

    public LocalDateTime getLdt() {
        return ldt;
    }

    public void setLdt(LocalDateTime ldt) {
        this.ldt = ldt;
    }

    @Override
    public String toString(){
        return this.idNota+"#"+this.studentId+"#"+this.temaLabId+"#"+this.valoare+"#"+this.ldt;
    }
}
