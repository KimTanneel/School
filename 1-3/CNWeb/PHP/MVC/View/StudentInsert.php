
    <h2>Thêm thông tin Sinh Viên</h2>
    <?php
        include("../header.php");
        
         echo " 
         <form  action='C_Student.php?choice=3' method='post'>
               
                        <div class='form-group'>
                            <label>Mã Sinh viên</label>
                            <input class='form-control' readonly name='id' value='' ></input>
                        </div>
                            
                        <div class='form-group'>
                            <label>Họ tên</label>
                            <input class='form-control'  type ='text' value ='' name = 'name'>
                        </div>
                        <div class='form-group'>
                            <label>Tuổi</label>
                            <input class='form-control'  type ='text' value =''name='age'>
                        </div>
                        <div class='form-group'>
                            <label>Đại học</label>
                            <input class='form-control'  type ='text' value ='' name ='university'>
                        </div>
            
                        <button type='submit' class='btn btn-primary'>Thêm Sinh Viên</button>
         </form>
         ";  
    ?>  
    </br>
    <p><a href="http://localhost/MVC/index/index.php">Home Page</a></p>
</body>
</html>