package ICLab2.Repository.MemoryRepository;

import ICLab2.Domain.Student;
import ICLab2.Validator.IValidator;

public class StudentRepo extends AbstractCrudRepo<String, Student> {
    public StudentRepo(IValidator<Student> v){ super(v);
    }
}