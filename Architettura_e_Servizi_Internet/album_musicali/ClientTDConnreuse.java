package album_musicali;
import java.io.*;
import java.net.*;

public class ClientTDConnreuse {
    public static void main(String[] args) {
        if(args.length!=2){
            System.err.println("Usage: java ClientTDConnreuse hostname porta\n");
            System.exit(1);
        }
        try{
            Socket socket = new Socket(args[0],Integer.parseInt(args[1]));
            BufferedReader netIn = new BufferedReader(new InputStreamReader(socket.getInputStream(),"UTF-8"));
            BufferedWriter netOut = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream(),"UTF-8"));
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

            while(true){
                System.out.println("Inserisci username: ('fine' per terminare)\n");
                var username = br.readLine();
                if(username.equals("fine")){
                    break;
                }
                System.out.println("Inserisci password:\n");
                var password = br.readLine();
                
                System.out.println("Inserisci nome e cognome artista\n");
                var artista = br.readLine();

                netOut.write(username+"\n");
                netOut.write(password+"\n");
                netOut.write(artista+"\n");
                netOut.flush();

                String risposta;
                while((risposta = netIn.readLine())!=null){
                    if(risposta.equals("---END RESPONSE---")){
                        break;
                    }
                    System.out.println(risposta);
                }
            }
        } catch (Exception e){
            e.printStackTrace();
            System.err.println(e.getMessage());
            System.exit(0);
        }
    }
}
