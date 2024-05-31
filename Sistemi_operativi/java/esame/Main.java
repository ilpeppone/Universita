package esame;
class Main{
    public static void main(String[] args){
        Consumi consumi = new Consumi();
        SimulaConsumi simulaConsumi = new SimulaConsumi(consumi);
        Thread threadSimulaConsumi = new Thread(simulaConsumi);
        threadSimulaConsumi.start();

        int count = 0;
        float precedente = 0.0F;
        float attuale = 0.0F;
        while(true){
            try{
                Thread.sleep(900);
            } catch(InterruptedException e){
                e.setStackTrace(null);
            }

            attuale = consumi.getConsumo();
            System.out.println("Consumo rilevato - "+attuale);
            if (attuale>precedente){
                if((attuale-precedente)>(precedente * 30)/100){
                    System.out.println("Warning: superato il valore precedente di più del 30% ("+precedente+")");
                }
            }
            if(attuale>20){
                count ++;
            }else {
                count =0;
            }
            if (count == 3){
                System.out.println("Rilevati 3 valori consecutivi > 20, terminazione SimulazioneConsumi");
                simulaConsumi.terminaSimulazioneConsumi();
                break;
            }
            precedente=attuale;
        }
        System.out.println("Attendo la terminazione di SimulaConsumi");
        try{
            threadSimulaConsumi.join();
        } catch (InterruptedException e){
            e.printStackTrace();
        }
        System.out.println("Terminazione SimulaConsumi,Terminazione Main");
    }   
}