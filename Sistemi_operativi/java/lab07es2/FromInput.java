package lab07es2;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.PipedOutputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class FromInput implements Runnable{
    private Thread t = null;
    private PipedOutputStream pos= null;
    
    FromInput (PipedOutputStream pos){
        this.pos=pos;
    }

    public void start(){
        t=new Thread(this);
        t.start();
    }

    public void run(){
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line=null;
        try{
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(pos));
            System.out.println("FromInput - Inserire uno o piu' messaggi:");
            while((line=br.readLine())!=null ){
                
                bw.write(line);
                bw.newLine();
                bw.flush();
            }
            
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}