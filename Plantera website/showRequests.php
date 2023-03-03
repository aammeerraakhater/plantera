<?php
    $page_name = "Get All Requests";
    $style = "showRequests.css";
    $semanticstyle = "semantic.min.css";
    require_once "init.php";
    require 'topNav.php';
    ?>
      <div class="container-fluid ">
        <div class="allContent">
    <div class="container mb-3">
        <img style="display: block;margin: auto;margin-top:10px;margin-bottom:20px; width:15%" class="add_admin" src="imgs/img_377947.png" alt="add_admin">
        <h3 class="text-center mt-2 mb-3">Welcome To Website Dashboard .</h3>
        <p class="text-center">From This Page You Can Show All Requests</p>

        <?php// $allData = getAllData("contact_us");?>
<div class="row mt-5">
        <?php //foreach ($allData as $all_messages){ ?>
<div class="col-md-6">
            <div class="ui cards mb-3 text-center">
                <div class="card">
                    <div class="content">
                    <img style="margin: 20px 0;width:20%" src="imgs/user.png" alt="sender">
                    <div class="header pb-3">
                        <?php echo //$all_messages["name"];
                        "Amira";?>
                    </div>
                    <div class="meta">
                    <?php echo //$all_messages["time"];
                    "10:10:11";?>
                    </div>
                    <div class="meta">
                    <?php //echo $all_messages["msgfrom"];
                    "Hey how r u ?"?>
                    </div>
                    <div class="meta">
                    <?php //echo $all_messages["subject"];
                    "Hey how r u ?"?>
                    </div>
                    <div class="description pb-3">
                    <?php //echo $all_messages["msg"];
                    "Hey how r u ?"?>
                    </div>
                    </div>
                    <div class="extra content">
                    <div class="ui two buttons">
                       <a class="ui basic brown button" style="text-decoration: none !important;" href="delete.php?from=messages&id=<?php echo $all_messages["id"]?>&table=messages"> Show </a>
                    </div>
                    </div>
                    </div>
                </div>
        </div>
        <?php //}?>
        </div>

            <?php //if (count_users("id","contact_us") == 0){?>
                <p style="margin-top: 100px;font-weight: 700;font-size: 30px;" class="text-danger text-center">* There is No Message To Show *</p>
            <?php// } ?>

      </div>
    </div>
</div>
    <?php 
// }else{
//         header("location:signin.php");
//     }
//}else{
  //  header("Location:LogIn.php");
//}
//ob_end_flush();