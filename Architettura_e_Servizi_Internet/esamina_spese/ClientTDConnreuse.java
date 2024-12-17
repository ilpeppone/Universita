import java.io.*;
import java.net.*;
public class ClientTDConnreuse{
    public static void main(String[] args) {
        if(args.length!=2){
            System.err.println("Uso: java ClientTDConnreuse server porta\n");
            System.exit(1);
        }
        try{
            Socket socket = new Socket(args[0],Integer.parseInt(args[1]));
            BufferedReader netIn = new BufferedReader(new InputStreamReader(socket.getInputStream(),"UTF-8"));
            BufferedWriter netOut = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream(),"UTF-8"));
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

            while(true){
                System.out.println("Inserisci il mese\n");
                var mese = br.readLine();
                System.out.println("Inserisci categoria di spesa\n");
                var categoria = br.readLine();
                System.out.println("Inserisci il numero di spese più onerose da visualizzare\n");
                var numero_spese = br.readLine();

                netOut.write(mese+"\n");
                netOut.write(categoria+"\n");
                netOut.write(numero_spese+"\n");
                netOut.flush();

                String risposta;
                while((risposta = netIn.readLine())!=null){
                    if(risposta.equals("---END RESPONSE---"))
                        break;
                    System.out.println(risposta);
                }
            }
            // socket.close(); opzionale
        } catch(Exception e){
            e.printStackTrace();
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }
}