package ICLab2.Service.TxtFileService;
import ICLab2.Domain.*;
import ICLab2.Repository.TxtFileRepository.NotaFileRepo;

public class NotaService extends AbstractService<Integer,Nota> {
    public NotaService(NotaFileRepo notaRepo){
        super(notaRepo);
    }
}
