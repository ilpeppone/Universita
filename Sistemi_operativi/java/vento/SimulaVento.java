package vento;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PipedOutputStream;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class SimulaVento implements Runnable{
    private final AtomicBoolean running=new AtomicBoolean(false);
    private final Random random=new Random();
    private PipedOutputStream pos;

    

    public SimulaVento(PipedOutputStream pos){
        this.pos=pos;
    }

    public void run(){
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(pos));
        while(!running.get()){
            try {
                int valore=random.nextInt(101);
                bw.write(Integer.toString(valore));
                bw.newLine();
                bw.flush();
                Thread.sleep(1000);
            } catch (InterruptedException | IOException e) {
                e.printStackTrace();
            }
        }
        try {
            pos.close(); // Close the stream when done
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public void termina(){
        running.set(true);
    }


}
