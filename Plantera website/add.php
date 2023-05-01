<?php
  include "config.php";
  session_start();
  // fullname  companysName email phone cityURL noOfFarms
  
  if($_SERVER["REQUEST_METHOD"]=="POST" && isset($_POST['createUserAccBtn'])){
    $email =  $_POST["email"];
    $fullname = $_POST["fullname"];
    $phone = '+20'.$_POST["phone"];
    try {
        $userEmail = $auth->getUserByEmail($email);
        $userPhone = $auth->getUserByPhoneNumber($phone);
    } catch (\Kreait\Firebase\Exception\Auth\UserNotFound $e) {
        $e->getMessage();
    }    if(isset($userEmail) || isset($userPhone)){
        $_SESSION['accStatus'] = 'Email or phone already exists';
        header("location:showaccs.php"); 
    }
    else{
        $userProperties = [
              'email' => $email,
              'emailVerified' => false,
              'phoneNumber' => $phone,
              'password' => 'secretPassword',
              'displayName' => $fullname,
          ];
          $createdUser = $auth->createUser($userProperties);
        if($createdUser){
            $uid = $createdUser->uid;
            $farmDes = $_POST['farmDes'];
            $noOfFarms = 1;
            $soilType = $_POST['soilType'];
            // =>
            $farmsData = [
                'farm1'=>[
                    "PredictedOutput"=> ["value"=> 0],
                    "SoilType"=> "black",
                    "airhumidity_realtime"=>[ "RT"=> 52], 
                    "battery"=>["value"=> 10],
                    "meanSoilMoisture"=> 77,
                    "mean_air_humidity" => 65,
                    "mean_h"=>["value"=> 49],
                    "mean_max_temp"=> 56,
                    "mean_min_temp"=>87,
                    "ph_realtime"=>[ "RT"=> 0],
                    "phc"=>[ "value"=> 14],
                    "php"=>[ "value"=> 35],
                    "pht"=>["value"=> 30],
                    "plant"=> 0,
                    "soilc"=> ["value"=> 50],
                    "soilmoisture_realtime"=>["RT"=> 86.12],
                    "soilp"=>["value"=>30],
                    "soilt"=>["value"=> 50] ,
                    "temperature_realtime"=>["RT"=> 27.1],
                    "value"=> 10,
                    "weather"=>["rainy"=> 0],],
            ];
            $ref_table = "user/".$uid;
            $postRef = $database->getReference($ref_table)->set($farmsData);
        }
        else{
            $_SESSION['accStatus'] = "Data is not inserted";
            header("location:createAcc.php");
        }
        if($postRef && $createdUser){
            $_SESSION['accStatus'] = "Data inserted successfully";
            header("location:showaccs.php");
        }
        else if($createdUser && !$postRef){
            try {
                $auth->deleteUser($uid);
            }catch (\Kreait\Firebase\Exception\Auth\UserNotFound $e) {
                $e->getMessage();
                $_SESSION['accStatus'] = "Data not inserted but user created try and delete user";
                header("location:showaccs.php");

            } catch (\Kreait\Firebase\Exception\AuthException $e) {
                $_SESSION['accStatus'] = "Data not inserted ";
                header("location:showaccs.php");
            }
        }
    
  //first if end
    }
 }
 //////////////////////////////////adding user done //////////////////////////////////////////////
 /////////////////////////////////                  /////////////////////////////////////////////
 ////////////////////////////////adding farm to usr//////////////////////////////////////////////
 

 if($_SERVER["REQUEST_METHOD"]=="POST" && isset( $_POST['addFarm'])){

    $id = $_POST['id'];
    $farmDes = $_POST['farmDes'];
    $soilType = $_POST['soiltype'];
    $ref_table = "user/".$id;
    $noOfFarms = ($database->getReference($ref_table)->getSnapshot()->numChildren())+1;

    $farmData = [
      'farm'.$noOfFarms=>[
        "PredictedOutput"=> ["value"=> 0],
        "SoilType"=> $soilType,
        "airhumidity_realtime"=>[ "RT"=> 52], 
        "battery"=>["value"=> 10],
        "meanSoilMoisture"=> 77,
        "mean_air_humidity" => 65,
        "mean_h"=>["value"=> 49],
        "mean_max_temp"=> 56,
        "mean_min_temp"=>87,
        "ph_realtime"=>[ "RT"=> 0],
        "phc"=>[ "value"=> 14],
        "php"=>[ "value"=> 35],
        "pht"=>["value"=> 30],
        "plant"=> 0,
        "soilc"=> ["value"=> 50],
        "soilmoisture_realtime"=>["RT"=> 86.12],
        "soilp"=>["value"=>30],
        "soilt"=>["value"=> 50] ,
        "temperature_realtime"=>["RT"=> 27.1],
        "value"=> 10,
        "weather"=>["rainy"=> 0],
        'farmDes' => $farmDes,
    ],
    ];
  $updatequery = $database->getReference($ref_table)->update($farmData);
  if($updatequery){
    $_SESSION['accStatus'] = "Farm is added successfully";
    header("location:showaccs.php");
    }else{
        $_SESSION['accStatus'] = "Farm is not added";
        header("location:showaccs.php");
    }
 }
?>


  