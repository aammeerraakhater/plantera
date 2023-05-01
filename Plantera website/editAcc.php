<?php        
  $style = "createacc.css";
  session_start();

  include 'init.php';
  include 'topNav.php';
  include "config.php";
// fullname  companysName email phone cityURL noOfFarms
if (isset($_POST['editAccBTN']) || isset($_POST['editUserBTN'])) {
////////////////// Load data first time ////////////////////
if(isset($_POST['editAccBTN'])){
  $uid = $_POST['editaccKey'];
  try {
    $user = $auth->getUser($uid);
  } catch (\Kreait\Firebase\Exception\Auth\UserNotFound $e) {
      echo $e->getMessage();
      $_SESSION['accStatus'] = "Some error occured try again later";
      header("location:showacss.php");
  }
}
//////////////////////////////////////////////
if($_SERVER["REQUEST_METHOD"]=="POST" && isset($_POST['editUserBTN'])){
  $uid = $_POST['id'];
  $email = $_POST['email'];
  $phone = $_POST['phone'];
  $name = $_POST['fullname'];
  try {
    $userEmail = $auth->getUserByEmail($email);
    $userNumber = $auth->getUserByPhoneNumber($phone);
  } catch (\Kreait\Firebase\Exception\Auth\UserNotFound $e) {
    $e->getMessage();
  }
  if((isset($userEmail)&& $userEmail->uid !=$uid)||(isset($userNumber)&& $userNumber->uid)){
    $_SESSION['EditaccStatus'] = "Email or phone number already exist to other account";
    try {
      $user = $auth->getUser($uid);
    } catch (\Kreait\Firebase\Exception\Auth\UserNotFound $e) {
        echo $e->getMessage();
        $_SESSION['accStatus'] = "Some error occured try again later";
        header("location:showaccs.php");
    }}
  else{
    $properties = [
      'displayName' => $name,
      'email' => $email,
      'phoneNumber' => $phone,
  ];
    try {
      $updatedUser = $auth->updateUser($uid, $properties);
      $_SESSION['accStatus'] = "Updated successfully";
      header("location:showaccs.php"); 
  } catch (\Kreait\Firebase\Exception\Auth\UserNotFound $e) {
    $e->getMessage();
    }
  }
    
}


/////////////////////// Show toastr ///////////////////////////
if(isset($_SESSION['EditaccStatus'])){
  echo "
  <script>
  toastr.info('" . $_SESSION['EditaccStatus'] . "')
  </script>";
  unset($_SESSION['EditaccStatus']);
} 

?>
    

  <div class="container requestTxt">
    <h1>Edit and update user's account</h1>
  </div>
  <!-- Request form start here-->
  <!-- fullname  companysName email phone cityURL noOfFarms-->
  <div class="container requestform">
    <div  alt="add Account picture" class="addAccount"></div>
    <form action="editAcc.php" method="POST">
      <div class="form-row">
      <input  type="hidden"  name="id" value="<?=$user->uid;?>" class="form-control formInpt">

        <div class="col-md-12">
          <input required type="text"  name="fullname" value="<?=$user->displayName;?>" class="form-control formInpt" placeholder="First and last name">
        </div>
      </div>
      <div class="form-row">
        <div class="col-md-12">
          <input required type="text" name="email" value="<?=$user->email;?>" class="form-control formInpt" placeholder="Email">
        </div>
        <div class="col-md-12">
          <input required type="tel" name="phone" value="<?=$user->phoneNumber;?>" class="form-control formInpt" placeholder="Phone">
        </div>
      </div>
      <input class="btn btn-primary requestBTN" name='editUserBTN' type="submit" value="Update">
    </form>
    </div>
  <?php
} else {
  $_SESSION['accStatus'] = "Please select a user";
  header("location:showacss.php");
}

?>