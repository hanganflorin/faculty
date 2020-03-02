package ICLab2.Repository.MemoryRepository;


import ICLab2.Domain.Nota;
import ICLab2.Validator.IValidator;

public class NotaRepo extends AbstractCrudRepo<Integer, Nota> {
    public NotaRepo(IValidator<Nota> v){ super(v);
    }
}