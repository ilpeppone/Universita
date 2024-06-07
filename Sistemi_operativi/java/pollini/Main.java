package pollini;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;

public class Main {

    public static void main(String[] args){
        int i =0;
        PipedOutputStream pos = new PipedOutputStream();
        int cronometro=0;
        int newTime=0,oldTime=0;
        try{
            PipedInputStream pis = new PipedInputStream(pos);
            BufferedReader br = new BufferedReader(new InputStreamReader(pis));
            RilevatoreAria ra = new RilevatoreAria(pos);
            ra.start();
            while(i<8){
                String line=br.readLine();
                int valore= Integer.parseInt(line);
                line=br.readLine();
                int ts = Integer.parseInt(line);
                
                System.out.println(valore + " " + Qualità(valore) + ", " + ts);
                newTime = ts;
                cronometro=newTime-oldTime;
                if(cronometro<15 && cronometro!=0){
                    System.out.println("Attenzione");
                }
                oldTime = newTime;
                i++;
            }
            br.close();
            ra.fermaRilevatoreAria();

            try{
                ra.join();
            } catch (InterruptedException e){
                e.printStackTrace();
            }

        } catch (IOException e){
            e.printStackTrace();
        }
        
        
    }

    public static String Qualità(int valore){
        if (valore<20)
            return "Basso";
        else if (valore<76)
            return "Medio";
        return "Alto";
    }
}
