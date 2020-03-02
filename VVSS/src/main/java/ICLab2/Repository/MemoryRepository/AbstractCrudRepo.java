package ICLab2.Repository.MemoryRepository;



import ICLab2.Domain.HasId;
import ICLab2.Exceptions.ValidatorException;
import ICLab2.Repository.Repo;
import ICLab2.Validator.IValidator;

import java.util.*;
public abstract class AbstractCrudRepo<ID,E extends HasId<ID>> implements Repo<ID,E> {
    Map<ID,E> entityes;
    IValidator<E> validator;
    public AbstractCrudRepo(IValidator v){
        entityes=new HashMap<ID,E>();
        validator=v;
    }
    @Override
    public E findOne(ID id){
        if (entityes.get(id)==null){
            return null;
        }else{
            if(id==null){
                throw new IllegalArgumentException();
            }else{
                return entityes.get(id);
            }
        }

    }

    @Override
    public Iterable<E> findAll(){
        return entityes.values();
    }
    @Override
    public E save(E entity) throws ValidatorException {
        if(entity==null){
            throw new IllegalArgumentException("Entity can not be null!\n");
        }
        try{
            validator.validate(entity);
            return entityes.putIfAbsent(entity.getId(),entity);
        }catch(ValidatorException ex){
            throw new ValidatorException(ex.getMessage());
        }
    }
    @Override
    public E delete(ID id){
        return entityes.remove(id);
    }
    @Override
    public E update(E entity) {
        try {
            if (entity == null) {
                throw new IllegalArgumentException("Entity can not be null!\n");
            } else {
                validator.validate(entity);
                return entityes.replace(entity.getId(), entity);
            }
        }catch(ValidatorException e){
            return null;
        }
    }
    //@Override
    public long size(){
        return entityes.size();
    }

}