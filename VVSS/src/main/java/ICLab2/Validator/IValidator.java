package ICLab2.Validator;

import ICLab2.Exceptions.ValidatorException;

public interface IValidator<E> {
    void validate(E entity) throws ValidatorException;
}