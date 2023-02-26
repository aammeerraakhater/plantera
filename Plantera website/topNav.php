<body class="sb-nav-fixed">
<nav class="sb-topnav navbar navbar-expand navbar-dark bg-dark">
            <a class="navbar-brand" href="index.html"><i class="fas fa-clinic-medical mr-3"></i> IEEE-BUB SB </a>
            <button class="btn btn-link btn-sm order-1 order-lg-0" id="sidebarToggle" href="#"><i class="fas fa-bars"></i></button>
            <!-- Navbar Search-->
            <form class="d-none d-md-inline-block form-inline ml-auto mr-0 mr-md-3 my-2 my-md-0">
            </form>
            <!-- Navbar-->
            <ul class="navbar-nav ml-auto ml-md-0">
                <li class="nav-item dropdown">
                    <a class="nav-link dropdown-toggle" id="userDropdown" href="#" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"><i class="fas fa-user fa-fw"></i></a>
                    <div class="dropdown-menu dropdown-menu-right" aria-labelledby="userDropdown">
                        <a class="dropdown-item" href="admin_dash.php">Dashboard</a>
                        <button type="button" style="border:unset;background-color: unset;padding-left: 1.5rem;padding-top:5px;" data-toggle="modal" data-target="#exampleModal">
                        Activity Log
                        </button>
                        <div class="dropdown-divider"></div>
                        <a class="dropdown-item" href="logout.php">Logout</a>
                    </div>
                </li>
            </ul>
        </nav>


        
<!-- Modal -->
<div class="modal fade" id="exampleModal" tabindex="-1" aria-labelledby="exampleModalLabel" aria-hidden="true">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <h5 class="modal-title" id="exampleModalLabel">Online Now</h5>
        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
      <div class="modal-body">


<?php $admin = select_Admins(); 
    foreach($admin as $online_admins){
        if($online_admins['state'] == 1){?>
                                        <a style="color: #000 !important;font-size: 18px;font-weight: 500;" class="nav-link">
    <div style="display: inline-block;" class="sb-nav-link-icon"><span style="color:green">●</span></div>
    <?php echo $online_admins['name']; ?>
</a>
        <?php }else{?>
          <a style="color: #888 !important;font-size: 18px;font-weight: 500;" class="nav-link">
            <div style="display: inline-block;" class="sb-nav-link-icon"><span style="color:red">●</span></div>
            <?php echo $online_admins['name']; ?>
</a>

        <?php }
    }
?>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-secondary" data-dismiss="modal">Close</button>
      </div>
    </div>
  </div>
</div>