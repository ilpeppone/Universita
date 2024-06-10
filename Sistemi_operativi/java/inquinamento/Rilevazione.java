package inquinamento;

import java.io.Serializable;

public class Rilevazione implements Serializable{
    private int valore = 0 ;
    private long timestamp= 0;
    

    public  Rilevazione(int valore, long timestamp){
        this.valore=valore;
        this.timestamp=timestamp;
    }

    public int getValore() {
        return valore;
    }
     
    public long getTimestamp() {
        return timestamp;
    }

    public void setValore(int valore) {
        this.valore = valore;
    }

    public void setTimestamp(long timestamp) {
        this.timestamp = timestamp;
    }

    
    
}
