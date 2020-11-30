<?php
    include_once("E_Student.php");
    include_once("E_Database.php");
    class Model_Student{
        public $arrStudent =array();
        public $database ;    
        
        public function __construct()
        {
            $this->database = new Entity_Database();
        }
      
        public function setArrayStudent(){
            $sql = "select * from student ";
            $rs =$this->database->getResultFromDB($sql);
            // $rs = mysqli_query($this->database->link,$sql);
            while($row = mysqli_fetch_array($rs)){
                $stid = $row["id"];
                $name = $row["name"];
                $age = $row["age"];
                $university = $row["university"];
                $newStudent = new Entity_Student($stid,$name,$age,$university);
                array_push($this->arrStudent,$newStudent);
            }
        }
        public function getAllStudent(){
                return $this->arrStudent;
        }
        public function getStudentDetail($stid){
            // Gia su rang ta load du lieu tu CSDL
            
            // $allStudent = $this->getAllStudent();
            for( $i=0;$i<sizeof($this->arrStudent);$i++){
                if($this->arrStudent[$i]->id==$stid){
                    return $this->arrStudent[$i];
                }
            }
             
        }
    }
?>