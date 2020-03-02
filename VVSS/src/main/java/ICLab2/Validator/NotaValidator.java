package ICLab2.Validator;


import ICLab2.Domain.Nota;
import ICLab2.Exceptions.ValidatorException;

public class NotaValidator implements IValidator<Nota> {

    public void validate(Nota n) throws ValidatorException {
        String errors="";
        if(n.getId()<=0){
            errors+="Id invalid\n";
        }
        if(n.getStudentId().equals("") || n.getStudentId()==null){
            errors+="Id student invalid\n";
        }
        if(n.getTemaLabId()<=0){
            errors+="Id tema invalid\n";
        }
        if(n.getValoare()<=0 || n.getValoare()>10 ){
            errors+="Valoare invalida\n";
        }
        if (errors.length()!=0){
            throw  new ValidatorException(errors);
        }
    }
}