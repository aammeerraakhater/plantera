<?php        
  $style = "logIn.css";
  include 'init.php';
  ?>

<div class="container">
      <div class="containerimg">
      </div>
      <div class="formcontainer">
    <form action="" method="POST">
    <div class="form-group ">
    <label for="exampleInputEmail1">Email address</label>
    <input required type="email" name="email" class="form-control" id="exampleInputEmail1" aria-describedby="emailHelp">
    <small id="emailHelp" class="form-text text-muted">Enter your email address</small>
    </div>

    <div class="form-group ">
    <label for="exampleInputEmail1">Password</label>
    <input required type="password" name="password" class="form-control" id="exampleInputEmail1" >
    <small id="emailHelp" class="form-text text-muted">Enter your password </small>
  </div>

    <button class="btn btn-primary btn-block btn-submit">Login </button>   
 </form>

      </div>
</div>
<!--  -->