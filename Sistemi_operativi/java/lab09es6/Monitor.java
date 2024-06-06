package lab09es6;

import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

public class Monitor implements Runnable{
    private final AtomicBoolean flag= new AtomicBoolean(false);
    private final Random random = new Random();
    private int id;
    private double cpuLoad;
    ThreadLoad tl= new ThreadLoad();
    

    public Monitor(ThreadLoad tl) {
        this.tl = tl;
    }
    public void run(){
        while(!flag.get()){
            id= random.nextInt(50);
            cpuLoad=random.nextDouble() * (100);
            tl.setThreadLoad(id, cpuLoad);
            try{
                Thread.sleep(200);
            } catch (InterruptedException e){
                e.printStackTrace();
            }
        }
    }
    public void termina(){
        flag.set(true);
    }

}
