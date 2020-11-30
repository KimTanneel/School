<?php
    include_once("../Model/M_Student.php");
    class Ctrl_Student{
        public function invoke(){
            $modelStudent = new Model_Student();
            $modelStudent->setArrayStudent();
            if(isset($_GET['stid'])){
                $student = $modelStudent->getStudentDetail($_GET['stid']);
                include_once('../View/StudentDetail.php');
            }
            else{
                $studentList = $modelStudent->getAllStudent();
                include_once('../View/StudentList.php');
            }
        }
        public function update(){   
            $modelStudent = new Model_Student();
            $modelStudent->setArrayStudent();
            // Nếu post --> update
            if($_SERVER['REQUEST_METHOD'] == 'POST'){
                
                $id =$_POST['id'];
                $name=$_POST['name'];
                $age =$_POST['age'];
                $university=$_POST['university'];
                $sql = "Update student set name='".$name."',age='".$age."',university='".$university."' where id = ".$id;
                // $sql =  $conn->prepare("UPDATE INTO MyGuests (firstname, lastname, email) VALUES (?, ?, ?)");
                $modelStudent->database->excuteSQL($sql);
                echo $sql;
                header("Location:http://localhost/MVC/Controller/C_Student.php?choice=2");
                            
            }
            else{
                if(isset($_GET['stid'])){
                    $student = $modelStudent->getStudentDetail($_GET['stid']);
                    include_once('../View/StudentUpdateDetail.php');
                }
                else{
                    $studentList = $modelStudent->getAllStudent();   
                    include_once('../View/StudentUpdate.php');
                }
            }
           
        }
        public function insert(){
            if($_SERVER['REQUEST_METHOD'] == 'POST'){
                $id =$_POST['id'];
                $name=$_POST['name'];
                $age =$_POST['age'];
                $university=$_POST['university'];

                $sql = "INSERT INTO student (id,name,age,university) values (NULL,'".$name."','".$age."','".$university."')";
                $modelStudent = new Model_Student();
                $modelStudent->database->excuteSQL($sql);
                $modelStudent->setArrayStudent();
                $studentList = $modelStudent->getAllStudent();   
                include_once('../View/StudentUpdate.php');
            }
            else
                include_once('../View/StudentInsert.php');
        }
        public function isSession(){
            session_start();
            if($_SESSION['admin']){

            }
        }
    }
        
    $C_Student = new Ctrl_Student();
    // $stid = $_REQUEST['stid'];
    $choice =$_REQUEST['choice'];
    switch($choice){
        case "1":    
            $C_Student->invoke();
        break;
        case "2":
            $C_Student->update();
        break;
        case "3":
            $C_Student->insert();
    }
?>