package inquinamento;


import java.io.IOException;
import java.io.ObjectOutputStream;


import java.io.PipedOutputStream;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class GeneraRilevazioni extends Thread {
    private PipedOutputStream pos;
    private final AtomicBoolean isRunning=new AtomicBoolean(false);
    private final Random random = new Random();
    public GeneraRilevazioni(PipedOutputStream pos) {
        this.pos = pos;
    }

    public void run(){
        isRunning.set(true);
        ObjectOutputStream oos = null;  
            try{
                oos= new ObjectOutputStream(pos);
            } catch (IOException e){
                e.printStackTrace();
                System.exit(-1);
            }
            while(isRunning.get()){
                Rilevazione r = new Rilevazione(random.nextInt(200), System.currentTimeMillis());
                try{
                    oos.writeObject(r);
                    oos.flush();
                } catch (IOException e){
                    e.printStackTrace();
                }
                try{
                    Thread.sleep(300);
                } catch (InterruptedException e){
                    e.printStackTrace();
                }
            }
       }
    void terminaRilevazioni (){
        isRunning.set(false);
    }
}
