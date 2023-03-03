<?php        
  $style = "createacc.css";
  include 'init.php';
  include 'topNav.php'

  ?>
  <div class="container requestTxt">
    <h1>Create user's first account</h1>
  </div>

  <!-- Request form start here-->
  <div class="container requestform">
    <div  alt="add Account picture" class="addAccount"></div>
    <form>
      <div class="form-row">
        <div class="col-md-12">
          <input type="text" class="form-control formInpt" placeholder="First and last name">
        </div>
        <div class="col-md-12">
          <input type="text" class="form-control formInpt" placeholder="User's company's name">
        </div>
      </div>
      <div class="form-row">
        <div class="col-md-12">
          <input type="text" class="form-control formInpt" placeholder="Email">
        </div>
        <div class="col-md-12">
          <input type="text" class="form-control formInpt" placeholder="Phone">
        </div>
      </div>
      <div class="form-row">
        <div class="col-md-12">
          <input type="text" class="form-control formInpt" placeholder="City">
        </div>
        <div class=" col-md-12 ">
          <input type="text" class="form-control formInpt" placeholder="How many farms' installation do user need">
        </div>
      </div>
      <input class="btn btn-primary requestBTN" type="submit" value="Create">
    </form>
    </div>
  <!-- Request form end here-->
