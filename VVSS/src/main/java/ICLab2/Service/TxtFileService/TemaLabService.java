package ICLab2.Service.TxtFileService;
import ICLab2.Exceptions.ValidatorException;
import ICLab2.Domain.*;
import ICLab2.Repository.TxtFileRepository.TemaLabFileRepo;

public class TemaLabService extends AbstractService<Integer,TemaLab> {
    //StudentFileRepo stdRepo;
    public TemaLabService(TemaLabFileRepo tmLbRepo){
        super(tmLbRepo);
    }

    public void prelungireTemaLab(String nr,String descr,String sl,String sp,int sc) throws ValidatorException {
        if(sc<=Integer.parseInt(sp)){
            String sln=Integer.toString(Integer.parseInt(sl)+1) ;
            String[] params={nr,descr,sln,sp};
            upd(params);
        }

    }
    /*
    @Override
    public Student extractEntity(String[] info){
        return new Student("","",2,"","");
    }
    */
}
