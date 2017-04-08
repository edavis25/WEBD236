<?php include_once 'include/util.inc' ?>

<!DOCTYPE html>
<html>
    <head>
        <link rel="stylesheet" href="/lab/lab3/css/style.css" />

        <title><?php echo( $title ); ?></title>
    </head>
    <body>
        <!-- Page wrapper -->
        <div id="content-wrapper">

            <!-- Navigation bar -->
            <div id="nav">
                <ul>

                    <?php if (isLoggedIn()) : ?>
                    <li><a href="/lab/lab3/logout">Logout</a></li>
                        <?php  if (Authenticator::instance() -> can('admin_page')) : ?>
                        <li><a href="/lab/lab3/admin">Administrator</a></li>
                        <?php  endif; ?>
                    <li><a href="/lab/lab3/user/view_user/<?php echo(safeParam($_SESSION, 'UserID', false)); ?>">My Profile</a></li>
                    <?php  else : ?>
                    <li><a href="/lab/lab3/login">Login</a></li>
                    <li><a href="/lab/lab3/user/register">Register</a></li>	
                    <?php  endif; ?>

                    <!-- Home link always present -->
                    <li><a href="/lab/lab3/index">Home</a></li>
                </ul>
            </div>

            <!-- User greeting -->
            <div id="greeting">
                <?php  if (isLoggedIn()) : ?>
                <?php echo( "Welcome, " . safeParam($_SESSION, 'FirstName', false) ." ". safeParam($_SESSION, 'LastName', false) ."!" ); ?>
                <?php  endif; ?>
            </div>

<h1><?php echo($title); ?></h1>

<table class="users-table">
<?php  foreach ($users as $user) : ?>
    <tr>
        <td><a href="/lab/lab3/user/view_user/<?php echo($user->getId()); ?>">View</a></td>
        <td><a href="/lab/lab3/user/user_groups/<?php echo($user->getId()); ?>">Groups</td>
        <td>
            <div class="delete-wrapper">
                <a href="##" class="delete-button"> Delete</a>&nbsp;
                <div class="confirm-delete" style="display: none;">
                    <a href="/lab/lab3/user/delete_user/<?php echo($user->getId()); ?>">yes</a> / <a href="##" class="delete-button">no</a>
                </div>
            </div>
        <td><?php echo(User::getFullName($user->getId())); ?></td>
    </tr>
<?php  endforeach; ?>
</table>

<br />
<a href="/lab/lab3/admin">&lt;&lt; Back</a>
	
</div> <!-- End content wrapper -->
<footer>
    &copy; Eric Davis
</footer>

<!-- Javascript to toggle yes/no confirmation of delete -->
<script src="/lab/lab3/js/jquery-3.2.0.min.js"></script>



<script type="text/javascript">
    
      function toggle(element) {
        if (element) {
           var display = element.style.display;
           if (display == "none") {
               element.style.display = "inline-block";
           }
           else {
               element.style.display = "none";
           }
       }
    }
   
     $('.delete-button').on('click', function() {
        var parent = $(this).closest('div[class^="delete-wrapper"]');
        
        var div = parent.children();
        toggle(div[1]);
    });
    
 
    
  

</script>
</body>
</html>
