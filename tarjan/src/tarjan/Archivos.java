/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package tarjan;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import static java.lang.Integer.parseInt;
import java.util.ArrayList;

/**
 *
 * @author Cesar
 */
public class Archivos {
    public Region miRegion;
    public ArrayList<String> misDatos;
    
    public Archivos(){
        misDatos = new ArrayList();
    }
    
    
    public void Leer() throws FileNotFoundException, IOException{
        ArrayList<String> datos = new ArrayList();
       String fileName = "src\\tarjan\\box.txt\\";
        File file = new File(fileName);
        FileReader fr = new FileReader(file);
        BufferedReader br = new BufferedReader(fr);
        String line;
        while((line = br.readLine()) != null){
        datos.add(line);     
        }
        misDatos = datos ;
        String aux2 = misDatos.get(0); 
        //System.out.println(aux2.charAt(0));
    }
    
    public void wea(){
        
        for(int i = 0; i< misDatos.size(); i = i+1){
            System.out.println(""+misDatos.get(i));
        }
        
    }
    
    public void llenarRegion(){
        miRegion = new Region(Character.getNumericValue(misDatos.get(0).charAt(0)));
        
        for(int i = 0; i < miRegion.nEntrenadores; i = i+1){
            Entrenador aux = new Entrenador();
            String aux2 = new String();
            int big = 0;
            for(int m = 0; m < misDatos.get(i+1).length(); m = m+1){
                if(misDatos.get(i+1).charAt(m) != ' '){
                    aux2 = aux2 + misDatos.get(i+1).charAt(m); 
                }
                else {
                   aux.ncontactos = Character.getNumericValue(misDatos.get(i+1).charAt(m+1));
                   big = m + 3;
                   break; 
                }               
            }
            aux.nombre = aux2;
            aux2 = new String();
            for(int v = 0; v < aux.ncontactos; v = v+1){
                for(int q = big ; q< misDatos.get(i+1).length(); q = q+1){
                 if(misDatos.get(i+1).charAt(q) != ' '){
                     aux2 = aux2 + misDatos.get(i+1).charAt(q); 
                 }
                 else {
                   aux.añadirContacto(aux2);
                   aux2 = "";
                   big = q + 1;
                   break; 
                } 
             }
            }
            if( misDatos.get(i+1).length()- big ==3 ){
                aux.sociable = false;
            }
            
            else if( misDatos.get(i+1).length()- big == 2 ){
                aux.sociable = true;
            }
            
            miRegion.addEntrenadores(aux);
            
       
        }
        
    
    }
    
}
