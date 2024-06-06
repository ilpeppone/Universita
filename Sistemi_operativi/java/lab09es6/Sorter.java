package lab09es6;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PipedOutputStream;
import java.util.concurrent.atomic.AtomicBoolean;

public class Sorter implements Runnable{
    private final AtomicBoolean flag = new AtomicBoolean(false);
    private ThreadLoad tl= null;
    private PipedOutputStream pos=null;

    
    public Sorter(ThreadLoad tl, PipedOutputStream pos) {
        this.tl = tl;
        this.pos = pos;
    }

    public void run(){
        flag.set(true);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(pos));
        while(flag.get()){
            try{
                Integer ti = tl.getMaximumThreadId();
                if (ti==null)
                    continue;
                Double cpuLoad = tl.getCpuLoad(ti);
                if (cpuLoad==null)
                    continue;
                
                String result= "Thread: " + ti + ", con cpuLoad: " + cpuLoad;
                bw.write(result);
                bw.newLine();
                bw.flush();

                Thread.sleep(150);
            } catch (IOException | InterruptedException e){}

        }
    }
    public void termina(){
        
        flag.set(false);
    }
}
