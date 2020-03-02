package ICLab2.Repository.TxtFileRepository;

import ICLab2.Domain.HasId;
import ICLab2.Repository.MemoryRepository.AbstractCrudRepo;
import ICLab2.Validator.IValidator;
import ICLab2.Exceptions.ValidatorException;
import ICLab2.Exceptions.RepositoryException;
import java.io.IOException;
import java.io.*;

public abstract class AbstractFileRepository<ID,E extends HasId<ID>> extends AbstractCrudRepo<ID,E> {
    private String filename;

    public AbstractFileRepository(IValidator v,String filename) {
        super(v);
        this.filename=filename;
        //readFromFile();
    }

    private void writeAll() throws IOException{
        DataOutputStream out = new DataOutputStream(new FileOutputStream(filename));
        super.findAll().forEach(x-> { try { out.writeChars(x.toString()); } catch (IOException e) { e.printStackTrace(); } });

    }
    private void writeToFile(E entity)throws IOException {
        DataOutputStream out = new DataOutputStream(new FileOutputStream(filename));
        out.writeChars(entity.toString());
    }

    private void readFromFile() throws IOException, ValidatorException {
        DataInputStream in = new DataInputStream(new FileInputStream(filename));
        String line;
        while((line=in.readUTF())!=null){
            String[] info=line.split("#");
            E e=extractEntity(info);
            E saved = super.save(e);

        }

    }

    public abstract E extractEntity(String[] info);
    @Override
    public E findOne(ID id) {
        return super.findOne(id);
    }

    @Override
    public Iterable<E> findAll() {
        return super.findAll();
    }
    @Override
    public E save(E entity) throws ValidatorException {
        try{
            E e=super.save(entity);
           // writeToFile(entity);
            writeAll();
            return e;
        }
        catch (IOException ex){
            throw new RepositoryException("The file "+filename+" cannot be found!\n");
        }
    }

    @Override
    public E delete(ID id) {
        try{
            E e=super.delete(id);
            writeAll();
            return e;
        }
        catch (IOException ex){
            throw new RepositoryException("The file "+filename+" cannot be found!\n");
        }
    }

    @Override
    public E update(E entity) {
        try{
            E e= super.update(entity);
            writeAll();
            return e;
        }catch (IOException ex){
            throw  new RepositoryException("The file "+filename+" cannot be found!\n");
        }
    }


}