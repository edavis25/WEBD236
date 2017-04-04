<?php include_once 'include/util.inc' ?>

<!DOCTYPE html>
<html>
    <head>
        <link rel="stylesheet" href="/Aptana/lab2/lab3/css/style.css" />

        <title><?php echo( $title ); ?></title>
    </head>
    <body>
        <!-- Page wrapper -->
        <div id="content-wrapper">

            <!-- Navigation bar -->
            <div id="nav">
                <ul>

                    <?php if (isLoggedIn()) : ?>
                    <li><a href="/Aptana/lab2/lab3/logout">Logout</a></li>
                    <li><a href="/Aptana/lab2/lab3/user/view_user/<?php echo(safeParam($_SESSION, 'UserID', false)); ?>">My Profile</a></li>
                    <?php  else : ?>
                    <li><a href="/Aptana/lab2/lab3/login">Login</a></li>
                    <li><a href="/Aptana/lab2/lab3/user/register">Register</a></li>	
                    <?php  endif; ?>

                    <!-- Home link always present -->
                    <li><a href="/Aptana/lab2/lab3/index">Home</a></li>
                </ul>
            </div>

            <!-- User greeting -->
            <div id="greeting">
                <?php  if (isLoggedIn()) : ?>
                <?php echo( "Welcome, " . safeParam($_SESSION, 'FirstName', false) ." ". safeParam($_SESSION, 'LastName', false) ."!" ); ?>
                <?php  endif; ?>
            </div>


<h1><?php echo( $title ); ?></h1>

<div id="errors">
    <?php  if (isset($errors) && count($errors) > 0) : ?>
        <ul>
            <?php  foreach($errors as $error) : ?>
                <li><?php echo( $error ); ?></li>
            <?php  endforeach; ?>
        </ul>
    <?php  endif; ?>
</div>

<form action="/Aptana/lab2/lab3/questions/add_question" method="post">
    <label for="title">Title</label>
    <br />
    <input type="text" id="title" name="title" class="full-width" value= "<?php echo( isset($inputs['title']) ? $inputs['title'] : '' ); ?>" />
    <br />
    <label for="content-textarea">Content</label>
    <br />
    <textarea name="content" id="content-textarea" rows="15" class="full-width"><?php echo( isset($inputs['content']) ? $inputs['content'] : '' ); ?></textarea>
    <br />
    <label for="tags">Tags</label>
    <input type="text" id="tags" name="tags" class="full-width" value="<?php echo( isset($inputs['tags']) ? $inputs['tags'] : '' ); ?>" />
    <br />
    <br />
    <input type="submit" value="Post Question" id="submit-question" />
</form>
<br />
<a href="/Aptana/lab2/lab3/index">&lt;&lt; Back</a>

	
</div> <!-- End content wrapper -->
<footer>
    &copy; Eric Davis
</footer>

<!-- Javascript to toggle yes/no confirmation of delete -->
<script src="/Aptana/lab2/lab3/js/jquery-3.2.0.min.js"></script>



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