package lab07es1;

public class Main{
    final static int N=4;
    public static void main(String[] args){
        Accumulatore acc =new Accumulatore(0.0);

        Thread ct[] = new Thread[N];

        for (int i=0; i<N; i++){
            ct[i]= new Thread(new CounterThread(acc));
            ct[i].start();
        }

        for (int i=0; i<N; i++){
            try{
            ct[i].join();
            } catch (InterruptedException e){
                e.printStackTrace();
            }
        }

        System.out.println("Thread Main Accumuatore vale " + acc.getValue());
    }
}