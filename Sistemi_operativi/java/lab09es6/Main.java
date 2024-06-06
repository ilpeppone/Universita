package lab09es6;

import java.io.IOException;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;

public class Main {
    public static void main(String[] args){
        ThreadLoad tl= new ThreadLoad();
        Monitor monitor = new Monitor(tl);
        Thread tmonitor = new Thread(monitor);

        PipedInputStream pis=new PipedInputStream();
        try{
            PipedOutputStream pos =new PipedOutputStream(pis);

            Sorter sorter = new Sorter(tl, pos);
            Thread tsorter = new Thread(sorter);

            Manager manager= new Manager(pis, sorter, monitor);
            Thread tmanager = new Thread(manager);

            tmonitor.start();
            tsorter.start();
            tmanager.start();
        } catch (IOException e){
            e.printStackTrace();
            System.out.println("Errore pipe");
            System.exit(-1);
        }
        
    }
}
