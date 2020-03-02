package ICLab2.Domain;

import ICLab2.Domain.HasId;

public class TemaLab implements HasId<Integer> {
    private int nr;
    private String descriere;
    private int termenLimita;
   // private int saptamanaCurenta;
    private int saptammanaPredarii;
    public TemaLab(int nr,String descriere,int termenLimita,int saptammanaPredarii){
        this.setId(nr);
        this.setDescriere(descriere);
        this.setTermenLimita(termenLimita);
        //this.setSaptamanaCurenta(saptamanaCurenta);
        this.setSaptammanaPredarii(saptammanaPredarii);
    }
    @Override
    public Integer getId() {
        return nr;
    }
    @Override
    public void setId(Integer nr) {
        this.nr = nr;
    }

    public String getDescriere() {
        return descriere;
    }

    public void setDescriere(String descriere) {
        this.descriere = descriere;
    }

    public int getTermenLimita() {
        return termenLimita;
    }

    public void setTermenLimita(int termenLimita) {
        this.termenLimita = termenLimita;
    }

    public int getSaptammanaPredarii() {
        return saptammanaPredarii;
    }

    public void setSaptammanaPredarii(int saptammanaPredarii) {
        this.saptammanaPredarii = saptammanaPredarii;
    }
    @Override
    public String toString(){
        return this.nr+"#"+this.descriere+"#"+this.termenLimita+"#"+this.saptammanaPredarii;
    }

    //public int getSaptamanaCurenta() { return saptamanaCurenta; }

    //public void setSaptamanaCurenta(int saptamanaCurenta) {this.saptamanaCurenta = saptamanaCurenta;}
}
