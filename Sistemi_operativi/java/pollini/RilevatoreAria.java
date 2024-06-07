package pollini;

import java.io.BufferedWriter;
import java.io.IOException;

import java.io.OutputStreamWriter;
import java.io.PipedOutputStream;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class RilevatoreAria extends Thread{
    private final Random random=new Random();
    private final AtomicBoolean isRunning=new AtomicBoolean(true);
    private int valore;
    private PipedOutputStream pos;

    

    public RilevatoreAria(PipedOutputStream pos) {
        this.pos = pos;
    }

    public void run(){
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(pos));
        while(isRunning.get()){
            try{
                valore=random.nextInt(110);
                int ts =(int) (System.currentTimeMillis()/1000);
                bw.write(String.valueOf(valore));
                bw.newLine();
                bw.write(String.valueOf(ts));
                bw.newLine();
                bw.flush();
            }catch(IOException e){
                e.printStackTrace();
            }
            try{
                Thread.sleep(100);
            }catch (InterruptedException e){
                e.printStackTrace();
            }
        }
    }

    public void fermaRilevatoreAria(){
        isRunning.set(false);
    }
}
