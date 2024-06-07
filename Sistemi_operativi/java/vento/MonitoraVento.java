package vento;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PipedInputStream;
import java.util.concurrent.atomic.AtomicBoolean;

public class MonitoraVento implements Runnable{
    protected final AtomicBoolean running = new AtomicBoolean(false);
    protected PipedInputStream pis;
    

    public MonitoraVento(PipedInputStream pis) {
        this.pis = pis;
    }

    public void run(){
        BufferedReader br = new BufferedReader(new InputStreamReader(pis));
        while(!running.get()){
            try{
                String line=br.readLine();
                while(line!=null){
                    int valore = Integer.parseInt(line);
                    String message = Message(valore);
                    System.out.println("Valore: " + valore + " " + message);
                    line=br.readLine();
                }
            } catch (IOException  e){
                e.printStackTrace();
            }
        }
    }

    public String Message(Integer valore){
        if (valore <10)
            return "vento leggero";
        else if (valore<30)
            return "vento moderato";
         else if (valore<50)
            return "vento forte";
        return "vento impetuoso";
    }

    public void termina(){
        try {
            pis.close(); // Close the stream when done
        } catch (IOException e) {
            e.printStackTrace();
        }
        running.set(true);
    }
}
