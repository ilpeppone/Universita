import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class speseClient{
    public static void main(String[] args) {
        if(args.length!=2){
            System.err.println("Uso: speseClient server porta");
            System.exit(-1);
        }

        var hostname = args[0];
        var porta = args[1];

        try{
            Socket client = new Socket(hostname,Integer.parseInt(porta));
            System.out.println("Connessione avvenuta con successo!");
            var netIn = new BufferedReader(new InputStreamReader(client.getInputStream()));
            var netOut = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()));
            while(true){
                
                BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
                System.out.println("Inserire il mese in formato AAAAMM");
                netOut.write(br.readLine());
                netOut.newLine();
                
                System.out.println("Inserisci la categoria di spesa");

                System.out.println("Inserisci il numero N di spese di interesse");
                netOut.write(br.readLine());
                netOut.newLine();
                netOut.flush();

            }
        }catch(Exception e){
            e.printStackTrace();
            System.err.println(e.getMessage());
            System.out.println("Errore connessione client-server");
        }
    }
}