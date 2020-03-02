package ICLab2.Exceptions;


public class ServiceException extends RuntimeException {
    String message;
    public ServiceException(String message){
        this.message=message;
    }
    public String getMessage(){
        return this.message;
    }
}