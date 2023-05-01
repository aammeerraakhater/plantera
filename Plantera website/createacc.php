<?php        
  $style = "createacc.css";
  session_start();

  include 'init.php';
  include 'topNav.php';
?>    

  <div class="container requestTxt">
    <h1>Create user's first account</h1>
  </div>
  <div class="container requestform">

  <?php
    if(isset($_SESSION['accStatus'])){
      echo "
      <script>
      toastr.info('" . $_SESSION['accStatus'] . "')
      </script>";
      unset($_SESSION['accStatus']);
   } 
    ?>
  <!-- Request form start here-->
  <!-- fullname  companysName email phone cityURL noOfFarms-->
    <div  alt="add Account picture" class="addAccount"></div>
    <form action="add.php" method="POST">
      <div class="form-row">
        <div class="col-md-12">
          <input required type="text" name="fullname" class="form-control formInpt" placeholder="First and last name">
        </div>
      </div>
      <div class="form-row">
        <div class="col-md-12">
          <input required type="text" name="email" class="form-control formInpt" placeholder="Email">
        </div>
        <div class="col-md-12">
          <input required type="text" name="phone" class="form-control formInpt" placeholder="Phone">
        </div>
      </div>
      <div class="form-row">
      <div class=" col-md-12 ">
          <input required type="text" name="farmDes" class="form-control formInpt" placeholder="Farm's destenation">
        </div>
        <div class=" col-md-12 ">
          <input type="text" name="soilType" class="form-control formInpt" placeholder="Soil type">
        </div>
      </div>
      <input name="createUserAccBtn" class="btn btn-primary requestBTN" type="submit" value="Create">
    </form>
    </div>
  <!-- Request form end here-->
