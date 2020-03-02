package ICLab2.Repository.XMLFileRepository;

import ICLab2.Domain.HasId;
import ICLab2.Exceptions.ValidatorException;
import ICLab2.Repository.MemoryRepository.AbstractCrudRepo;
import ICLab2.Validator.IValidator;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

public abstract class AbstractXMLRepo<ID,E extends HasId<ID>> extends AbstractCrudRepo<ID,E> {
    private String fileName;

    public AbstractXMLRepo(IValidator v, String fileName) {
        super(v);
        this.fileName = fileName;
        loadFromFile();
    }

    protected abstract E createEntityFromElement(Element entityElement);

    protected abstract Element createElementFromEntity(Document document,E e);

    protected Element createElement(String tag, Document doc, String value){
        Element e = (Element) doc.createElement(tag);
        e.setTextContent(value);
        Element root = doc.getDocumentElement();
        return e;
    }

    private void loadFromFile() {
        try {
            Document document = DocumentBuilderFactory
                    .newInstance()
                    .newDocumentBuilder()
                    .parse(this.fileName);

            Element root=document.getDocumentElement();
            NodeList children=root.getChildNodes();
            for(int i=0;i<children.getLength();i++){
                Node entityElement=children.item(i);
                if(entityElement instanceof Element){
                    E e=createEntityFromElement((Element)entityElement);
                    super.save(e);
                }
            }
        }catch (Exception ex){

        }
    }

    private void writeAll(){
        try{
            Document document=DocumentBuilderFactory
                    .newInstance()
                    .newDocumentBuilder()
                    .newDocument();
            Element root=document.createElement("inbox");
            document.appendChild(root);
            super.findAll().forEach(s->{
                Element e=createElementFromEntity(document,s);
                root.appendChild(e);
            });
            Transformer transformer= TransformerFactory
                    .newInstance()
                    .newTransformer();
            transformer.transform(new DOMSource(document),new StreamResult(fileName));
        }catch (Exception ex){
            System.out.println(ex.getMessage());
        }
    }

    @Override
    public E save(E e) throws ValidatorException {
        E stuff=super.save(e);
        if(stuff==null){
            writeAll();
        }
        return stuff;
    }

    @Override
    public E delete(ID id) {
        E stuff=super.delete(id);
        if(stuff!=null)
            writeAll();
        return stuff;
    }

    @Override
    public E update(E entity) {
        E stuff=super.update(entity);
        if(stuff!=null)
            writeAll();
        return stuff;
    }
    @Override
    public  E findOne(ID id){
        return super.findOne(id);
    }

    public int getSize(){
        int x=0;
        for(E s:super.findAll()){
            x++;
        }
        return x;
    }
}
