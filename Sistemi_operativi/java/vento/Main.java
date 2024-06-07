package vento;

import java.io.IOException;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;

public class Main {
    public static void main(String[] args){
        PipedInputStream pis = new PipedInputStream();
        try{
            PipedOutputStream pos = new PipedOutputStream(pis);
            SimulaVento simulavento=new SimulaVento(pos);
            MonitoraVento monitoravento=new MonitoraVento(pis);
            Thread tsimulavento= new Thread(simulavento);
            Thread tmonitoravento=new Thread(monitoravento);
            tsimulavento.start();
            tmonitoravento.start();
            Thread.sleep(45000);
            simulavento.termina();
            monitoravento.termina();
            tsimulavento.join();
            tmonitoravento.join();
        } catch (IOException | InterruptedException e){
            e.printStackTrace();
            System.out.println("Errore pipe");
            System.exit(-1);
        }
    }
}
