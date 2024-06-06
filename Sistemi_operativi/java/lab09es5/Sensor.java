package lab09es5;

import java.io.*;
import java.util.*;
public class Sensor extends Thread{
    private PipedOutputStream pos;

    public Sensor(PipedOutputStream pos) {
        this.pos = pos;
    }

    public void run(){
        final Random random = new Random();
        DataOutputStream dos = new DataOutputStream(pos);

        while(true){
            try{
                float temperature = 18 + random.nextFloat() * (21 - 18);
                try{
                    dos.writeFloat(temperature);
                    dos.flush();
                } catch (IOException e){
                    e.printStackTrace();
                }
                Thread.sleep(300);
            } catch (InterruptedException ie){
                
            }
        }
    }
    
   
}   
