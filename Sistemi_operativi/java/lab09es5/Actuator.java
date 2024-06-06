package lab09es5;

import java.io.*;

public class Actuator extends Thread {
    private PipedInputStream pis;
    private float desiredTemperature;
    public Actuator(PipedInputStream pis,float temperature) {
        this.pis = pis;
        this.desiredTemperature = temperature;
    }
    
    public void run (){
        final DataInputStream dis = new DataInputStream(pis);

        try{
            while(true){
            float temperature=dis.readFloat();
            if (temperature < desiredTemperature){
                System.out.println("Accendere il riscaldamento\n");
            } }
        } catch (IOException e){
            System.err.println("Errore lettura dal Sensor");
            e.printStackTrace();
        }

    }
}
