import java.io.*;

public class Main{
    public static void main(String[] args) {
        System.out.println("Inserisci il valore di soglia minima (tra 0 e 200)\n");
        try{
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            int soglia_critica;
            do{
            soglia_critica = Integer.parseInt(br.readLine());
            } while(soglia_critica < 0 || soglia_critica>200);
        } catch (IOException e){
            System.err.println("Errore di input: "+e.getMessage());
        } catch (NumberFormatException e) {
            System.err.println("Per favore inserisci un numero intero valido.");
        }

    }
}