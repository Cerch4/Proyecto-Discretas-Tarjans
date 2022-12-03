/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package tarjan;

import java.util.ArrayList;

/**
 *
 * @author Cesar
 */
public class Entrenador {
    public String nombre;
    public int ncontactos;
    public ArrayList<String> contactos = new ArrayList();
    public boolean sociable;
    
    public Entrenador (){
        
        
    }
    
    public boolean estanConectados(String p){
        
        for (int i = 0; i< contactos.size() ; i++ ){
            if(!contactos.isEmpty() && contactos.get(i).equals(p)){
                return true;
            }
        }
        return false;
    }
    
    public void añadirContacto(String p){
        if(contactos.size() < ncontactos){
            contactos.add(p);
        }
    }
   
}
