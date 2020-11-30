<?php
    class Entity_Database{
        public $link ;
        public $db_selected ; 
        // public $sql;
        // public $rs;
        public function __construct()
        {
            $this->link  = mysqli_connect ('localhost','root') or die('Could not connect');
            $this->db_selected = mysqli_select_db($this->link,'DULIEU3');
        }
        public function getResultFromDB($sql){
            // print $this->link;
            // print "hello";
            return  mysqli_query($this->link,$sql);
        }
        public function excuteSQL($sql){
             mysqli_query($this->link,$sql);

        }
        // $link = mysqli_connect ('localhost','root') or die('Could not connect');
        //     $db_selected = mysqli_select_db($link,'DULIEU3');
        //     $sql = "select * from student ";
        //     $rs = mysqli_query($link,$sql);  
    }
?>