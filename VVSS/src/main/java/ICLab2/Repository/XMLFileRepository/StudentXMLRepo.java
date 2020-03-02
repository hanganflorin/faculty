package ICLab2.Repository.XMLFileRepository;

import ICLab2.Domain.Student;
import ICLab2.Validator.StudentValidator;
import org.w3c.dom.Document;
import org.w3c.dom.Element;


public class StudentXMLRepo extends AbstractXMLRepo<String, Student> {
    //private String fileName;

    public StudentXMLRepo(StudentValidator v, String fileName) {
        super(v,fileName);
    }

    @Override
    protected Element createElementFromEntity(Document document,Student s) {
        Element root = document.getDocumentElement();
        Element e = document.createElement("student");
        e.appendChild(createElement("id", document, s.getId()));
        e.appendChild(createElement("nume", document, s.getNume()));
        e.appendChild(createElement("grupa", document, Integer.toString(s.getGrupa())));
        e.appendChild(createElement("email", document, s.getEmail()));
        e.appendChild(createElement("profesor", document, s.getIndrumator()));
        return e;
    }


    @Override
    protected Student createEntityFromElement(Element studentElement){
        String id=studentElement
                .getAttribute("id");
        String nume=studentElement
                .getElementsByTagName("nume")
                .item(0)
                .getTextContent();
        String grupa=studentElement
                .getElementsByTagName("grupa")
                .item(0)
                .getTextContent();
        int gr=Integer.parseInt(grupa);
        String email=studentElement
                .getElementsByTagName("email")
                .item(0)
                .getTextContent();
        String prof=studentElement
                .getElementsByTagName("prof")
                .item(0)
                .getTextContent();
        return new Student(id,nume,gr,email,prof);
    }

}

