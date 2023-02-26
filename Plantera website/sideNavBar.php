<div id="layoutSidenav_nav">
                <nav class="sb-sidenav accordion sb-sidenav-dark" id="sidenavAccordion">
                    <div class="sb-sidenav-menu">
                        <div class="nav">
                            <div class="sb-sidenav-menu-heading">Core</div>
                            <a class="nav-link" href="<?php echo "admin_dash.php";?>">
                                <div class="sb-nav-link-icon"><i class="fas fa-tachometer-alt"></i></div>
                                Dashboard
                            </a>
                            <div class="sb-sidenav-menu-heading">Departments</div>
                            
                            <?php if(isset($_SESSION['role']) && $_SESSION['role'] == 0){?>
                            <a class="nav-link collapsed" href="#" data-toggle="collapse" data-target="#collapseLayouts9" aria-expanded="false" aria-controls="collapseLayouts9">
                                <div class="sb-nav-link-icon"><i class="fal fa-user-crown"></i></div>
                                Admins
                                <div class="sb-sidenav-collapse-arrow"><i class="fas fa-angle-down"></i></div>
                            </a>
                            <div class="collapse" id="collapseLayouts9" aria-labelledby="headingOne" data-parent="#sidenavAccordion">
                                <nav class="sb-sidenav-menu-nested nav">
                                    <a class="nav-link" href="<?php echo "add_admin.php";?>">Add Admin</a>
                                    <a class="nav-link" href="<?php echo "all_admins.php";?>">Edit / Delete Admin</a>
                                </nav>
                            </div>
                            <?php } ?>

                            <?php if(isset($_SESSION['role']) && $_SESSION['role'] == 0){?>
                            <a class="nav-link collapsed" href="#" data-toggle="collapse" data-target="#collapseLayouts5" aria-expanded="false" aria-controls="collapseLayouts5">
                                <div class="sb-nav-link-icon"><i class="fal fa-users-crown"></i></div>
                                Board
                                <div class="sb-sidenav-collapse-arrow"><i class="fas fa-angle-down"></i></div>
                            </a>
                            <div class="collapse" id="collapseLayouts5" aria-labelledby="headingOne" data-parent="#sidenavAccordion">
                                <nav class="sb-sidenav-menu-nested nav">
                                    <a class="nav-link" href="<?php echo "add_board_member.php";?>">Add Board</a>
                                    <a class="nav-link" href="<?php echo "all_board.php";?>">Edit / Delete Board</a>
                                </nav>
                            </div>
                            <?php } ?>


                            <a class="nav-link collapsed" href="#" data-toggle="collapse" data-target="#collapseLayouts" aria-expanded="false" aria-controls="collapseLayouts">
                                <div class="sb-nav-link-icon"><i class="far fa-calendar-star"></i></div>
                                Events
                                <div class="sb-sidenav-collapse-arrow"><i class="fas fa-angle-down"></i></div>
                            </a>
                            <div class="collapse" id="collapseLayouts" aria-labelledby="headingOne" data-parent="#sidenavAccordion">
                                <nav class="sb-sidenav-menu-nested nav">
                                    <a class="nav-link" href="<?php echo "add_events.php";?>">Add Event</a>
                                    <a class="nav-link" href="<?php echo "all_events.php";?>">Edit / Delete Event</a>
                                </nav>
                            </div>

                            <a class="nav-link collapsed" href="#" data-toggle="collapse" data-target="#collapsePages" aria-expanded="false" aria-controls="collapsePages">
                                <div class="sb-nav-link-icon"><i class="fal fa-clipboard-user"></i></div>
                                Members
                                <div class="sb-sidenav-collapse-arrow"><i class="fas fa-angle-down"></i></div>
                            </a>
                            <div class="collapse" id="collapsePages" aria-labelledby="headingTwo" data-parent="#sidenavAccordion">
                            <nav class="sb-sidenav-menu-nested nav">
                                    <a class="nav-link" href="<?php echo "add_member.php";?>">Add Member</a>
                                    <a class="nav-link" href="<?php echo "all_members.php";?>">Edit / Delete Member</a>
                                </nav>
                            </div>

                            <a class="nav-link collapsed" href="#" data-toggle="collapse" data-target="#collapseLayouts_meeting" aria-expanded="false" aria-controls="collapseLayouts_meeting">
                                <div class="sb-nav-link-icon"><i class="fal fa-user-crown"></i></div>
                                Meetings
                                <div class="sb-sidenav-collapse-arrow"><i class="fas fa-angle-down"></i></div>
                            </a>
                            <div class="collapse" id="collapseLayouts_meeting" aria-labelledby="headingOne" data-parent="#sidenavAccordion">
                                <nav class="sb-sidenav-menu-nested nav">
                                    <a class="nav-link" href="<?php echo "add_meeting_info.php";?>">Add Meeting</a>
                                    <a class="nav-link" href="<?php echo "all_meeting_info.php";?>">Edit / Delete Meeting</a>
                                </nav>
                            </div>

                            <a class="nav-link collapsed" href="#" data-toggle="collapse" data-target="#collapseLayouts_blogs" aria-expanded="false" aria-controls="collapseLayouts_blogs">
                                <div class="sb-nav-link-icon"><i class="fal fa-user-crown"></i></div>
                                Blogs
                                <div class="sb-sidenav-collapse-arrow"><i class="fas fa-angle-down"></i></div>
                            </a>
                            <div class="collapse" id="collapseLayouts_blogs" aria-labelledby="headingOne" data-parent="#sidenavAccordion">
                                <nav class="sb-sidenav-menu-nested nav">
                                    <a class="nav-link" href="<?php echo "add_blog.php";?>">Add Blog</a>
                                    <a class="nav-link" href="<?php echo "all_blogs.php";?>">Edit / Delete Blogs</a>
                                </nav>
                            </div>

                            <div class="sb-sidenav-menu-heading">Other Departments</div>
                            <a class="nav-link" href="<?php echo "commiteies.php";?>">
                                <div class="sb-nav-link-icon"><i class="fas fa-chart-area"></i></div>
                                All Committes
                            </a>
                            <a class="nav-link" href="all_messages.php">
                                <div class="sb-nav-link-icon"><i class="fal fa-envelope-open-text"></i></div>
                                All Messages
                            </a>
                            <?php if(isset($_SESSION['role']) && $_SESSION['role'] == 0){?>
                            <a class="nav-link" href="all_registration.php">
                                <div class="sb-nav-link-icon"><i class="fal fa-envelope-open-text"></i></div>
                                All Registration
                            </a>
                            <?php } ?>
                            <?php if(isset($_SESSION['role']) && $_SESSION['role'] == 0){?>
                            <a class="nav-link" href="all_members_ids.php">
                                <div class="sb-nav-link-icon"><i class="fal fa-envelope-open-text"></i></div>
                                All Members IDS
                            </a>
                            <?php } ?>
                            <?php if(isset($_SESSION['role']) && $_SESSION['role'] == 0){?>
                            <a class="nav-link" href="all_winterEvent.php">
                                <div class="sb-nav-link-icon"><i class="fal fa-envelope-open-text"></i></div>
                                All Winter Event Attendee
                            </a>
                            <?php } ?>
                            <div style="letter-spacing: 1.5px;" class="sb-sidenav-menu-heading">Online Now</div>

                            <?php $admin = select_Admins(); 
                                foreach($admin as $online_admins){
                                    if($online_admins['state'] == 1){?>
                                                                    <a style="color: #fff !important;" class="nav-link">
                                <div class="sb-nav-link-icon"><span style="color:green">●</span></div>
                                <?php echo $online_admins['name']; ?>
                            </a>
                                    <?php }else{?>
                                      <a style="color: #888 !important;" class="nav-link">
                                        <div class="sb-nav-link-icon"><span style="color:red">●</span></div>
                                        <?php echo $online_admins['name']; ?>
                            </a>

                                    <?php }
                                }
                            ?>
                            
                        </div>
                    </div>
                    <div class="sb-sidenav-footer">
                        <div class="small">You Logged in as:  

                        <?php 
                            if(@$_SESSION['role'] == 0){
                                echo "<td>". "Height Board" ."</td>";
                            }elseif($_SESSION['role'] == 1){
                                echo "<td>". "Head" ."</td>";
                            }elseif($_SESSION['role'] == 2){
                                echo "<td>". "Vice" ."</td>";
                            }
                        ?>

                        </div>
                        IEEE فوووووووق
                    </div>
                </nav>
            </div>