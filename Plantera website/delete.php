<?php
session_start();
include ('config.php');

if(isset($_POST['deleteACC'])){
    $uid = $_POST['deleteACC'];
    try {
        $auth->deleteUser($uid);
        $ref_table = "user/".$uid;
        $deleteData = $database->getReference($ref_table)->remove();
        if($deleteData){
            $_SESSION['accStatus']="Data is deleted successfully";
        }
        else{
            $_SESSION['accStatus']="Some error might happen";
        }
        header("location:showaccs.php");
    }catch (\Kreait\Firebase\Exception\Auth\UserNotFound $e) {
        $_SESSION['accStatus']="User not found";
        header("location:showaccs.php");
    } catch (\Kreait\Firebase\Exception\AuthException $e) {
        $_SESSION['accStatus']="Data is not deleted";
        header("location:showaccs.php");
    }
}

if(isset($_POST['deleteRequestID'])){
    $RequestID = $_POST['deleteRequestID'];
    $ref_table = "request/".$RequestID;
    $deleteData = $database->getReference($ref_table)->remove();

    if($deleteData){
        $_SESSION['requestStatus']="Request is deleted successfully";
        header("location:showRequests.php");

    }else{
        $_SESSION['requestStatus']="Request is not deleted";
        header("location:showRequests.php");

    }
} 