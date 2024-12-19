package dati_sensori;
import java.io.*;
import java.net.*;

public class ClientTDConnreuse {
    public static void main(String[] args) {
        if(args.length!=2){
            System.err.println("Uso: java ClientTDConnreuse hostname porta\n");
            System.exit(1);
        }
        try{
            Socket socket = new Socket(args[0],Integer.parseInt(args[1]));
            BufferedReader netIn = new BufferedReader(new InputStreamReader(socket.getInputStream(),"UTF-8"));
            BufferedWriter netOut = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream(),"UTF-8"));
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

            while(true){
                System.out.println("Inserisci data YYYYMMDD('fine' per terminare)");
                var data = br.readLine();

                if(data.equals("fine")){
                    break;
                }
                System.out.println("Inserisci il sensore('fine' per terminare)");
                var sensore = br.readLine();

                if(sensore.equals("fine")){
                    break;
                }
                System.out.println("Inserisci stanza('fine' per terminare)");
                var stanza = br.readLine();

                if(stanza.equals("fine")){
                    break;
                }

                netOut.write(data +"\n");
                netOut.write(sensore +"\n");
                netOut.write(stanza +"\n");
                netOut.flush();

                String risposta;
                while((risposta = netIn.readLine())!=null){
                    if(risposta.equals("---END RESPONSE---")){
                        break;
                    }
                    System.out.println(risposta);
                }
            }
        } catch(Exception e){
            e.printStackTrace();
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }
}
