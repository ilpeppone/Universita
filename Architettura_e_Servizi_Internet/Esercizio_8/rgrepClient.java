import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

class rgrepClient{
    public static void main(String[] args) {
        if(args.length!=4){
            System.err.println("Uso: java rgrepClient hostname porta stringa nomefile\n");
            System.exit(-1);
        }
        var hostname = args[0];
        var porta = args[1];
        var stringa = args[2];
        var nome_file = args[3];

        try{
            var s = new Socket(hostname, Integer.parseInt(porta));
            
            var netIn = new BufferedReader(new InputStreamReader(s.getInputStream()));
            var netOut = new BufferedWriter(new OutputStreamWriter(s.getOutputStream()));
            
            netOut.write(stringa);
            netOut.newLine();
            netOut.write(nome_file);
            netOut.newLine();
            netOut.flush();
            
            String line;
            while((line=netIn.readLine())!=null){
                System.out.println(line);
            }
            s.close(); 
        } catch (Exception e) {
            System.err.println("Errore connessione al server" + e.getMessage());
        }
    }
}