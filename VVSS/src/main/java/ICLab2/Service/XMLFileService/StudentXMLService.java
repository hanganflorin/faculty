package ICLab2.Service.XMLFileService;

import ICLab2.Domain.Student;
import ICLab2.Repository.XMLFileRepository.StudentXMLRepo;

public class StudentXMLService extends AbstractXMLService<String,Student>{
    private StudentXMLRepo xmlrepo;

    public StudentXMLService(StudentXMLRepo xmlrepo)  {
        super(xmlrepo);
    }

    @Override
    protected Student extractEntity(String[] params){
        int grupa=0;
        try{
            grupa=Integer.parseInt(params[2]);
        }catch(NumberFormatException ex){
            System.out.println(ex.getMessage());
        }
        return new Student(params[0],params[1],grupa,params[3],params[4]);
    }

}