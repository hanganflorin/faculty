package ICLab2;

import ICLab2.Exceptions.ValidatorException;
import ICLab2.Repository.XMLFileRepository.NotaXMLRepo;
import ICLab2.Repository.XMLFileRepository.StudentXMLRepo;
import ICLab2.Repository.XMLFileRepository.TemaLabXMLRepo;
import ICLab2.Service.XMLFileService.NotaXMLService;
import ICLab2.Service.XMLFileService.StudentXMLService;
import ICLab2.Service.XMLFileService.TemaLabXMLService;
import ICLab2.UI.ui;
import ICLab2.Validator.NotaValidator;
import ICLab2.Validator.StudentValidator;
import ICLab2.Validator.TemaLabValidator;

import java.io.IOException;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args ) throws IOException, ValidatorException
    {
        //System.out.println("Hello World!");
        StudentValidator vs=new StudentValidator();
        TemaLabValidator vt=new TemaLabValidator();
        NotaValidator vn=new NotaValidator();
        StudentXMLRepo strepo=new StudentXMLRepo(vs,"StudentiXML.xml");
        TemaLabXMLRepo tmrepo=new TemaLabXMLRepo(vt,"TemaLaboratorXML.xml");
        NotaXMLRepo ntrepo=new NotaXMLRepo(vn,"NotaXML.xml");
        StudentXMLService stsrv=new StudentXMLService(strepo);
        TemaLabXMLService tmsrv=new TemaLabXMLService(tmrepo);
        NotaXMLService ntsrv=new NotaXMLService(ntrepo);
        ui ui=new ui(stsrv,tmsrv,ntsrv);
        ui.run();System.out.println( "Hello World!" );
    }
}
