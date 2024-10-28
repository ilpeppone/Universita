import java.io.*;

import java.net.Socket;

class RemoteSquareClient{
    public static void main(String[] args) {
        if(args.length!=2){
            System.err.println("Errore! La sintassi corretta è");
            System.err.println("\tjava RemoteSquareClient hostname porta");
            System.exit(1);
        }
        
        var hostname = args[0];
        var port = args[1];
        
        BufferedReader br;
        String numero;
        while(true){
        try{
            System.out.println("Inserisci un numero intero\n");
            br= new BufferedReader(new InputStreamReader(System.in));
            numero = br.readLine();
            if(numero.equals("fine")){
                break;
            }
            
            var s = new Socket(hostname, Integer.parseInt(port));
            var netIn = new BufferedReader(new InputStreamReader(s.getInputStream(), "UTF-8"));
            var netOut = new BufferedWriter(new OutputStreamWriter(s.getOutputStream(),"UTF-8"));
    
                
                netOut.write(numero);
                netOut.newLine();
                netOut.flush(); // non necessario; performance optimization
                System.out.println(netIn.readLine());
    
            s.close();
        } catch (IOException e){
            System.err.println(e.getMessage());
            e.printStackTrace(System.err);
            System.exit(1);
        }
    }
        

    }
}