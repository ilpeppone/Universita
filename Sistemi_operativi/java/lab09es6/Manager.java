package lab09es6;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PipedInputStream;


public class Manager extends Thread{
    
    PipedInputStream pis=null;
    Sorter sorter=null;
    Monitor monitor=null;

    public Manager(PipedInputStream pis, Sorter sorter, Monitor monitor) {
        this.pis = pis;
        this.sorter = sorter;
        this.monitor = monitor;
    }

    public void run(){
        int i=0;
        BufferedReader br = new BufferedReader(new InputStreamReader(pis));
        while(i<10){
            try{
                String line = br.readLine();
                System.out.println(line);
            }catch (IOException  e){
            }
            i++;
        }
        monitor.termina();
        sorter.termina();
    }
    
    


    
}
