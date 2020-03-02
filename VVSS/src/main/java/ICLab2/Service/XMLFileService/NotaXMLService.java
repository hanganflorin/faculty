package ICLab2.Service.XMLFileService;

import ICLab2.Domain.*;
import ICLab2.Repository.XMLFileRepository.NotaXMLRepo;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class NotaXMLService extends AbstractXMLService<Integer,Nota>{
    private NotaXMLRepo xmlrepo;

    public NotaXMLService(NotaXMLRepo xmlrepo)  {
        super(xmlrepo);
    }

    public String depunctare(TemaLabXMLService srv,String idt,String val){
        TemaLab t=srv.findOne(Integer.parseInt(idt));
        System.out.println(t);
        //Nota n=this.findOne(Integer.parseInt(idn));
        //System.out.println(n);
        String val1=Double.toString(Double.parseDouble(val)-(t.getSaptammanaPredarii()-t.getTermenLimita())*2.5);
        System.out.println(val1);
        //Nota n1=new Nota(idn,n.getStudentId(),idt,n.getValoare()-(t.getSaptammanaPredarii()-t.getTermenLimita()),n.getLdt());
        return val1;
    }

    public void printAllNotes(TemaLabXMLService srv) throws IOException {
        DataOutputStream out = new DataOutputStream(new FileOutputStream("NoteStudenti.txt"));
        this.findAll().forEach(n-> {
            try {
                out.writeChars("Tema: "+n.getTemaLabId()+
                        "\nNota: "+n.getValoare()+
                        "\nPredata in saptamana: "+srv.findOne(n.getTemaLabId()).getSaptammanaPredarii()+
                        "\nDeadline: "+srv.findOne(n.getTemaLabId()).getTermenLimita()+
                        "\nFeedback: Se putea si mai bine!\n\n\n");
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

    }

    @Override
    protected Nota extractEntity(String[] params){
        Nota n=new Nota(Integer.parseInt(params[0]),params[1],Integer.parseInt(params[2]),Double.parseDouble(params[3]), LocalDateTime.parse(params[4], DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm")));
        return n;

    }

}