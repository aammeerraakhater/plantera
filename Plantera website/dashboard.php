<?php
  $style = "showaccs.css";
  $semanticstyle = "semantic.min.css";
  include 'init.php';
  require 'topNav.php';
 ?>
          
          
          
          



<div id="layoutSidenav_content">
    


        <main>
        <div class="container-fluid">
            <h1 class="mt-4">Plantera admin-page</h1>
            <ol class="breadcrumb mb-4">
                <li class="breadcrumb-item active">Dashboard</li>
            </ol>
            <div class="row">
                <div class="col-xl-3 col-md-6">
                    <div class="card bg-primary text-white mb-4">
                        <div class="card-body">Farmers' accounts</div>
                        <div class="card-footer d-flex align-items-center justify-content-between">
                            <a class="small text-white stretched-link" href="showaccs.php">View Details</a>

                            <div class="small text-white"><i class="far fa-hand-point-right"></i></div>
                        </div>
                    </div>
                </div>
                <div class="col-xl-3 col-md-6">
                    <div class="card bg-success text-white mb-4">
                        <div class="card-body">Contact-us History</div>
                        <div class="card-footer d-flex align-items-center justify-content-between">
                            <a class="small text-white stretched-link" href="showRequests.php">View Details</a> 
                            <div class="small text-white"><i class="far fa-hand-point-right"></i></div>
                        </div>
                    </div>
                </div>
            </div>
            <!--<div class="card mb-4">
                <div class="card-header">
                    <i class="fas fa-table mr-1"></i>
                        Plantera Members
                </div>
                 <div class="card-body">
                    <div class="table-responsive">
                        <table class="table text-center table-bordered" id="dataTable" width="100%" cellspacing="0">
                            <thead>
                                <tr>
                                    <th>ID</th>
                                    <th>Username</th>
                                    <th>Email</th>
                                    <th>Farms</th>
                                </tr>
                            </thead>
                            <tfoot>
                                <tr>
                                    <th>ID</th>
                                    <th>Username</th>
                                    <th>Email</th>
                                    <th>Farms</th>
                                </tr>
                            </tfoot>
                            <tbody>

                            </tbody>
                        </table>
                    </div>
                </div> -->
            </div>
        </div>
    </main>
