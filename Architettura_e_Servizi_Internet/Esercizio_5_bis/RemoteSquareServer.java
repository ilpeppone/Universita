import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class RemoteSquareServer {
    public static void main(String[] args) {
        if(args.length!=1){
            System.err.println("Uso: java RemoteSquareServer porta");
            
        }
        var porta = args[0];
        
        try(ServerSocket server = new ServerSocket(Integer.parseInt(porta))){
            
            while(true){
                try{
                Socket clientSocket = server.accept();
                var netIn = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                var netOut = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));
                String line;
                while((line=netIn.readLine())!=null){
                    if(line.equals("fine")){
                        System.out.println("Terminazione avvenuta con successo!");
                        System.exit(0);;
                    }
                    int numero = Integer.parseInt(line);
                    String quadrato =Integer.toString(numero * numero) ;
                    
                    netOut.write(quadrato);
                    netOut.newLine();
                    netOut.flush();
                }
                }catch(Exception e){
                    System.err.println("Errore socket client" + e.getMessage());
                    e.printStackTrace();
                }
            }
        }catch(Exception e){
            System.err.println("Errore Server"+e.getMessage());
            e.printStackTrace();
        } 
        
    }
}
