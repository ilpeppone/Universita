import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class RemoteSquareClient {

    public static void main(String[] args) {
        if(args.length!=2){
            System.err.println("Uso: java RemoteSquareCliente hostname porta");
            System.exit(-1);
        }

        var hostname = args[0];
        var porta = args[1];

        BufferedReader br;
        String line;
        try{
            Socket s = new Socket(hostname,Integer.parseInt(porta));
            var netIn = new BufferedReader(new InputStreamReader(s.getInputStream()));
            var netOut = new BufferedWriter(new OutputStreamWriter(s.getOutputStream()));
            while(true){
                System.out.println("Inserisci il numero di cui vuoi calcolarne il quadrato");
                try{
                    br = new BufferedReader(new InputStreamReader(System.in));
                    line = br.readLine();
                    netOut.write(line);
                    netOut.newLine();
                    netOut.flush();
                    if(line.equals("fine")){
                        System.out.println("Terminazione avvenuta con successo!");
                        break;
                    }
                    

                    System.out.println(netIn.readLine());
                }catch (Exception e){
                    e.printStackTrace();
                }
                
            }
            s.close();
        }catch(IOException e){
            e.printStackTrace();
        }
    }
}