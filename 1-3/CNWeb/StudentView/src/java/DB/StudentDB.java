/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package DB;

import Model.Student;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author macbookpro
 */
public class StudentDB {
    public static List<Student> listStu = getAll();
    
    public static List<Student> getAll() {
         if (listStu == null) {
            listStu = new ArrayList<>();
            listStu.add(new Student("1","Duong Van Chinh" , "yua2307@gmail.com","1" ));
            listStu.add(new Student("2","Phan Thi Nhu Quynh", "quynhnauz@gmail.com","2"));
             listStu.add(new Student("3","Duong Van Trung", "trung@gmail.com","5"));
        }   
        return listStu;
    }
   public static Student getStudentByID(String id,List<Student> listStu)
   {
       for( Student stu : listStu)
       {
           if(stu.getId().equals(id))
           {
               return stu;
           }
       }
       return null;
   }
   public static void xoa(Student stu)
   {
       listStu.remove(stu);
   }
}
