package lab07es2;

import java.io.PipedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
public class ToOutput implements Runnable{
    private Thread t = null;
    private PipedInputStream pis=null;

    ToOutput(PipedInputStream pis){
        this.pis=pis;
    }

    public void start(){
        Thread t = new Thread();
        t.start();
    }

    public void run(){
        System.out.println(Thread.currentThread() + " Hello, this is ToOutput");
        try{
            String line=null;
            BufferedReader br = new BufferedReader(new InputStreamReader(pis));
            while((line=br.readLine())!=null){
                System.out.println("ToOutput"+line);
            }
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}
