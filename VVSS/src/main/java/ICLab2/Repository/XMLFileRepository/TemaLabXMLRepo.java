package ICLab2.Repository.XMLFileRepository;

import ICLab2.Domain.TemaLab;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import ICLab2.Validator.TemaLabValidator;


public class TemaLabXMLRepo extends AbstractXMLRepo<Integer, TemaLab> {
    //private String fileName;

    public TemaLabXMLRepo(TemaLabValidator v, String fileName) {
        super(v,fileName);
    }

    @Override
    protected Element createElementFromEntity(Document document,TemaLab t) {
        Element root = document.getDocumentElement();
        Element e = document.createElement("tema");
        e.appendChild(createElement("id", document, t.getId().toString()));
        e.appendChild(createElement("descriere", document, t.getDescriere()));
        e.appendChild(createElement("saptamanaLimita", document, Integer.toString(t.getTermenLimita())));
        e.appendChild(createElement("saptamanaPredarii", document, Integer.toString(t.getSaptammanaPredarii())));
        return e;
    }


    @Override
    protected TemaLab createEntityFromElement(Element temaLabElement){
        String nr=temaLabElement.getAttribute("nr");
        String descr=temaLabElement
                .getElementsByTagName("descriere")
                .item(0)
                .getTextContent();
        String sptLim=temaLabElement
                .getElementsByTagName("saptamanaLimita")
                .item(0)
                .getTextContent();
        String sptPrd=temaLabElement
                .getElementsByTagName("saptamanaPredarii")
                .item(0)
                .getTextContent();

        return new TemaLab(Integer.parseInt(nr),descr,Integer.parseInt(sptLim),Integer.parseInt(sptPrd));
    }

}