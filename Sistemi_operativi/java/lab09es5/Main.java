package lab09es5;

import java.io.*;

public class Main {
    public static void main(String[] args){
        float temperature=0.0F;
        System.out.println("Inserisci il valore soglia desiderato:\n");
        InputStreamReader isr=new InputStreamReader(System.in);
        BufferedReader stdin = new BufferedReader (isr);
        String strTemperature = "";
        try{
            strTemperature = stdin.readLine();
        } catch (IOException e){
            System.err.println("Errore nella lettura della temperatura\n");
            System.exit(-1);
        }
        try{
            temperature=Float.parseFloat(strTemperature);
        } catch (NumberFormatException e){
            System.err.println("Errore nella conversione a float\n");
            System.exit(-1);
        }
        PipedInputStream pis=new PipedInputStream();
        PipedOutputStream pos = null;

        try{
            pos=new PipedOutputStream(pis);
        } catch (IOException e){
            System.err.println("Impossibile creare PipeOutputStream\n");
            System.exit(-1);
        }

        Actuator actuator = new Actuator(pis, temperature);
        Sensor sensor = new Sensor(pos);
        
        actuator.start();
        sensor.start();
    }
}
